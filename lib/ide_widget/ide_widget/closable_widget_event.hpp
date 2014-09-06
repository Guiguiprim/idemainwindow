#ifndef IDE_CLOSABLE_WIDGET_EVENT_HPP
#define IDE_CLOSABLE_WIDGET_EVENT_HPP

#include <QEvent>

namespace IDE
{

class ClosableWidgetEvent : public QEvent
{
public:
  enum RequestedAction {
    Close,
    Unsplit,
    VerticalSplit,
    HorizontalSplit,
    NewWindow
  };
public:
  ClosableWidgetEvent(RequestedAction requestedAction);

  RequestedAction requestedAction() const;

  static QEvent::Type type();

private:
  RequestedAction _requestedAction;
  static QEvent::Type s_eventType;
};

} // namespace IDE

#endif // IDE_CLOSABLE_WIDGET_EVENT_HPP
