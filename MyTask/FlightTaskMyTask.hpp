//for preprocessing, ensures header file is included only once
#pragma once

//to allow for inheritance
#include "FlightTask.hpp"

//inherit from the FlightTask superclass
class FlightTaskMyTask : public FlightTask
{

public:


//default contstructor
  FlightTaskMyTask() = default;

//virtual default DESTRUCTOR to ensure accurate deletion of objects
  virtual ~FlightTaskMyTask() = default;

//function declerations, including accepted parameters
  bool update();
  bool activate(vehicle_local_position_setpoint_s last_setpoint);

//storage for reference point of the flight task
private:
  float _origin_z{0.f};
};
