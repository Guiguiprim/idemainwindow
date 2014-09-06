#ifndef IDE_BOTTOM_PANEL_HPP
#define IDE_BOTTOM_PANEL_HPP

#include <QWidget>

namespace IDE
{

class BottomPanel : public QWidget
{
  Q_OBJECT
public:
  explicit BottomPanel(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_BOTTOM_PANEL_HPP
