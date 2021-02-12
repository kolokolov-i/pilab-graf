#include "LabScheme1.h"

#include <cmath>

using namespace IPF;

LabScheme1::LabScheme1()
    : sourceRecord("src", "Source")
{
    imageTable.push_back(ImageRecord("gray", "Grayscale;"));

    imageTable.push_back(ImageRecord("gaus_b=zero", "Gauss: s=5, border=zero;"));
    imageTable.push_back(ImageRecord("gaus_b=replic", "Gauss: s=5, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_b=reflec", "Gauss: s=5, border=reflect;"));
    imageTable.push_back(ImageRecord("gaus_b=wrap", "Gauss: s=5, border=wrap;"));

    imageTable.push_back(ImageRecord("gaus_s=3", "Gauss: s=3, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_s=4", "Gauss: s=4, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_s=5", "Gauss: s=5, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_s=3+4", "Gauss: s=3+4, border=replicate;"));

    imageTable.push_back(ImageRecord("deriv_x", "Derivatives: axis = X;"));
    imageTable.push_back(ImageRecord("deriv_y", "Derivatives: axis = Y;"));
    imageTable.push_back(ImageRecord("deriv_xy", "Derivatives: axis = XY;"));

    imageTable.push_back(ImageRecord("gaus_sep=x", "Gauss: s=5, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_sep=y", "Gauss: s=5, border=replicate;"));
    imageTable.push_back(ImageRecord("gaus_sep=x+y", "Gauss: s=5, border=replicate;"));
    updatePorts();
}

LabScheme1::~LabScheme1()
{
}

void LabScheme1::process()
{
    if (sourceRecord.pixbuf)
    {
        int i = 0;
        MatrixD *mGray = PixbufUtil::grayMatrix(sourceRecord.pixbuf);
        imageTable[i++].setMatrix(mGray);

        // different border types
        MatrixD *mKGaus5 = MatrixUtil::kernelGaussQ(5.0);
        mGray->borderResolver = MatrixD::Zero;
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus5));
        mGray->borderResolver = MatrixD::Replicate;
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus5));
        mGray->borderResolver = MatrixD::Reflect;
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus5));
        mGray->borderResolver = MatrixD::Wrap;
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus5));
        mGray->borderResolver = MatrixD::Replicate;

        // Gaussian filter
        MatrixD *mKGaus3 = MatrixUtil::kernelGaussQ(3.0);
        // MatrixUtil::print(std::cout, mKGaus3);
        MatrixD *mKGaus4 = MatrixUtil::kernelGaussQ(4.0);
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus3));
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus4));
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mKGaus5));
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(
            MatrixUtil::filterConvolute(mGray, mKGaus3), mKGaus4));

        // Sobel
        double tableX[] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
        MatrixD *mKSobelX = new MatrixD(3, 3, tableX);
        double tableY[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
        MatrixD *mKSobelY = new MatrixD(3, 3, tableY);
        MatrixD *mDerivX = MatrixUtil::filterConvolute(mGray, mKSobelX);
        MatrixD *mDerivY = MatrixUtil::filterConvolute(mGray, mKSobelY);
        imageTable[i++].setMatrix(mDerivX, -1, +1);
        imageTable[i++].setMatrix(mDerivY, -1, +1);
        imageTable[i++].setMatrix(MatrixUtil::calc(mDerivX, mDerivY, hypot), 0, 2);

        // separable Gaussian
        MatrixD *mGausX = MatrixUtil::kernelGaussV(5, 15, 0);
        // MatrixUtil::print(std::cout, mGausX);
        MatrixD *mGausY = MatrixUtil::kernelGaussV(5, 0, 15);
        // MatrixUtil::print(std::cout, mGausY);
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mGausX));
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(mGray, mGausY));
        imageTable[i++].setMatrix(MatrixUtil::filterConvolute(
            MatrixUtil::filterConvolute(mGray, mGausX), mGausY));
    }
    else
    {
        for (auto it = imageTable.begin(); it != imageTable.end(); ++it)
        {
            it->empty = true;
        }
    }
    updatePorts();
}

void LabScheme1::loadImage(std::string filePath)
{
    this->filePath = filePath;
    try
    {
        sourceRecord.pixbuf = Gdk::Pixbuf::create_from_file(filePath);
        this->filePath = filePath;
        sourceRecord.empty = false;
    }
    catch (const Gio::ResourceError &ex)
    {
        throw IPF::Image_File_Error("Resource Error");
    }
    catch (const Gdk::PixbufError &ex)
    {
        throw IPF::Image_File_Error("Pixbuf Error");
    }
}

void LabScheme1::updatePorts()
{
    ports.resize(0);
    for (auto its = imageTable.begin(); its != imageTable.end(); ++its)
    {
        ports.push_back(ImagePort::fromRecord(*its, filePath));
    }
}

ImagePort LabScheme1::getSourcePort()
{
    return ImagePort::fromRecord(sourceRecord, filePath);
}