#ifndef IDE_SPLITTER_WIDGET_HPP
#define IDE_SPLITTER_WIDGET_HPP

#include <splittable_area/splitter_widget_base.hpp>


namespace IDE
{
class SplitterArea;

class SplitterWidget : public SplitterWidgetBase
{
  Q_OBJECT
public:
  SplitterWidget(SplitterArea *splitterArea = NULL);


};

} // namespace IDE

#endif // IDE_SPLITTER_WIDGET_HPP
