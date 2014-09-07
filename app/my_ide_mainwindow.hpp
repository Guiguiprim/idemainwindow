#ifndef IDE_MY_IDE_MAINWINDOW_HPP
#define IDE_MY_IDE_MAINWINDOW_HPP

#include <ide_widget/ide_mainwindow.hpp>

namespace IDE
{

class MyIdeMainWindow : public IDEMainWindow
{
  Q_OBJECT
public:
  explicit MyIdeMainWindow(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_MY_IDE_MAINWINDOW_HPP
