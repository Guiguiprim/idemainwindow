#ifndef IDE_CLOSABLE_WIDGET_HPP
#define IDE_CLOSABLE_WIDGET_HPP

#include <QWidget>

class QHBoxLayout;
class QToolBar;
class QVBoxLayout;

namespace IDE
{
class ClosableWidgetElement;

class ClosableWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ClosableWidget(QWidget *parent = NULL);
  ~ClosableWidget();

  bool isVSplitEnable() const;
  bool isHSplitEnable() const;
  bool isWSplitEnable() const;
  void setVSplitEnable(bool enable);
  void setHSplitEnable(bool enable);
  void setWSplitEnable(bool enable);

  QWidget* widget() const;
  void setWidget(QWidget* widget, bool takeOwnership = false);
  void setWidget(ClosableWidgetElement* widget, bool takeOwnership = false);

  void addToolBarAction(QAction* action);

Q_SIGNALS:
  void closeTriggered();
  void vSplitTriggered();
  void hSplitTriggered();
  void wSplitTriggered();

private:
  QHBoxLayout* _toolBarLayout;
  //QToolBar* _toolBarChooser;
  QToolBar* _toolBar;
  QToolBar* _toolBarEnd;

  QVBoxLayout* _layout;
  QWidget* _widget;
  bool _hasOwnership;

  QAction* _vSplitAction;
  QAction* _hSplitAction;
  QAction* _wSplitAction;
};

} // namespace IDE

#endif // IDE_CLOSABLE_WIDGET_HPP
