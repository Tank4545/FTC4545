void setServos(int diff)
{
	servo[servoRightBridge] = 240 - diff;
	servo[servoLeftBridge] = diff;
}

void setMotors(int speed)
{
	motor[motorFL] = speed;
	motor[motorBL] = speed;
	motor[motorFR] = speed;
	motor[motorBR] = speed;
}

void hitKickstand()
{
	setMotors(60);
	wait1Msec(1000);
	setMotors(0);
}

void releaseGoal() //Grab onto the rolling goal
{
	servo[servoRearGrabberR] = 0; //Grab onto the rolling goal
	servo[servoRearGrabberL] = 255;
}

void grabGoal() //Release rolling goal
{
	servo[servoRearGrabberR] = 128;
	servo[servoRearGrabberL] = 127;
}
