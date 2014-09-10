#ifndef IDE_SPLITTER_AREA_HPP
#define IDE_SPLITTER_AREA_HPP

#include <QWidget>

#include <QList>

// inspiration http://qt-project.org/wiki/Widget-moveable-and-resizeable ??

namespace IDE
{
class SplitterHandler;
class SplitterWidget;

class SplitterArea : public QWidget
{
  Q_OBJECT
public:
  SplitterArea(QWidget *parent = NULL);

  void createSomeHandlers();

protected:
  virtual void resizeEvent(QResizeEvent* event);

private:
  SplitterHandler* _topHandler;
  SplitterHandler* _bottomHandler;
  SplitterHandler* _leftHandler;
  SplitterHandler* _rightHandler;

  QList<SplitterHandler*> _verticalHandlers;
  QList<SplitterHandler*> _horizontalHandlers;
  QList<SplitterWidget*> _widgets;
};

} // namespace IDE

#endif // IDE_SPLITTER_AREA_HPP
