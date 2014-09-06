cmake_minimum_required(VERSION 2.8)
project(idemainwindow)

find_package(qibuild)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(
  idemainwindow_src
  "main.cpp"
)

qt4_wrap_cpp(
  idemainwindow_moc_src
)

qi_create_bin(
  idemainwindow 
  ${idemainwindow_src}
  ${idemainwindow_src_moc}
)

# Add a simple test:
#enable_testing()
#qi_create_test(
#  test_idemainwindow
#)

