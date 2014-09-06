#ifndef IDE_SIDE_PANEL_HPP
#define IDE_SIDE_PANEL_HPP

#include <QWidget>

namespace IDE
{

class SidePanel : public QWidget
{
  Q_OBJECT
public:
  explicit SidePanel(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_SIDE_PANEL_HPP
