#include <editor/editor_interface.hpp>

#include <QFile>

namespace IDE
{

EditorInterface::EditorInterface(QObject *parent)
  : QObject(parent)
{
}

bool EditorInterface::load(const QString& filePath)
{
  if(filePath.isEmpty())
    return false;

  QFile file(filePath);
  if(!file.open(QFile::ReadOnly))
    return false;

  QByteArray content = file.readAll();
  if(!readFrom(content))
    return false;

  return true;
}

bool EditorInterface::save(const QString& filePath) const
{
  if(filePath.isEmpty())
    return false;

  QFile file(filePath);
  if(!file.open(QFile::WriteOnly))
    return false;

  QByteArray content;
  if(!writeTo(content))
    return false;

  if(file.write(content) != (qint64)content.size())
    return false;

  return true;
}

} // namespace IDE
