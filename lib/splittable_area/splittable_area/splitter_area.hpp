#ifndef IDE_SPLITTER_AREA_HPP
#define IDE_SPLITTER_AREA_HPP

#include <QWidget>

#include <QList>

// inspiration http://qt-project.org/wiki/Widget-moveable-and-resizeable ??

namespace IDE
{
class SplitterHandler;

class SplitterArea : public QWidget
{
  Q_OBJECT
public:
  SplitterArea(QWidget *parent = NULL);

protected:
  virtual void resizeEvent(QResizeEvent* event);

private:
  SplitterHandler* _topHandler;
  SplitterHandler* _bottomHandler;
  SplitterHandler* _leftHandler;
  SplitterHandler* _rightHandler;

  QList<SplitterHandler*> _verticalHandler;
  QList<SplitterHandler*> _horizontalHandler;
};

} // namespace IDE

#endif // IDE_SPLITTER_AREA_HPP
