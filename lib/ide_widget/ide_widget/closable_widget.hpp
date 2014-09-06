#ifndef IDE_CLOSABLE_WIDGET_HPP
#define IDE_CLOSABLE_WIDGET_HPP

#include <QWidget>

class QHBoxLayout;
class QMenu;
class QToolBar;
class QToolButton;
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
  void setWidget(QWidget* widget, bool deleteOld = false);
  void setWidget(ClosableWidgetElement* widget, bool deleteOld = false);

  void addToolBarAction(QAction* action);

private Q_SLOTS:
  void emitEvent();

private:
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
  QToolButton* _toolButton;
  QMenu* _splitMenu;
};

} // namespace IDE

#endif // IDE_CLOSABLE_WIDGET_HPP
