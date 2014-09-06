#ifndef IDE_PANEL_WIDGET_HPP
#define IDE_PANEL_WIDGET_HPP

#include <QWidget>

namespace IDE
{

class PanelWidget : public QWidget
{
  Q_OBJECT
public:
  explicit PanelWidget(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_PANEL_WIDGET_HPP
