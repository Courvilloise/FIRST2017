// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "GamePadDrive.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GamePadDrive::GamePadDrive(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::vehicle.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

	btnRecordPressed = false;
	btnToggleGatePressed = false;
	posGearGate = Geargate::openGate;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GamePadDrive::Initialize() {
	pJoystick = Robot::oi->getJoystick();
	int nAxis = pJoystick->GetAxisCount();
	printf("Number of Gamepad axis = %d\n", nAxis);

	// We start with an open gate
	posGearGate = Geargate::openGate;
	(Robot::geargate.get())->SetGatePosition(posGearGate);
}

// Called repeatedly when this Command is scheduled to run
void GamePadDrive::Execute()
{
//	UpdateRecorder(); // Should be the first function called if we want to record all calls
	UpdateVehicle();
	UpdateCatapult();
	UpdateWinch();
	UpdateGearGate();
}

// Make this return true when this Command no longer needs to run execute()
bool GamePadDrive::IsFinished()
{
    return false;
}

// Called once after isFinished returns true
void GamePadDrive::End()
{
	(Robot::vehicle.get())->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GamePadDrive::Interrupted()
{

}

// Update the vehicle based on the gamepad command
void GamePadDrive::UpdateVehicle()
{
	// Used to turn: coefficient (0% to 100% applied on the left and right speed).
	// 0% will fully break the speed (full break).
	// 100% will not break at all the speed
	double leftSpeedCoef = 1.0f;
	double rightSpeedCoef = 1.0f;

	// Get the forward speed (0-1.0)
	// We have to convert a Raw Axis between -1 (not pressed) and +1 to an speed between 0 and 1.0
	double forwadSpeed = (pJoystick->GetRawAxis(3) + 1.0f) / 2.0f;

	// Get the reverse speed (0-1.0)
	// We have to convert a Raw Axis between -1 (not pressed) and +1 to an speed between 0 and 1.0
	double reverseSpeed = (pJoystick->GetRawAxis(4) + 1.0f) / 2.0f;

	// Real speed (the player can press forward and reverse in the same time to speed-up the transition)
	double realSpeed = forwadSpeed - reverseSpeed;

	// Get the direction of the wheel (between -1.0 (full left) to +1.0 (full right))
	double direction = pJoystick->GetRawAxis(0);

	// If the a speed is applied the vehicle will turn while move forward
	if (std::abs(realSpeed) > 0.001)
	{
		//We like to turn on left (we have to break the left side)
		leftSpeedCoef = (direction < 0.0f ? 1.0f + direction : leftSpeedCoef);
		rightSpeedCoef = (direction > 0.0f ? 1.0f - direction : rightSpeedCoef);

		// Apply the speed on the vehicle
		(Robot::vehicle.get())->Move(realSpeed * leftSpeedCoef, realSpeed * rightSpeedCoef);
	}
	// If the user wants to turn its vehicle on itself
	else if (std::abs(direction) > 0.05f)
	{
		// Apply the speed on the vehicle
		(Robot::vehicle.get())->Move(direction, -1.0f * direction);
	}
	else // If no turn, not move forward, we stop!
	{
		(Robot::vehicle.get())->Stop();
	}
}

// Update the catapult based on the gamepad command
void GamePadDrive::UpdateCatapult()
{
	// To control the speed of the catapult we use the POV on the gamepad.
	int povValue = pJoystick->GetPOV(0);

	// If the user press up it will increase the speed of the catapult
	if (povValue == 0)
	{
		(Robot::catapult.get())->IncreaseSpeed(0.01);
		return;
	}

	// If the user press down it will decrease the speed of the catapult
	if (povValue == 180)
	{
		(Robot::catapult.get())->IncreaseSpeed(-0.01);
		return;
	}

	// If the user press on left it will stop the catapult
	if (povValue == 270)
	{
		(Robot::catapult.get())->Stop();
		return;
	}

	// If the user press on right it will restore the previous saved value
	if (povValue == 90)
	{
		// If no previous saved value, the catapult will take a default value we set
		(Robot::catapult.get())->RestoreSavedSpeed(0.5);
		return;
	}

	// If the user press on the share button, it will save the current speed
	if (pJoystick->GetRawButton(9))
	{
		(Robot::catapult.get())->SaveCurrentSpeed();
	}
}

void GamePadDrive::UpdateWinch()
{
	// Get the speed of the winch and its direction (between -1.0 (full left) to +1.0 (full right))
	double direction = pJoystick->GetRawAxis(5);

	(Robot::winch.get())->Move(direction);
}

void GamePadDrive::UpdateGearGate()
{
	if (!btnToggleGatePressed && pJoystick->GetRawButton(1))
	{
		posGearGate = (posGearGate==Geargate::openGate ? Geargate::closeGate : Geargate::openGate);
		(Robot::geargate.get())->SetGatePosition(posGearGate);
		btnToggleGatePressed = true;
	}
	else if (btnToggleGatePressed && !pJoystick->GetRawButton(1))
	{
		btnToggleGatePressed = false;
	}
	(Robot::geargate.get())->Update();
}

// If the user wants to record a sequence of actions
void GamePadDrive::UpdateRecorder()
{
	// If the user wants to start a record or stop it
	if (!btnRecordPressed && pJoystick->GetRawButton(14))
	{
		if (!pActionsRecorder->RecordInProgress())
		{
			pActionsRecorder->Clear();
			pActionsRecorder->StartRecord();
		}
		else
		{
			pActionsRecorder->StopRecord();
		}

		btnRecordPressed = true;

	}
	else // If the user isn't pressing anymore the record button
	{
		btnRecordPressed = false;
	}

	pActionsRecorder->Tick();
}
