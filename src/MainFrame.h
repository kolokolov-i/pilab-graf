#pragma once

#include <gtkmm.h>

class MainFrame : public Gtk::Window
{
    public:
    MainFrame();
    virtual ~MainFrame();

protected:
    void btn_open_clicked();
    void btn_process_clicked();
    void btn_save_clicked();
    void btn_show_clicked(Glib::ustring tag);

    void buildPorts();

    Gtk::Box rootBox, boxToolOpen, boxToolProcess, boxPorts;
    Gtk::Button btnOpen, btnShowSrc, btnProcess, btnSave;
    Gtk::Label lblOpen1, lblOpen2;
    Gtk::Separator sepOpen;
};