cmake_minimum_required(VERSION 2.8)
project(idemainwindow)

find_package(qibuild)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(
  idemainwindow_src
  "main.cpp"

  "my_ide_mainwindow.hpp"
  "my_ide_mainwindow.cpp"
  "controller/editors_controller.hpp"
  "controller/editors_controller.cpp"
  "controller/side_panel_controller.hpp"
  "controller/side_panel_controller.cpp"

  "dummy_content/dummy_closable_widget_element.hpp"
  "dummy_content/dummy_closable_widget_element.cpp"
)

set(
  idemainwindow_moc_header
  "my_ide_mainwindow.hpp"
  "controller/editors_controller.hpp"
  "controller/side_panel_controller.hpp"
)

qt4_wrap_cpp(
  idemainwindow_moc_src
  ${idemainwindow_moc_header}
)

qi_create_bin(
  idemainwindow 
  ${idemainwindow_src}
  ${idemainwindow_moc_src}
  DEPENDS
  QT_QTCORE
  QT_QTGUI
  ide_widget
)

# Add a simple test:
#enable_testing()
#qi_create_test(
#  test_idemainwindow
#)

