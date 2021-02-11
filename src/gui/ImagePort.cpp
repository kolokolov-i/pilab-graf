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

void ImagePort::save(std::string path)
{
    std::string name = fileName;
    int k = name.find_last_of("/\\");
    name = name.substr(k + 1);
    k = name.find_last_of(".");
    std::string ext = name.substr(k + 1);
    name = name.substr(0, k);
    name.append(".");
    name.append(tag);
    name.append(".");
    name.append(ext);
    std::string saveName(path);
    saveName.append("\\");
    saveName.append(name);
    pixbuf->save(saveName, "jpeg");
}