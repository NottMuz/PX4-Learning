############################################################################
#
#   Copyright (c) 2024 PX4 Development Team. All rights reserved.
#

# function for adding a library for this flight task
px4_add_library(FlightTaskMyTask
    FlightTaskMyTask.cpp
)

# take care of dependencies
target_link_libraries(FlightTaskMyTask PUBLIC FlightTask)
target_include_directories(FlightTaskMyTask PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
