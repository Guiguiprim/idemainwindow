#ifndef IDE_EDITOR_WIDGET_HPP
#define IDE_EDITOR_WIDGET_HPP

#include <QWidget>

namespace IDE
{

class EditorWidget : public QWidget
{
  Q_OBJECT
public:
  explicit EditorWidget(QWidget *parent = NULL);

};

} // namespace IDE

#endif // IDE_EDITOR_WIDGET_HPP
