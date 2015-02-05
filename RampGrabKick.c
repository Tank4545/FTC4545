#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTGYRO,         sensorI2CMuxController)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeftPulleyT, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLeftPulley, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorManipulator, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorRightPulley, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorRightPulleyT, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motorM,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    servoLeftBridge,      tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    servoRightBridge,     tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servoRearGrabberR,    tServoStandard)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servoRearGrabberL,    tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    servo1,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool ramp = true;
bool FLdone = false;
bool BLdone = false;
bool FRdone = false;
bool BRdone = false;
int _dirAC = 0;
int _dirDC = 0;
int irTotal = 0;
int dcS1, dcS2, dcS3, dcS4, dcS5, acS1, acS2, acS3, acS4, acS5 = 0;
int heading = 0;

#include "reset.h"
#include "JoystickDriver.c"
#include "autonomousChooserNew.h"
#include "moveRobotRearW.h"
#include "setServos.h"
#include "drivers\hitechnic-sensormux.h"
#include "drivers\hitechnic-irseeker-v2.h"
#include "drivers\hitechnic-gyro.h"
#include "gyroTurn.h"
#include "lift.h"
#include "readIR.h"



task timer()
{
	clearTimer(T3);
	while(time1[T3] < 30000)
	{
	}
	while(true){
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
	motor[motorRightPulley] = 0;
	motor[motorLeftPulley] = 0;
	nVolume = 4;
	playSound(soundBeepBeep);
	}
}

void initializeRobot()
{
	HTGYROstartCal(HTGYRO);
	startTask(timer);
	initializeServos(); //Initializes Servos to initial values
	initializeLift(); //Lifts the lift slightly off of the ground
	servo[servoRearGrabberR] = 0; //Moves the servos slightly forward to make sure the ablls dont roll out
	servo[servoRearGrabberL] = 240;
}

task main()
{
	waitForStart();
	initializeRobot();
	moveRobotBL(-30,2.5); //Move backwards down the ramp
	grab(0); //Grab onto the goal
	moveRobotBL(30,0.75); //Move forwards
	gyroTurn(30,45); //Turn 45 degrees right
	moveRobotBL(30,4); //Move back towards parking zone
	gyroTurn(30, 135); //Turn 135 degrees right
	moveRobotBL(-30,1); //Back up to parking zone
	grab(140); //Let go of goal
	moveRobotBL(30,0.75); //Set up to read kickstand position
	while(true){wait1Msec(100);}}
