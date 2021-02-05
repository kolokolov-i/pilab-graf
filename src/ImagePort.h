#pragma once

#include <gtkmm.h>

class ImagePort
{
public:
    // ImagePort()

    Glib::RefPtr<Gdk::Pixbuf> image;
    Glib::ustring tag;
    Glib::ustring description;
    Glib::ustring fileName;
};