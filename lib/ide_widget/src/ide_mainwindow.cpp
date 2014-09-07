#include <ide_widget/ide_mainwindow.hpp>

#include <ide_widget/commun/splitter.hpp>
#include <ide_widget/commun/closable_widget.hpp>

#include <ide_widget/bottom_panel/bottom_panel.hpp>
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

  this->setCentralWidget(globalSplitter);
}

} // namespace IDE
