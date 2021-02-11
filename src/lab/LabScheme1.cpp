#include "LabScheme1.h"

using namespace IPF;

LabScheme1::LabScheme1()
{
    sourceRecord.tag = "src";
    sourceRecord.description = "Source";
    sourceRecord.empty = true;

    imageTable.push_back(ImageRecord{true, std::shared_ptr<MatrixD>(), Glib::RefPtr<Gdk::Pixbuf>(), "gray", "Grayscale"});
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
        imageTable[0].matrix.reset(mGray);
        imageTable[0].pixbuf = PixbufUtil::grayPixbuf(mGray);
        imageTable[0].empty = false;
    }
    else
    {
        imageTable[0].empty = true;
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