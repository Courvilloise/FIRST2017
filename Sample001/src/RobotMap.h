// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "CANTalon.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<SpeedController> vehiclePMW2LeftEngine;
	static std::shared_ptr<SpeedController> vehiclePMW0LeftEngine;
	static std::shared_ptr<SpeedController> vehiclePMW3RightEngine;
	static std::shared_ptr<SpeedController> vehiclePMW1RightEngine;
	static std::shared_ptr<SpeedController> catapultPMW4AgitatorEngine;
	static std::shared_ptr<CANTalon> catapultCAN1ThrowEngine;
	static std::shared_ptr<SpeedController> winchPMW5WinchEngine;
	static std::shared_ptr<SpeedController> winchPMW6WinchEngine;
	static std::shared_ptr<DigitalInput> geargateD0LimitOpenSwitch;
	static std::shared_ptr<DigitalInput> geargateD1LimitCloseSwitch;
	static std::shared_ptr<SpeedController> geargatePMW4GateEngine;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static void init();
};
#endif
