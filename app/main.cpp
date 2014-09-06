#include <QApplication>

#include "idemainwindow/ide_mainwindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  IDE::IDEMainWindow window;
  window.setWindowTitle("My IDE");
  window.show();

  return app.exec();
}
