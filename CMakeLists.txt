cmake_minimum_required(VERSION 2.8.3)
project(point_plotter)

find_package(catkin REQUIRED COMPONENTS
  qt_build
  roscpp
)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package()

set(CMAKE_INCLUDE_CURRENT_DIR ON) 
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport) 

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui) 
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc) 


QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES}) 
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) 

include_directories(
    include 
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5PrintSupport_INCLUDE_DIRS}
    ${Eigen_INCLUDE_DIRS}
)

add_definitions( -std=c++11 -fPIC)

set( QT_SOURCES
	src/main.cpp
	src/pointplot.cpp
	src/mapviewer.cpp
	src/pp_qros.cpp

	include/point_plotter/pointplot.h
	include/point_plotter/mapviewer.h
    include/point_plotter/pp_qros.h

)

##############################################################################
# Binaries
##############################################################################

add_executable(point_plotter ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})

target_link_libraries(point_plotter yaml-cpp
${catkin_LIBRARIES}
	Qt5::Core
	Qt5::Widgets
	Qt5::PrintSupport  
    /usr/local/lib/libCornucopia.a
)
install(TARGETS point_plotter RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
