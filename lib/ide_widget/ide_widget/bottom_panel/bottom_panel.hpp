#ifndef IDE_BOTTOM_PANEL_HPP
#define IDE_BOTTOM_PANEL_HPP

#include "../api.hpp"
#include <ide_widget/commun/closable_widget.hpp>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT BottomPanel : public ClosableWidget
{
  Q_OBJECT
public:
  explicit BottomPanel(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_BOTTOM_PANEL_HPP
