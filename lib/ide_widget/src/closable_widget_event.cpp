#include <ide_widget/closable_widget_event.hpp>

namespace IDE
{
QEvent::Type ClosableWidgetEvent::s_eventType = QEvent::None;

ClosableWidgetEvent::ClosableWidgetEvent(RequestedAction requestedAction)
  : QEvent(ClosableWidgetEvent::type())
  , _requestedAction(requestedAction)
{}

ClosableWidgetEvent::RequestedAction ClosableWidgetEvent::requestedAction() const
{
  return _requestedAction;
}

QEvent::Type ClosableWidgetEvent::type()
{
  if (s_eventType == QEvent::None)
  {
      int generatedType = QEvent::registerEventType();
      s_eventType = static_cast<QEvent::Type>(generatedType);
  }
  return s_eventType;
}

} // namespace IDE
