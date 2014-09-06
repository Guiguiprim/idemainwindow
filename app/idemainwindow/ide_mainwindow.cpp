#include "ide_mainwindow.hpp"

#include <ide_widget/splitter.hpp>

#include "bottom_panel.hpp"
#include "editors_area.hpp"
#include "side_panel.hpp"

namespace IDE
{

IDEMainWindow::IDEMainWindow(QWidget *parent)
  : QMainWindow(parent)
  , _editorsArea(new EditorsArea)
  , _leftPanel(new SidePanel)
  , _rightPanel(new SidePanel)
  , _bottomPanel(new BottomPanel)
{
  Splitter* centralSplitter = new Splitter(Qt::Vertical);
  centralSplitter->addWidget(_editorsArea);
  centralSplitter->addWidget(_bottomPanel);
  centralSplitter->setCollapsible(0, false);
  centralSplitter->setCollapsible(1, false);

  Splitter* globalSplitter = new Splitter(Qt::Horizontal);
  globalSplitter->addWidget(_leftPanel);
  globalSplitter->addWidget(centralSplitter);
  globalSplitter->addWidget(_rightPanel);
  globalSplitter->setCollapsible(0, false);
  globalSplitter->setCollapsible(1, false);
  globalSplitter->setCollapsible(2, false);
  _rightPanel->hide();

  this->setCentralWidget(globalSplitter);

  this->resize(800,600);
  centralSplitter->setStretchFactor(0,4);
  centralSplitter->setStretchFactor(1,1);
  globalSplitter->setStretchFactor(0,1);
  globalSplitter->setStretchFactor(1,4);
  globalSplitter->setStretchFactor(2,1);
}

} // namespace IDE
