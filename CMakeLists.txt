cmake_minimum_required(VERSION 2.8)
project(BIGCAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig)
find_package(OpenCV REQUIRED)

add_library(MYLIBS
	src/stereotypes/Actuator.h			src/stereotypes/Actuator.cpp
	src/stereotypes/ComThread.h			src/stereotypes/ComThread.cpp
	src/stereotypes/Exteroceptive.h		src/stereotypes/Exteroceptive.cpp
	src/stereotypes/Proprioceptive.h	src/stereotypes/Proprioceptive.cpp
	src/stereotypes/Sensor.h			src/stereotypes/Sensor.cpp
	src/Compas.h						src/Compas.cpp
	src/Robot.h							src/Robot.cpp
	src/State.h							src/State.cpp
	src/Topic.h							src/Topic.cpp
)

# Projet Minority-Report
add_executable(drone src/mains/drone.cpp)
target_link_libraries(drone ${OpenCV_LIBS} MYLIBS)
