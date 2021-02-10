#include <gtkmm.h>
#include "gui/MainFrame.h"

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "superbro.pilab.graf");
  MainFrame mainFrame;
  return app->run(mainFrame);
}