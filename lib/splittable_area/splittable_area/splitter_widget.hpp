#ifndef IDE_SPLITTER_WIDGET_HPP
#define IDE_SPLITTER_WIDGET_HPP

#include <splittable_area/splitter_widget_base.hpp>

class QScrollArea;

namespace IDE
{
class SplitterArea;

class SplitterWidget : public SplitterWidgetBase
{
  Q_OBJECT
public:
  SplitterWidget(SplitterArea *splitterArea = NULL);

  void setColor(const QString& color);

  void setWidget(QWidget* widget);
  QWidget* widget() const;

private:
  QScrollArea* _srcollArea;
};

} // namespace IDE

#endif // IDE_SPLITTER_WIDGET_HPP
