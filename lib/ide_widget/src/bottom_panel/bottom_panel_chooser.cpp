#include <ide_widget/bottom_panel/bottom_panel_chooser.hpp>

#include <QAction>

namespace IDE
{

BottomPanelChooser::WidgetAction::~WidgetAction()
{
  delete openAction;
  delete displayAction;
}

BottomPanelChooser::BottomPanelChooser(
    BottomPanel* bottomPanel,
    QWidget *parent)
  : QToolBar(parent)
  , _bottomPanel(bottomPanel)
  , _splitMenu(NULL)
  , _menuAction(NULL)
{
  this->setObjectName("DarkToolBar");
}

BottomPanelChooser::~BottomPanelChooser()
{
  qDeleteAll(_widgetActions);
  _widgetActions.clear();
}

} // namespace IDE
