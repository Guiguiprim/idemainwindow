#include <ide_widget/ide_mainwindow.hpp>

#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>

#include <ide_widget/bottom_panel/bottom_panel.hpp>
#include <ide_widget/bottom_panel/bottom_panel_chooser.hpp>
#include <ide_widget/commun/splitter.hpp>
#include <ide_widget/commun/closable_widget.hpp>
#include <ide_widget/editor/recursive_splitter.hpp>
#include <ide_widget/side_panel/side_panel.hpp>

namespace IDE
{

IDEMainWindow::IDEMainWindow(QWidget *parent)
  : QMainWindow(parent)
  , _editorsArea(new EditorsArea)
  , _leftPanel(new SidePanel)
  , _rightPanel(new SidePanel)
  , _bottomPanel(new BottomPanel)
  , _bottomToolBar(NULL)
  , _leftVisibilityAction(NULL)
  , _rightVisibilityAction(NULL)
  , _bottomPanelChooser(NULL)
{
  this->resize(800,600);

  this->setStyleSheet("QToolBar#DarkToolBar { spacing: 0px; color: darkgray;"
                      "background: qlineargradient(y1:0, y2:1, stop: 0 #AAAAAA, stop: 1.0 #8A8A8A); }");

  Splitter* centralSplitter = new Splitter(Qt::Vertical);
  centralSplitter->addWidget(_editorsArea);
  centralSplitter->addWidget(_bottomPanel);
  _bottomPanel->hide();

  Splitter* globalSplitter = new Splitter(Qt::Horizontal);
  globalSplitter->addWidget(_leftPanel);
  globalSplitter->addWidget(centralSplitter);
  globalSplitter->addWidget(_rightPanel);
  _leftPanel->hide();
  _rightPanel->hide();

  _bottomPanelChooser = new BottomPanelChooser(_bottomPanel);

  _bottomToolBar = new QToolBar;
  _bottomToolBar->setIconSize(QSize(16,16));
  _bottomToolBar->setObjectName("DarkToolBar");

  _leftVisibilityAction = _bottomToolBar->addAction(QIcon(":/icons/left_hide.svg"), "Show left panel",
                                                    this, SLOT(xChangeLeftVisibility()));

  QWidget* s = new QWidget;
  s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _bottomToolBar->addWidget(s);

  _bottomToolBar->addWidget(_bottomPanelChooser);

  s = new QWidget;
  s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _bottomToolBar->addWidget(s);

  _rightVisibilityAction = _bottomToolBar->addAction(QIcon(":/icons/right_hide.svg"), "Show right panel",
                                                     this, SLOT(xChangeRightVisibility()));

  QWidget* w = new QWidget;
  QVBoxLayout* lyt = new QVBoxLayout(w);
  lyt->setMargin(0);
  lyt->setSpacing(0);
  lyt->addWidget(globalSplitter);
  lyt->addWidget(_bottomToolBar);

  this->setCentralWidget(w);
}

void IDEMainWindow::xChangeLeftVisibility()
{
  _leftPanel->setVisible(!_leftPanel->isVisible());
  if(_leftPanel->isVisible())
    _leftVisibilityAction->setText("Hide left panel");
  else
    _leftVisibilityAction->setText("Show left panel");
}

void IDEMainWindow::xChangeRightVisibility()
{
  _rightPanel->setVisible(!_rightPanel->isVisible());
  if(_rightPanel->isVisible())
    _rightVisibilityAction->setText("Hide right panel");
  else
    _rightVisibilityAction->setText("Show right panel");
}

} // namespace IDE
