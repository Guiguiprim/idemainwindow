#include <QApplication>

#include <splittable_area/splitter_area.hpp>
#include <splittable_area/splitter_widget.hpp>

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  IDE::SplitterArea splittableArea;
  IDE::SplitterWidget* widget = splittableArea.verticalSplit(0);
  widget->setColor("blue");
  widget = splittableArea.horizontalSplit(0);
  widget->setColor("green");
  splittableArea.show();

  return app.exec();
}
