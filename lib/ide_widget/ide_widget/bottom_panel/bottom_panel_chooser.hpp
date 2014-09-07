#ifndef IDE_BOTTOM_PANEL_CHOOSER_HPP
#define IDE_BOTTOM_PANEL_CHOOSER_HPP

#include <QToolBar>
#include <QMap>

class QMenu;

namespace IDE
{
class BottomPanel;

class BottomPanelChooser : public QToolBar
{
  Q_OBJECT
public:
  struct WidgetAction {
    QAction* openAction;
    QAction* displayAction;
    WidgetAction() : openAction(NULL), displayAction(NULL) {}
    ~WidgetAction();
  };

public:
  explicit BottomPanelChooser(BottomPanel* bottomPanel, QWidget *parent = NULL);
  ~BottomPanelChooser();

private Q_SLOTS:

private:
  BottomPanel* _bottomPanel;
  QMenu* _splitMenu;
  QAction* _menuAction;
  QMap<QWidget*, WidgetAction*> _widgetActions;
};

} // namespace IDE

#endif // IDE_BOTTOM_PANEL_CHOOSER_HPP
