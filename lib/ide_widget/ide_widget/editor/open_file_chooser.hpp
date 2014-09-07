#ifndef IDE_OPEN_FILE_CHOOSER_HPP
#define IDE_OPEN_FILE_CHOOSER_HPP

#include "../api.hpp"
#include <QWidget>

namespace IDE
{

class IDE_WIDGET_LIB_EXPORT OpenFileChooser : public QWidget
{
  Q_OBJECT
public:
  explicit OpenFileChooser(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_OPEN_FILE_CHOOSER_HPP
