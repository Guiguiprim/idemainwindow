#ifndef IDE_WIDGET_CHOOSER_HPP
#define IDE_WIDGET_CHOOSER_HPP

#include "../api.hpp"
#include <QWidget>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT WidgetChooser : public QWidget
{
  Q_OBJECT
public:
  explicit WidgetChooser(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_WIDGET_CHOOSER_HPP
