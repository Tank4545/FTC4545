#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void initializeRobot(){
	return;
} // end of initialization

task Holodrive()
{
	// Set variables
	short FL = 0;
	short FR = 0;
	short BL = 0;
	short BR = 0;
	short threshold = 5;
	short rot = 0;
	short y1 = 0;
	short x1 = 0;

	while (true){
	/*	motor[motorFL] = FL;
		motor[motorFR] = FR;
		motor[motorBL] = BL;
		motor[motorBR] = BR;
		*/
		// convert joystick input values to motor percentages
	//	rot = ((short)joystick.joy1_x2 * 100) / 127;
	//	y1 = ((short)joystick.joy1_y1 * 100) / 127;
	//	x1 = ((short)joystick.joy1_x1 * 100) / 127;

		// MOVEMENT
		if (abs(y1) >= threshold)
		{
			motor[motorFL] = y1;
			motor[motorFR] = y1;
			motor[motorBL] = y1;
			motor[motorBR] = y1;
		} // End of if
		if (abs(x1) >= threshold)
		{
			motor[motorFL] = x1;
			motor[motorFR] = -x1;
			motor[motorBL] = -x1;
			motor[motorBR] = x1;
		} // End of if
		// Q1
	/*	if (x1 >= threshold && y1 >= threshold)
		{
			FL = sqrt(pow(x1,2) + pow(y1,2));
			FR = 0;
			BL = 0;
			BR = sqrt(pow(x1,2) + pow(y1,2));
		} // End of if
		// Q2
		if (x1 <= -(threshold) && y1 >= threshold)
		{
			FL = 0;
			FR = sqrt(pow(x1,2) + pow(y1,2));
			BL = sqrt(pow(x1,2) + pow(y1,2));
			BR = 0;
		} // End of if
		// Q3
		if (x1 <= -(threshold) && y1 <= -(threshold))
		{
			FL = -(sqrt(pow(x1,2) + pow(y1,2)));
			FR = 0;
			BL = 0;
			BR = -(sqrt(pow(x1,2) + pow(y1,2)));
		} // End of if
		// Q4
		if (x1 >= threshold && y1 <= -(threshold))
		{
			FL = 0;
			FR = -(sqrt(pow(x1,2) + pow(y1,2)));
			BL = -(sqrt(pow(x1,2) + pow(y1,2)));
			BR = 0;
		} // End of if

		// ROTATION
		if (rot >= threshold)
		{
			FL = FL + rot;
			BL = BL + rot;
			FR = FR - rot;
			BR = BR - rot;
		} // End of if
		if (rot <= -1 * threshold)
		{
			FL = FL - rot;
			BL = BL - rot;
			FR = FR + rot;
			BR = BR + rot;
		} // End of if
		*/
	} // End of while true
} // End of task Holodrive

task main()
{
	initializeRobot();
	waitForStart();
	startTask(Holodrive);
	while(true){}
} // End of task main
