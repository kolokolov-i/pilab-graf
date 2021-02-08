#pragma once

#include "PortRecord.h"
#include "ImagePort.h"

#include <gtkmm.h>

#include <vector>
#include <iostream>

class LabScheme1
{
public:
    LabScheme1();
    ~LabScheme1();
    bool loadImage(std::string filePath);
    Glib::RefPtr<Gdk::Pixbuf> getPixbuf(std::string tag);
    ImagePort getImagePort(int index);
    ImagePort getImagePortSrc();

    std::vector<PortRecord> ports;
    void process();

private:
    Glib::RefPtr<Gdk::Pixbuf> source;
    std::vector<Glib::RefPtr<Gdk::Pixbuf>> images;
    std::string filePath;
};