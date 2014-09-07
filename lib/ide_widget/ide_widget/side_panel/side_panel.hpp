#ifndef IDE_SIDE_PANEL_HPP
#define IDE_SIDE_PANEL_HPP

#include "../api.hpp"
#include <ide_widget/commun/splitter.hpp>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT SidePanel : public Splitter
{
  Q_OBJECT
public:
  explicit SidePanel(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_SIDE_PANEL_HPP
