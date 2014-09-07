#include <ide_widget/editor/editor_widget.hpp>

namespace IDE
{

EditorWidget::EditorWidget(EditorInterface* editor, QWidget *parent)
  : QWidget(parent)
  , _editor(editor)
{}

void EditorWidget::setEditor(EditorInterface* editor)
{
  if(editor != _editor)
  {
    _editor = editor;
    editorChanged();
  }
}

EditorInterface* EditorWidget::editor() const
{
  return _editor;
}

} // namespace IDE
