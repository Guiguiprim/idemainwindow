#include <QApplication>

#include <splittable_area/splitter_area.hpp>

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  IDE::SplitterArea splittableArea;
  splittableArea.createSomeHandlers();
  splittableArea.show();

  return app.exec();
}
