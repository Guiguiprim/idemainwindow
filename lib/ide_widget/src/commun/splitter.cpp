#include <ide_widget/commun/splitter.hpp>

#include <QPainter>
#include <QPaintEvent>

namespace IDE
{

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter* parent)
  : QSplitterHandle(orientation, parent)
{
  _gradient.setColorAt(0, QColor(200,200,200));
  _gradient.setColorAt(0.5, QColor(50,50,50));
  _gradient.setColorAt(1, QColor(200,200,200));
}

void SplitterHandle::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  if (orientation() == Qt::Vertical) {
      _gradient.setStart(rect().left(), rect().height()/2);
      _gradient.setFinalStop(rect().right(), rect().height()/2);
  } else {
      _gradient.setStart(rect().width()/2, rect().top());
      _gradient.setFinalStop(rect().width()/2, rect().bottom());
  }
  painter.fillRect(event->rect(), QBrush(_gradient));
}

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
  : QSplitter(orientation, parent)
{
  this->setHandleWidth(2);
}

QSplitterHandle* Splitter::createHandle()
{
  return new SplitterHandle(orientation(), this);
}

} // namespace IDE
