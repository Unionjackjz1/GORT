#pragma systemfile

/* Arm Controllers */
void
armPID( int iDes ) {
	float kP = 0.8;
	float kD = 0.5;
	int i = 0;
	int iError = (iDes - getArm());
	int iLastError, iDer;
	while(abs(iError)>30 && i < (1000)/25) {
		i++;
		iDer = (iError - iLastError)/25;
		iError = (iDes - getArm());
		arm((iError*kP)+(iDer*kD));
		delay( 25 ); //Don't hog the CPU!
		iLastError = iError;
	}
}

/* Chassis Controllers */
void
driveStraightPID( int iDes, int iDesAngle, int iMaxPower ) {
	iDesAngle = fDegreeToRadians(iDesAngle);
	float kP = 1;
	int i = 0;
	int iLeftDriveError  = (iDes - getLeftChassis());
	int iRightDriveError = (iDes - getRightChassis());
	int iAngleError;
	while(abs(iLeftDriveError)>50 && i < 2000) {
		i++;
		iAngleError = (iDesAngle - getCurrentAngle());
		//Drive P
		iLeftDriveError  = (iDes - getLeftChassis());
		iRightDriveError = (iDes - getRightChassis());
		tankWithoutTrueSpeed(clipNum(iLeftDriveError*kP, iMaxPower),
			clipNum(iLeftDriveError*kP, iMaxPower));
		delay( 1 ); //Don't hog the CPU!
	}
	tankWithoutTrueSpeed(-10, -10);
}

/* Mogo PID */
void
mogoPID( int iDes ) {
	float kP = 0.5;
	int i = 0;
	int iError = (iDes - getMogoSensor());
	while(abs(iError)>50 && i < 1000) {
		i++;
		iError = (iDes - getMogoSensor());
		mogoSet(iError*kP);
		delay(1);
	}
	mogoSet(0);
}

int iMogoOutput;
task
mogoHoldPos( ) {
	while(true) {
		mogoSet((iMogoOutput-getMogoSensor())*0.5);
	}
}

void
translationalControl( ) {
	static int  iPassive;
	if(vexRT[Btn5UXmtr2]) {
		translational(127);
		iPassive = 20;
	}
	else if(vexRT[Btn5DXmtr2]) {
		translational(-127);
		iPassive = -20;
	}
	else{
		translational(iPassive);
	}
}
