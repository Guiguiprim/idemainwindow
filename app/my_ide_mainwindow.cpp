#include "my_ide_mainwindow.hpp"

#include "controller/editors_controller.hpp"
#include "controller/side_panel_controller.hpp"
#include "dummy_content/dummy_closable_widget_element.hpp"

#include <ide_widget/bottom_panel/bottom_panel_chooser.hpp>

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

  _bottomPanelChooser->registerWidget(new DCW1);
  _bottomPanelChooser->registerWidget(new DCW2);
  _bottomPanelChooser->registerWidget(new DCW3);
}

} // namespace IDE
