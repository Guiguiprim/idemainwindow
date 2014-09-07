#include "dummy_closable_widget_element.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace IDE
{

DCW1::DCW1(QWidget *parent)
  : ClosableWidgetElement("DCW1", parent)
{
  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->addWidget(new QLabel("Bla bla"));
  lyt->addWidget(new QLineEdit);
  lyt->addWidget(new QPushButton("Super action"));
  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  lyt->addWidget(w);
  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

DCW2::DCW2(QWidget *parent)
  : ClosableWidgetElement("DCW2", parent)
{
  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->addWidget(new QLabel("Bla bla"));
  lyt->addWidget(new QLabel("Bla bla"));
  lyt->addWidget(new QLabel("Bla bla"));
  lyt->addWidget(new QLabel("Bla bla"));
  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  lyt->addWidget(w);
  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

DCW3::DCW3(QWidget *parent)
  : ClosableWidgetElement("DCW3", parent)
{
  QVBoxLayout* lyt = new QVBoxLayout(this);
  lyt->addWidget(new QPushButton("Action 1"));
  lyt->addWidget(new QPushButton("Action 2"));
  lyt->addWidget(new QPushButton("Action 3"));
  lyt->addWidget(new QPushButton("Action 4"));
  lyt->addWidget(new QPushButton("Super Action"));
  QWidget* w = new QWidget;
  w->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  lyt->addWidget(w);
  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

} // namespace IDE
