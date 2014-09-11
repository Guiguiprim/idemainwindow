#ifndef IDE_MAIN_WINDOW_HPP
#define IDE_MAIN_WINDOW_HPP

#include <QMainWindow>

namespace IDE
{

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = NULL);


};

} // namespace IDE

#endif // IDE_MAIN_WINDOW_HPP
