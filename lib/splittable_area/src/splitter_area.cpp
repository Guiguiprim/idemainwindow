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

}

void SplitterArea::createSomeHandlers()
{
  SplitterHandler* hHandler = new SplitterHandler(Qt::Horizontal, this);
  hHandler->setPos(200);
  hHandler->setHandler(IDE::LEFT, _leftHandler);
  hHandler->setHandler(IDE::RIGHT, _rightHandler);
  _horizontalHandlers.append(hHandler);

  SplitterWidget* widget = new SplitterWidget(this);
  widget->setHandler(IDE::LEFT, _leftHandler);
  widget->setHandler(IDE::RIGHT, _rightHandler);
  widget->setHandler(IDE::TOP, hHandler);
  widget->setHandler(IDE::BOTTOM, _bottomHandler);
  _widgets.append(widget);

  SplitterHandler* vHandler = new SplitterHandler(Qt::Vertical, this);
  vHandler->setPos(200);
  vHandler->setHandler(IDE::TOP, _topHandler);
  vHandler->setHandler(IDE::BOTTOM, hHandler);
  _verticalHandlers.append(vHandler);

  widget = new SplitterWidget(this);
  widget->setColor("blue");
  widget->setHandler(IDE::LEFT, _leftHandler);
  widget->setHandler(IDE::RIGHT, vHandler);
  widget->setHandler(IDE::TOP, _topHandler);
  widget->setHandler(IDE::BOTTOM, hHandler);
  _widgets.append(widget);

  widget = new SplitterWidget(this);
  widget->setColor("green");
  widget->setHandler(IDE::LEFT, vHandler);
  widget->setHandler(IDE::RIGHT, _rightHandler);
  widget->setHandler(IDE::TOP, _topHandler);
  widget->setHandler(IDE::BOTTOM, hHandler);
  _widgets.append(widget);
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
  for(int i=0; i<_widgets.size(); ++i)
  {
    if(_widgets.at(i)->widget() = widget)
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

}

SplitterWidget* SplitterArea::horizontalSplit(
    int index,
    float proportion)
{

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
