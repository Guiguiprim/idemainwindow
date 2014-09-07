cmake_minimum_required(VERSION 2.8)
project(ide_widget)
find_package(qibuild)

include(qibuild/modules/qt-tools)

include_directories(".")
add_definitions(-DIDE_WIDGET_LIBRARY)

set(
  ide_widget_public_header
  "ide_widget/enum.hpp"
  "ide_widget/ide_mainwindow.hpp"

  "ide_widget/bottom_panel/bottom_panel.hpp"

  "ide_widget/commun/closable_widget.hpp"
  "ide_widget/commun/closable_widget_element.hpp"
  "ide_widget/commun/closable_widget_event.hpp"
  "ide_widget/commun/splitter.hpp"

  "ide_widget/editor/editor_interface.hpp"
  "ide_widget/editor/editor_widget.hpp"
  "ide_widget/editor/editor_widget_interface.hpp"
  "ide_widget/editor/open_file_chooser.hpp"
  "ide_widget/editor/open_file_chooser_model.hpp"
  "ide_widget/editor/recursive_splitter.hpp"

  "ide_widget/side_panel/side_panel.hpp"
  "ide_widget/side_panel/widget_chooser.hpp"
  "ide_widget/side_panel/widget_chooser_model.hpp"
)

set(
  ide_widget_src
  "src/ide_mainwindow.cpp"

  "src/bottom_panel/bottom_panel.cpp"

  "src/commun/closable_widget.cpp"
  "src/commun/closable_widget_element.cpp"
  "src/commun/closable_widget_event.cpp"
  "src/commun/splitter.cpp"

  "src/editor/editor_interface.cpp"
  "src/editor/editor_widget.cpp"
  "src/editor/open_file_chooser.cpp"
  "src/editor/open_file_chooser_model.cpp"
  "src/editor/recursive_splitter.cpp"

  "src/side_panel/side_panel.cpp"
  "src/side_panel/widget_chooser.cpp"
  "src/side_panel/widget_chooser_model.cpp"
)

set(
  ide_widget_public_moc_header
  "ide_widget/ide_mainwindow.hpp"

  "ide_widget/bottom_panel/bottom_panel.hpp"

  "ide_widget/commun/closable_widget.hpp"
  "ide_widget/commun/closable_widget_element.hpp"

  "ide_widget/editor/editor_interface.hpp"
  "ide_widget/editor/editor_widget.hpp"
  "ide_widget/editor/open_file_chooser.hpp"
  "ide_widget/editor/open_file_chooser_model.hpp"
  "ide_widget/editor/recursive_splitter.hpp"

  "ide_widget/side_panel/side_panel.hpp"
  "ide_widget/side_panel/widget_chooser.hpp"
  "ide_widget/side_panel/widget_chooser_model.hpp"
)

qt4_wrap_cpp(
  ide_widget_public_moc_src
  ${ide_widget_public_moc_header}
)

qt4_add_resources(
  ide_widget_res
  "res/icons.qrc"
)

qi_create_lib(
  ide_widget
  ${ide_widget_public_header}
  ${ide_widget_src}
  ${ide_widget_public_moc_src}
  ${ide_widget_res}
  SHARED
)	

qi_use_lib(
  ide_widget
  QT_QTCORE
  QT_QTGUI
)

qi_stage_lib(ide_widget)

qi_install_header(
  KEEP_RELATIVE_PATHS
  ${ide_widget_public_header}
)


