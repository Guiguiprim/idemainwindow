#include <QApplication>

#include <QLabel>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  IDE::SplitterArea splittableArea;

  IDE::SplitterWidget* widget = splittableArea.verticalSplit(0);
  widget->setColor("blue");
  widget = splittableArea.horizontalSplit(1);
  widget->setColor("green");

  splittableArea.setWidgetAt(new QLabel("first text"), 0);
  splittableArea.addWidget(new QLabel("Should be last"), 0);
  splittableArea.insertWidget(new QLabel("Should be first"), 0);

  splittableArea.show();

  return app.exec();
}
