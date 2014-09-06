#include <ide_widget/closable_widget.hpp>

#include <QAction>
#include <QHBoxLayout>
#include <QToolBar>
#include <QStyle>
#include <QVBoxLayout>

#include <ide_widget/closable_widget_element.hpp>

namespace IDE
{

ClosableWidget::ClosableWidget(
    QWidget *parent)
  : QWidget(parent)
  , _toolBarLayout(new QHBoxLayout)
  , _toolBar(new QToolBar)
  , _toolBarEnd(new QToolBar)
  , _layout(new QVBoxLayout(this))
  , _widget(new QWidget)
  , _vSplitAction(NULL)
  , _hSplitAction(NULL)
  , _wSplitAction(NULL)
{
  _layout->setMargin(0);
  _layout->setSpacing(0);
  _layout->addLayout(_toolBarLayout);
  _layout->addWidget(_widget);

  _toolBarLayout->setMargin(0);
  _toolBarLayout->setSpacing(0);
  //_toolBarLayout->addWidget(_toolBarChooser);
  _toolBarLayout->addWidget(_toolBar);
  _toolBarLayout->addWidget(_toolBarEnd);

  _toolBar->setIconSize(QSize(16,16));
  _toolBar->setStyleSheet("QToolBar { spacing: 0px;"
                          "background: qlineargradient(y1:0, y2:1, stop: 0 #AAAAAA, stop: 1.0 #8A8A8A);"
                          "color: darkgray;"
                          "}");
  _toolBarEnd->setIconSize(QSize(16,16));
  _toolBarEnd->setStyleSheet("QToolBar { spacing: 0px;"
                             "background: qlineargradient(y1:0, y2:1, stop: 0 #AAAAAA, stop: 1.0 #8A8A8A);"
                             "color: darkgray;"
                             "}");

  QAction* close = new QAction(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton),
                               "Close", this);
  connect(close, SIGNAL(triggered()),
          this, SIGNAL(closeTriggered()));

  _vSplitAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_ToolBarVerticalExtensionButton),
                    "Vertical split", this);
  connect(_vSplitAction, SIGNAL(triggered()),
          this, SIGNAL(vSplitTriggered()));

  _hSplitAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton),
                    "Horizontal split", this);
  connect(_hSplitAction, SIGNAL(triggered()),
          this, SIGNAL(hSplitTriggered()));

  _wSplitAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_TitleBarMaxButton),
                    "Open in a new window", this);
  connect(_wSplitAction, SIGNAL(triggered()),
          this, SIGNAL(wSplitTriggered()));

  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _toolBarEnd->addWidget(w);
  _toolBarEnd->addAction(_vSplitAction);
  _toolBarEnd->addAction(_hSplitAction);
  _toolBarEnd->addAction(_wSplitAction);
  _toolBarEnd->addAction(close);

  _vSplitAction->setVisible(false);
  _hSplitAction->setVisible(false);
}

ClosableWidget::~ClosableWidget()
{}

bool ClosableWidget::isVSplitEnable() const
{
  return _vSplitAction->isVisible();
}

bool ClosableWidget::isHSplitEnable() const
{
  return _hSplitAction->isVisible();
}

bool ClosableWidget::isWSplitEnable() const
{
  return _wSplitAction->isVisible();
}

void ClosableWidget::setVSplitEnable(bool enable)
{
  _vSplitAction->setVisible(enable);
}

void ClosableWidget::setHSplitEnable(bool enable)
{
  _hSplitAction->setVisible(enable);
}

void ClosableWidget::setWSplitEnable(bool enable)
{
  _wSplitAction->setVisible(enable);
}

QWidget* ClosableWidget::widget() const
{
  return _widget;
}

void ClosableWidget::setWidget(QWidget* widget, bool deleteOld)
{
  if(_widget == widget)
    return;

  _layout->removeWidget(_widget);
  if(deleteOld)
    delete _widget;

  _layout->addWidget(_widget);
  _toolBar->clear();
}

void ClosableWidget::setWidget(ClosableWidgetElement* widget, bool deleteOld)
{
  setWidget(static_cast<QWidget*>(widget), deleteOld);
  _toolBar->addActions(widget->attachActions());
}

void ClosableWidget::addToolBarAction(QAction* action)
{
  _toolBar->addAction(action);
}

} // namespace IDE
