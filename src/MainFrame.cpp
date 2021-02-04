#include "MainFrame.h"

MainFrame::MainFrame()
:
    rootBox(Gtk::ORIENTATION_VERTICAL),
    toolBoxOpen(Gtk::ORIENTATION_HORIZONTAL),
    toolBoxPorts(Gtk::ORIENTATION_HORIZONTAL),
    btnOpen("Open"),
    lblOpen1("Select source file:"),
    lblOpen2("None")
{
    set_title("Graf Lab1");
    set_border_width(10);
    add(rootBox);
    lblOpen2.set_justify(Gtk::JUSTIFY_LEFT);
    toolBoxOpen.set_border_width(5);
    toolBoxOpen.pack_start(lblOpen1, Gtk::PACK_SHRINK);
    toolBoxOpen.pack_start(btnOpen, Gtk::PACK_SHRINK, 5);
    toolBoxOpen.pack_start(lblOpen2, Gtk::PACK_EXPAND_WIDGET);
    rootBox.pack_start(toolBoxOpen, Gtk::PACK_SHRINK);
    buildPorts();
    rootBox.pack_start(toolBoxPorts, Gtk::PACK_SHRINK);
    btnOpen.signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::btn_open_clicked));
    set_default_size(300, 400);
    show_all_children();
}

MainFrame::~MainFrame()
{

}

void MainFrame::buildPorts()
{
    Glib::ustring descript1("Grayscale");
    Gtk::Box box1;
    Gtk::Button btnShow1("Show");
    btnShow1.signal_clicked().connect(sigc::bind< -1, Glib::ustring >(
        sigc::mem_fun(*this, &MainFrame::btn_show_clicked), "grayscale"));
}

void MainFrame::btn_open_clicked()
{
    Gtk::MessageDialog dialog(*this, "This is an INFO MessageDialog");
  dialog.set_secondary_text(
          "And this is the secondary text that explains things.");

  dialog.run();
}

void MainFrame::btn_show_clicked(Glib::ustring tag)
{

}