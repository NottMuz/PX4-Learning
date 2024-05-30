############################################################################
#
#   Copyright (c) 2015 PX4 Development Team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name PX4 nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################


#this method (px4_add_module) builds a static library (a collection of objects linked into a program
	#during the buildprocess), useful in the case of PX4 for handling specific sensors, communication
		#protocols like MAVLink etc
px4_add_module(

	#firmware unique name (px4_simple_app), prefixed by the parent directory that leads to 
		#src (examples__)
	MODULE examples__px4_simple_app
	MAIN px4_simple_app
	SRCS
		px4_simple_app.c
	DEPENDS
	)
	#Note:
	#If you specify DYNAMIC as an option to px4_add_module, a shared library is created instead of a 
	#static library on POSIX platforms (these can be loaded without having to recompile PX4, and 
	#shared to others as binaries rather than source code). Your app will not become a builtin command,
	#but ends up in a separate file called examples__px4_simple_app.px4mod. You can then run your 
	#command by loading the file at runtime using the dyn command: dyn ./examples__px4_simple_app.px4mod