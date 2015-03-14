# BIGCAM
Student project : designing, build and program an autonomous plane in order to map the ground with a camera.

## Status
+    **[DONE]** Communication between threads
+    **[TODO]** State management
+    **[DONE]** Take decisions
+    **[DONE]** Gathering data from sensors
+    **[DONE]** Control actuators
+    **[DONE]** Remote control and monitoring by TCP and joystick/keyboard
+    **[TODO]** Autonomous control
+    **[DONE]** Tag camera images
+    **[DONE]** Assemble camera images to build a map
+    **[DONE]** Easy UI to manage and monitor robot(s)
+    **[DONE]** Test on Raspberry Pi

## Dependencies for robot
+    **CMake**
+    **GCC** for c++11
+    **OpenCV** with **GTK** (Qt does not support GUI over multithreading)
+    **V4L** driver for camera
+    **DOT** library to generate connexion graph
+    **WiringPi** for Raspberry serial, I2C, ...
+    **GNU/Linux** (not tested on Windows and MAC OS)

## Dependencies for remote controller
+    **Python2.7** with **PyGame**, **OpenCV** and **NumPy**

## To compile and execute on robot (server)
Remember to adjust `MODE_RASPI` and `MODE_SIMU_CAM` in `CMakeLists.txt` to enable/disable Raspberry management and camera simulator.  

    git clone https://github.com/rouviecy/BIGCAM
    cd BIGCAM/build
    cmake ..
    make
    sudo ./drone
    ./map_builder

## To execute on remote controller (client)

    git clone https://github.com/rouviecy/BIGCAM
    cd BIGCAM/Remote_python/
    python main.py {ip address of robot}

## GUI on remote controller
+    Press `q` to quit
+    Press `a`/`z` (or `A`/`B` on joystick) to activate or desactivate remote control
+    Press `LEFT`/`RIGHT` (or `axis_left`/`axis_right` on joystick) to turn to left or right
+    Press `UP`/`DOWN` (or `axis_up`/`axis_down` on joystick) to control horizontal tailfin
+    Press `not implemented on keyboard yet` (or `hat_left`/`hat_right` on joystick) to control vertical tailfin
+    Press `+`/`-` (or scroll on joystick) to step on the gas or slow down

## For Raspberry Pi
Install packages to compile

    sudo apt-get install build-essential cmake g++-4.8 git libopencv-dev

Enable camera (load `bcm2835-v4l2` and `v4l2-ctl` after each boot)

    sudo raspi-config
    sudo apt-get install v4l-utils
    sudo modprobe bcm2835-v4l2
    sudo v4l2-ctl --set-fmt-video=width=400,height=300,pixelformat="H264" -d /dev/video0

Disable Serial over console

    sudo raspi-config

Enable I2C (load `i2c-dev` and `chmod` after each boot)

    sudo raspi-config
    sudo modprobe i2c-dev
    sudo chmod o+rw /dev/i2c

Compile and execute ...

## About the code ...
This code is designed for 4-spaces tab-indent. Unfornatunately, GitHub shows tabs with 8 spaces ! Just add `?ts=4` at the end of the URL to change this parameter.