#pragma once

#include "gtkmm.h"

struct PortRecord
{
    PortRecord(Glib::ustring tag, Glib::ustring descript);
    Glib::ustring tag;
    Glib::ustring description;
};