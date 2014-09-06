#ifndef IDE_EDITORS_AREA_HPP
#define IDE_EDITORS_AREA_HPP

#include <QWidget>

namespace IDE
{

class EditorsArea : public QWidget
{
  Q_OBJECT
public:
  explicit EditorsArea(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_EDITORS_AREA_HPP
