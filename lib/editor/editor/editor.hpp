#ifndef IDE_EDITOR_HPP
#define IDE_EDITOR_HPP

#include <QObject>

namespace IDE
{

class Editor : public QObject
{
  Q_OBJECT
public:
  explicit Editor(QObject *parent = NULL);

};

} // namespace IDE

#endif // IDE_EDITOR_HPP
