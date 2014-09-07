#ifndef IDE_EDITOR_INTERFACE_HPP
#define IDE_EDITOR_INTERFACE_HPP

#include "../api.hpp"
#include <QObject>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT EditorInterface : public QObject
{
  Q_OBJECT
public:
  explicit EditorInterface(QObject *parent = NULL);

  virtual bool openNew() = 0;

  bool load(const QString& filePath);
  virtual bool readFrom(QByteArray& from) = 0;

  bool save(const QString& filePath) const ;
  virtual bool writeTo(QByteArray& to) const = 0;
};

} // namespace IDE

#endif // IDE_EDITOR_INTERFACE_HPP
