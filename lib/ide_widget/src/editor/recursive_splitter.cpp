#include <ide_widget/editor/recursive_splitter.hpp>

#include <QDialog>

#include <ide_widget/commun/closable_widget.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>

namespace IDE
{

RecursiveSplitter::RecursiveSplitter(
    QWidget *parent)
  : Splitter(Qt::Horizontal, parent)
{}

RecursiveSplitter::RecursiveSplitter(
    const Qt::Orientation orientation,
    QWidget *parent)
  : Splitter(orientation, parent)
{}

bool RecursiveSplitter::eventFilter(
    QObject* watched,
    QEvent* event)
{
  if(event->type() == ClosableWidgetEvent::type())
  {
    ClosableWidgetEvent* cwEvent = static_cast<ClosableWidgetEvent*>(event);
    ClosableWidget* cw = dynamic_cast<ClosableWidget*>(watched);
    if(cw)
    {
      if(cwEvent->requestedAction() == ClosableWidgetEvent::Unsplit)
      {
        if(this->count() > 1)
          if(this->removeWidget(cw))
            delete cw;
      }
      else if(cwEvent->requestedAction() == ClosableWidgetEvent::HorizontalSplit ||
              cwEvent->requestedAction() == ClosableWidgetEvent::VerticalSplit)
      {
        Qt::Orientation orientation = Qt::Horizontal;
        if(cwEvent->requestedAction() == ClosableWidgetEvent::VerticalSplit)
          orientation = Qt::Vertical;
        ClosableWidget* cw2 = new ClosableWidget(ClosableWidget::SplitAndNewWindow);
        RecursiveIndex index = this->indexOf(cw);
        if(this->insertWidget(index, cw2, orientation))
        {
          cw2->installEventFilter(this);
        }
        else
        {
          delete cw2;
        }
      }
      else if(cwEvent->requestedAction() == ClosableWidgetEvent::NewWindow)
      {
        RecursiveSplitter* rs = new RecursiveSplitter;
        ClosableWidget* cw2 = new ClosableWidget(ClosableWidget::SplitAndNewWindow);
        rs->addWidget(cw2);
        cw2->installEventFilter(rs);
        rs->show();
//        QDialog* dlg = new QDialog;
//        QVBoxLayout* lyt = new QVBoxLayout(dlg);
//        lyt->setMargin(0);
//        lyt->addWidget(rs);
//        dlg->show();
      }
    }
    return true;
  }
  else
    return QSplitter::eventFilter(watched, event);
}

bool RecursiveSplitter::addWidget(
    ClosableWidget* widget,
    const Qt::Orientation orientation,
    const RecursiveIndex& index)
{
  if(index.isEmpty())
  {
    if(this->count() < 2)
      this->setOrientation(orientation);

    if(this->orientation() == orientation)
    {
      this->QSplitter::addWidget(widget);
      return true;
    }
    else
    {
      // if orientation is different start a recursion
      QWidget* w = this->widget(this->count() - 1);
      RecursiveSplitter* rs =  new RecursiveSplitter(orientation);
      this->QSplitter::addWidget(rs);
      rs->QSplitter::addWidget(w);
      rs->QSplitter::addWidget(widget);
      return true;
    }
  }
  else
  {
    QWidget* w = this->widget(index.first());
    RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);
    if(rs)
    {
      RecursiveIndex i = index;
      i.pop_front();
      return rs->addWidget(widget, orientation, i);
    }
  }
  return false;
}

RecursiveIndex RecursiveSplitter::indexOf(
    QWidget* widget) const
{
  int i = this->QSplitter::indexOf(widget);
  if(i != -1)
  {
    RecursiveIndex index;
    index.append(i);
    return index;
  }

  for(int i=0; i<this->count(); ++i)
  {
    QWidget* w = this->widget(i);
    RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);
    if(rs)
    {
      RecursiveIndex tmp = rs->indexOf(widget);
      if(!tmp.isEmpty())
      {
        tmp.push_front(i);
        return tmp;
      }
    }
  }

  return RecursiveIndex();
}

bool RecursiveSplitter::insertWidget(
    const RecursiveIndex& index,
    ClosableWidget* widget,
    const Qt::Orientation orientation)
{
  if(index.size() == 1)
  {
    if(this->count() < 2)
      this->setOrientation(orientation);

    if(this->orientation() == orientation)
    {
      this->QSplitter::insertWidget(index.first(), widget);
      return true;
    }
    else
    {
      // if orientation is different start a recursion
      QWidget* w = this->widget(index.first());
      RecursiveSplitter* rs =  new RecursiveSplitter(orientation);
      this->QSplitter::insertWidget(index.first(), rs);
      rs->QSplitter::addWidget(w);
      rs->QSplitter::addWidget(widget);
      return true;
    }
  }
  else if(index.size() > 1)
  {
    QWidget* w = this->widget(index.first());
    RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);
    if(rs)
    {
      RecursiveIndex i = index;
      i.pop_front();
      return rs->insertWidget(i, widget, orientation);
    }
  }
  return false;
}

bool RecursiveSplitter::removeWidget(
    QWidget* widget,
    QWidget* newParent)
{
  RecursiveIndex index = indexOf(widget);
  if(this->removeWidget(index, newParent) == widget)
    return true;
  return false;
}

QWidget* RecursiveSplitter::removeWidget(
    const RecursiveIndex& index,
    QWidget* newParent)
{
  if(index.isEmpty())
    return NULL;

  QWidget* w = this->widget(index.first());
  if(w && index.size() == 1)
  {
    w->setParent(newParent);
    return w;
  }

  RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);
  if(rs)
  {
    RecursiveIndex i = index;
    i.pop_front();
    QWidget* w2 = rs->removeWidget(i, newParent);
    if(w2)
    {
      if(rs->count() == 1)
      {
        // remove useless recursion splitter
        QWidget* w3 = rs->widget(0);
        this->QSplitter::insertWidget(index.first(), w3);
        delete rs;
      }
      return w2;
    }
  }

  return NULL;
}

bool RecursiveSplitter::isSplitter(
    const RecursiveIndex& index) const
{
  if(index.isEmpty())
    return true;

  RecursiveSplitter* rs = this->recursiveSplitter(index);

  if(rs)
    return true;

  return false;
}

RecursiveSplitter* RecursiveSplitter::recursiveSplitter(
    const RecursiveIndex& index) const
{
  if(index.isEmpty())
    return const_cast<RecursiveSplitter*>(this);

  QWidget* w = this->widget(index.first());
  RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);

  if(index.size() == 1)
    return rs;

  if(rs) // && index.size() > 1
  {
    RecursiveIndex i = index;
    i.pop_front();
    return rs->recursiveSplitter(i);
  }

  return NULL;
}

QWidget* RecursiveSplitter::widgetAt(
    const RecursiveIndex& index) const
{
  if(index.isEmpty())
    return const_cast<RecursiveSplitter*>(this);

  QWidget* w = this->widget(index.first());

  if(index.size() == 1)
    return w;

  // index.size() > 1
  RecursiveIndex i = index;
  i.pop_front();
  RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(w);
  if(rs)
    return rs->widgetAt(i);

  return NULL;
}

RecursiveSplitter* RecursiveSplitter::rootRecursiveSplitter() const
{
  RecursiveSplitter* rs = dynamic_cast<RecursiveSplitter*>(this->parentWidget());
  if(rs)
    return rs->rootRecursiveSplitter();
  return const_cast<RecursiveSplitter*>(this);
}

} // namespace IDE
