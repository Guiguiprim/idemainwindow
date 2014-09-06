#ifndef IDE_SIDE_PANEL_ITEM_HPP
#define IDE_SIDE_PANEL_ITEM_HPP

#include <QWidget>

namespace IDE
{

class SidePanelItem : public QWidget
{
  Q_OBJECT
public:
  explicit SidePanelItem(QWidget *parent = NULL);


};

} // namespace IDE

#endif // IDE_SIDE_PANEL_ITEM_HPP
