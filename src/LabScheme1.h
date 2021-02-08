#pragma once

#include "PortRecord.h"
#include "ImagePort.h"
#include "ipf/IPF.h"
#include "ipf/MatrixD.h"

#include <gtkmm.h>

#include <vector>

class LabScheme1
{
public:
    LabScheme1();
    ~LabScheme1();
    void loadImage(std::string filePath);
    Glib::RefPtr<Gdk::Pixbuf> getPixbuf(std::string tag);
    ImagePort getImagePort(int index);
    ImagePort getImagePortSrc();

    std::vector<PortRecord> ports;
    void process();

private:
    Glib::RefPtr<Gdk::Pixbuf> source;
    std::vector<IPF::MatrixD> resultsImage;
    std::vector<Glib::RefPtr<Gdk::Pixbuf>> resultsPixbuf;
    std::string filePath;
};