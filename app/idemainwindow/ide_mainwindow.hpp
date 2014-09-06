#ifndef IDE_IDE_MAINWINDOW_HPP
#define IDE_IDE_MAINWINDOW_HPP

#include <QMainWindow>

namespace IDE
{

class IDEMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit IDEMainWindow(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_IDE_MAINWINDOW_HPP
