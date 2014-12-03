void gyroTurn(bool left, int speed, int goal)
{
	float divisor = 0;
	//Establishing divisor values
	if(goal == 90)
		divisor = 0.85;
	else if(goal == 45)
		divisor = 0.76;
	else
		divisor = 1;
	clearScreen();
	int rotPos = 0;
	int num = 0;
	float rotVel = 0;
	int position = 0;
	if(left)
		speed = speed * -1;
	while(abs(position) < abs(goal))
	{
		clearTimer(T3);
		motor[motorFL] = speed;
		motor[motorBL] = speed;
		motor[motorFR] = -speed;
		motor[motorBR] = -speed;
		wait1Msec(100);
		num = time1(T3) / 1000;
		rotPos = HTGYROreadCal(HTGYRO);
		rotVel = HTGYROreadRot(HTGYRO);
		if(abs(rotVel) > 10)
		{
			rotVel = rotVel * divisor;
			position = position + rotVel / (1000 / time1(T3));
		}
		nxtDisplayCenteredTextLine(2, "position: %d", position);
	}
	stopMotors();
	wait1Msec(500);
}
