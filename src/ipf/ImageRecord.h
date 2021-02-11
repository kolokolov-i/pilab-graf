#pragma once

#include "MatrixD.h"

#include <gtkmm.h>

#include <memory>

namespace IPF
{
    struct ImageRecord
    {
        bool empty;
        std::shared_ptr<IPF::MatrixD> matrix;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        std::string tag;
        std::string description;
        void (*processingFunction)(IPF::MatrixD matrix);
    };
} // namespace IPF