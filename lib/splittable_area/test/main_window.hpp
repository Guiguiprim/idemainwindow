#ifndef IDE_MAIN_WINDOW_HPP
#define IDE_MAIN_WINDOW_HPP

#include <QMainWindow>

namespace IDE
{
class SplitterArea;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = NULL);

private Q_SLOTS:
  void onVerticalSplit();
  void onHorizontalSplit();
  void onLeftSplit();
  void onRightSplit();
  void onTopSplit();
  void onBottomSplit();
  void onRemoveCurrent();

private:
  int _i;
  SplitterArea* _splittableArea;

  QAction* _verticalSplit;
  QAction* _horizontalSplit;
  QAction* _leftSplit;
  QAction* _rightSplit;
  QAction* _topSplit;
  QAction* _bottomSplit;
  QAction* _removeCurrent;
};

} // namespace IDE

#endif // IDE_MAIN_WINDOW_HPP
