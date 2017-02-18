// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Catapult.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Catapult::Catapult() : Subsystem("Catapult") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    pMW4AgitatorEngine = RobotMap::catapultPMW4AgitatorEngine;
    cAN1ThrowEngine = RobotMap::catapultCAN1ThrowEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	currentSpeed = 0.0f;
	savedSpeed = 0.0f;
	valueSaved = false;

	//pCAN1ThrowEngine->SetControlMode(CANTalon::kDisabled);
	Stop();
}

void Catapult::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Specify the speed of the motor that throw balls. Range between 0.0 to 1.0
void Catapult::SetRotationSpeed(double speed)
{
	// Make sur the value are in a valid range
	if (speed < 0.0f)
		speed = 0.0f;
	else if (speed > 1.0f)
		speed = 1.0f;

	// We multiply by -1.0f to have the motor throwing on the right direction
	cAN1ThrowEngine->Set(speed);
	currentSpeed = speed;

	// If we have enough speed, we should start the agitator;
	if (std::abs(currentSpeed) > 0.01)
	{
		pMW4AgitatorEngine->Set(0.3);
	}
	else
	{
		pMW4AgitatorEngine->Set(0.0);
	}
}

// Increase (or decrase) the current speed by a specific delta. Range between -1.0 to 1.0
void Catapult::IncreaseSpeed(double delta)
{
	SetRotationSpeed(currentSpeed + delta);
}

// Completely stop the motor that throw balls
void Catapult::Stop()
{
	cAN1ThrowEngine->Set(0.0);
	currentSpeed = 0.0;
	pMW4AgitatorEngine->Set(0.0);
}

// Save the current speed
void Catapult::SaveCurrentSpeed()
{
	// We copy the current speed in our a memory.. :)
	savedSpeed = currentSpeed;
	valueSaved = true;
}

// Restore the speed with the previous value.
void Catapult::RestoreSavedSpeed(double defaultSpeed)
{
	// If no previous value saved, we will apply the default speed
	if (!valueSaved)
	{
		SetRotationSpeed(defaultSpeed);
		return;
	}

	SetRotationSpeed(savedSpeed);
}

