#include "editors_controller.hpp"

#include <ide_widget/editor/recursive_splitter.hpp>
#include <ide_widget/commun/closable_widget.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>

namespace IDE
{

EditorsController::EditorsController(EditorsArea* editorsArea, QObject *parent)
  : QObject(parent)
  , _editorsArea(editorsArea)
{
  ClosableWidget* cw = newClosableWidget();
  _editorsArea->addWidget(cw);
}

bool EditorsController::eventFilter(
  QObject* watched,
  QEvent* event)
{
  if(event->type() == ClosableWidgetEvent::type())
  {
    ClosableWidgetEvent* cwEvent = static_cast<ClosableWidgetEvent*>(event);
    ClosableWidget* cw = dynamic_cast<ClosableWidget*>(watched);
    RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(watched->parent());
    if(cw && rs)
    {
      rs = rs->rootRecursiveSplitter();

      if(cwEvent->requestedAction() == ClosableWidgetEvent::Unsplit)
      {
        if(rs->count() > 1)
          if(rs->removeWidget(cw))
            delete cw;
      }
      else if(cwEvent->requestedAction() == ClosableWidgetEvent::HorizontalSplit ||
              cwEvent->requestedAction() == ClosableWidgetEvent::VerticalSplit)
      {
        Qt::Orientation orientation = Qt::Horizontal;
        if(cwEvent->requestedAction() == ClosableWidgetEvent::VerticalSplit)
          orientation = Qt::Vertical;
        ClosableWidget* cw2 = newClosableWidget();
        RecursiveIndex index = rs->indexOf(cw);
        if(!rs->insertWidget(index, cw2, orientation))
        {
          delete cw2;
        }
      }
      else if(cwEvent->requestedAction() == ClosableWidgetEvent::NewWindow)
      {
        ClosableWidget* cw2 = newClosableWidget();
        RecursiveSplitter* rs = newRecursiveSplitter();
        rs->addWidget(cw2);
        rs->show();

        connect(rs, SIGNAL(destroyed(QObject*)), this, SLOT(xWindowDestroyed(QObject*)));
        _editorsAreaWindows.append(rs);
      }
    }
    return true;
  }
  else
    return QObject::eventFilter(watched, event);
}

ClosableWidget* EditorsController::newClosableWidget() const
{
  ClosableWidget* cw = new ClosableWidget(ClosableWidget::SplitAndNewWindow);
  cw->installEventFilter(const_cast<EditorsController*>(this));
  return cw;
}

RecursiveSplitter* EditorsController::newRecursiveSplitter()
{
  RecursiveSplitter* rs = new RecursiveSplitter;
  connect(rs, SIGNAL(destroyed(QObject*)), this, SLOT(xWindowDestroyed(QObject*)));
  _editorsAreaWindows.append(rs);
  return rs;
}

void EditorsController::xWindowDestroyed(QObject* window)
{
  _editorsAreaWindows.removeOne(static_cast<RecursiveSplitter*>(window));
}

} // namespace IDE
