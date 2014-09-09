#include <splittable_area/splitter_handler.hpp>

#include <QApplication>
#include <QPainter>
#include <QPaintEvent>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

namespace IDE
{

SplitterHandler::SplitterHandler(Qt::Orientation orientation, SplitterArea* splitterArea)
  : SplitterWidgetBase(splitterArea)
  , _orientation(orientation)
  , _thickness(5)
  , _movable(true)
  , _pos(0)
{
  this->setVisible(true);
  this->setMouseTracking(true);
  this->move(0,0);

  _gradient.setColorAt(0, QColor(200,200,200));
  _gradient.setColorAt(0.5, QColor(50,50,50));
  _gradient.setColorAt(1, QColor(200,200,200));
  this->resize(_thickness, _thickness);
}

Qt::Orientation SplitterHandler::orientation() const
{
  return _orientation;
}

int SplitterHandler::thickness() const
{
  return _thickness;
}

bool SplitterHandler::movable() const
{
  return _movable;
}

void SplitterHandler::setMovable(bool movable)
{
  _movable = movable;
}

int SplitterHandler::pos() const
{
  return _pos;
}

void SplitterHandler::setPos(int pos)
{
  if(pos != _pos)
  {
    _pos = pos;
    if(_orientation == Qt::Horizontal)
    {
      this->move(this->QWidget::pos().x(), _pos);
      QMap<SplitterWidgetBase*, SplitterSide>::iterator it;
      for(it = _handleWidgets.begin(); it != _handleWidgets.end(); ++it)
      {
        if(it.value() == IDE::TOP)
          it.key()->setTopPos(_pos + _thickness);
        else if(it.value() == IDE::BOTTOM)
          it.key()->setBottomPos(_pos);
      }
    }
    else
    {
      this->move(_pos, this->QWidget::pos().y());
      QMap<SplitterWidgetBase*, SplitterSide>::iterator it;
      for(it = _handleWidgets.begin(); it != _handleWidgets.end(); ++it)
      {
        if(it.value() == IDE::LEFT)
          it.key()->setLeftPos(_pos + _thickness);
        else if(it.value() == IDE::RIGHT)
          it.key()->setRightPos(_pos);
      }
    }
  }
}

void SplitterHandler::addHandleWidget(SplitterSide side, SplitterWidgetBase* widget)
{
  if(!widget)
    return;

  if(_orientation == Qt::Horizontal)
  {
    if(side == IDE::BOTTOM || side == IDE::TOP)
    {
      _handleWidgets[widget] = side;
      connect(widget, SIGNAL(destroyed(QObject*)),
              this, SLOT(xOnWidgetDestroy(QObject*)),
              Qt::UniqueConnection);
      if(side == IDE::TOP)
        widget->setTopPos(_pos + _thickness);
      else if(side == IDE::BOTTOM)
        widget->setBottomPos(_pos);
    }
  }
  else
  {
    if(side == IDE::LEFT || side == IDE::RIGHT)
    {
      _handleWidgets[widget] = side;
      connect(widget, SIGNAL(destroyed(QObject*)),
              this, SLOT(xOnWidgetDestroy(QObject*)),
              Qt::UniqueConnection);
      if(side == IDE::LEFT)
        widget->setLeftPos(_pos + _thickness);
      else if(side == IDE::RIGHT)
        widget->setRightPos(_pos);
    }
  }
}

void SplitterHandler::removeHandleWidget(SplitterWidgetBase* widget)
{
  _handleWidgets.remove(widget);
  disconnect(widget, SIGNAL(destroyed(QObject*)),
             this, SLOT(xOnWidgetDestroy(QObject*)));
}

void SplitterHandler::setHandler(SplitterSide side, SplitterHandler* handler)
{
  if(_orientation == Qt::Horizontal)
  {
    if(side == IDE::LEFT || side == IDE::RIGHT)
    {
      SplitterWidgetBase::setHandler(side, handler);
    }
  }
  else
  {
    if(side == IDE::BOTTOM || side == IDE::TOP)
    {
      SplitterWidgetBase::setHandler(side, handler);
    }
  }
}

void SplitterHandler::xOnWidgetDestroy(QObject* obj)
{
  _handleWidgets.remove(static_cast<SplitterWidgetBase*>(obj));
}

void SplitterHandler::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  if (orientation() == Qt::Vertical) {
      _gradient.setStart(rect().left(), rect().height()/2);
      _gradient.setFinalStop(rect().right(), rect().height()/2);
  } else {
      _gradient.setStart(rect().width()/2, rect().top());
      _gradient.setFinalStop(rect().width()/2, rect().bottom());
  }
  //painter.fillRect(event->rect(), QBrush(_gradient));
  painter.fillRect(event->rect(), QBrush(Qt::red));
}

} // namespace IDE
