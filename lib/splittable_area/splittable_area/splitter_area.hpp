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

  QByteArray saveConfig() const;
  bool loadConfig(QByteArray config);

  int indexOf(QWidget* widget) const;
  int indexAt(QPoint pos) const; // local pos
  QWidget* widgetAt(int index) const;
  QWidget* widgetAt(QPoint pos) const; // local pos
  SplitterWidget* splitterWidgetAt(int index) const;
  SplitterWidget* splitterWidgetAt(QPoint pos) const; // local pos

  SplitterWidget* verticalSplit(
      int index,
      float proportion = 0.5f);
  SplitterWidget* horizontalSplit(
      int index,
      float proportion = 0.5f);

  bool add(
      QWidget* widget,
      int index,
      Qt::Orientation orientation,
      float proportion = 0.5f);
  bool insert(
      QWidget* widget,
      int index,
      Qt::Orientation orientation,
      float proportion = 0.5f);

protected:
  virtual void resizeEvent(QResizeEvent* event);

private:
  /**
   * @brief xVerticalHandlerIndex
   * @param handler: Handler which index we want
   * @return
   *   -1 if not found
   *   0 if it's the left handler
   *   1 if it's the left handler
   *   else a value > 1 ( = list index + 2 )
   */
  int xVerticalHandlerIndex(SplitterHandler* handler) const;
  int xHorizontalHandlerIndex(SplitterHandler* handler) const;

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
