#pragma once

#include "MatrixD.h"
#include "PixbufUtil.h"

#include <gtkmm.h>

#include <memory>

namespace IPF
{
    struct ImageRecord
    {
        ImageRecord(std::string tag, std::string description);

        bool empty;
        std::shared_ptr<MatrixD> matrix;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        std::string tag;
        std::string description;
        void (*processMatrix)(MatrixD matrix);

        void setMatrix(MatrixD *m);
    };
} // namespace IPF