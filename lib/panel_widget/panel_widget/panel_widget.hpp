#ifndef IDE_PANEL_WIDGET_HPP
#define IDE_PANEL_WIDGET_HPP

#include <QWidget>

#include <QList>

class QAction;

namespace IDE
{

class PanelWidget : public QWidget
{
  Q_OBJECT
public:
  explicit PanelWidget(const QString& panelName, QWidget *parent = NULL);

  QString panelName() const;

  QList<QAction*> attachActions() const;
  void addAttachAction(QAction* action);
  void removeAttachAction(QAction* action);

private:
  QString _panelName;
  QList<QAction*> _attachActions;
};

} // namespace IDE

#endif // IDE_PANEL_WIDGET_HPP
