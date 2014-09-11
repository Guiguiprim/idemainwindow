#include <splittable_area/widget_focus_watcher.hpp>

#include <QApplication>
#include <QChildEvent>
#include <QWidget>

namespace IDE
{
QEvent::Type WidgetFocusEvent::s_myType = QEvent::None;

WidgetFocusEvent::WidgetFocusEvent(QWidget* widget)
  : QEvent(type())
  , _widget(widget)
{}

QWidget* WidgetFocusEvent::widget()
{
  return _widget;
}

QEvent::Type WidgetFocusEvent::type()
{
  if(QEvent::None == s_myType)
  {
    int t = QEvent::registerEventType();
    s_myType = static_cast<QEvent::Type>(t);
  }
  return s_myType;
}

WidgetFocusWatcher::WidgetFocusWatcher(QWidget* toWatch, QObject *toWarn)
  : QObject(toWatch) // WidgetFocusWatcher won't watch itself has is only watch QWidget children
  , _watched(toWatch)
  , _toWarn(toWarn)
{
  xInstallFilter(toWatch);
}

bool WidgetFocusWatcher::eventFilter(QObject* watched, QEvent* event)
{
  if(event->type() == QEvent::FocusIn)
  {
    WidgetFocusEvent event(_watched);
    QApplication::sendEvent(_toWarn, &event);
  }
  else if(event->type() == QEvent::ChildAdded)
  {
    QChildEvent* ce = static_cast<QChildEvent*>(event);
    xInstallFilter(ce->child());
  }
  else if(event->type() == QEvent::ChildRemoved)
  {
    QChildEvent* ce = static_cast<QChildEvent*>(event);
    xRemoveFilter(ce->child());
  }
  return QObject::eventFilter(watched, event);
}

void WidgetFocusWatcher::xInstallFilter(QObject* toWatch)
{
  if(toWatch->isWidgetType())
  {
    toWatch->installEventFilter(this);
    Q_FOREACH(QObject* child, toWatch->children())
    {
      xInstallFilter(child);
    }
  }
}

void WidgetFocusWatcher::xRemoveFilter(QObject* toNotWatch)
{
  if(toNotWatch->isWidgetType())
  {
    toNotWatch->removeEventFilter(this);
    Q_FOREACH(QObject* child, toNotWatch->children())
    {
      xRemoveFilter(child);
    }
  }
}

} // namespace AR
