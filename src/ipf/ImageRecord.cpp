#include "ImageRecord.h"

using namespace IPF;

ImageRecord::ImageRecord(std::string tag, std::string description)
{
    empty = true;
    matrix = std::shared_ptr<MatrixD>();
    pixbuf = Glib::RefPtr<Gdk::Pixbuf>();
    this->tag = tag;
    this->description = description;
}

void ImageRecord::setMatrix(MatrixD *m)
{
    matrix.reset(m);
    pixbuf = PixbufUtil::grayPixbuf(m);
    empty = false;
}

void ImageRecord::setMatrix(MatrixD *m, double min, double max)
{
    matrix.reset(m);
    pixbuf = PixbufUtil::grayPixbuf(m, min, max);
    empty = false;
}