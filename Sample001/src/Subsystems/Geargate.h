// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GEARGATE_H
#define GEARGATE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Geargate: public Subsystem {
public:
	// Gate position
	enum gatePosition { notDefined, openGate, closeGate};

private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<DigitalInput> d0LimitOpenSwitch;
	std::shared_ptr<DigitalInput> d1LimitCloseSwitch;
	std::shared_ptr<SpeedController> pMW7GateEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// To know the actual gate position
	gatePosition currentPosition;
public:

	Geargate();
	void InitDefaultCommand();

	// Ste a specific position for the gate
	void SetGatePosition(gatePosition Position);
	// Should be call regularly
	void Update();


	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif