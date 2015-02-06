#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorNull,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLeftPulley, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorManipulator, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorRightPulley, tmotorTetrix, openLoop, reversed)
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

void initializeRobot()
{

}

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
task main()
{
	waitForStart();
	initializeRobot();
	HTGYROstartCal(HTGYRO);
	startTask(timer);
	initializeServos(); //Initializes Servos to initial values
	initializeLift(); //Lifts the lift slightly off of the ground
	servo[servoRearGrabberR] = 0; //Moves the servos slightly forward to make sure the ablls dont roll out
	servo[servoRearGrabberL] = 240;
	moveRobotBL(30,0.75); //Move forward for better readings
	//while(true){
	irTotal = readIR(); //Read the IR value
	_dirDC = HTIRS2readACDir(HTIRS2);
	nxtDisplayCenteredBigTextLine(2,"%d",_dirDC);
	//}

	if(acS2 > 11) //If preset 2
	{
		gyroTurn(30,-45); //Turn Left 45 degrees
		moveRobotBL(30,2.105); //Move forward
		gyroTurn(30,-62.5); //Turn Left 90 degrees
		//moveRobotBL(30,1); //Move forward
		liftCenter(); //Raise the lift to the center goal
		moveRobotBL(-20,0.8); //Back up to the center goal
		dumpCenter(); //Dump the balls in the center goal
		moveRobotBL(20,0.5); //Move away from the center goal
		lowerCenter(); //Lower the lift
		gyroTurn(45,-90); //Turn Left 90 Degrees
		moveRobotBL(45,0.75); //Move forward
		gyroTurn(45,-80); //Turn Left 90 degrees
		hitKickstand(); //Run into the kickstand
	}
	else if(acS3 > 25) //If preset 3
	{
		//moveRobotBL(30,0.5); //Move forward more
		gyroTurn(55,165); //Turn Right 90 degrees
		//gyroTurn(45,90); //Turn Right 90 degrees
		//moveRobotBL(-30,1); //Back up to the center goal
		liftCenter(); //Raise the lift to the center goal
		motor[motorRightPulley] = 30;
		motor[motorLeftPulley] = 30;
		moveRobotBL(-20,1.14); //Back up to center goal
		dumpCenter(); //Dump the balls in the center goal
		moveRobotBL(30,0.5); //Move back forwards
		motor[motorRightPulley] = 0;
		motor[motorLeftPulley] = 0;
		lowerCenter(); //Lower the lift to the floor
		gyroTurn(45,-90); //Turn 90 degrees to the left
		moveRobotBL(45,0.5); //Move forwards
		gyroTurn(45,-60); //Turn 90 degrees to the left
		//gyroTurn(40,-15); //Turn an additional 20 degrees to the left
		hitKickstand(); //Run into the kickstand
		//liftToGround();
	}
	else //If preset 1
	{
		gyroTurn(30,-45); //Turn Left 45 Degrees
		moveRobotBL(30,3.15); //Move forward
		gyroTurn(30,-45); //Turn Left 45 Degrees
		moveRobotBL(-30,0.75); //Back up to the center goal
		liftCenter(); //Raise the lift to the center goal
		moveRobotBL(-20,0.4); //Back up to the center goal
		dumpCenter(); //Dump the balls in the center goal
		moveRobotBL(20,0.5); //Move away form the center goal
		lowerCenter(); //Lower the lift
		gyroTurn(45,-90); //Turn Left 90 Degrees
		moveRobotBL(45,0.35); //Move forward
		gyroTurn(45,-50); //Turn Left 90 degrees
		hitKickstand(); //Run into the kickstand
	}
	while(true){wait1Msec(100);}
}
