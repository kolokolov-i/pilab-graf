#include "MainFrame.h"

#include <string>

// TODO viewframe pool
// TODO multithread processing

MainFrame::MainFrame()
    : rootBox(Gtk::ORIENTATION_VERTICAL),
      boxToolOpen(Gtk::ORIENTATION_HORIZONTAL),
      boxToolProcess(Gtk::ORIENTATION_HORIZONTAL),
      boxPorts(Gtk::ORIENTATION_VERTICAL),
      btnOpen("Open"),
      btnShowSrc("Show Source"),
      btnProcess("Process"),
      btnSave("Save All"),
      lblOpen1("Select source file:"),
      lblOpen2("None")
{
    buildGUI();
}

void MainFrame::buildGUI()
{
    set_title("Graf Lab1");
    set_border_width(5);
    set_default_size(300, 400);
    add(rootBox);

    lblOpen2.set_justify(Gtk::JUSTIFY_LEFT);
    boxToolOpen.set_border_width(5);
    boxToolOpen.pack_start(lblOpen1, Gtk::PACK_SHRINK);
    boxToolOpen.pack_start(btnOpen, Gtk::PACK_SHRINK, 5);
    boxToolOpen.pack_start(lblOpen2, Gtk::PACK_SHRINK);

    boxToolProcess.pack_end(btnSave, Gtk::PACK_SHRINK);
    boxToolProcess.pack_start(btnShowSrc, Gtk::PACK_SHRINK);
    boxToolProcess.pack_start(btnProcess, Gtk::PACK_EXPAND_WIDGET);

    sepOpen.set_margin_top(5);
    sepOpen.set_margin_bottom(5);
    rootBox.pack_start(boxToolOpen, Gtk::PACK_SHRINK);
    rootBox.pack_start(boxToolProcess, Gtk::PACK_SHRINK);
    rootBox.pack_start(sepOpen, Gtk::PACK_SHRINK);
    buildPorts();
    rootBox.pack_start(scrolledWindow, Gtk::PACK_EXPAND_WIDGET);

    btnOpen.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_open_clicked));
    btnShowSrc.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_show_clicked));
    btnProcess.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_process_clicked));
    btnSave.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_save_clicked));

    resetSource();
    show_all_children();
}

MainFrame::~MainFrame()
{
}

void MainFrame::buildPorts()
{
    scrolledWindow.add(lstPorts);
    scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    refTreeModel = Gtk::ListStore::create(portsColumns);
    lstPorts.set_model(refTreeModel);

    for (auto it = scheme.ports.begin(); it != scheme.ports.end(); ++it)
    {
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[portsColumns.col_btn] = false;
        row[portsColumns.col_descript] = it->description;
        row[portsColumns.col_tag] = it->tag;
    }

    auto cell = Gtk::make_managed<Gtk::CellRendererToggle>();
    lstPorts.append_column("Result", *cell);
    cell->signal_toggled().connect(
        sigc::mem_fun(*this, &MainFrame::cellrenderer_on_toogle));
    lstPorts.append_column("Description", portsColumns.col_descript);
    lstPorts.append_column("Tag", portsColumns.col_tag);

    auto pColumn = lstPorts.get_column(0);
    if (pColumn)
    {
        pColumn->add_attribute(cell->property_active(), portsColumns.col_btn);
    }
}

void MainFrame::btn_open_clicked()
{
    Gtk::FileChooserDialog dialog("Open image", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    auto filter_image = Gtk::FileFilter::create();
    filter_image->set_name("Image files");
    filter_image->add_mime_type("image/jpeg");
    dialog.add_filter(filter_image);
    dialog.set_current_folder("../media/color/");
    int result = dialog.run();
    switch (result)
    {
    case (Gtk::RESPONSE_OK):
    {
        fileName = dialog.get_filename();
        try
        {
            scheme.loadImage(fileName);
            lblOpen2.set_text(fileName);
            btnShowSrc.set_sensitive(true);
            btnProcess.set_sensitive(true);
            resetPorts();
            viewSource.showPort(scheme.getSourcePort());
        }
        catch (std::string message)
        {
            Gtk::MessageDialog dialog(*this, "Error", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_CLOSE);
            dialog.set_secondary_text(message);
            dialog.run();
            resetSource();
        }
        break;
    }
    case (Gtk::RESPONSE_CANCEL):
    default:
    {
        break;
    }
    }
}

void MainFrame::resetSource()
{
    lblOpen2.set_text("None");
    btnShowSrc.set_sensitive(false);
    btnProcess.set_sensitive(false);
    btnSave.set_sensitive(false);
    resetPorts();
}

void MainFrame::resetPorts()
{
    auto children = refTreeModel->children();
    for (auto iter = children.begin(); iter != children.end(); ++iter)
    {
        Gtk::TreeModel::Row row = *iter;
        row.set_value(0, false);
    }
    viewPort.reset();
}

void MainFrame::btn_process_clicked()
{
    scheme.process();
    btnSave.set_sensitive(true);
    auto children = refTreeModel->children();
    for (auto iter = children.begin(); iter != children.end(); ++iter)
    {
        Gtk::TreeModel::Row row = *iter;
        row.set_value(0, true);
    }
}

void MainFrame::btn_save_clicked()
{
    Gtk::FileChooserDialog dialog("Choose folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    dialog.set_current_folder("");
    int result = dialog.run();
    switch (result)
    {
    case (Gtk::RESPONSE_OK):
    {
        // todo
        Gtk::MessageDialog dialog(*this, "Saving");
        dialog.set_secondary_text("stub");
        dialog.run();
        break;
    }
    }
}

void MainFrame::btn_show_clicked()
{
    viewSource.showPort(scheme.getSourcePort());
}

void MainFrame::cellrenderer_on_toogle(const Glib::ustring &path)
{
    viewPort.showPort(scheme.ports[std::atoi(path.c_str())]);
}