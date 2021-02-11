#include "ImagePort.h"

ImagePort ImagePort::fromRecord(IPF::ImageRecord rec, std::string filePath)
{
    ImagePort result;
    result.pixbuf = rec.pixbuf;
    result.fileName = filePath;
    result.description = rec.description;
    result.tag = rec.tag;
    result.empty = rec.empty;
    return result;
}