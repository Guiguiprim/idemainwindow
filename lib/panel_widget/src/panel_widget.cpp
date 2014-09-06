#include <panel_widget/panel_widget.hpp>

namespace IDE
{

PanelWidget::PanelWidget(
    const QString& panelName,
    QWidget *parent)
  : QWidget(parent)
  , _attachActions()
  , _panelName(panelName)
{}

QString PanelWidget::panelName() const
{
  return _panelName;
}

QList<QAction*> PanelWidget::attachActions() const
{
  return _attachActions;
}

void PanelWidget::addAttachAction(QAction* action)
{
  if(!_attachActions.contains(action))
    _attachActions.append(action);
}

void PanelWidget::removeAttachAction(QAction* action)
{
  _attachActions.removeOne(action);
}

} // namespace IDE
