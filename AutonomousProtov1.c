#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTGYRO,         sensorAnalogInactive)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     Sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorManipulator, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop)
//#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "drivers\hitechnic-sensormux.h"
#include "drivers\hitechnic-irseeker-v2.h"
#include "drivers\hitechnic-gyro.h"

tHTIRS2DSPMode _mode = DSP_1200;
int _dirDC = 0;
int _dirAC = 0;
int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
int acS1, acS2, acS3, acS4, acS5 = 0;
int irNear = 0;
int irFar = 0;
int irDist = 0;
int irSect = 0;
int irTotal = 0;
int preset = 0;
int num = 0;
int ramp = 0;
int red = 0;
int blue = 0;
int irMax = 0;
int irAvg = 0;
int kickBlueOneNum = 0;
float ultsonar = 0.0;
int magicKey = 0;
int irTotalOld = 0;
int alignDir = 20;
int final = 0;
int count = 0;
bool FLdone = true;
bool BLdone = true;
bool FRdone = true;
bool BRdone = true;

void initializeRobot()
{
	return;
} // end of initialization

void StopAll()
{
	stopAllTasks();
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
	while(true){	wait10Msec(3000);}
}

task blueOneMoveFL()
{
	nMotorEncoder[motorFL] = 0;
	while(nMotorEncoder[motorFL] < 560)
	{
		motor[motorFL] = 60;
	}
	motor[motorFL] = 0;
	bool FLdone = false;
	stopTask(blueOneMoveFL);
}

task blueOneMoveBL()
{
	nMotorEncoder[motorBL] = 0;
	while(nMotorEncoder[motorBL] < 560)
	{
		motor[motorBL] = 60;
	}
	motor[motorBL] = 0;
	bool BLdone = false;
	stopTask(blueOneMoveBL);
}

task blueOneMoveFR()
{
	nMotorEncoder[motorFR] = 0;
	while(nMotorEncoder[motorFR] < 560)
	{
		motor[motorFR] = 60;
	}
	motor[motorBL] = 0;
	bool FRdone = false;
	stopTask(blueOneMoveFR);
}

task blueOneMoveBR()
{
	nMotorEncoder[motorBR] = 0;
	while(nMotorEncoder[motorBR] < 560)
	{
		motor[motorBR] = 60;
	}
	motor[motorBR] = 0;
	bool BRdone = false;
	stopTask(blueOneMoveBR);
}

task blueOneAlignFL()
{
	nMotorEncoder[motorFL] = 0;
	while(nMotorEncoder[motorFL] < (560 / count)
	{
		motor[motorFL] = 60;
	}
	motor[motorFL] = 0;
	bool FLdone = false;
	stopTask(blueOneAlignFL);
}

task blueOneAlignBL()
{
	nMotorEncoder[motorBL] = 0;
	while(nMotorEncoder[motorBL] > (-560 / count)
	{
		motor[motorBL] = -60;
	}
	motor[motorBL] = 0;
	bool BLdone = false;
	stopTask(blueOneAlignBL);
}

task blueOneAlignFR()
{
	nMotorEncoder[motorFR] = 0;
	while(nMotorEncoder[motorFR] > (-560 / count)
	{
		motor[motorFR] = -60;
	}
	motor[motorFR] = 0;
	bool FRdone = false;
	stopTask(blueOneAlignFR);
}

task blueOneAlignBR()
{
	nMotorEncoder[motorBR] = 0;
	while(nMotorEncoder[motorBR] < (560 / count)
	{
		motor[motorBR] = 60;
	}
	motor[motorBR] = 0;
	bool BRdone = false;
	stopTask(blueOneAlignBR);
}

task emergency()
{
	if(joy1Btn(8))
	{
		StopAll();
		//stop program???
	}
}

void startPos()
{
	_dirDC = HTIRS2readDCDir(HTIRS2);
	_dirAC = HTIRS2readACDir(HTIRS2);
	HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5);
	HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5);
	irFar = acS3;
	irNear = dcS3;
	if(irNear >= 30 && irNear <= 60)
	{
		if(irNear <= 60 && irNear >= 55)
			irDist = 15;
		else if(irNear <= 55 && irNear >= 37)
			irDist = 20;
		else if(irNear <= 37 && irNear >= 30)
			irDist = 25;
	}
	else
	{
		if(irFar <= 200 && irFar >= 190)
			irDist = 15;
		else if(irFar <= 190 && irFar >= 188)
			irDist = 20;
		else if(irFar <= 188 && irFar >= 183)
			irDist = 30;
		else if(irFar <= 183 && irFar >= 172)
			irDist = 35;
		else if(irFar <= 172 && irFar >= 145)
			irDist = 40;
		else if(irFar <= 145 && irFar >= 137)
			irDist = 45;
		else if(irFar <= 137 && irFar >= 131)
			irDist = 50;
		else if(irFar <= 131 && irFar >= 120)
			irDist = 55;
		else if(irFar <= 120 && irFar >= 109)
			irDist = 60;
		else if(irFar <= 109 && irFar >= 100)
			irDist = 65;
		else if(irFar <= 100 && irFar >= 92)
			irDist = 70;
		else if(irFar <= 92 && irFar >= 90)
			irDist = 75;
		else if(irFar <= 90 && irFar >= 88)
			irDist = 80;
		else if(irFar <= 88 && irFar >= 85)
			irDist = 85;
		else if(irFar <= 85 && irFar >= 75)
			irDist = 90;
		else if(irFar <= 75 && irFar >= 67)
			irDist = 100;
		else if(irFar <= 67 && irFar >= 62)
			irDist = 105;
		else if(irFar <= 62 && irFar >= 56)
			irDist = 110;
		else
			irDist = -10;
	}
	if(true)// if(_dirAC >= 4 && _dirAC <= 6 && _dirDC >= 4 && _dirDC <= 6)
	{
		preset = 1;
		num = 1;
	}
	else if(_dirAC == 0 && _dirDC == 0)
	{
		preset = 3;
		num = 1;
	}
	else{
		preset = 2;
	}
}

void kickBlueOne()
{
	motor[motorFL] = 70;
	motor[motorBL] = 70;
	motor[motorFR] = 70;
	motor[motorBR] = 70;
	wait1Msec(1000);
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
	wait1Msec(500);
	motor[motorFL] = -70;
	motor[motorBL] = -70;
	motor[motorFR] = -70;
	motor[motorBR] = -70;
	wait1Msec(900);
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
}

task liftCenter()
{
	PlaySound(soundBeepBeep);
	//play sound
	wait1Msec(5000);
	stopTask(liftCenter);
}

void alignOne()
{
	int count = 0;
	irTotal = 0;
	for(int i = 0; i <= 25; i++)
	{
		_dirDC = HTIRS2readDCDir(HTIRS2);
		_dirAC = HTIRS2readACDir(HTIRS2);
		if(!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
			wait1Msec(0);
		if(!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS4))
			wait1Msec(0);
		irTotal = irTotal + acS3 + dcS3;
		wait1Msec(5);
	}
	irMax = irTotal;
	startTask(blueOneMoveFL);//motor[motorFL] = -50;
	startTask(blueOneMoveBL); //motor[motorBL] = 50;
	startTask(blueOneMoveFR); //motor[motorFR] = 50;
	startTask(blueOneMoveBR); //motor[motorBR] = -50;
	while(FLdone && BLdone && FRdone && BRdone)
	{
		wait1Msec(10);
	}// == 1 && BR
	FLdone = true;
	BLdone = true;
	FRdone = true;
	BRdone = true;
	while(final == 0)
	{
		startTask(blueOneAlignFL); //motor[motorFL] = alignDir * 2;
		startTask(blueOneAlignBL); //motor[motorBL] = alignDir * -2;
		startTask(blueOneAlignFR); //= alignDir * -2;
		startTask(blueOneAlignBR); //motor[motorBR] = alignDir * 2;
		while(FLdone && BLdone && FRdone && BRdone)
		{
			wait1Msec(10);
		}// == 1 && BR
		wait1Msec(200);
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		irTotal = 0;
		for(int i = 0; i <= 25; i++)
		{
			_dirDC = HTIRS2readDCDir(HTIRS2);
			_dirAC = HTIRS2readACDir(HTIRS2);
			if(!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
				wait1Msec(0);
			if(!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS4))
				wait1Msec(0);
			irTotal = irTotal + acS3 + dcS3;
			wait1Msec(5);
			//string output =  irTotal + "";
			writeDebugStreamLine("int x is %d", irTotal);
		}
		//int temp = irTotal + 100;
		if(irMax > irTotal)
		{
			alignDir = alignDir * -1;
			count = count + 1;
		}
		else if(irMax < irTotal && count > 2)
		{
			final = 1;
		}
		else if(irTotalOld < irTotal)
		{
			irMax = irTotal;
			alignDir = alignDir;
		}
		else
		{
			alignDir = alignDir;
		}
	}
	while(ultsonar >= 20.0)
	{
		wait1Msec(5);
		motor[motorFL] = 20;
		motor[motorBL] = 20;
		motor[motorFR] = 20;
		motor[motorBR] = 20;
		wait1Msec(10);
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		wait1Msec(50);
		ultsonar = SensorValue[Sonar];
	}
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
	startTask(liftCenter);
}

void autoType()
{
	//Starting on blue ramp
	//blue = 1;
	//ramp = 1;

	//Starting on blue floor
	blue = 1;
	ramp = 0;

	//Starting on red ramp
	//red = 1;
	//ramp = 1;

	//Starting on red floor
	//red = 1;
	//ramp = 0;

	if(blue == 1)
		red = 0;
	if(red == 1)
		blue = 0;
}

void one()
{
	irDist = 0;
	irNear = 0;
	irMax = 0;
	if(blue == 1 && ramp == 1)
	{
		//run down the ramp, run through kickstand
	}
	else if(blue == 1 && ramp == 0)
	{
		kickBlueOne();
		int count = 0;
		count = count + 1;
		irTotal = 0;
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		for(int i = 0; i <= 15; i++)
		{
			_dirDC = HTIRS2readDCDir(HTIRS2);
			_dirAC = HTIRS2readACDir(HTIRS2);
			if(!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
				wait1Msec(0);
			if(!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS4))
				wait1Msec(0);
			irTotal = irTotal + acS3 + dcS4;
			wait1Msec(5);
		}
		ultsonar = SensorValue[Sonar];

		alignOne();
		/*if(irTotal > irMax && count > 1)
		{
		while(ultsonar >= 20.0)
		{
		wait1Msec(5);
		motor[motorFL] = 20;
		motor[motorBL] = 20;
		motor[motorFR] = 20;
		motor[motorBR] = 20;
		wait1Msec(5);
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		ultsonar = SensorValue[Sonar];
		}
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		startTask(liftCenter);
		}
		else if(count == 1)
		{
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		}
		else
		{
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
		}

		}*/
	}
}


task two()
{
	int a = 0;
}

task three()
{
	int a = 0;
}

task oneA()
{
	int a = 0;
}

task main()
{
	initializeRobot();
	//waitForStart();
	startTask(emergency);
	autoType();
	startPos();
	if(preset == 1)
		one();
	else if(preset == 2)
		startTask(two);
	else if(preset == 3)
		startTask(three);
	while(true){}
}
