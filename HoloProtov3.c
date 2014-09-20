#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void initializeRobot(){
	return;
} // end of initialization


	task HoloDrive()
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		float num = 0.00;
		float FL = 0.00;
		float BL = 0.00;
		float FR = 0.00;
		float BR = 0.00;
		while(true)
		{
			getJoystickSettings(joystick);
			x1 = joystick.joy1_x1;
			y1 = joystick.joy1_y1;
			x2 = joystick.joy1_x2;

			x1 = x1 / 1.28;
			y1 = y1 / 1.28;
			x2 = x2 / 1.28;

			FL = x1 + y1 - x2;
			BL = x1 + y1 + x2;
			FR = x1 - y1 + x2;
			BR = x1 - y1 - x2;

			/*if(abs(FL) >= abs(BL) && abs(FL) >= abs(FR) && abs(FL) >= abs(BR) && abs(FL) > 100)
			{
				num = FL / 100;
				FL = FL / num;
				BL = BL / num;
				FR = FR / num;
				BR = BR / num;
			} // end of if
			if(abs(BL) >= abs(FL) && abs(BL) >= abs(FR) && abs(BL) >= abs(BR) && abs(BL) > 100)
			{
				num = BL / 100;
				FL = FL / num;
				BL = BL / num;
				FR = FR / num;
				BR = BR / num;
			} // end of if
			if(abs(FR) >= abs(FL) && abs(FR) >= abs(BL) && abs(FR) >= abs(BR) && abs(FR) > 100)
			{
				num = FR / 100;
				FL = FL / num;
				BL = BL / num;
				FR = FR / num;
				BR = BR / num;
			} // end of if
			if(abs(BR) >= abs(FL) && abs(BR) >= abs(BL) && abs(BR) >= abs(FR) && abs(BR) > 100)
			{
				num = BR / 100;
				FL = FL / num;
				BL = BL / num;
				FR = FR / num;
				BR = BR / num;
			} // end of if*/

			//All Motors at 1/4 speed
			FL = FL * 0.25;
			BL = BL * 0.25;
			FR = FR * 0.25;
			BR = BR * 0.25;

			//Run the motors
			if(abs(joystick.joy1_x1) >= 10 || abs(joystick.joy1_y1) >= 10 || abs(joystick.joy1_y2) >= 10)
			{
			motor[motorFL] = FL;
			motor[motorBL] = BL;
			motor[motorFR] = -FR;
			motor[motorBR] = -BR;
			}
			else{
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
			}
			wait1Msec(7);
		}
}

	task main()
	{
		initializeRobot();
		waitForStart();
		startTask(HoloDrive);
		while(true){wait1Msec(1);}
	} // End of task main
