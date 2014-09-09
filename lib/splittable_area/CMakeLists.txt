cmake_minimum_required(VERSION 2.8)
project(splittable_area)
find_package(qibuild)

include(qibuild/modules/qt-tools)

include_directories(".")
add_definitions(-DIDE_WIDGET_LIBRARY)

set(
  splittable_area_public_header
  "splittable_area/splitter_area.hpp"
  "splittable_area/splitter_enum.hpp"
  "splittable_area/splitter_handler.hpp"
  "splittable_area/splitter_widget.hpp"
  "splittable_area/splitter_widget_base.hpp"
)

set(
  splittable_area_src
  "src/splitter_area.cpp"
  "src/splitter_handler.cpp"
  "src/splitter_widget.cpp"
  "src/splitter_widget_base.cpp"
)

set(
  splittable_area_public_moc_header
  "splittable_area/splitter_area.hpp"
  "splittable_area/splitter_handler.hpp"
  "splittable_area/splitter_widget.hpp"
  "splittable_area/splitter_widget_base.hpp"
)

qt4_wrap_cpp(
  splittable_area_public_moc_src
  ${splittable_area_public_moc_header}
)

qt4_add_resources(
  splittable_area_res
)

qi_create_lib(
  splittable_area
  ${splittable_area_public_header}
  ${splittable_area_src}
  ${splittable_area_public_moc_src}
  ${splittable_area_res}
#  SHARED
)	

qi_use_lib(
  splittable_area
  QT_QTCORE
  QT_QTGUI
)

qi_stage_lib(splittable_area)

qi_install_header(
  KEEP_RELATIVE_PATHS
  ${splittable_area_public_header}
)

qi_generate_qt_conf()


# test
qi_create_bin(
  splittable_area_test
  "test/main.cpp"
  DEPENDS
  splittable_area
)

