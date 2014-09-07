#include "editors_area.hpp"

#include <QVBoxLayout>

#include <ide_widget/closable_widget.hpp>
#include <ide_widget/recursive_splitter.hpp>

namespace IDE
{

EditorsArea::EditorsArea(QWidget *parent)
  : QWidget(parent)
{
  ClosableWidget* cw = new ClosableWidget(ClosableWidget::SplitAndNewWindow);

  RecursiveSplitter* rs = new RecursiveSplitter;
  rs->addWidget(cw);
  cw->installEventFilter(rs);

  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->setMargin(0);
  lyt->addWidget(rs);
}

} // namespace IDE
