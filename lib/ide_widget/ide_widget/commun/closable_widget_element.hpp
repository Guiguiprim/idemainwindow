#ifndef IDE_CLOSABLE_WIDGET_ELEMENT_HPP
#define IDE_CLOSABLE_WIDGET_ELEMENT_HPP

#include "../api.hpp"
#include <QWidget>

#include <QList>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT ClosableWidgetElement : public QWidget
{
  Q_OBJECT
public:
  explicit ClosableWidgetElement(QString widgetName, QWidget *parent = NULL);

  QString widgetName() const;

  QList<QAction*> attachActions() const;
  void addAttachAction(QAction* action);

private:
  QString _widgetName;
  QList<QAction*> _attachActions;
};

} // namespace IDE

#endif // IDE_CLOSABLE_WIDGET_ELEMENT_HPP
