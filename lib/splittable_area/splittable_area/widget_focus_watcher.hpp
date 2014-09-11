#ifndef IDE_WIDGET_FOCUS_WATCHER_H
#define IDE_WIDGET_FOCUS_WATCHER_H

#include <QObject>
#include <QEvent>

class QWidget;

namespace IDE
{

class WidgetFocusEvent : public QEvent
{
public:
  WidgetFocusEvent(QWidget* widget);

  QWidget* widget();

  static QEvent::Type type();

private:
  static QEvent::Type s_myType;
  QWidget* _widget;
};


/**
 * @brief The WidgetFocusWatcher class
 * The goal of this class is to know that a widget (or any one of his children widget)
 * has gain the focus.
 * When a FocusIn event is detected by the eventFilter a WidgetFocusEvent is send
 * to the object to warn. That object should overlay the function customEvent()
 * to catch it.
 */
class WidgetFocusWatcher : public QObject
{
public:
  explicit WidgetFocusWatcher(QWidget* toWatch, QObject* toWarn);

  virtual bool eventFilter(QObject*, QEvent* event);

private:
  void xInstallFilter(QObject* toWatch);
  void xRemoveFilter(QObject* toNotWatch);

private:
  QWidget* _watched;
  QObject* _toWarn;
};

} // namespace AR

#endif // IDE_WIDGET_FOCUS_WATCHER_H
