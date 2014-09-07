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
  ClosableWidget* cw = new ClosableWidget(ClosableWidget::SplitAndNewWindow);
  _editorsArea->addWidget(cw);
  cw->installEventFilter(_editorsArea);

  Splitter* centralSplitter = new Splitter(Qt::Vertical);
  centralSplitter->addWidget(_editorsArea);
  centralSplitter->addWidget(_bottomPanel);

  Splitter* globalSplitter = new Splitter(Qt::Horizontal);
  globalSplitter->addWidget(_leftPanel);
  globalSplitter->addWidget(centralSplitter);
  globalSplitter->addWidget(_rightPanel);
  _rightPanel->hide();

  this->setCentralWidget(globalSplitter);

  this->resize(800,600);
}

} // namespace IDE
