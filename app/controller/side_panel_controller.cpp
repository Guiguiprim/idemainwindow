#include "side_panel_controller.hpp"

#include <ide_widget/commun/closable_widget.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>
#include <ide_widget/side_panel/side_panel.hpp>

namespace IDE
{

SidePanelController::SidePanelController(
    SidePanel* sidePanel,
    QObject *parent)
  : QObject(parent)
  , _sidePanel(sidePanel)
{
  ClosableWidget* cw = newClosableWidget();
  _sidePanel->addWidget(cw);
}

bool SidePanelController::eventFilter(
  QObject* watched,
  QEvent* event)
{
  if(event->type() == ClosableWidgetEvent::type())
  {
    ClosableWidgetEvent* cwEvent = static_cast<ClosableWidgetEvent*>(event);
    ClosableWidget* cw = dynamic_cast<ClosableWidget*>(watched);
    if(cw)
    {
      if(cwEvent->requestedAction() == ClosableWidgetEvent::Close)
      {
        if(_sidePanel->count() > 1)
        {
          delete cw;
        }
        else
        {
          _sidePanel->hide();
        }
      }
      else if(cwEvent->requestedAction() == ClosableWidgetEvent::VerticalSplit)
      {
        ClosableWidget* cw2 = newClosableWidget();
        int index = _sidePanel->indexOf(cw);
        _sidePanel->insertWidget(index+1, cw2);
      }
    }
    return true;
  }
  else
    return QObject::eventFilter(watched, event);
}

ClosableWidget* SidePanelController::newClosableWidget() const
{
  ClosableWidget* cw = new ClosableWidget(ClosableWidget::VSplit);
  cw->enableUnsplit(false);
  cw->installEventFilter(const_cast<SidePanelController*>(this));
  return cw;
}

} // namespace IDE
