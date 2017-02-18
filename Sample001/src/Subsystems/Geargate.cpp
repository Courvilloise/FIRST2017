// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Geargate.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Geargate::Geargate() : Subsystem("Geargate") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    d0LimitOpenSwitch = RobotMap::geargateD0LimitOpenSwitch;
    d1LimitCloseSwitch = RobotMap::geargateD1LimitCloseSwitch;
    pMW7GateEngine = RobotMap::geargatePMW7GateEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    currentPosition = Geargate::notDefined;
    pMW7GateEngine->Set(0.0f);
}

void Geargate::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

// Start to open or close the gate
void Geargate::SetGatePosition(gatePosition Position)
{
	currentPosition = Position;

	if ((Position == Geargate::openGate) && !d0LimitOpenSwitch->Get())
	{
		pMW7GateEngine->Set(-0.75f);
	}
	else if ((Position == Geargate::closeGate) && !d1LimitCloseSwitch->Get())
	{
		pMW7GateEngine->Set(0.75f);
	}
}

// Will stop the engin when an end course contact is reached
void Geargate::Update()
{
	if (((currentPosition == Geargate::openGate) && d0LimitOpenSwitch->Get()) ||
		((currentPosition == Geargate::closeGate) && d1LimitCloseSwitch->Get()) ||
		(currentPosition == Geargate::notDefined))
	{
		pMW7GateEngine->Set(0.0f);
	}
}
