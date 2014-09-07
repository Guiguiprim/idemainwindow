#include <ide_widget/bottom_panel/bottom_panel.hpp>

#include <QComboBox>
#include <QVBoxLayout>

namespace IDE
{

BottomPanel::BottomPanel(QWidget *parent)
  :QWidget(parent)
{
  QComboBox* combo = new QComboBox();
  combo->setEditable(false);
  combo->addItem("test");
  //combo->addItem("test2");

  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->addWidget(combo);
}

} // namespace IDE
