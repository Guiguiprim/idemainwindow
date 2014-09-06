#ifndef IDE_SPLITTER_HPP
#define IDE_SPLITTER_HPP

#include <QLinearGradient>
#include <QSplitter>
#include <QSplitterHandle>

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

class Splitter : public QSplitter
{
  Q_OBJECT
public:
  explicit Splitter(Qt::Orientation orientation, QWidget *parent = NULL);

protected:
  virtual QSplitterHandle* createHandle();
};

} // namespace IDE

#endif // IDE_SPLITTER_HPP
