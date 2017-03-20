// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "Vehicle.h"
#include "../RobotMap.h"
#include "../Commands/GamePadDrive.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Vehicle::Vehicle() : Subsystem("Vehicle") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    pMW2LeftEngine = RobotMap::vehiclePMW2LeftEngine;
    pMW0LeftEngine = RobotMap::vehiclePMW0LeftEngine;
    pMW3RightEngine = RobotMap::vehiclePMW3RightEngine;
    pMW1RightEngine = RobotMap::vehiclePMW1RightEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Stop the recorder
	ActionsRecorder::GetInstance()->StopRecord();
    Stop();
}

void Vehicle::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new GamePadDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Vehicle::Stop()
{
	pMW0LeftEngine->Set(0.0f);
	pMW2LeftEngine->Set(0.0f);
	pMW3RightEngine->Set(0.0f);
	pMW1RightEngine->Set(0.0f);

	// Will record the new values of the speeds if different than previous values..
	if ((currentLeftSpeed != 0.0f) ||
	    (currentRightSpeed != 0.0f))
	{
		currentLeftSpeed = 0.0f;
	    currentRightSpeed = 0.0f;
		ActionsRecorder::GetInstance()->RecordCommand(FUNC_VEHICLE_STOP, currentLeftSpeed, currentRightSpeed);
	}
}

// The vehicle will move
// Full speed forward is +1.0
// Full speed reverse is -1.0
void Vehicle::Move(double leftSpeed, double rightSpeed)
{
	// Make sure the leftPower is clipped in the supported range by the Vehicle
	if (leftSpeed > 1.0f)
		leftSpeed = 1.0f;
	if (leftSpeed < -1.0f)
		leftSpeed = -1.0f;

	// Make sure the rightPower is clipped in the supported range by the Vehicle
	if (rightSpeed > 1.0f)
		rightSpeed = 1.0f;
	if (rightSpeed < -1.0f)
		rightSpeed = -1.0f;

	// Will record the new values of the speeds if different than previous values..
	if ((leftSpeed != currentLeftSpeed) ||
	    (rightSpeed != currentRightSpeed))
	{
		currentLeftSpeed = leftSpeed;
		currentRightSpeed = rightSpeed;

		ActionsRecorder::GetInstance()->RecordCommand(FUNC_VEHICLE_MOVE, leftSpeed, rightSpeed);
	}


	// The right engines rotates in the opposite side of the left engines
	rightSpeed = rightSpeed * -1.0f;

	// Set the power on the first pair engines
	pMW0LeftEngine->Set(leftSpeed);
	pMW2LeftEngine->Set(leftSpeed);

	// Set the power on the second pair engines
	pMW1RightEngine->Set(rightSpeed);
	pMW3RightEngine->Set(rightSpeed);

	//printf("leftSpeed = %f, rightSpeed = %f\n", leftSpeed, rightSpeed);
}


