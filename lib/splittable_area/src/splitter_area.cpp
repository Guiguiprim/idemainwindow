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

  _topHandler = new SplitterHandler(Qt::Horizontal, this);
  _bottomHandler = new SplitterHandler(Qt::Horizontal, this);
  _leftHandler = new SplitterHandler(Qt::Vertical, this);
  _rightHandler = new SplitterHandler(Qt::Vertical, this);

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

  SplitterWidget* widget = new SplitterWidget(this);
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
int SplitterArea::indexAt(QPoint pos) const
{

}
QWidget* SplitterArea::widgetAt(int index) const
{

}
QWidget* SplitterArea::widgetAt(QPoint pos) const
{

}
SplitterWidget* SplitterArea::splitterWidgetAt(int index) const
{

}
SplitterWidget* SplitterArea::splitterWidgetAt(QPoint pos) const
{

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

  SplitterHandler* newHandler = new SplitterHandler(Qt::Vertical, this);
  _verticalHandlers.append(newHandler);
  newHandler->setHandler(IDE::TOP, topHandler);
  newHandler->setHandler(IDE::BOTTOM, bottomHandler);

  int width = rightHandler->pos() - leftHandler->pos();
  int pos = leftHandler->pos() + width * proportion;
  newHandler->setPos(pos);

  sw->setHandler(IDE::RIGHT, newHandler);

  SplitterWidget* nsw = new SplitterWidget(this);
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

  SplitterHandler* newHandler = new SplitterHandler(Qt::Horizontal, this);
  _horizontalHandlers.append(newHandler);
  newHandler->setHandler(IDE::LEFT, leftHandler);
  newHandler->setHandler(IDE::RIGHT, rightHandler);

  int height = bottomHandler->pos() - topHandler->pos();
  int pos = topHandler->pos() + height * proportion;
  newHandler->setPos(pos);

  sw->setHandler(IDE::BOTTOM, newHandler);

  SplitterWidget* nsw = new SplitterWidget(this);
  _splitterWidgets.append(nsw);
  nsw->setHandler(IDE::TOP, newHandler);
  nsw->setHandler(IDE::BOTTOM, bottomHandler);
  nsw->setHandler(IDE::LEFT, leftHandler);
  nsw->setHandler(IDE::RIGHT, rightHandler);

  return nsw;
}

bool SplitterArea::add(
    QWidget* widget,
    int index,
    Qt::Orientation orientation,
    float proportion)
{

}

bool SplitterArea::insert(
    QWidget* widget,
    int index,
    Qt::Orientation orientation,
    float proportion)
{

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

} // namespace IDE
