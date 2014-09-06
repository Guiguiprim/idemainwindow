#include <ide_widget/closable_widget.hpp>

#include <QAction>
#include <QApplication>
#include <QHBoxLayout>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QVBoxLayout>

#include <ide_widget/closable_widget_element.hpp>
#include <ide_widget/closable_widget_event.hpp>

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
  , _close(NULL)
  , _unsplitAction(NULL)
  , _vSplitAction(NULL)
  , _hSplitAction(NULL)
  , _newWindowAction(NULL)
  , _toolButton(NULL)
  , _splitMenu(NULL)
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

  _close = new QAction(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton),
                       "Close", this);

  _vSplitAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_ToolBarVerticalExtensionButton),
                    "Vertical split", this);

  _hSplitAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton),
                    "Horizontal split", this);

  _newWindowAction = new QAction(
                    this->style()->standardIcon(QStyle::SP_TitleBarMaxButton),
                    "Open in a new window", this);

  _unsplitAction = new QAction(
                     this->style()->standardIcon(QStyle::SP_TitleBarMaxButton),
                     "Unsplit", this);

  _splitMenu = new QMenu("test");
  _splitMenu->addAction(_vSplitAction);
  _splitMenu->addAction(_hSplitAction);
  _splitMenu->addAction(_newWindowAction);
  _toolButton = new QToolButton;
  _toolButton->setMenu(_splitMenu);
  _toolButton->setPopupMode(QToolButton::InstantPopup);

  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _toolBarEnd->addWidget(w);
  _toolBarEnd->addWidget(_toolButton);
  _toolBarEnd->addAction(_unsplitAction);
  _toolBarEnd->addAction(_close);

  connect(_close, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_unsplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_vSplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_hSplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_newWindowAction, SIGNAL(triggered()), SLOT(emitEvent()));
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
  return _newWindowAction->isVisible();
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
  _newWindowAction->setVisible(enable);
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

void ClosableWidget::emitEvent()
{
  QObject* action = sender();
  if(action == _close)
  {
    ClosableWidgetEvent event(ClosableWidgetEvent::Close);
    QApplication::sendEvent(this, &event);
  }
  else if(action == _unsplitAction)
  {
    ClosableWidgetEvent event(ClosableWidgetEvent::Unsplit);
    QApplication::sendEvent(this, &event);
  }
  else if(action == _vSplitAction)
  {
    ClosableWidgetEvent event(ClosableWidgetEvent::VerticalSplit);
    QApplication::sendEvent(this, &event);
  }
  else if(action == _hSplitAction)
  {
    ClosableWidgetEvent event(ClosableWidgetEvent::HorizontalSplit);
    QApplication::sendEvent(this, &event);
  }
  else if(action == _newWindowAction)
  {
    ClosableWidgetEvent event(ClosableWidgetEvent::NewWindow);
    QApplication::sendEvent(this, &event);
  }
}

} // namespace IDE
