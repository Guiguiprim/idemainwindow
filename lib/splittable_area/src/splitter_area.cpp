#include <splittable_area/splitter_area.hpp>

#include <QResizeEvent>

#include <splittable_area/splitter_handler.hpp>

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

  _topHandler->show();
  _bottomHandler->show();
  _leftHandler->show();
  _rightHandler->show();
}

void SplitterArea::resizeEvent(QResizeEvent* event)
{
  float vFac = this->height() / event->oldSize().height();
  float hFac = this->width() / event->oldSize().width();

  Q_FOREACH(SplitterHandler* handler, _verticalHandler)
  {
    handler->setPos(handler->pos() * vFac);
  }

  Q_FOREACH(SplitterHandler* handler, _horizontalHandler)
  {
    handler->setPos(handler->pos() * hFac);
  }

  _bottomHandler->setPos(this->height() - _bottomHandler->thickness());
  _rightHandler->setPos(this->width() - _rightHandler->thickness());
}

} // namespace IDE
