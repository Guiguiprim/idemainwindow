#ifndef IDE_EDITORS_CONTROLLER_HPP
#define IDE_EDITORS_CONTROLLER_HPP

#include <QObject>

#include <QList>

namespace IDE
{
class RecursiveSplitter;
typedef RecursiveSplitter EditorsArea;

class EditorsController : public QObject
{
  Q_OBJECT
public:
  explicit EditorsController(EditorsArea* editorsArea, QObject *parent = NULL);

  virtual bool eventFilter(
      QObject* watched,
      QEvent* event);

private Q_SLOTS:
  void xWindowDestroyed(QObject* window);

private:
  EditorsArea* _editorsArea;
  QList<RecursiveSplitter*> _editorsAreaWindows;
};

} // namespace IDE

#endif // IDE_EDITORS_CONTROLLER_HPP
