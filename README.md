# BIGCAM
Student project : designing, build and program an autonomous plane in order to map the ground with a camera.

## Status
+    **[DONE]** Communication between threads
+    **[TODO]** State management
+    **[TODO]** Take decisions
+    **[TODO]** Gathering data from sensors
+    **[TODO]** Control actuators
+    **[DONE]** Tag camera images
+    **[TODO]** Assemble camera images to build a map
+    **[DONE]** Easy UI to manage and monitor robot(s)
+    **[DONE]** Test on Raspberry Pi

## Dependencies
+    **CMake**
+    **GCC** for c++11
+    **OpenCV** with **GTK** (Qt does not support GUI over multithreading)
+    **V4L** driver for camera
+    **DOT** library to generate connexion graph
+    **GNU/Linux** (not tested on Windows and MAC OS)

## To compile and execute
    git clone https://github.com/rouviecy/BIGCAM; cd BIGCAM
    mkdir build; cd build
    mkdir test
    cmake ..
    make
    ./drone

## GUI
+    Press `q` to quit
+    Press `+`/`-` to activate or desactivate remote control
+    Press `UP`/`DOWN` to step on the gas or slow down
+    Press `LEFT`/`RIGHT` to turn to left or right

## For Raspberry Pi
Install packages to compile

    sudo apt-get install build-essential cmake g++-4.8 git libopencv-dev

Enable camera (load module and v4l2-ctl after each boot)

    sudo raspi-config
    sudo apt-get install v4l-utils
    sudo modprobe bcm2835-v4l2
    sudo v4l2-ctl --set-fmt-video=width=400,height=300,pixelformat="H264" -d /dev/video0

Enable I2C (local module and chmod after each boot)

    sudo raspi-config
    sudo modprobe i2c-dev
    sudo chmod o+rw /dev/i2c

Compile and execute ...
