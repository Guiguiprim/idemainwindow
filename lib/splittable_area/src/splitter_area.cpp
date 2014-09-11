#include <splittable_area/splitter_area.hpp>

#include <QResizeEvent>

#include <splittable_area/splitter_handler.hpp>
#include <splittable_area/splitter_widget.hpp>

namespace IDE
{

SplitterArea::SplitterArea(QWidget* parent)
  : QWidget(parent)
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

  _bottomHandler->setPos(this->height() - _bottomHandler->thickness());
  _bottomHandler->setMovable(false);
  _bottomHandler->setHandler(IDE::LEFT, _leftHandler);
  _bottomHandler->setHandler(IDE::RIGHT, _rightHandler);

  _leftHandler->setPos(0);
  _leftHandler->setMovable(false);
  _leftHandler->setHandler(IDE::TOP, _topHandler);
  _leftHandler->setHandler(IDE::BOTTOM, _bottomHandler);

  _rightHandler->setPos(this->width() - _rightHandler->thickness());
  _rightHandler->setMovable(false);
  _rightHandler->setHandler(IDE::TOP, _topHandler);
  _rightHandler->setHandler(IDE::BOTTOM, _bottomHandler);

  SplitterWidget* widget = xCreateWidget();
  _splitterWidgets.append(widget);
  widget->setHandler(IDE::TOP, _topHandler);
  widget->setHandler(IDE::BOTTOM, _bottomHandler);
  widget->setHandler(IDE::LEFT, _leftHandler);
  widget->setHandler(IDE::RIGHT, _rightHandler);
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
  if(pos.x() < _leftHandler->thickness())
    pos.setX(_leftHandler->thickness() + 1);
  else if(pos.x() > this->width() - _rightHandler->thickness())
    pos.setX(this->width() - _rightHandler->thickness() - 1);

  if(pos.y() < _topHandler->thickness())
    pos.setY(_topHandler->thickness() + 1);
  else if(pos.y() > this->height() - _bottomHandler->thickness())
    pos.setY(this->height() - _bottomHandler->thickness() - 1);

  QWidget* w = this->QWidget::childAt(pos);
  SplitterWidget* sw = dynamic_cast<SplitterWidget*>(w);
  if(sw)
    return sw;

  SplitterHandler* sh = dynamic_cast<SplitterHandler*>(w);
  if(sh) // we hit a handler let move a little bit
  {
    if(sh->orientation() == Qt::Vertical)
      pos.setX(pos.x() - sh->thickness());
    else
      pos.setY(pos.y() - sh->thickness());

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

  return nsw;
}

bool SplitterArea::addWidget(
    QWidget* widget,
    int index,
    Qt::Orientation orientation,
    float proportion)
{
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
    QWidget* widget,
    int index,
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

void SplitterArea::resizeEvent(QResizeEvent* event)
{
  if(!this->isVisible())
    return;

  float vFac = this->height() / event->oldSize().height();
  float hFac = this->width() / event->oldSize().width();

  Q_FOREACH(SplitterHandler* handler, _verticalHandlers)
  {
    handler->setPos(handler->pos() * vFac);
  }

  Q_FOREACH(SplitterHandler* handler, _horizontalHandlers)
  {
    handler->setPos(handler->pos() * hFac);
  }

  _bottomHandler->setPos(this->height() - _bottomHandler->thickness());
  _rightHandler->setPos(this->width() - _rightHandler->thickness());
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


SplitterHandler* SplitterArea::xCreateHandler(Qt::Orientation orientation) const
{
  return new SplitterHandler(orientation, const_cast<SplitterArea*>(this));
}

SplitterWidget* SplitterArea::xCreateWidget() const
{
  return new SplitterWidget(const_cast<SplitterArea*>(this));
}

} // namespace IDE
