#include "ViewFrame.h"

#include <iostream>

ViewFrame::ViewFrame()
    : rootBox(Gtk::ORIENTATION_VERTICAL),
      boxTool(Gtk::ORIENTATION_HORIZONTAL),
      btnSave("Save")
{
    set_title("View");
    lblDescription.set_margin_left(5);
    boxTool.pack_start(lblDescription, Gtk::PACK_SHRINK);
    boxTool.pack_end(btnSave, Gtk::PACK_SHRINK);
    rootBox.pack_start(boxTool, Gtk::PACK_SHRINK);
    rootBox.pack_start(imagePanel, Gtk::PACK_EXPAND_WIDGET);
    add(rootBox);

    btnSave.signal_clicked().connect(sigc::mem_fun(*this, &ViewFrame::btn_save_clicked));
}

ViewFrame::~ViewFrame()
{
}

void ViewFrame::reset()
{
    hide();
    lblDescription.set_text("");
    imagePanel.clear();
}

void ViewFrame::showPort(ImagePort port)
{
    if (!port.empty)
    {
        lblDescription.set_text(port.description);
        imagePanel.set(port.pixbuf);
        show_all_children();
        show();
    }
}

void ViewFrame::btn_save_clicked()
{
    Gtk::FileChooserDialog dialog("Save file", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    dialog.set_current_folder("");
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