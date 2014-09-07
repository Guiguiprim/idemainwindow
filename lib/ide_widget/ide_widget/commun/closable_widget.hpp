#ifndef IDE_CLOSABLE_WIDGET_HPP
#define IDE_CLOSABLE_WIDGET_HPP

#include "../api.hpp"
#include <QWidget>

class QHBoxLayout;
class QMenu;
class QToolBar;
class QToolButton;
class QVBoxLayout;

namespace IDE
{
class ClosableWidgetElement;

class IDE_WIDGET_LIB_EXPORT ClosableWidget : public QWidget
{
  Q_OBJECT
public:
  enum SplitConfig {
    NoSplit,
    VSplit,
    Split,
    SplitAndNewWindow
  };

public:
  explicit ClosableWidget(SplitConfig splitConfig = NoSplit, QWidget *parent = NULL);
  ~ClosableWidget();

  SplitConfig splitConfig() const;
  void setSplitConfig(SplitConfig splitConfig);

  void enableUnsplit(bool enable, Qt::Orientation orientation = Qt::Horizontal);

  QWidget* widget() const;
  void setWidget(QWidget* widget, bool deleteOld = false);
  void setWidget(ClosableWidgetElement* widget, bool deleteOld = false);

  void addToolBarAction(QAction* action);

private Q_SLOTS:
  void emitEvent();

private:
  SplitConfig _splitConfig;
  QHBoxLayout* _toolBarLayout;
  //QToolBar* _toolBarChooser;
  QToolBar* _toolBar;
  QToolBar* _toolBarEnd;

  QVBoxLayout* _layout;
  QWidget* _widget;

  QAction* _close;
  QAction* _unsplitAction;
  QAction* _vSplitAction;
  QAction* _hSplitAction;
  QAction* _newWindowAction;
  QAction* _splitActions;
  QMenu* _splitMenu;
};

} // namespace IDE

#endif // IDE_CLOSABLE_WIDGET_HPP
