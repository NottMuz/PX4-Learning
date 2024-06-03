#  Creation & Implementation of a Task
- Will provide an overview of all the steps required to create a task

### 1. Create a directory for the new flight task in PX4-Autopilot/src/modules/flight_mode_manager/tasks
### 2. Create empty source code and cmake files for the new flight task in the MyTask directory using the prefix "FlightTask":

- CMakeLists.txt
- FlightTaskMyTask.hpp
- FlightTaskMyTask.cpp

### 3. Update CMakeLists.txt for the new task
- This .txt file is used to resolve the dependencies of the library

### 4. Update the header file (in this case FlightTaskMyTask.hpp): Most tasks reimplement the virtual methods activate() and update()
- The .hpp file basically defines the structure of a MyTask class

### 5. Update the cpp file as appropriate. This example provides as simple implementation of FlightTaskMyTask.cpp that simply indicates that the task methods are called.
- See the .cpp file for more info

### 6. Add the new task to the list of tasks to be built in PX4-Autopilot/src/modules/flight_mode_manager/CMakeLists.txt

### 7. Update a flight mode to ensure that the task is called. Usually a parameter is used to select when a particular flight task should be used.

For example, to enable our new MyTask in multicopter Position mode:

- Update MPC_POS_MODE (mc_pos_control_params.c

(opens new window)) to add an option for selecting "MyTask" if the parameter has a previously unused value like 5:

```cpp
* @value 4 Acceleration based input
* @value 5 MyTask position mode implementation
* @group Multicopter Position Control
*/
PARAM_DEFINE_INT32(MPC_POS_MODE, 4);
```

### 8. Add a case for your new option in the switch for the parameter FlightModeManager.cpp to enable the task when _param_mpc_pos_mode has the right value.

```cpp
switch (_param_mpc_pos_mode.get()) {
  ...
  case 3:
     error = switchTask(FlightTaskIndex::ManualPositionSmoothVel);
     break;
  case 5: // Add case for new task: MyTask
     error = switchTask(FlightTaskIndex::MyTask);
     break;
```
