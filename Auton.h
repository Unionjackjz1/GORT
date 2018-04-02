void
fivePointScore( bool bSide ) {
	if(bSide) {
		tank(-127, 127);
		delay(750);
		tank(10, -10);
		delay(100);
		tank(-127, -127);
		delay(200);
	}
	else {
		tank(127, -127);
		delay(750);
		tank(-10, 10);
		delay(100);
		tank(-127, -127);
		delay(200);
	}

	tank(10, 10);
	mogoPID(3500);
	tank(-127, -127);
	delay(500);
	tank(0, 0);
}

void
twentyPointScore( bool bSide ) {
	if(bSide) {
		tank(-127, 127);
		delay(250);
		tank(10, -10);
		delay(100);
		tank(0, 0);
		tank(-127, -127);
		delay(800);
		tank(10, 10);
		delay(100);
		tank(-127, 127);
		delay(450);
		tank(10, -10);
		delay(50);
	}
	else{
		tank(127, -127);
		delay(250);
		tank(-10, 10);
		delay(100);
		tank(0, 0);
		tank(-127, -127);
		delay(800);
		tank(10, 10);
		delay(100);
		tank(127, -127);
		delay(450);
		tank(-10, 10);
		delay(50);
	}

	tank(127, 127);
	delay(1250);
	tank(30, 30);
	mogoPID(3000);
	tank(-127, -127);
	delay(1000);
	tank(0, 0);
}

void
autonStart( ) {
	/* Clear Sensors */
	SensorValue[ ARM_SENSOR ] = 0;
	//SensorValue[ LEFT_CHASSIS ] =
	//SensorValue[ RIGHT_CHASSIS ] = 0;

	//Arm up
	armPID(100);
	iArmOutput = 100;
	startTask(armHoldPos);

	//Mobile goal out
	iMogoOutput = 3500;
	startTask(mogoHoldPos);

	//Drive forward to mobile goal and intake mobile goal
	driveStraightPID(1200, 0, 127);
	tank(-10, 10);
	delay(250);
	tank(20, 20);
	stopTask(mogoHoldPos);
	mogoPID(1200);
	tank(0, 0);

	//Move to next cone
	iArmOutput = 150;
	driveStraightPID(1750, 0, 60);
	delay(250);

	//Score preload
	tank(20, 20);
	stopTask(armHoldPos);
	armPID(-20);
	arm(-20);
	translational(-127);
	delay(400);
	translational(-50);

	//Intake
	stopTask(armHoldPos);
	arm(-127);
	delay(250);
	armPID(150);
	startTask(armHoldPos);
	translational(80);
	delay(200);
	translational(20);

	//Drive to third cone
	//driveStraightPID(2200, 0, 50);
	//delay(250);

	//Score second cone
	stopTask(armHoldPos);
	arm(-127);
	delay(250);
	translational(-80);
	delay(200);
	translational(-80);
	arm(-127);
	delay(600);
	iArmOutput = 200;
	startTask(armHoldPos);
	translational(10);

	//Go back
	driveStraightPID(300, 0, 127);
}
