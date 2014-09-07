#ifndef IDE_SPLITTER_HPP
#define IDE_SPLITTER_HPP

#include "api.hpp"
#include <QLinearGradient>
#include <QSplitter>

namespace IDE
{

class SplitterHandle : public QSplitterHandle
{
  Q_OBJECT
public:
  explicit SplitterHandle(Qt::Orientation orientation, QSplitter *parent = NULL);

protected:
  virtual void paintEvent(QPaintEvent *event);

private:
  QLinearGradient _gradient;
};

class IDE_WIDGET_LIB_EXPORT Splitter : public QSplitter
{
  Q_OBJECT
public:
  explicit Splitter(Qt::Orientation orientation, QWidget *parent = NULL);

protected:
  virtual QSplitterHandle* createHandle();
};

} // namespace IDE

#endif // IDE_SPLITTER_HPP
