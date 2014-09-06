#include <ide_widget/closable_widget_element.hpp>

namespace IDE
{

ClosableWidgetElement::ClosableWidgetElement(
    QString widgetName,
    QWidget *parent)
  : QWidget(parent)
  , _attachActions()
  , _widgetName(widgetName)
{}

QString ClosableWidgetElement::widgetName() const
{
  return _widgetName;
}

QList<QAction*> ClosableWidgetElement::attachActions() const
{
  return _attachActions;
}

void ClosableWidgetElement::addAttachAction(QAction* action)
{
  if(!_attachActions.contains(action))
    _attachActions.append(action);
}

} // namespace IDE
