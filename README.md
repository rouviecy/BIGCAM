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
+    **[TODO]** Easy UI to manage and monitor robot(s)

## Dependencies
+    **CMake**
+    **GCC** for c++11
+    **OpenCV** with **Qt** (no GTK)
+    **V4L** driver for camera
+    **GNU/Linux** (not tested on Windows and MAC OS)

## To compile and execute
    cd BIGCAM
    mkdir build;
    cd build
    mkdir test
    cmake ..
    make
    ./drone

## GUI
+    Press `q` to quit
+    Press `+`/`-` to activate or desactivate remote control
+    Press `8`/`2` to step on the gas or slow down
+    Press `4`/`6` to turn to left or right