#ifndef IDE_EDITORS_CONTROLLER_HPP
#define IDE_EDITORS_CONTROLLER_HPP

#include <QObject>

namespace IDE {

class EditorsController : public QObject
{
  Q_OBJECT
public:
  explicit EditorsController(QObject *parent = NULL);


};

} // namespace IDE

#endif // IDE_EDITORS_CONTROLLER_HPP
