#ifndef IDE_OPEN_FILE_CHOOSER_HPP
#define IDE_OPEN_FILE_CHOOSER_HPP

#include <QWidget>

namespace IDE
{

class OpenFileChooser : public QWidget
{
  Q_OBJECT
public:
  explicit OpenFileChooser(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_OPEN_FILE_CHOOSER_HPP
