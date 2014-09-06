cmake_minimum_required(VERSION 2.8)
project(ide_widget)
find_package(qibuild)

include(qibuild/modules/qt-tools)

include_directories(".")

set(
  ide_widget_public_header
  "ide_widget/closable_widget.hpp"
  "ide_widget/closable_widget_element.hpp"
  "ide_widget/closable_widget_event.hpp"
  "ide_widget/enum.hpp"
  "ide_widget/open_file_chooser.hpp"
  "ide_widget/open_file_chooser_model.hpp"
  "ide_widget/recursive_splitter.hpp"
  "ide_widget/splitter.hpp"
  "ide_widget/widget_chooser.hpp"
  "ide_widget/widget_chooser_model.hpp"
)

set(
  ide_widget_src
  "src/closable_widget.cpp"
  "src/closable_widget_element.cpp"
  "src/closable_widget_event.cpp"
  "src/open_file_chooser.cpp"
  "src/open_file_chooser_model.cpp"
  "src/recursive_splitter.cpp"
  "src/splitter.cpp"
  "src/widget_chooser.cpp"
  "src/widget_chooser_model.cpp"
)

set(
  ide_widget_public_moc_header
  "ide_widget/closable_widget.hpp"
  "ide_widget/closable_widget_element.hpp"
  "ide_widget/open_file_chooser.hpp"
  "ide_widget/open_file_chooser_model.hpp"
  "ide_widget/recursive_splitter.hpp"
  "ide_widget/splitter.hpp"
  "ide_widget/widget_chooser.hpp"
  "ide_widget/widget_chooser_model.hpp"
)

qt4_wrap_cpp(
  ide_widget_public_moc_src
  ${ide_widget_public_moc_header}
)

qi_create_lib(
  ide_widget
  ${ide_widget_public_header}
  ${ide_widget_src}
  ${ide_widget_public_moc_src}
  STATIC
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


