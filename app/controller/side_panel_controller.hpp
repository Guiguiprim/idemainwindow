#ifndef IDE_SIDE_PANEL_CONTROLLER_HPP
#define IDE_SIDE_PANEL_CONTROLLER_HPP

#include <QObject>

namespace IDE
{
class ClosableWidget;
class SidePanel;

class SidePanelController : public QObject
{
  Q_OBJECT
public:
  explicit SidePanelController(SidePanel* sidePanel, QObject *parent = NULL);

  virtual bool eventFilter(
      QObject* watched,
      QEvent* event);

  virtual ClosableWidget* newClosableWidget() const;

private:
  SidePanel* _sidePanel;
};

} // namespace IDE

#endif // IDE_SIDE_PANEL_CONTROLLER_HPP
