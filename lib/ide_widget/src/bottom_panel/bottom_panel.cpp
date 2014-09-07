#include <ide_widget/bottom_panel/bottom_panel.hpp>

#include <QComboBox>
#include <QVBoxLayout>

namespace IDE
{

BottomPanel::BottomPanel(QWidget *parent)
  : ClosableWidget(ClosableWidget::NoSplit, parent)
{}

} // namespace IDE
