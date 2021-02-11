#pragma once

#include "ViewFrame.h"
#include "../lab/LabScheme1.h" // TODO reduce coupling

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
    void btn_show_clicked();
    void cellrenderer_on_toogle(const Glib::ustring &path);


    Gtk::Box rootBox, boxToolOpen, boxToolProcess, boxPorts;
    Gtk::Button btnOpen, btnShowSrc, btnProcess, btnSave;
    Gtk::Label lblOpen1, lblOpen2;
    Gtk::Separator sepOpen;

    class PortsColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        PortsColumns()
        {
            add(col_btn);
            add(col_descript);
            add(col_tag);
        }

        Gtk::TreeModelColumn<gboolean> col_btn;
        Gtk::TreeModelColumn<Glib::ustring> col_descript;
        Gtk::TreeModelColumn<Glib::ustring> col_tag;
    };

    PortsColumns portsColumns;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView lstPorts;
    Glib::RefPtr<Gtk::ListStore> refTreeModel;

    ViewFrame viewSource, viewPort;
    std::string fileName;

    LabScheme1 scheme;

private:
    void buildGUI();
    void buildPorts();
    void resetSource();
    void resetPorts();
};