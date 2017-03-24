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
#include "../Definitions.h"
#include <stdlib.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GamePadDrive::GamePadDrive(): Command() {
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::vehicle.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GamePadDrive::Initialize() {

	// By default there is no button pressed
	btnTooggleRecordPressed = false;
	btnTooglePlayPressed = false;
	btnToggleGatePressed = false;
	btnToggleWinchBreakPressed = false;
	btnToggleStopCatapult = false;
	btnToggleInvertDriveControl = false;
	btnTooggleCycleSlotPressed = false;
	btnToggleAgitatorPanicPressed = false;

	// By default we don't invert the control
	invertDriverControlCoef = 1.0f;
	printf("Commands to drive the robot are not inverted\n");
	SmartDashboard::PutString("DB/String 0", "CTRL NORMAL");

	currentRecorderSlot = 0;
	SmartDashboard::PutString("DB/String 5", "SLOT 0");
	pActionsRecorder = ActionsRecorder::GetInstance();
	pJoystick = Robot::oi->getJoystick();
	SmartDashboard::PutString("DB/String 1", "RECORD OFF");

//	int val = system("cp /home/lvuser/gearbackup002.bin /home/lvuser/slot9.bin");


//	int val = system("cp /home/lvuser/autonmous.bin /home/lvuser/gearbackup002.bin");
//	printf("cp done! return value = %d\n", val);

	// We start with an open gate
	posGearGate = Geargate::closeGate;
	(Robot::geargate.get())->SetGatePosition(posGearGate);
	//test HERE Gate
	SmartDashboard::PutString("DB/String 7", "Gate Closed");
}

// Called repeatedly when this Command is scheduled to run
void GamePadDrive::Execute()
{
	// Should be the first function called if we want to record all calls
	UpdateRecorder();

	// If we replay a sequence we should not update the subsystems based on the gamepad
	if ((pActionsRecorder->GetStatus() == ActionsRecorder::disabled) ||
		(pActionsRecorder->GetStatus() == ActionsRecorder::recordInProgress))
	{
		UpdateVehicle();
		UpdateCatapult();
		UpdateWinch();
		UpdateGearGate();
	}
	else if (pActionsRecorder->GetStatus() == ActionsRecorder::playInProgress)
	{
		// The only system that we need to tick during a replay..
		(Robot::geargate.get())->Update();
	}
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

	if (pActionsRecorder->GetStatus() == ActionsRecorder::recordInProgress)
		pActionsRecorder->StopRecord();
	else if (pActionsRecorder->GetStatus() == ActionsRecorder::playInProgress)
		pActionsRecorder->StopPlay();
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

	// To inverse we should invert the control to drive (used when we drive backward)
	if (pJoystick->GetRawButton(VEHICLE_INVERT_CONTROL) && !btnToggleInvertDriveControl)
	{
		// We invert the control
		invertDriverControlCoef *= -1.0f;
		btnToggleInvertDriveControl = true;

		if (invertDriverControlCoef <= 0.0f)
		{
			printf("Commands to drive the robot are inverted\n");
			SmartDashboard::PutString("DB/String 0", "CTRL INVERTED");
		}
		else
		{
			printf("Commands to drive the robot are not inverted\n");
			SmartDashboard::PutString("DB/String 0", "CTRL NORMAL");
		}
	}
	else if (!pJoystick->GetRawButton(VEHICLE_INVERT_CONTROL) && btnToggleInvertDriveControl)
	{
		btnToggleInvertDriveControl = false;
	}

	// Get the forward speed (0-1.0)
	// We have to convert a Raw Axis between -1 (not pressed) and +1 to an speed between 0 and 1.0
	double forwardSpeed = (pJoystick->GetRawAxis(VEHICLE_GACHETTE_FORWARD) + 1.0f) / 2.0f;

	// Get the reverse speed (0-1.0)
	// We have to convert a Raw Axis between -1 (not pressed) and +1 to an speed between 0 and 1.0
	double reverseSpeed = (pJoystick->GetRawAxis(VEHICLE_GACHETTE_REVERSE) + 1.0f) / 2.0f;

	// Real speed (the player can press forward and reverse in the same time to speed-up the transition)
	double realSpeed = forwardSpeed - reverseSpeed;

	// We invert de speed if the commands are inverted
	realSpeed *= invertDriverControlCoef;

	// Get the direction of the wheel (between -1.0 (full left) to +1.0 (full right))
	double direction = pJoystick->GetRawAxis(VEHICLE_DIRECTION);

	// If the a speed is applied the vehicle will turn while move forward
	if (std::abs(realSpeed) > VEHICLE_AUTORATION_SPEED_THRESHOLD)
	{
		//We like to turn on left (we have to break the left side)
		if (invertDriverControlCoef > 0.0f)
		{
			leftSpeedCoef = (direction < 0.0f ? 1.0f + direction : leftSpeedCoef);
			rightSpeedCoef = (direction > 0.0f ? 1.0f - direction : rightSpeedCoef);
		}
		else
		{
			rightSpeedCoef = (direction < 0.0f ? 1.0f + direction : leftSpeedCoef);
			leftSpeedCoef = (direction > 0.0f ? 1.0f - direction : rightSpeedCoef);
		}
		// Apply the speed on the vehicle
		(Robot::vehicle.get())->Move(realSpeed * leftSpeedCoef,
				realSpeed * rightSpeedCoef);
	}
	// If the user wants to turn its vehicle on itself (autorotation)
	else if (std::abs(direction) > VEHICLE_MINIMUM_ANGLE_FOR_AUTORATION)
	{
		// As a linear interpolation triggers a very fast auto-rotation, we use a square approach
		double autorotationSpeed = (direction * direction) / 2.0f;

		// we keep a negative rotation speed if it was negative before the square calculation
		if (direction < 0.0f)
		{
			autorotationSpeed *= -1.0f;
		}

		// Apply the speed on the vehicle
		(Robot::vehicle.get())->Move(autorotationSpeed,
				-1.0f * autorotationSpeed);
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
	int povValue = pJoystick->GetPOV(CATAPULT_POV);

	// If the user press up it will increase the speed of the catapult
	if (povValue == CATAPULT_BUTTON_INCREASE_SPEED)
	{
		// The first increment will jump directly to the restore saved speed
		if ((Robot::catapult.get())->GetCurrentBallSpeed() == 0.0)
			(Robot::catapult.get())->RestoreSavedSpeed();
		else
			(Robot::catapult.get())->IncreaseSpeed(CATAPULT_INCREASE_SPEED_DELTA);
		return;
	}

	// If the user press down it will decrease the speed of the catapult
	if (povValue == CATAPULT_BUTTON_DESCREASE_SPEED)
	{
		(Robot::catapult.get())->IncreaseSpeed(-CATAPULT_INCREASE_SPEED_DELTA);
		return;
	}


	// If the user press on left it will stop the catapult (we protect the code between multiple pressure)
	if (!btnToggleStopCatapult && (povValue == CATAPULT_BUTTON_STOP_SPEED))
	{
		(Robot::catapult.get())->SaveCurrentSpeed();
		(Robot::catapult.get())->Stop();
		btnToggleStopCatapult = true;
		return;
	}
	else if (btnToggleStopCatapult && (povValue != CATAPULT_BUTTON_STOP_SPEED))
	{
		btnToggleStopCatapult = false;
	}

	// If the user press the panic button to stop the agitator
	if (!btnToggleAgitatorPanicPressed && (povValue == CATAPULT_BUTTON_AGITATOR_PANIC))
	{
		btnToggleAgitatorPanicPressed = true;
		(Robot::catapult.get())->StopAgitator();
		return;
	}
	else if (btnToggleAgitatorPanicPressed && (povValue != CATAPULT_BUTTON_AGITATOR_PANIC))
	{
		btnToggleAgitatorPanicPressed = false;
	}
}

void GamePadDrive::UpdateWinch()
{
	// Get the speed of the winch and its direction (between -1.0 (full left) to +1.0 (full right))
	double direction = pJoystick->GetRawAxis(WINCH_DIRECTION);
	(Robot::winch.get())->Move(direction);

	if (!btnToggleWinchBreakPressed && pJoystick->GetRawButton(WINCH_BREAK))
	{
		(Robot::winch.get())->Break();
		btnToggleWinchBreakPressed = true;
	}
	else if (btnToggleWinchBreakPressed && !pJoystick->GetRawButton(WINCH_BREAK))
	{
		btnToggleWinchBreakPressed = false;
	}
}

void GamePadDrive::UpdateGearGate()
{
	if (!btnToggleGatePressed && pJoystick->GetRawButton(GEARGATE_BUTTON_TOGGLE))
	{
		if (posGearGate==Geargate::openGate)
		{
			posGearGate = Geargate::closeGate;
			SmartDashboard::PutString("DB/String 7", "Gate Closed");
		}
		else
		{
			posGearGate = Geargate::openGate;
			SmartDashboard::PutString("DB/String 7", "Gate Open");
		}

		//posGearGate = (posGearGate==Geargate::openGate ? Geargate::closeGate : Geargate::openGate);
		(Robot::geargate.get())->SetGatePosition(posGearGate);
		btnToggleGatePressed = true;
	}
	else if (btnToggleGatePressed && !pJoystick->GetRawButton(GEARGATE_BUTTON_TOGGLE))
	{
		btnToggleGatePressed = false;
	}

	(Robot::geargate.get())->Update();
}

// If the user wants to record a sequence of actions
void GamePadDrive::UpdateRecorder()
{	// If the user want to cycle slot
	if (!btnTooggleCycleSlotPressed && pJoystick->GetRawButton(RECORD_CYCLE_SLOT_BUTTON))
	{
		btnTooggleCycleSlotPressed = true;
		currentRecorderSlot = (currentRecorderSlot + 1) % RECORDER_NUMBER_SLOTS;
		switch(currentRecorderSlot)
		{
		case 0:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 0");
			break;
		case 1:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 1");
			break;
		case 2:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 2");
			break;
		case 3:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 3");
			break;
		case 4:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 4");
			break;
		case 5:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 5");
			break;
		case 6:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 6");
			break;
		case 7:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 7");
			break;
		case 8:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 8");
			break;
		case 9:
			SmartDashboard::PutString("DB/String 5", "REC SLOT 9");
			break;
		default:
			SmartDashboard::PutString("DB/String 5", "REC PROBLEM");
			break;
		}
	}
	else if (btnTooggleCycleSlotPressed && !pJoystick->GetRawButton(RECORD_CYCLE_SLOT_BUTTON))
	{
		btnTooggleCycleSlotPressed = false;
	}

	// If the user wants to start or stop a record
	if (!btnTooggleRecordPressed && pJoystick->GetRawButton(RECORDER_START_STOP_RECORD))
	{
		if (pActionsRecorder->GetStatus()==ActionsRecorder::disabled)
		{
			printf("START A SEQUENCE RECORD\n");
			SmartDashboard::PutString("DB/String 1", "RECORD ON");

			pActionsRecorder->Clear();
			pActionsRecorder->StartRecord();
		}
		else if (pActionsRecorder->GetStatus()==ActionsRecorder::recordInProgress)
		{
			printf("STOP A SEQUENCE RECORD\n");
			pActionsRecorder->StopRecord();

			switch(currentRecorderSlot)
			{
			case 0:
				pActionsRecorder->SaveFile(RECORDER_SLOT0_FILE_NAME);
				break;
			case 1:
				pActionsRecorder->SaveFile(RECORDER_SLOT1_FILE_NAME);
				break;
			case 2:
				pActionsRecorder->SaveFile(RECORDER_SLOT2_FILE_NAME);
				break;
			case 3:
				pActionsRecorder->SaveFile(RECORDER_SLOT3_FILE_NAME);
				break;
			case 4:
				pActionsRecorder->SaveFile(RECORDER_SLOT4_FILE_NAME);
				break;
			case 5:
				pActionsRecorder->SaveFile(RECORDER_SLOT5_FILE_NAME);
				break;
			case 6:
				pActionsRecorder->SaveFile(RECORDER_SLOT6_FILE_NAME);
				break;
			case 7:
				pActionsRecorder->SaveFile(RECORDER_SLOT7_FILE_NAME);
				break;
			case 8:
				pActionsRecorder->SaveFile(RECORDER_SLOT8_FILE_NAME);
				break;
			case 9:
				pActionsRecorder->SaveFile(RECORDER_SLOT9_FILE_NAME);
				break;
			default:
				break;
			}

			SmartDashboard::PutString("DB/String 1", "RECORDER OFF");
		}

		btnTooggleRecordPressed = true;
	}
	// If the user stops to press on the button to start or stop a record (not necessary if we use the button class)
	else if (btnTooggleRecordPressed && !pJoystick->GetRawButton(RECORDER_START_STOP_RECORD))
	{
		btnTooggleRecordPressed = false;
	}

	if (!btnTooggleSetAutonomousPressed && pJoystick->GetRawButton(RECORD_SET_AUTONOMOUS_BUTTON))
	{
		btnTooggleSetAutonomousPressed = true;
		char cmd[100];

		switch(currentRecorderSlot)
		{
		case 0:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT0_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 0 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 0");
			break;
		case 1:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT1_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 1 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 1");
			break;
		case 2:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT2_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 2 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 2");
			break;
		case 3:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT3_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 3 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 3");
			break;
		case 4:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT4_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 4 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 4");
			break;
		case 5:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT5_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 5 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 5");
			break;
		case 6:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT6_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 6 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 6");
			break;
		case 7:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT7_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 7 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 7");
			break;
		case 8:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT8_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 8 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 8");
			break;
		case 9:
			sprintf(cmd, "cp -fr %s %s", RECORDER_SLOT9_FILE_NAME, RECORDER_AUTONOMOUS_FILE_NAME);
			printf("Slot 9 applied for autonmous mode\n");
			SmartDashboard::PutString("DB/String 6", "AUTO = 9");
			break;
		default:
			break;
		}

		system(cmd);
	}
	else if (btnTooggleSetAutonomousPressed && !pJoystick->GetRawButton(RECORD_SET_AUTONOMOUS_BUTTON))
	{
		btnTooggleSetAutonomousPressed = false;
	}

	// If the user wants to start or stop a play
	if(!btnTooglePlayPressed && pJoystick->GetRawButton(RECORDER_START_STOP_PLAY))
	{
		if (pActionsRecorder->GetStatus()==ActionsRecorder::disabled)
		{
			printf("START A SEQUENCE PLAY\n");

			pActionsRecorder->StartPlay();
		}
		else if (pActionsRecorder->GetStatus()==ActionsRecorder::playInProgress)
		{
			printf("STOP A SEQUENCE PLAY\n");

			pActionsRecorder->StopPlay();
		}

		btnTooglePlayPressed = true;
	}
	// If the user stops to press on the button to start or stop a play (not necessary if we use the button class)
	else if (btnTooglePlayPressed && !pJoystick->GetRawButton(RECORDER_START_STOP_PLAY))
	{
		btnTooglePlayPressed = false;
	}

	// Necessary to operate the recorder
	pActionsRecorder->Update();
}
