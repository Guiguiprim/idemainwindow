#include <ide_widget/commun/closable_widget.hpp>

#include <QAction>
#include <QApplication>
#include <QHBoxLayout>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QVBoxLayout>

#include <ide_widget/commun/closable_widget_element.hpp>
#include <ide_widget/commun/closable_widget_event.hpp>

namespace IDE
{

ClosableWidget::ClosableWidget(
    SplitConfig splitConfig,
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
  , _splitActions(NULL)
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
  _toolBar->setObjectName("DarkToolBar");
  _toolBarEnd->setIconSize(QSize(16,16));
  _toolBarEnd->setObjectName("DarkToolBar");

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

  _splitMenu = new QMenu("");
  _splitMenu->addAction(_vSplitAction);
  _splitMenu->addAction(_hSplitAction);
  _splitMenu->addAction(_newWindowAction);
  QToolButton* toolButton = new QToolButton;
  toolButton->setToolTip("Split");
  toolButton->setMenu(_splitMenu);
  toolButton->setPopupMode(QToolButton::InstantPopup);

  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _toolBarEnd->addWidget(w);
  _splitActions = _toolBarEnd->addWidget(toolButton);
  _toolBarEnd->addAction(_vSplitAction);
  _toolBarEnd->addAction(_unsplitAction);
  _toolBarEnd->addAction(_close);

  connect(_close, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_unsplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_vSplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_hSplitAction, SIGNAL(triggered()), SLOT(emitEvent()));
  connect(_newWindowAction, SIGNAL(triggered()), SLOT(emitEvent()));

  setSplitConfig(splitConfig);
}

ClosableWidget::~ClosableWidget()
{
}

ClosableWidget::SplitConfig ClosableWidget::splitConfig() const
{
  return _splitConfig;
}

void ClosableWidget::setSplitConfig(SplitConfig splitConfig)
{
  _splitConfig = splitConfig;
  if(NoSplit == splitConfig)
  {
    _vSplitAction->setEnabled(false);
    _hSplitAction->setEnabled(false);
    _newWindowAction->setEnabled(false);
    _unsplitAction->setEnabled(false);

    _toolBarEnd->removeAction(_splitActions);
    _toolBarEnd->removeAction(_vSplitAction);
    _toolBarEnd->removeAction(_unsplitAction);
  }
  else if(VSplit == splitConfig)
  {
    _vSplitAction->setEnabled(true);
    _hSplitAction->setEnabled(false);
    _newWindowAction->setEnabled(false);

    _toolBarEnd->removeAction(_splitActions);
    _toolBarEnd->removeAction(_vSplitAction);
    _toolBarEnd->removeAction(_unsplitAction);
    _toolBarEnd->insertAction(_close, _vSplitAction);
    _toolBarEnd->insertAction(_close, _unsplitAction);
  }
  else if(Split == splitConfig || SplitAndNewWindow == splitConfig)
  {
    _vSplitAction->setEnabled(true);
    _hSplitAction->setEnabled(true);
    _newWindowAction->setEnabled(SplitAndNewWindow == splitConfig);
    _newWindowAction->setVisible(SplitAndNewWindow == splitConfig);

    _toolBarEnd->removeAction(_splitActions);
    _toolBarEnd->removeAction(_vSplitAction);
    _toolBarEnd->removeAction(_unsplitAction);
    _toolBarEnd->insertAction(_close, _splitActions);
    _toolBarEnd->insertAction(_close, _unsplitAction);
  }
}

void ClosableWidget::enableUnsplit(bool enable, Qt::Orientation orientation)
{
  Q_UNUSED(orientation)
  _unsplitAction->setEnabled(enable);
  _unsplitAction->setVisible(enable);
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
