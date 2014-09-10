#include <splittable_area/splitter_widget.hpp>

#include <QPainter>
#include <QPaintEvent>

#include <splittable_area/splitter_area.hpp>

namespace IDE
{

SplitterWidget::SplitterWidget(SplitterArea* splitterArea)
  : SplitterWidgetBase(splitterArea)
  , _color(Qt::red)
{
}

void SplitterWidget::setColor(QColor color)
{
  _color = color;
  this->update();
}

void SplitterWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.fillRect(event->rect(), QBrush(_color));
}

} // namespace IDE
