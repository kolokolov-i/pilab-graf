#pragma once

#include "../ipf/MatrixD.h"
#include "../ipf/ImageRecord.h"

#include <gtkmm.h>

#include <memory>

struct ImagePort
{
public:
    bool empty;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    Glib::ustring tag;
    Glib::ustring description;
    Glib::ustring fileName;

    static ImagePort fromRecord(IPF::ImageRecord rec, std::string filePath);
};