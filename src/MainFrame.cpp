#include "MainFrame.h"

#include <string>

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
    rootBox.pack_start(boxPorts, Gtk::PACK_SHRINK);

    btnOpen.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_open_clicked));
    btnShowSrc.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
        sigc::mem_fun(*this, &MainFrame::btn_show_clicked), "src"));
    btnProcess.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_process_clicked));
    btnSave.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_save_clicked));

    show_all_children();
}

MainFrame::~MainFrame()
{
}

void MainFrame::buildPorts()
{
    Gtk::Box *box1 = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL);
    Gtk::Label *lbl = Gtk::make_managed<Gtk::Label>("Grayscale");
    Gtk::Button *btnShow = Gtk::make_managed<Gtk::Button>("Show");
    btnShow->signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
        sigc::mem_fun(*this, &MainFrame::btn_show_clicked), "grayscale"));
    box1->pack_start(*btnShow, Gtk::PACK_SHRINK);
    box1->pack_start(*lbl, Gtk::PACK_SHRINK);
    boxPorts.pack_start(*box1, Gtk::PACK_SHRINK);
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
    dialog.set_current_folder("../media/");
    int result = dialog.run();
    switch (result)
    {
    case (Gtk::RESPONSE_OK):
    {
        std::string filename = dialog.get_filename();
        lblOpen2.set_text(filename);
        break;
    }
    case (Gtk::RESPONSE_CANCEL):
    default:
    {
        lblOpen2.set_text("None");
        break;
    }
    }
}

void MainFrame::btn_process_clicked()
{
    Gtk::MessageDialog dialog(*this, "Processing");
    dialog.set_secondary_text("stub");
    dialog.run();
}

void MainFrame::btn_save_clicked()
{
    Gtk::FileChooserDialog dialog("Choose folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    int result = dialog.run();
    switch (result)
    {
    case (Gtk::RESPONSE_OK):
    {
        Gtk::MessageDialog dialog(*this, "Saving");
        dialog.set_secondary_text("stub");
        dialog.run();
        break;
    }
    }
}

void MainFrame::btn_show_clicked(Glib::ustring tag)
{
    Gtk::MessageDialog dialog(*this, "Showing");
    dialog.set_secondary_text(tag);
    dialog.run();
}