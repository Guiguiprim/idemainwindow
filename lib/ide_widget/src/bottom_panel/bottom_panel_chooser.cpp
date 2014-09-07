#include <ide_widget/bottom_panel/bottom_panel_chooser.hpp>

#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QSignalMapper>

#include <ide_widget/bottom_panel/bottom_panel.hpp>
#include <ide_widget/commun/closable_widget_element.hpp>

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
  , _displayMenu(NULL)
  , _menuAction(NULL)
  , _openMap(new QSignalMapper(this))
  , _displayMap(new QSignalMapper(this))
{
  this->setObjectName("DarkToolBar");

  _displayMenu = new QMenu;

  QToolButton* toolButton = new QToolButton;
  //toolButton->setIcon(QIcon());
  toolButton->setMenu(_displayMenu);
  toolButton->setPopupMode(QToolButton::InstantPopup);

  _menuAction = this->QToolBar::addWidget(toolButton);
  _menuAction->setVisible(false);

  connect(_openMap, SIGNAL(mapped(QWidget*)), this, SLOT(xOnOpenTriggered(QWidget*)));
  connect(_displayMap, SIGNAL(mapped(QWidget*)), this, SLOT(xOnDisplayTriggered(QWidget*)));
}

BottomPanelChooser::~BottomPanelChooser()
{
  QMap<QWidget*, WidgetAction*>::iterator it;
  while(_widgetActions.size() > 0)
  {
    QWidget* w = it.key();
    WidgetAction* wa = it.value();
    _widgetActions.remove(w);
    delete wa;
    delete w;
  }
  _widgetActions.clear();
}

void BottomPanelChooser::registerWidget(QWidget *widget, const QString& name, bool display)
{
  if(_widgetActions.find(widget) != _widgetActions.end())
    return;

  WidgetAction* wa = new WidgetAction;
  wa->name = name;
  wa->openAction = new QAction(name, this);
  wa->openAction->setCheckable(true);
  wa->displayAction = new QAction(name, this);
  wa->displayAction->setCheckable(true);
  wa->displayAction->setChecked(true);

  _widgetActions.insert(widget, wa);

  _openMap->setMapping(wa->openAction, widget);
  connect(wa->openAction, SIGNAL(triggered()), _openMap, SLOT(map()));

  _displayMap->setMapping(wa->displayAction, widget);
  connect(wa->displayAction, SIGNAL(triggered()), _displayMap, SLOT(map()));

  _displayMenu->addAction(wa->displayAction);
  this->insertAction(_menuAction, wa->openAction);

  if(!_menuAction->isVisible())
    _menuAction->setVisible(true);

  if(!display)
  {
    wa->openAction->setVisible(false);
    wa->displayAction->setChecked(false);
  }
}

void BottomPanelChooser::registerWidget(ClosableWidgetElement *widget, bool display)
{
  registerWidget(widget, widget->widgetName(), display);
}

void BottomPanelChooser::xOnDisplayTriggered(QWidget* widget)
{
  if(_widgetActions.find(widget) == _widgetActions.end())
    return;

  if(_widgetActions[widget]->displayAction->isChecked())
    _widgetActions[widget]->openAction->setVisible(true);
  else
    _widgetActions[widget]->openAction->setVisible(false);
}

void BottomPanelChooser::xOnOpenTriggered(QWidget* widget)
{
  if(_widgetActions[widget]->openAction->isChecked())
  {
    _bottomPanel->setWidget(widget);
    _bottomPanel->show();
    QMap<QWidget*, WidgetAction*>::iterator it;
    for(it = _widgetActions.begin(); it != _widgetActions.end(); ++it)
    {
      if(it.key() != widget)
      {
        it.value()->openAction->blockSignals(true);
        it.value()->openAction->setChecked(false);
        it.value()->openAction->blockSignals(false);
      }
    }
  }
  else
    _bottomPanel->hide();
}

} // namespace IDE
