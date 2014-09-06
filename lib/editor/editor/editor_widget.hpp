#ifndef IDE_EDITOR_WIDGET_HPP
#define IDE_EDITOR_WIDGET_HPP

#include <QWidget>

namespace IDE
{
class EditorInterface;

class EditorWidget : public QWidget
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
