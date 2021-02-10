#pragma once

#include "MatrixD.h"

#include <gtkmm.h>

namespace IPF
{
    class PixbufUtil
    {
    public:
        static MatrixD *grayMatrix(Glib::RefPtr<Gdk::Pixbuf> px);
        static Glib::RefPtr<Gdk::Pixbuf> grayPixbuf(MatrixD *matrix, double min = 0, double max = 1);
    };
}