cmake_minimum_required(VERSION 2.8)
project(idemainwindow)

find_package(qibuild)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(
  idemainwindow_src
  "main.cpp"

  "idemainwindow/ide_mainwindow.hpp"
  "idemainwindow/ide_mainwindow.cpp"
)

set(
  idemainwindow_moc_header
  "idemainwindow/ide_mainwindow.hpp"
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
  editor
  panel_widget
)

# Add a simple test:
#enable_testing()
#qi_create_test(
#  test_idemainwindow
#)

