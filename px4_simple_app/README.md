# Minimal Application
  - This folder contains the necessary code for creating an application for the PX4 platform
  - You will see that the **`main`** function is created in a **`.c`** file
  - For further comments on the syntax of the code see the **`.c`** file
# General Overview
 ### 1. Create The .c File
     - Export the main function 
 ### 2. Create The CMakeList.txt File
     - This will create a static library from the module description which will allow it to be handled      - Provides an entry point by registering a command with NuttX to allowed it to be called by the PX4 shell and the SITL console
 ### 3. Create a Kconfig Definition File
  
