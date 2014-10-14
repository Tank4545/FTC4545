//Uses motor encoders to move the FL motor at the start

void floorOneAStrafe()
{
	doneReset();
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorBL] = 0;
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorBR] = 0;
	while(!FLdone || !BLdone || !FRdone || !BRdone)
	{
		if(abs(nMotorEncoder[motorFL]) < 560)
			motor[motorFL] = 60;
		else
		{
			motor[motorFL] = 0;
			FLdone = true;
		}
		if(abs(nMotorEncoder[motorBL]) < 560)
			motor[motorBL] = -60;
		else
		{
			motor[motorBL] = 0;
			BLdone = true;
		}
		if(abs(nMotorEncoder[motorFR]) < 560)
			motor[motorFR] = -60;
		else
		{
			motor[motorFR] = 0;
			FRdone = true;
		}
		if(abs(nMotorEncoder[motorBR]) < 560)
			motor[motorBR] = 60;
		else
		{
			motor[motorBR] = 0;
			BRdone = true;
		}
	}
	doneReset();
}
