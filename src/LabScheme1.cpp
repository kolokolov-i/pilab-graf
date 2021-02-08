#include "LabScheme1.h"

LabScheme1::LabScheme1()
{
    ports.push_back(PortRecord("gray", "Grayscale"));
}

LabScheme1::~LabScheme1()
{
}

void LabScheme1::process()
{

}

void LabScheme1::loadImage(std::string filePath)
{
    this->filePath = filePath;
    try
    {
        this->source = Gdk::Pixbuf::create_from_file(filePath);
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

ImagePort LabScheme1::getImagePort(int index)
{
    ImagePort result;
    PortRecord port = ports[index];
    result.image = resultsPixbuf[index];
    result.fileName = filePath;
    result.description = port.description;
    result.tag = port.tag;
    return result;
}

ImagePort LabScheme1::getImagePortSrc()
{
    ImagePort result;
    result.image = this->source;
    result.fileName = filePath;
    result.description = "Source";
    result.tag = "src";
    return result;
}