#ifndef IDE_DUMMY_CLOSABLE_WIDGET_ELEMENT_HPP
#define IDE_DUMMY_CLOSABLE_WIDGET_ELEMENT_HPP

#include <ide_widget/commun/closable_widget_element.hpp>

namespace IDE
{

class DCW1 : public ClosableWidgetElement
{
public:
  explicit DCW1(QWidget *parent = NULL);
};

class DCW2 : public ClosableWidgetElement
{
public:
  explicit DCW2(QWidget *parent = NULL);
};

class DCW3 : public ClosableWidgetElement
{
public:
  explicit DCW3(QWidget *parent = NULL);
};

} // namespace IDE

#endif // IDE_DUMMY_CLOSABLE_WIDGET_ELEMENT_HPP
