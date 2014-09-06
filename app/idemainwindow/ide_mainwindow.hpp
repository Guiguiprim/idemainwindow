#ifndef IDE_IDE_MAINWINDOW_HPP
#define IDE_IDE_MAINWINDOW_HPP

#include <QMainWindow>

namespace IDE
{
class BottomPanel;
class SidePanel;
class EditorsArea;

class IDEMainWindow : public QMainWindow
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
