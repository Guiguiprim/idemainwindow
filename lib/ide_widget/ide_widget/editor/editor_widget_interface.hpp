#ifndef IDE_EDITOR_WIDGET_INTERFACE_HPP
#define IDE_EDITOR_WIDGET_INTERFACE_HPP

#include <ide_widget/editor/editor_widget.hpp>

#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>

namespace IDE
{
class EditorInterface;

template<typename MyEditor>
class EditorWidgetInterface : public EditorWidget
{

public:
  explicit EditorWidgetInterface(
      MyEditor* editor,
      QWidget *parent = NULL,
      typename boost::enable_if< boost::is_base_of<EditorInterface, MyEditor> >::type* dummy = NULL)
    : EditorWidget(editor, parent)
  {}

  typename boost::enable_if< boost::is_base_of<EditorInterface, MyEditor>, void >::type
  setEditor(MyEditor* editor)
  {
    EditorWidget::setEditor(editor);
  }

  MyEditor* editor() const
  {
    if(!_editor)
      return NULL;
    return static_cast<MyEditor*>(_editor);
  }
};

} // namespace IDE

#endif // IDE_EDITOR_WIDGET_INTERFACE_HPP
