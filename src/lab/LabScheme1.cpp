#include "LabScheme1.h"

using namespace IPF;

LabScheme1::LabScheme1()
    : sourceRecord("src", "Source")
{
    imageTable.push_back(ImageRecord("gray", "Grayscale;"));
    imageTable.push_back(ImageRecord("gaus_s=5_b=zero", "Gauss: s=5 border=zero;"));
    updatePorts();
}

LabScheme1::~LabScheme1()
{
}

void LabScheme1::process()
{
    if (sourceRecord.pixbuf)
    {
        MatrixD *mGray = PixbufUtil::grayMatrix(sourceRecord.pixbuf);
        imageTable[0].setMatrix(mGray);

        MatrixD *kernel5 = MatrixUtil::kernelGauss(5.0, 12);
        imageTable[1].setMatrix(MatrixUtil::filterConvolute(mGray, kernel5));
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

// ImagePort LabScheme1::getImagePort(int index)
// {
//     ImagePort result;
//     PortRecord port = ports[index];
//     result.image = resultsPixbuf[index];
//     result.fileName = filePath;
//     result.description = port.description;
//     result.tag = port.tag;
//     return result;
// }

ImagePort LabScheme1::getSourcePort()
{
    return ImagePort::fromRecord(sourceRecord, filePath);
}