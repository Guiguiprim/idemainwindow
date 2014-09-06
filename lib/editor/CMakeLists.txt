cmake_minimum_required(VERSION 2.8)
project(editor)
find_package(qibuild)

include(qibuild/modules/qt-tools)

include_directories(".")

set(
  editor_public_header
  "editor/editor_interface.hpp"
  "editor/editor_widget.hpp"
)

set(
  editor_src
  "src/editor_interface.cpp"
  "src/editor_widget.cpp"
)

qi_create_lib(
  editor
  ${editor_public_header}
  ${editor_src}
  STATIC
)	

qi_use_lib(
  editor
  QT_QTCORE
  QT_QTGUI
)

qi_stage_lib(editor)

qi_install_header(
  KEEP_RELATIVE_PATHS
  ${editor_public_header}
)


