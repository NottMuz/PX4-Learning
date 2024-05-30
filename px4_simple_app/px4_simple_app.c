/****************************************************************************
 *
 *   Copyright (c) 2012-2019 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file px4_simple_app.c
 * Minimal application example for PX4 autopilot
 *
 * @muzz  User <muzzammil.r04@example.com>
 */

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>
#include <px4_platform_common/posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>

#include <uORB/uORB.h>


#include <px4_platform_common/log.h>

//imports the sensor_combined topic for subscription
#include <uORB/topics/sensor_combined.h>

//imports the vehicle_attitude topic for publication
#include <uORB/topics/vehicle_attitude.h>


//The main function must be named <module_name>_main and exported from the module as shown.
__EXPORT int px4_simple_app_main(int argc, char *argv[]);




int px4_simple_app_main(int argc, char *argv[])
{
	//PX4_INFO is the equivalent of printf for the PX4 shell (included from px4_platform_common/log.h). 
		//There are different log levels: PX4_INFO, PX4_WARN, PX4_ERR, PX4_DEBUG. Warnings and errors are 
			//additionally added to the ULog 
	PX4_INFO("Hello Sky!");





//-------------------------------------SUBSCRIBING-------------------------------------------------------
	
	//creates a subscription to the uORB message being sent by the sensor_combined topic via 
		//its ORB (Object Request Broker) ID that is created by the ORB_ID function
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	//Note: The syntax here is quite interesting to me;
		// int : identifies the variable type of the fd (file descriptor), after research it now makes sense
				// a fd is a low-level interger handle used by an OS to identify things like files, sockets, pipes etc.
		// sensor_sub_fd : this is the name of the file descriptor, this variable uniquely identifies
				// this subscription to the topic, will be used to interact with it
	

	/* limit the update rate to 5 Hz */
	orb_set_interval(sensor_sub_fd, 200);

//--------------------------------------------------------------------------------------------------------




//-------------------------------------ADVERTISING/PUBLISHING---------------------------------------------
	//This structure will be used to hold the attitude data for the vehicle
	struct vehicle_attitude_s att;

	//initializes all fields in the "att" structure to 0
	memset(&att, 0, sizeof(att));

	//setups up the advertisement variable, and gives the memory address of the data being advertised
	orb_advert_t att_pub_fd = orb_advertise(ORB_ID(vehicle_attitude), &att);
//--------------------------------------------------------------------------------------------------------




//-------------------------------------POLLING/LISTENING--------------------------------------------------
/*
	- "px4_pollfd_struct_t": It is a STRUCTURE TYPE defined by the Pixhawk codebase that provides a format
	   to poll information

	- ".fd": The struct requires the file descriptor so it knows where to poll info from

	- ".events": Identifies what type of polling/polling information is being collects, see the documentation 
		for the other commands
*/
/* one could wait for multiple topics with this technique, just using one here */
px4_pollfd_struct_t fds[] = {
    { .fd = sensor_sub_fd,   .events = POLLIN },
		/* there could be more file descriptors here, in the form like:
		 * { .fd = other_sub_fd,   .events = POLLIN },
		 */
};
//--------------------------------------------------------------------------------------------------------







int error_counter = 0;
//-------------------------------------DISPLAYING & PUBLISHING DATA--------------------------------------------------
//will poll and process sensor data 5 times
for (int i = 0; i < 5; i++) {
	
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		int poll_ret = px4_poll(fds, 1, 1000);

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			PX4_ERR("Got no data within a second");

		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				PX4_ERR("ERROR return value from poll(): %d", poll_ret);
			}

			error_counter++;

		} else {

			if (fds[0].revents & POLLIN) {
				/* obtained data for the first file descriptor */
				struct sensor_combined_s raw;
				/* copy sensors raw data into local buffer */
				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
				PX4_INFO("Accelerometer:\t%8.4f\t%8.4f\t%8.4f",
					 (double)raw.accelerometer_m_s2[0],
					 (double)raw.accelerometer_m_s2[1],
					 (double)raw.accelerometer_m_s2[2]);

				/* set att and publish this information for other apps
				 the following does not have any meaning, it's just an example
				*/
				att.q[0] = raw.accelerometer_m_s2[0];
				att.q[1] = raw.accelerometer_m_s2[1];
				att.q[2] = raw.accelerometer_m_s2[2];

				orb_publish(ORB_ID(vehicle_attitude), att_pub, &att);
			}

			/* there could be more file descriptors here, in the form like:
			 * if (fds[1..n].revents & POLLIN) {}
			 */
		}
	}
//--------------------------------------------------------------------------------------------------------









//-------------------------------------DISPLAYING DATA--------------------------------------------------

//creates an infinite loop, useful for continous operation in embedded systems etc.
//while (true) {

	/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
	//int poll_ret = px4_poll(fds, 1, 1000);
	//..

	//if there is data for the first entry in the array in the .revents feild (in the form of 0b0001)
		// and it matches the value of POLLIN (in the form of 0b0001)
	//remeber that '&' is a bitwise operation, and compares bit values which is what is done here
	//if (fds[0].revents & POLLIN)//essentially checks if there is data to be read

	 	//{
		/* obtained data for the first file descriptor */
		//this struct is able to hold the combined sensor data
		//struct sensor_combined_s raw;

		/* copy sensors raw data into local buffer (raw) */
		//orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);

		// displays the data from it
		//PX4_INFO("Accelerometer:\t%8.4f\t%8.4f\t%8.4f",
					//(double)raw.accelerometer_m_s2[0],
					//(double)raw.accelerometer_m_s2[1],
					//(double)raw.accelerometer_m_s2[2]);
		//}
	//}	
//--------------------------------------------------------------------------------------------------------
	PX4_INFO("exiting");

	return OK;
}


