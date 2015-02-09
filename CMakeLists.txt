cmake_minimum_required(VERSION 2.8)
project(BIGCAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_COMPILER g++-4.8.3)

find_package(PkgConfig)
find_package(OpenCV REQUIRED)

add_library(MYLIBS
	src/img_proc/Io_file.h				src/img_proc/Io_file.cpp
	src/img_proc/Builder.h				src/img_proc/Builder.cpp
	src/stereotypes/Actuator.h			src/stereotypes/Actuator.cpp
	src/stereotypes/ComThread.h			src/stereotypes/ComThread.cpp
	src/stereotypes/Exteroceptive.h		src/stereotypes/Exteroceptive.cpp
	src/stereotypes/Proprioceptive.h	src/stereotypes/Proprioceptive.cpp
	src/stereotypes/Sensor.h			src/stereotypes/Sensor.cpp
	src/Autonomy.h						src/Autonomy.cpp
	src/Camera.h						src/Camera.cpp
	src/Clock.h							src/Clock.cpp
	src/Compas.h						src/Compas.cpp
	src/Gps.h							src/Gps.cpp
	src/Imu.h							src/Imu.cpp
	src/Monitor.h						src/Monitor.cpp
	src/Motor.h							src/Motor.cpp
	src/Remote.h						src/Remote.cpp
	src/Robot.h							src/Robot.cpp
	src/Servo.h							src/Servo.cpp
	src/Simulator.h						src/Simulator.cpp
	src/Share.h							src/Share.cpp
	src/State.h							src/State.cpp
)

add_executable(drone src/mains/drone.cpp)
target_link_libraries(drone ${OpenCV_LIBS} MYLIBS)

add_executable(map_builder src/mains/map_builder.cpp)
target_link_libraries(map_builder ${OpenCV_LIBS} MYLIBS)
