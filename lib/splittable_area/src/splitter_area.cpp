#include <splittable_area/splitter_area.hpp>

#include <QResizeEvent>

#include <splittable_area/splitter_handler.hpp>
#include <splittable_area/splitter_widget.hpp>
#include <splittable_area/widget_focus_watcher.hpp>

namespace IDE
{
typedef QPair<SplitterSide,SplitterSide> DirPair;

SplitterArea::SplitterArea(QWidget* parent)
  : QWidget(parent)
  , _handlerThickness(3)
  , _widgetMinimumSize(40)
  , _lastUsedSplitterWidget(NULL)
{
  this->resize(400,400);

  _topHandler = xCreateHandler(Qt::Horizontal);
  _bottomHandler = xCreateHandler(Qt::Horizontal);
  _leftHandler = xCreateHandler(Qt::Vertical);
  _rightHandler = xCreateHandler(Qt::Vertical);

  _topHandler->setPos(0);
  _topHandler->setMovable(false);
  _topHandler->setHandler(IDE::LEFT, _leftHandler);
  _topHandler->setHandler(IDE::RIGHT, _rightHandler);

  _bottomHandler->setPos(this->height() - handlerThickness());
  _bottomHandler->setMovable(false);
  _bottomHandler->setHandler(IDE::LEFT, _leftHandler);
  _bottomHandler->setHandler(IDE::RIGHT, _rightHandler);

  _leftHandler->setPos(0);
  _leftHandler->setMovable(false);
  _leftHandler->setHandler(IDE::TOP, _topHandler);
  _leftHandler->setHandler(IDE::BOTTOM, _bottomHandler);

  _rightHandler->setPos(this->width() - handlerThickness());
  _rightHandler->setMovable(false);
  _rightHandler->setHandler(IDE::TOP, _topHandler);
  _rightHandler->setHandler(IDE::BOTTOM, _bottomHandler);

  SplitterWidget* widget = xCreateWidget();
  _splitterWidgets.append(widget);
  widget->setHandler(IDE::TOP, _topHandler);
  widget->setHandler(IDE::BOTTOM, _bottomHandler);
  widget->setHandler(IDE::LEFT, _leftHandler);
  widget->setHandler(IDE::RIGHT, _rightHandler);

  xRecomputeMinimumSize();
}

int SplitterArea::handlerThickness() const
{
  return _handlerThickness;
}

int SplitterArea::widgetMinimumSize() const
{
  return _widgetMinimumSize;
}

int SplitterArea::count() const
{
  return _splitterWidgets.count();
}

QByteArray SplitterArea::saveConfig() const
{
  return QByteArray();
}

bool SplitterArea::loadConfig(QByteArray config)
{
  return false;
}

int SplitterArea::indexOf(QWidget* widget) const
{
  for(int i=0; i<_splitterWidgets.size(); ++i)
  {
    if(_splitterWidgets.at(i)->widget() == widget)
      return i;
  }
  return -1;
}

int SplitterArea::indexOfSplitterWidget(SplitterWidget* splitterWidget) const
{
  for(int i=0; i<_splitterWidgets.size(); ++i)
  {
    if(_splitterWidgets.at(i) == splitterWidget)
      return i;
  }
  return -1;
}

int SplitterArea::indexAt(QPoint pos) const
{
  SplitterWidget* sw = splitterWidgetAt(pos);
  return _splitterWidgets.indexOf(sw);
}

QWidget* SplitterArea::widgetAt(int index) const
{
  if(index < 0 || index >= _splitterWidgets.size())
    return NULL; // invalide index

  return _splitterWidgets.at(index)->widget();
}

QWidget* SplitterArea::widgetAt(QPoint pos) const
{
  SplitterWidget* sw = splitterWidgetAt(pos);
  if(sw)
    return sw->widget();
  return NULL;
}

SplitterWidget* SplitterArea::splitterWidgetAt(int index) const
{
  if(index < 0 || index >= _splitterWidgets.size())
    return NULL; // invalide index

  return _splitterWidgets.at(index);
}

SplitterWidget* SplitterArea::splitterWidgetAt(QPoint pos) const
{
  // check that we won't hit the border
  if(pos.x() < handlerThickness())
    pos.setX(handlerThickness() + 1);
  else if(pos.x() > this->width() - handlerThickness())
    pos.setX(this->width() - handlerThickness() - 1);

  if(pos.y() < handlerThickness())
    pos.setY(handlerThickness() + 1);
  else if(pos.y() > this->height() - handlerThickness())
    pos.setY(this->height() - handlerThickness() - 1);

  QWidget* w = this->QWidget::childAt(pos);
  SplitterWidget* sw = dynamic_cast<SplitterWidget*>(w);
  if(sw)
    return sw;

  SplitterHandler* sh = dynamic_cast<SplitterHandler*>(w);
  if(sh) // we hit a handler let move a little bit
  {
    if(sh->orientation() == Qt::Vertical)
      pos.setX(pos.x() - handlerThickness());
    else
      pos.setY(pos.y() - handlerThickness());

    QWidget* w = this->QWidget::childAt(pos);
    SplitterWidget* sw = dynamic_cast<SplitterWidget*>(w);
    if(sw)
      return sw;
  }

  return NULL; // should never append
}

SplitterWidget* SplitterArea::verticalSplit(
    int index,
    float proportion)
{
  if(index < 0 || index >= _splitterWidgets.size())
    return NULL; // invalide index

  if(0 >= proportion || 1 <= proportion)
    return NULL; // invalide proportion

  SplitterWidget* sw = _splitterWidgets.at(index);
  SplitterHandler* topHandler = sw->handler(IDE::TOP);
  SplitterHandler* bottomHandler = sw->handler(IDE::BOTTOM);
  SplitterHandler* leftHandler = sw->handler(IDE::LEFT);
  SplitterHandler* rightHandler = sw->handler(IDE::RIGHT);

  SplitterHandler* newHandler = xCreateHandler(Qt::Vertical);
  _verticalHandlers.append(newHandler);
  newHandler->setHandler(IDE::TOP, topHandler);
  newHandler->setHandler(IDE::BOTTOM, bottomHandler);

  int width = rightHandler->pos() - leftHandler->pos();
  int pos = leftHandler->pos() + width * proportion;
  newHandler->setPos(pos);

  sw->setHandler(IDE::RIGHT, newHandler);

  SplitterWidget* nsw = xCreateWidget();
  _splitterWidgets.append(nsw);
  nsw->setHandler(IDE::TOP, topHandler);
  nsw->setHandler(IDE::BOTTOM, bottomHandler);
  nsw->setHandler(IDE::LEFT, newHandler);
  nsw->setHandler(IDE::RIGHT, rightHandler);

  xRecomputeMinimumSize();
  return nsw;
}

SplitterWidget* SplitterArea::horizontalSplit(
    int index,
    float proportion)
{
  if(index < 0 || index >= _splitterWidgets.size())
    return NULL; // invalide index

  if(0 >= proportion || 1 <= proportion)
    return NULL; // invalide proportion

  SplitterWidget* sw = _splitterWidgets.at(index);
  SplitterHandler* topHandler = sw->handler(IDE::TOP);
  SplitterHandler* bottomHandler = sw->handler(IDE::BOTTOM);
  SplitterHandler* leftHandler = sw->handler(IDE::LEFT);
  SplitterHandler* rightHandler = sw->handler(IDE::RIGHT);

  SplitterHandler* newHandler = xCreateHandler(Qt::Horizontal);
  _horizontalHandlers.append(newHandler);
  newHandler->setHandler(IDE::LEFT, leftHandler);
  newHandler->setHandler(IDE::RIGHT, rightHandler);

  int height = bottomHandler->pos() - topHandler->pos();
  int pos = topHandler->pos() + height * proportion;
  newHandler->setPos(pos);

  sw->setHandler(IDE::BOTTOM, newHandler);

  SplitterWidget* nsw = xCreateWidget();
  _splitterWidgets.append(nsw);
  nsw->setHandler(IDE::TOP, newHandler);
  nsw->setHandler(IDE::BOTTOM, bottomHandler);
  nsw->setHandler(IDE::LEFT, leftHandler);
  nsw->setHandler(IDE::RIGHT, rightHandler);

  xRecomputeMinimumSize();
  return nsw;
}

SplitterWidget* SplitterArea::sideSplit(
    SplitterSide side,
    float p)
{
  if(0 >= p || 1 <= p)
    return NULL; // invalide proportion

  SplitterHandler* topHandler = _topHandler;
  SplitterHandler* bottomHandler = _bottomHandler;
  SplitterHandler* leftHandler = _leftHandler;
  SplitterHandler* rightHandler = _rightHandler;

  if(side == IDE::TOP || side == IDE::BOTTOM)
  {
    Q_FOREACH(SplitterHandler* handler, _horizontalHandlers)
    {
      qreal xp = (qreal)handler->pos() / (qreal)this->height();
      qreal Xp = xp * (1-p);
      if(side == IDE::TOP)
        Xp += p;
      int newPos = this->height() * Xp;
      handler->setPos(newPos);
    }
  }
  else
  {
    Q_FOREACH(SplitterHandler* handler, _verticalHandlers)
    {
      qreal xp = (qreal)handler->pos() / (qreal)this->width();
      qreal Xp = xp * (1-p);
      if(side == IDE::LEFT)
        Xp += p;
      int newPos = this->width() * Xp;
      handler->setPos(newPos);
    }
  }

  SplitterHandler* newHandler = NULL;
  if(side == IDE::TOP || side == IDE::BOTTOM)
  {
    newHandler = xCreateHandler(Qt::Horizontal);
    newHandler->setHandler(IDE::LEFT, leftHandler);
    newHandler->setHandler(IDE::RIGHT, rightHandler);
    _horizontalHandlers.append(newHandler);
  }
  else
  {
    newHandler = xCreateHandler(Qt::Vertical);
    newHandler->setHandler(IDE::TOP, topHandler);
    newHandler->setHandler(IDE::BOTTOM, bottomHandler);
    _verticalHandlers.append(newHandler);
  }

  SplitterHandler* handler = NULL;
  int newPos = 0;
  switch(side)
  {
  case IDE::TOP:
    handler = topHandler;
    newPos = this->height() * p;
    bottomHandler = newHandler;
    break;
  case IDE::BOTTOM:
    handler = bottomHandler;
    newPos = this->height() * (1-p);
    topHandler = newHandler;
    break;
  case IDE::LEFT:
    handler = leftHandler;
    newPos = this->width() * p;
    rightHandler = newHandler;
    break;
  case IDE::RIGHT:
    handler = rightHandler;
    newPos = this->width() * (1-p);
    leftHandler = newHandler;
    break;
  }
  newHandler->setPos(newPos);

  QVector<SplitterWidgetBase*> handleWidgets = handler->handleWidgetsBase(side);
  Q_FOREACH(SplitterWidgetBase* swb, handleWidgets)
  {
    if(!xIsBorder(swb))
      swb->setHandler(side, newHandler);
  }

  SplitterWidget* nsw = xCreateWidget();
  nsw->setHandler(IDE::TOP, topHandler);
  nsw->setHandler(IDE::BOTTOM, bottomHandler);
  nsw->setHandler(IDE::LEFT, leftHandler);
  nsw->setHandler(IDE::RIGHT, rightHandler);
  _splitterWidgets.append(nsw);

  xRecomputeMinimumSize();
  return nsw;
}

bool SplitterArea::addWidget(
    QWidget* widget,
    int index,
    Qt::Orientation orientation,
    float proportion)
{
  if(index == -1)
    index = count() - 1;

  if(index < 0 || index >= _splitterWidgets.size())
    return false; // invalide index

  if(0 >= proportion || 1 <= proportion)
    return false; // invalide proportion

  SplitterWidget* nsw = NULL;
  if(Qt::Horizontal == orientation)
    nsw = this->horizontalSplit(index, proportion);
  else
    nsw = this->verticalSplit(index, proportion);

  if(!nsw)
    return false;

  nsw->setWidget(widget);
  return true;
}

bool SplitterArea::insertWidget(
    int index,
    QWidget* widget,
    Qt::Orientation orientation,
    float proportion)
{
  if(index < 0 || index >= _splitterWidgets.size())
    return false; // invalide index

  if(0 >= proportion || 1 <= proportion)
    return false; // invalide proportion

  SplitterWidget* sw = _splitterWidgets.at(index);
  SplitterWidget* nsw = NULL;
  if(Qt::Horizontal == orientation)
    nsw = this->horizontalSplit(index, proportion);
  else
    nsw = this->verticalSplit(index, proportion);

  if(!nsw)
    return false;

  nsw->setWidget(sw->takeWidget());
  sw->setWidget(widget);
  return true;
}

bool SplitterArea::setWidgetAt(
    QWidget* widget,
    int index)
{
  if(index < 0 || index >= _splitterWidgets.size())
    return false; // invalide index

  SplitterWidget* sw = _splitterWidgets.at(index);
  sw->setWidget(widget);
  return true;
}

bool SplitterArea::removeWidget(QWidget* widget)
{
  return remove(indexOf(widget));
}

bool SplitterArea::removeSplitterWidget(SplitterWidget* splitterWidget)
{
  return remove(indexOfSplitterWidget(splitterWidget));
}

bool SplitterArea::remove(int index)
{
  if(index < 0 || index >= _splitterWidgets.size())
    return false; // invalide index

  if(index == 0 && _splitterWidgets.size() == 1)
  {
    delete _splitterWidgets.first()->takeWidget();
    return true; // last widget so we just remove the widget and not the splitter widget
  }

  SplitterWidget* sw = _splitterWidgets.at(index);

  QVector<DirPair> removeDir;
  removeDir.append(DirPair(IDE::TOP, IDE::BOTTOM) );
  removeDir.append(DirPair(IDE::LEFT, IDE::RIGHT) );
  removeDir.append(DirPair(IDE::BOTTOM, IDE::TOP ) );
  removeDir.append(DirPair(IDE::RIGHT, IDE::LEFT ) );

  Q_FOREACH(DirPair dir, removeDir)
  {
    SplitterHandler* removableHandler = NULL;
    SplitterHandler* oppositeHandler = NULL;

    removableHandler = sw->handler(dir.first);
    if(removableHandler &&
       !xIsBorder(removableHandler) &&
       removableHandler->handleWidgetsBase(dir.first).size() == 1)
    {
      oppositeHandler = sw->handler(dir.second);
      if(oppositeHandler &&
         !xIsBorder(oppositeHandler) &&
         oppositeHandler->handleWidgetsBase(dir.second).size() == 1)
      {
        int newPos = (oppositeHandler->pos() - removableHandler->pos()) / 2;
        oppositeHandler->setPos(newPos);
      }

      QVector<SplitterWidgetBase*> handleWidgets = removableHandler->handleWidgetsBase(dir.second);
      Q_FOREACH(SplitterWidgetBase* swb, handleWidgets)
      {
        swb->setHandler(dir.second, oppositeHandler);
      }

      _verticalHandlers.removeOne(removableHandler);
      _horizontalHandlers.removeOne(removableHandler);
      _splitterWidgets.removeOne(sw);

      delete removableHandler;

      if(_lastUsedSplitterWidget == sw)
        _lastUsedSplitterWidget = NULL;

      delete sw;

      xRecomputeMinimumSize();
      return true;
    }
  }

  return false; // no removable handler found weird ...
}


int SplitterArea::indexLastUsedWidet() const
{
  return indexOfSplitterWidget(_lastUsedSplitterWidget);
}

void SplitterArea::resizeEvent(QResizeEvent* event)
{
  if(!this->isVisible())
    return;

  qreal vFac = (qreal)this->height() / (qreal)event->oldSize().height();
  qreal hFac = (qreal)this->width() / (qreal)event->oldSize().width();

  Q_FOREACH(SplitterHandler* handler, _verticalHandlers)
  {
    handler->setPos(handler->pos() * hFac);
  }

  Q_FOREACH(SplitterHandler* handler, _horizontalHandlers)
  {
    handler->setPos(handler->pos() * vFac);
  }

  _bottomHandler->setPos(this->height() - handlerThickness());
  _rightHandler->setPos(this->width() - handlerThickness());
}

void SplitterArea::customEvent(QEvent* event)
{
  if(event->type() == WidgetFocusEvent::type())
  {
    WidgetFocusEvent* wfe = static_cast<WidgetFocusEvent*>(event);
    _lastUsedSplitterWidget = dynamic_cast<SplitterWidget*>(wfe->widget());
    event->accept();
  }
}

bool SplitterArea::xIsBorder(SplitterWidgetBase* swb) const
{
  if(swb == (SplitterWidgetBase*)_topHandler ||
     swb == (SplitterWidgetBase*)_bottomHandler ||
     swb == (SplitterWidgetBase*)_leftHandler ||
     swb == (SplitterWidgetBase*)_rightHandler)
    return true;
  return false;
}

int SplitterArea::xVerticalHandlerIndex(SplitterHandler* handler) const
{
  if(handler == _leftHandler)
    return 0;

  if(handler == _rightHandler)
    return 1;

  int i = _verticalHandlers.indexOf(handler);
  if(i > -1)
    return i + 2;

  return -1;
}

int SplitterArea::xHorizontalHandlerIndex(SplitterHandler* handler) const
{
  if(handler == _topHandler)
    return 0;

  if(handler == _bottomHandler)
    return 1;

  int i = _horizontalHandlers.indexOf(handler);
  if(i > -1)
    return i + 2;

  return -1;
}

SplitterHandler* SplitterArea::xVerticalHandler(int index) const
{
  if(index == 0)
    return _leftHandler;

  if(index == 1)
    return _rightHandler;

  index -= 2;
  if(index < 0 || index >= _verticalHandlers.size())
    return NULL;

  return _verticalHandlers.at(index);
}

SplitterHandler* SplitterArea::xHorizontalHandler(int index) const
{
  if(index == 0)
    return _topHandler;

  if(index == 1)
    return _bottomHandler;

  index -= 2;
  if(index < 0 || index >= _horizontalHandlers.size())
    return NULL;

  return _horizontalHandlers.at(index);
}

SplitterHandler* SplitterArea::xCreateHandler(Qt::Orientation orientation) const
{
  return new SplitterHandler(orientation, const_cast<SplitterArea*>(this));
}

SplitterWidget* SplitterArea::xCreateWidget() const
{
  return new SplitterWidget(const_cast<SplitterArea*>(this));
}

void SplitterArea::xRecomputeMinimumSize()
{
  int widthCount = _leftHandler->maxWidgetNbrTo(_rightHandler);
  int minWidth = widthCount * _widgetMinimumSize + (widthCount+1) * _handlerThickness;
  int heightCount = _topHandler->maxWidgetNbrTo(_bottomHandler);
  int minHeight = heightCount * _widgetMinimumSize + (heightCount+1) * _handlerThickness;
  this->setMinimumSize(minWidth, minHeight);
}

} // namespace IDE
