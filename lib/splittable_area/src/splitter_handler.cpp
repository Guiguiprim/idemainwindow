#include <splittable_area/splitter_handler.hpp>

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

namespace IDE
{

SplitterHandler::SplitterHandler(Qt::Orientation orientation, SplitterArea* splitterArea)
  : SplitterWidgetBase(splitterArea)
  , _orientation(orientation)
  , _thickness(3)
  , _movable(true)
  , _pos(0)
  , _isBeingDrag(false)
{
  this->setVisible(true);
  this->setMouseTracking(true);
  this->move(0,0);

  _gradient.setColorAt(0, QColor(200,200,200));
  _gradient.setColorAt(0.5, QColor(50,50,50));
  _gradient.setColorAt(1, QColor(200,200,200));
  this->resize(_thickness, _thickness);

  if(_movable)
  {
    if(_orientation == Qt::Horizontal)
      this->setCursor(Qt::SizeVerCursor);
    else
      this->setCursor(Qt::SizeHorCursor);
  }
  else
    this->setCursor(Qt::ArrowCursor);
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
  if(_movable != movable)
  {
    _movable = movable;
    if(_movable)
    {
      if(_orientation == Qt::Horizontal)
        this->setCursor(Qt::SizeVerCursor);
      else
        this->setCursor(Qt::SizeHorCursor);
    }
    else
      this->setCursor(Qt::ArrowCursor);
  }
}

int SplitterHandler::pos() const
{
  return _pos;
}

QVector<SplitterWidgetBase*> SplitterHandler::handleWidgetsBase(SplitterSide side) const
{
  QVector<SplitterWidgetBase*> result;
  QMap<SplitterWidgetBase*, SplitterSide>::const_iterator it;
  for(it = _handleWidgets.begin(); it != _handleWidgets.end(); ++it)
  {
    if(it.value() == side)
      result.append(it.key());
  }
  return result;
}

int SplitterHandler::maxWidgetNbrTo(SplitterHandler* handler) const
{
  if(handler == this)
    return 0;

  QVector<SplitterWidgetBase*> swbs;
  SplitterSide otherSide;
  if(this->orientation() == Qt::Vertical)
  {
    swbs = this->handleWidgetsBase(IDE::LEFT);
    otherSide = IDE::RIGHT;
  }
  else
  {
    swbs = this->handleWidgetsBase(IDE::TOP);
    otherSide = IDE::BOTTOM;
  }

  int max = -1;
  Q_FOREACH(SplitterWidgetBase* swb, swbs)
  {
    SplitterWidget* sw = dynamic_cast<SplitterWidget*>(swb);
    if(sw)
    {
      SplitterHandler* sh = sw->handler(otherSide);
      if(sh)
      {
        int val = sh->maxWidgetNbrTo(handler);
        if(val > -1 && val + 1 > max)
          max = val + 1;
      }
    }
  }
  return max;
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
  painter.fillRect(event->rect(), QBrush(Qt::black));
  /*if (orientation() == Qt::Horizontal) {
      _gradient.setStart(rect().left(), rect().height()/2);
      _gradient.setFinalStop(rect().right(), rect().height()/2);
  } else {
      _gradient.setStart(rect().width()/2, rect().top());
      _gradient.setFinalStop(rect().width()/2, rect().bottom());
  }
  painter.fillRect(event->rect(), QBrush(_gradient));*/
}

void SplitterHandler::contextMenuEvent(QContextMenuEvent* event)
{
  QWidget::contextMenuEvent(event);
}

void SplitterHandler::enterEvent(QEvent* event)
{
  QWidget::enterEvent(event);
}

void SplitterHandler::leaveEvent(QEvent* event)
{
  QWidget::leaveEvent(event);
}

void SplitterHandler::mousePressEvent(QMouseEvent* event)
{
  if(event->button() == Qt::LeftButton)
  {
    _isBeingDrag = true;
    event->accept();
  }
}

void SplitterHandler::mouseReleaseEvent(QMouseEvent* event)
{
  if(event->button() == Qt::LeftButton)
  {
    _isBeingDrag = false;
    event->accept();
  }
}

void SplitterHandler::mouseMoveEvent(QMouseEvent* event)
{
  if(_isBeingDrag)
  {
    //@TODO : Handle move limitation:
    // should be block by other handler (+ min spacing)
    // => splitter area should compute minimum size
    int to;
    if(_orientation == Qt::Horizontal)
      to = _splitterArea->mapFromGlobal(event->globalPos()).y();
    else
      to = _splitterArea->mapFromGlobal(event->globalPos()).x();
    this->setPos(to);

    event->accept();
  }
}

} // namespace IDE
