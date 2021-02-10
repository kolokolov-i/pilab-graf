#pragma once

#include <gtkmm.h>

struct ImagePort
{
public:
    Glib::RefPtr<Gdk::Pixbuf> image;
    Glib::ustring tag;
    Glib::ustring description;
    Glib::ustring fileName;
};