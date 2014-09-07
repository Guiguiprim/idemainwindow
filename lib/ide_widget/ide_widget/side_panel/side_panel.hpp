#ifndef IDE_SIDE_PANEL_HPP
#define IDE_SIDE_PANEL_HPP

#include "../api.hpp"
#include <QWidget>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT SidePanel : public QWidget
{
  Q_OBJECT
public:
  explicit SidePanel(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_SIDE_PANEL_HPP
