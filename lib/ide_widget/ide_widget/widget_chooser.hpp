#ifndef IDE_WIDGET_CHOOSER_HPP
#define IDE_WIDGET_CHOOSER_HPP

#include <QWidget>

namespace IDE
{

class WidgetChooser : public QWidget
{
  Q_OBJECT
public:
  explicit WidgetChooser(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_WIDGET_CHOOSER_HPP
