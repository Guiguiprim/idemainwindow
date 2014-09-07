#include <ide_widget/ide_mainwindow.hpp>

#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>

#include <ide_widget/bottom_panel/bottom_panel.hpp>
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
  , _bottomVisibilityAction(NULL)
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

  _bottomToolBar = new QToolBar;
  _bottomToolBar->setObjectName("DarkToolBar");

  _leftVisibilityAction = _bottomToolBar->addAction("Hide left panel", this, SLOT(xChangeLeftVisibility()));

  QWidget* s = new QWidget;
  s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _bottomToolBar->addWidget(s);

  _bottomVisibilityAction = _bottomToolBar->addAction("Hide bottom panel", this, SLOT(xChangeBottomVisibility()));

  s = new QWidget;
  s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  _bottomToolBar->addWidget(s);

  _rightVisibilityAction = _bottomToolBar->addAction("Hide right panel", this, SLOT(xChangeRightVisibility()));

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
}

void IDEMainWindow::xChangeRightVisibility()
{
  _rightPanel->setVisible(!_rightPanel->isVisible());
}

void IDEMainWindow::xChangeBottomVisibility()
{
  _bottomPanel->setVisible(!_bottomPanel->isVisible());
}

} // namespace IDE