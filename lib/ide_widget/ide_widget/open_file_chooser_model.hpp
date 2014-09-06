#ifndef IDE_OPEN_FILE_CHOOSER_MODEL_HPP
#define IDE_OPEN_FILE_CHOOSER_MODEL_HPP

#include <QObject>

namespace IDE
{

class OpenFileChooserModel : public QObject
{
  Q_OBJECT
public:
  explicit OpenFileChooserModel(QObject *parent = NULL);

};

} // namespace IDE

#endif // IDE_OPEN_FILE_CHOOSER_MODEL_HPP
