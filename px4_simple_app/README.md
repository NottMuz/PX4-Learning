# Minimal Application
  - This folder contains the necessary code for creating an application for the PX4 platform
  - You will see that the **`main`** function is created in a **`.c`** file
  - For further comments on the syntax of the code see the **`.c`** file
# General Overview
 ### 1. Create The .c File
  - Export the main function 
 ### 2. Create The CMakeList.txt File
  - This will create a static library from the module description which will allow it to be handled      - Provides an entry point by registering a command with NuttX to allow it to be called by the PX4 shell and the SITL console
 ### 3. Create a Kconfig Definition File
  Am not entirely sure what it does yet, but my current understanding is that it helps configure the build system
 ### 4. Build The Application/Firmware
  - This is to make sure that the application is built as a part of PX4
  - To enable the compilation of the application into the firmware add the corresponding Kconfig key -```CONFIG_EXAMPLES_PX4_SIMPLE_APP=y```in the px4board file 

# Subscribing to Sensor Data
- To be useful, the application needs to **subscribe to inputs** and **publish output**, ie. servo commands
- For this application, we will use the sensor_combined topic, as it holds the synchronized sensor data of the entire system
- See the **`.c`** file for further comments on the syntax

#  Publishing Sensor Data to Attitude
- A general overview of this situation's publishing is that we essentially collect the polled data into a predefined struct variable that can hold it. After we also place that struct's/variable's data into the struct that is required for the topic that we want to publish to, after that its simply just publishing the memory address of the struct to the topic via a function.
- See the **`.c`** file for further comments on the syntax
