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
#include "../ActionsRecorder.h"
#include "../Definitions.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Geargate::Geargate() : Subsystem("Geargate") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    d0LimitOpenSwitch = RobotMap::geargateD0LimitOpenSwitch;
    d1LimitCloseSwitch = RobotMap::geargateD1LimitCloseSwitch;
    pMW4GateEngine = RobotMap::geargatePMW4GateEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Stop the recorder
	ActionsRecorder::GetInstance()->StopRecord();

    currentPosition = Geargate::closeGate;
    pMW4GateEngine->Set(0.0f);
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
void Geargate::SetGatePosition(gatePosition position)
{
	printf("void Geargate::SetGatePosition(gatePosition %d)\n", position);

	// If we need to record this new command
	if (position != currentPosition)
	{
		currentPosition = position;
		ActionsRecorder::GetInstance()->RecordCommand(FUNC_GEARGATE_SETGATEPOSITION, position);
		printf("ActionsRecorder::GetInstance()->RecordCommand(FUNC_GEARGATE_SETGATEPOSITION, position)\n");
	}

}

// Will stop the engin when an end course contact is reached
void Geargate::Update()
{
	if (currentPosition == Geargate::openGate)
	{
		if (!d0LimitOpenSwitch->Get())
			pMW4GateEngine->Set(0.2f);
		else
			pMW4GateEngine->Set(0.0f);
	}
	else if (currentPosition == Geargate::closeGate)
	{
		if (!d1LimitCloseSwitch->Get())
			pMW4GateEngine->Set(-0.2f);
		else
			pMW4GateEngine->Set(0.0f);
	}
	else
	{
		pMW4GateEngine->Set(0.0f);
	}
}
