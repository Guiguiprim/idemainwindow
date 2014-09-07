#include <ide_widget/side_panel/side_panel.hpp>

#include <QVBoxLayout>

#include <ide_widget/commun/closable_widget.hpp>

namespace IDE
{

SidePanel::SidePanel(QWidget *parent)
  : Splitter(Qt::Vertical, parent)
{}

} // namespace IDE
