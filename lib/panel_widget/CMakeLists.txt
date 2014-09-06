cmake_minimum_required(VERSION 2.8)
project(panel_widget)
find_package(qibuild)

include(qibuild/modules/qt-tools)

include_directories(".")

set(
  panel_widget_public_header
  "panel_widget/panel_widget.hpp"
)

set(
  panel_widget_src
  "src/panel_widget.cpp"
)

set(
  panel_widget_public_moc_header
  "panel_widget/panel_widget.hpp"
)

qt4_wrap_cpp(
  panel_widget_public_moc_src
  ${panel_widget_public_moc_header}
)

qi_create_lib(
  panel_widget
  ${panel_widget_public_header}
  ${panel_widget_src}
  ${panel_widget_public_moc_src}
  STATIC
)	

qi_use_lib(
  panel_widget
  QT_QTCORE
  QT_QTGUI
)

qi_stage_lib(panel_widget)

qi_install_header(
  KEEP_RELATIVE_PATHS
  ${panel_widget_public_header}
)


