#ifndef IDE_SPLITTER_WIDGET_BASE_HPP
#define IDE_SPLITTER_WIDGET_BASE_HPP

#include <QWidget>

#include <splittable_area/splitter_enum.hpp>

namespace IDE
{
class SplitterArea;
class SplitterHandler;

class SplitterWidgetBase : public QWidget
{
  Q_OBJECT
public:
  SplitterWidgetBase(SplitterArea *splitterArea = NULL);

  SplitterHandler* handler(SplitterSide side) const;

public Q_SLOTS:
  void setPos(int left, int top, int right, int bottom);
  void setTopPos(int top);
  void setBottomPos(int bottom);
  void setLeftPos(int left);
  void setRightPos(int right);

  virtual void setHandler(SplitterSide side, SplitterHandler* handler);

private Q_SLOTS:
  void xOnHandlerDestroy(QObject* obj);

protected:
  SplitterArea* _splitterArea;
  SplitterHandler* _handlers[4];
};

} // namespace IDE

#endif // IDE_SPLITTER_WIDGET_BASE_HPP
