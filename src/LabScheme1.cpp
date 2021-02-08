#include "LabScheme1.h"

void LabScheme1::process()
{

}

LabScheme1::LabScheme1()
{
    ports.push_back(PortRecord("gray", "Grayscale"));
}

LabScheme1::~LabScheme1()
{
}

bool LabScheme1::loadImage(std::string filePath)
{
    this->filePath = filePath;
    try
    {
        this->source = Gdk::Pixbuf::create_from_file(filePath);
        return true;
    }
    catch (const Gio::ResourceError &ex)
    {
        return false;
    }
    catch (const Gdk::PixbufError &ex)
    {
        return false;
    }
}

ImagePort LabScheme1::getImagePort(int index)
{
    std::cout << "> getImagePort" << std::endl;
    ImagePort result;
    PortRecord port = ports[index];
    std::cout << "! getImagePort" << std::endl;
    result.image = images[index];
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