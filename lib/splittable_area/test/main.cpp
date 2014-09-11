#include <QApplication>

#include <QLabel>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

#include "main_window.hpp"

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

//  IDE::SplitterArea splittableArea;
//  splittableArea.resize(400,400);

//  IDE::SplitterWidget* widget = splittableArea.verticalSplit(0);
//  widget->setColor("blue");
//  widget = splittableArea.horizontalSplit(1);
//  widget->setColor("green");

//  splittableArea.setWidgetAt(new QLabel("first text"), 0);
//  splittableArea.addWidget(new QLabel("Should be last"), 0);
//  splittableArea.insertWidget(new QLabel("Should be first"), 0);

//  IDE::SplitterWidget* widget = splittableArea.sideSplit(IDE::TOP, 0.2f);
//  widget->setColor("blue");

//  widget = splittableArea.sideSplit(IDE::BOTTOM, 0.2f);
//  widget->setColor("green");

//  widget = splittableArea.sideSplit(IDE::LEFT, 0.2f);
//  widget->setColor("orange");

//  widget = splittableArea.sideSplit(IDE::RIGHT, 0.2f);
//  widget->setColor("yellow");

//  splittableArea.show();

  IDE::MainWindow window;
  window.show();

  return app.exec();
}
