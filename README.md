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
    apt-get install build-essential cmake g++-4.8 git libopencv-dev v4l-utils
    sudo modprobe bcm2835-v4l2
    v4l2-ctl --set-fmt-video=width=400,height=300,pixelformat="H264" -d /dev/video0
    ./drone
