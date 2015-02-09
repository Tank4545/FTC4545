#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeftPulleyT, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLeftPulley, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorRightPulleyT, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorRightPulley, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S4_C1_1,    servoLeftBridge,      tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    servoRightBridge,     tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servoRearGrabberR,    tServoStandard)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servoRearGrabberL,    tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    servo1,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/


#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		//left is downz`1xx
		if(nNxtButtonPressed == 1)
		{
			motor[motorRightPulley] = -100;
			motor[motorRightPulleyT] = -100;
			motor[motorLeftPulley] = -100;
			motor[motorLeftPulleyT] = -100;
			wait1Msec(50);
		}
		if(nNxtButtonPressed == 2)
		{
			motor[motorRightPulley] = 100;
			motor[motorRightPulleyT] = 100;
			motor[motorLeftPulley] = 100;
			motor[motorLeftPulleyT] = 100;
			wait1Msec(50);
		}
		else
		{
			motor[motorRightPulley] = 0;
			motor[motorRightPulleyT] = 0;
			motor[motorLeftPulley] = 0;
			motor[motorLeftPulleyT] = 0;
		}
	}
}
