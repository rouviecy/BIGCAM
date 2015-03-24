cmake_minimum_required(VERSION 2.8)
project(BIGCAM)

find_package(PkgConfig)

set(MODE_RASPI OFF)
set(MODE_SIMU_CAM ON)

add_definitions(-DTCP_BUFFER_LEN=1024)
add_definitions(-DTCP_PORT_IN=4242)
add_definitions(-DTCP_PORT_OUT=4243)

if(${MODE_RASPI})
	add_definitions(-DMODE_RASPI)
	find_package(OpenCV REQUIRED)
	set(WiringPi_LIBS "-lwiringPi")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_COMPILER g++-4.8)
	set(LIBS
		${WiringPi_LIBS}
		${OpenCV_LIBS}
	)
	link_libraries(${LIBS})
else(${MODE_RASPI})
	find_package(OpenCV REQUIRED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_COMPILER g++-4.8.3)
	set(LIBS
		${OpenCV_LIBS}
	)
	link_libraries(${LIBS})
endif(${MODE_RASPI})

if(${MODE_SIMU_CAM})
	add_definitions(-DMODE_SIMU_CAM)
endif(${MODE_SIMU_CAM})

find_package(SDL REQUIRED)
set(LIBS
	${SDL_LIBRARY}
)

add_library(MYLIBS
	src/img_proc/Io_file.h				src/img_proc/Io_file.cpp
	src/img_proc/Builder.h				src/img_proc/Builder.cpp
	src/img_proc/Mask.h					src/img_proc/Mask.cpp
	src/img_proc/Tracking.h				src/img_proc/Tracking.cpp
	src/img_proc/Utils.h				src/img_proc/Utils.cpp
	src/stereotypes/Actuator.h			src/stereotypes/Actuator.cpp
	src/stereotypes/ComThread.h			src/stereotypes/ComThread.cpp
	src/stereotypes/Exteroceptive.h		src/stereotypes/Exteroceptive.cpp
	src/stereotypes/Proprioceptive.h	src/stereotypes/Proprioceptive.cpp
	src/stereotypes/Sensor.h			src/stereotypes/Sensor.cpp
	src/utils/ComDraw.h					src/utils/ComDraw.cpp
	src/utils/Joystick.h				src/utils/Joystick.cpp
	src/utils/Serial.h					src/utils/Serial.cpp
	src/utils/Tcp_server.h				src/utils/Tcp_server.cpp
	src/Autonomy.h						src/Autonomy.cpp
	src/Camera.h						src/Camera.cpp
	src/Clock.h							src/Clock.cpp
	src/Gps.h							src/Gps.cpp
	src/Imu.h							src/Imu.cpp
	src/Motor.h							src/Motor.cpp
	src/Pressure.h						src/Pressure.cpp
	src/Remote_rf.h						src/Remote_rf.cpp
	src/Robot.h							src/Robot.cpp
	src/Simulator.h						src/Simulator.cpp
	src/Share.h							src/Share.cpp
	src/State_rf.h						src/State_rf.cpp
)

add_executable(drone src/mains/drone.cpp)
target_link_libraries(drone ${LIBS} MYLIBS)

add_executable(map_builder src/mains/map_builder.cpp)
target_link_libraries(map_builder ${LIBS} MYLIBS)

add_executable(joystick src/mains/test.cpp)
target_link_libraries(joystick ${LIBS} MYLIBS)
