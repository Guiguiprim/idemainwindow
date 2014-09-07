#ifndef IDE_IDE_MAINWINDOW_HPP
#define IDE_IDE_MAINWINDOW_HPP

#include "api.hpp"
#include <QMainWindow>

namespace IDE
{
class BottomPanel;
class SidePanel;
class RecursiveSplitter;
typedef RecursiveSplitter EditorsArea;

class IDE_WIDGET_LIB_EXPORT IDEMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit IDEMainWindow(QWidget *parent = NULL);

private:
  EditorsArea* _editorsArea;
  SidePanel* _leftPanel;
  SidePanel* _rightPanel;
  BottomPanel* _bottomPanel;
};

} // namespace IDE

#endif // IDE_IDE_MAINWINDOW_HPP
