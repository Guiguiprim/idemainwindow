#include "my_ide_mainwindow.hpp"

#include "controller/editors_controller.hpp"
#include "controller/side_panel_controller.hpp"

namespace IDE
{

MyIdeMainWindow::MyIdeMainWindow(QWidget *parent)
  : IDEMainWindow(parent)
  , _editorsController(NULL)
  , _leftPanelController(NULL)
  , _rightPanelController(NULL)
{
  _editorsController = new EditorsController(_editorsArea, this);
  _leftPanelController = new SidePanelController(_leftPanel, this);
  _rightPanelController = new SidePanelController(_rightPanel, this);
}

} // namespace IDE
