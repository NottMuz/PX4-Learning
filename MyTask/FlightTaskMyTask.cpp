#include "FlightTaskMyTask.hpp"

bool FlightTaskMyTask::activate(vehicle_local_position_setpoint_s last_setpoint)
{
  bool ret = FlightTask::activate(last_setpoint);
  PX4_INFO("FlightTaskMyTask activate was called! ret: %d", ret); // report if activation was successful
  return ret;
}

bool FlightTaskMyTask::update()
{
  PX4_INFO("FlightTaskMyTask update was called!"); // report update
  return true;
}
