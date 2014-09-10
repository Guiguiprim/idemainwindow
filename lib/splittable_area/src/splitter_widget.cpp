#include <splittable_area/splitter_widget.hpp>

#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include <QVBoxLayout>

#include <splittable_area/splitter_area.hpp>

namespace IDE
{

SplitterWidget::SplitterWidget(SplitterArea* splitterArea)
  : SplitterWidgetBase(splitterArea)
  , _srcollArea(NULL)
{
  _srcollArea = new QScrollArea;

  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->setMargin(0);
  lyt->addWidget(_srcollArea);
  _srcollArea->setStyleSheet("background:red");
}

void SplitterWidget::setColor(const QString& color)
{
  _srcollArea->setStyleSheet("background:" + color);
}

void SplitterWidget::setWidget(QWidget* widget)
{
  _srcollArea->setWidget(widget);
}

QWidget* SplitterWidget::widget() const
{
  return _srcollArea->widget();
}

QWidget* SplitterWidget::takeWidget() const
{
  return _srcollArea->takeWidget();
}

} // namespace IDE
