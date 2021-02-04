#pragma once

#include <gtkmm.h>

class MainFrame : public Gtk::Window
{
    public:
    MainFrame();
    virtual ~MainFrame();

protected:
    void btn_open_clicked();
    void btn_show_clicked(Glib::ustring tag);

    void buildPorts();

    Gtk::Box rootBox, toolBoxOpen, toolBoxPorts;
    Gtk::Button btnOpen;
    Gtk::Label lblOpen1, lblOpen2;
};