# sandstorm
Repository for Team Sandstorm's OSV

# sandstorm Repository Organization

##Sandstorm
sandstorm 			- definitions, initialization

##Sensor

sensor_color 		    - color sensor functions, uses library

sensor_ultrasonic 	- ultrasonic sensor computations

sensor_pressure 		- pressure sensor computations

##Motor

motor_control		- motor controller operations

motor_lift			- lift functions, uses motor_control

motor_drive		  - drive functions, uses motor_control

##Task

task_general		  - most general task, executes other tasks

task_manipulation	- manipulation code for final phase

task_path			- basic path navigation algorithm

task_update		- rotation/distance error calculation

Code in .ino files will be rewritten to work in cpp files, possibly with object-oriented organization
