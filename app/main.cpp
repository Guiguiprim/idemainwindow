#include <QApplication>

#include "my_ide_mainwindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  IDE::MyIdeMainWindow window;
  window.setWindowTitle("My IDE");
  window.show();

  return app.exec();
}
