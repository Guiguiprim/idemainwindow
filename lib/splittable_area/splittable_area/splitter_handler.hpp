#ifndef IDE_SPLITTER_HANDLER_HPP
#define IDE_SPLITTER_HANDLER_HPP

#include <splittable_area/splitter_widget_base.hpp>

#include <QLinearGradient>
#include <QMap>

namespace IDE
{
class SplitterArea;
class SplitterWidget;

/**
 * If orientation == Vertical
 *    * start / side_1 = top
 *    * end / side_2 = bottom
 *
 * If orientation == Horizontal
 *    * start / side_1 = left
 *    * end / side_2 = right
 */


class SplitterHandler : public SplitterWidgetBase
{
  Q_OBJECT
public:
  SplitterHandler(Qt::Orientation orientation, SplitterArea *splitterArea);

  Qt::Orientation orientation() const;
  int thickness() const;

  bool movable() const;
  void setMovable(bool movable);

  int pos() const;

public Q_SLOTS:
  void setPos(int pos);
  /**
   * @brief addHandleWidget
   * @param side: the side is relative to the widget !!
   * @param widget
   */
  void addHandleWidget(SplitterSide side, SplitterWidgetBase* widget);
  void removeHandleWidget(SplitterWidgetBase* widget);

  virtual void setHandler(SplitterSide side, SplitterHandler* handler);

private Q_SLOTS:
  void xOnWidgetDestroy(QObject* obj);

protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void contextMenuEvent(QContextMenuEvent* event);
  virtual void enterEvent(QEvent* event);
  virtual void leaveEvent(QEvent* event);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);

private:
  QLinearGradient _gradient;
  Qt::Orientation _orientation;
  int _thickness;
  bool _movable;
  int _pos;

  bool _isBeingDrag;

  QMap<SplitterWidgetBase*, SplitterSide> _handleWidgets;
};

} // namespace IDE

#endif // IDE_SPLITTER_HANDLER_HPP
