#pragma config(Sensor, S4,     Sonar,          sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
	{
	while (true){
			short ultsonar = 0;
	ultsonar = SensorValue[Sonar];
	nxtDisplayTextLine(2, "%2.2f", ultsonar);

	}
	} // End of task main
