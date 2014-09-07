#include "side_panel_controller.hpp"

#include <ide_widget/commun/closable_widget.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>
#include <ide_widget/side_panel/side_panel.hpp>

#include "../dummy_content/dummy_closable_widget_element.hpp"

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
  static int i=0;
  ClosableWidget* cw = new ClosableWidget(ClosableWidget::VSplit);
  cw->enableUnsplit(false);
  cw->installEventFilter(const_cast<SidePanelController*>(this));
  if(i==0)
  {
    DCW1* dcw1 = new DCW1;
    cw->setWidget(dcw1);
  }
  else if(i==1)
  {
    DCW2* dcw2 = new DCW2;
    cw->setWidget(dcw2);
  }
  else if(i==2)
  {
    DCW3* dcw3 = new DCW3;
    cw->setWidget(dcw3);
  }
  i++;
  i %= 3;

  return cw;
}

} // namespace IDE
