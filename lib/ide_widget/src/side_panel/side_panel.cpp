#include <ide_widget/side_panel/side_panel.hpp>

#include <QVBoxLayout>

#include <ide_widget/commun/closable_widget.hpp>

namespace IDE
{

SidePanel::SidePanel(QWidget *parent)
  : QWidget(parent)
{
  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->setMargin(0);
  lyt->setSpacing(0);

  ClosableWidget* widget = new ClosableWidget(ClosableWidget::VSplit);
  lyt->addWidget(widget);
}

} // namespace IDE
