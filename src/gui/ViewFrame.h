#pragma once

#include "ImagePort.h"

#include <gtkmm.h>

class ViewFrame : public Gtk::Window
{
public:
    ViewFrame();
    virtual ~ViewFrame();

    void reset();
    void showPort(ImagePort port);

    void btn_save_clicked();

protected:
    Gtk::Box rootBox, boxTool;
    Gtk::Button btnSave;
    Gtk::Label lblDescription;
    Gtk::Image imagePanel;
};