#include "main_window.hpp"

#include <QAction>
#include <QToolBar>
#include <QLabel>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

namespace IDE
{

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , _i(0)
{
  _splittableArea = new SplitterArea;
  this->setCentralWidget(_splittableArea);

  QToolBar* toolBar = this->addToolBar("");

  _verticalSplit = toolBar->addAction("V split", this, SLOT(onVerticalSplit()));
  _horizontalSplit = toolBar->addAction("H split", this, SLOT(onHorizontalSplit()));
  _leftSplit = toolBar->addAction("left split", this, SLOT(onLeftSplit()));
  _rightSplit = toolBar->addAction("right split", this, SLOT(onRightSplit()));
  _topSplit = toolBar->addAction("top split", this, SLOT(onTopSplit()));
  _bottomSplit = toolBar->addAction("bottom split", this, SLOT(onBottomSplit()));
  _removeCurrent = toolBar->addAction("remove", this, SLOT(onRemoveCurrent()));

//  SplitterWidget* widget = _splittableArea->sideSplit(IDE::TOP, 0.2f);
//  widget->setColor("blue");
//  widget = _splittableArea->sideSplit(IDE::BOTTOM, 0.2f);
//  widget->setColor("green");
//  widget = _splittableArea->sideSplit(IDE::LEFT, 0.2f);
//  widget->setColor("orange");
//  widget = _splittableArea->sideSplit(IDE::RIGHT, 0.2f);
//  widget->setColor("yellow");

  this->resize(450,450);
}

void MainWindow::onVerticalSplit()
{
  int i = _splittableArea->indexLastUsedWidet();
  if(i != -1)
  {
    if(_splittableArea->addWidget(new QLabel("truc"), 0, Qt::Vertical))
     ++_i;
  }
}

void MainWindow::onHorizontalSplit()
{
  int i = _splittableArea->indexLastUsedWidet();
  if(i != -1)
  {
    _splittableArea->addWidget(new QLabel("truc"), 0, Qt::Horizontal);
    ++_i;
  }
}

void MainWindow::onLeftSplit()
{
  _splittableArea->sideSplit(IDE::LEFT, 0.2f)->setColor("blue");
  ++_i;
}

void MainWindow::onRightSplit()
{
  _splittableArea->sideSplit(IDE::RIGHT, 0.2f);
  ++_i;
}

void MainWindow::onTopSplit()
{
  _splittableArea->sideSplit(IDE::TOP, 0.2f);
  ++_i;
}

void MainWindow::onBottomSplit()
{
  _splittableArea->sideSplit(IDE::BOTTOM, 0.2f);
  ++_i;
}

void MainWindow::onRemoveCurrent()
{
  int i = _splittableArea->indexLastUsedWidet();
  if(i != -1)
  {
    _splittableArea->remove(i);
    --_i;
  }
}

} // namespace IDE
