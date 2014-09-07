#ifndef IDE_EDITOR_WIDGET_HPP
#define IDE_EDITOR_WIDGET_HPP

#include "../api.hpp"
#include <QWidget>

namespace IDE
{
class EditorInterface;

class IDE_WIDGET_LIB_EXPORT EditorWidget : public QWidget
{
  Q_OBJECT
public:
  explicit EditorWidget(EditorInterface* editor, QWidget *parent = NULL);

  void setEditor(EditorInterface* editor);
  EditorInterface* editor() const;

Q_SIGNALS:
  void editorChanged();

protected:
  EditorInterface* _editor;
};

} // namespace IDE

#endif // IDE_EDITOR_WIDGET_HPP
