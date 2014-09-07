#include <ide_widget/bottom_panel/bottom_panel_chooser.hpp>

#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QSignalMapper>

#include <ide_widget/bottom_panel/bottom_panel.hpp>
#include <ide_widget/commun/closable_widget_element.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>

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

  _bottomPanel->installEventFilter(this);

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
    it = _widgetActions.begin();
    QWidget* w = it.key();
    WidgetAction* wa = it.value();
    _widgetActions.remove(w);
    delete wa;
    disconnect(w, SIGNAL(destroyed(QObject*)),
               this, SLOT(xOnWidgetDestroyed(QObject*)));
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
  connect(widget, SIGNAL(destroyed(QObject*)),
          this, SLOT(xOnWidgetDestroyed(QObject*)));

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

bool BottomPanelChooser::eventFilter(
  QObject* watched,
  QEvent* event)
{
  if(event->type() == ClosableWidgetEvent::type())
  {
    ClosableWidgetEvent* cwEvent = static_cast<ClosableWidgetEvent*>(event);
    if(cwEvent->requestedAction() == ClosableWidgetEvent::Close)
    {
        _bottomPanel->hide();
    }
    return true;
  }
  else
    return QObject::eventFilter(watched, event);
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

void BottomPanelChooser::xOnWidgetDestroyed(QObject* obj)
{
  // obj is being destroy so dynamic_cast may fail
  // here we only use the pointer as value
  QWidget* w = static_cast<QWidget*>(obj);
  if(_widgetActions.find(w) != _widgetActions.end())
  {
    delete _widgetActions[w];
    _widgetActions.remove(w);
  }
}

} // namespace IDE
