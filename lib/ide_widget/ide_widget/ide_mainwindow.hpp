#ifndef IDE_IDE_MAINWINDOW_HPP
#define IDE_IDE_MAINWINDOW_HPP

#include "api.hpp"
#include <QMainWindow>

class QToolBar;

namespace IDE
{
class BottomPanel;
class BottomPanelChooser;
class SidePanel;
class RecursiveSplitter;
typedef RecursiveSplitter EditorsArea;

class IDE_WIDGET_LIB_EXPORT IDEMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit IDEMainWindow(QWidget *parent = NULL);

private Q_SLOTS:
  void xChangeLeftVisibility();
  void xChangeRightVisibility();

protected:
  EditorsArea* _editorsArea;
  SidePanel* _leftPanel;
  SidePanel* _rightPanel;
  BottomPanel* _bottomPanel;

  QToolBar* _bottomToolBar;
  QAction* _leftVisibilityAction;
  QAction* _rightVisibilityAction;

  BottomPanelChooser* _bottomPanelChooser;
};

} // namespace IDE

#endif // IDE_IDE_MAINWINDOW_HPP
