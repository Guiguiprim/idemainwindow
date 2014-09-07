#include "my_ide_mainwindow.hpp"

#include "controller/editors_controller.hpp"

namespace IDE
{

MyIdeMainWindow::MyIdeMainWindow(QWidget *parent)
  : IDEMainWindow(parent)
  , _editorsController(NULL)
{
  _editorsController = new EditorsController(_editorsArea, this);
}

} // namespace IDE
