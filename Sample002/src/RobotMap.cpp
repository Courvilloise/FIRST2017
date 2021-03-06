// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "CANTalon.h"
#include "CanTalonSRX.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<SpeedController> RobotMap::vehiclePMW2LeftEngine;
std::shared_ptr<SpeedController> RobotMap::vehiclePMW0LeftEngine;
std::shared_ptr<SpeedController> RobotMap::vehiclePMW3RightEngine;
std::shared_ptr<SpeedController> RobotMap::vehiclePMW1RightEngine;
std::shared_ptr<CANTalon> RobotMap::catapultCAN1ThrowEngine;

#ifdef UTILISE_ENGRENAGE
std::shared_ptr<SpeedController> RobotMap::engrenageMoteur;
std::shared_ptr<DigitalInput> RobotMap::engrenageLimitSwitchFermeture;
std::shared_ptr<DigitalInput> RobotMap::engrenageLimitSwitchOuverture;

#endif

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    vehiclePMW2LeftEngine.reset(new VictorSP(2));
    lw->AddActuator("Vehicle", "PMW2LeftEngine", std::static_pointer_cast<VictorSP>(vehiclePMW2LeftEngine));
    
    vehiclePMW0LeftEngine.reset(new VictorSP(0));
    lw->AddActuator("Vehicle", "PMW0LeftEngine", std::static_pointer_cast<VictorSP>(vehiclePMW0LeftEngine));
    
    vehiclePMW3RightEngine.reset(new VictorSP(3));
    lw->AddActuator("Vehicle", "PMW3RightEngine", std::static_pointer_cast<VictorSP>(vehiclePMW3RightEngine));
    
    vehiclePMW1RightEngine.reset(new VictorSP(1));
    lw->AddActuator("Vehicle", "PMW1RightEngine", std::static_pointer_cast<VictorSP>(vehiclePMW1RightEngine));
    
    catapultCAN1ThrowEngine.reset(new CANTalon(1));
    lw->AddActuator("Catapult", "CAN1ThrowEngine", catapultCAN1ThrowEngine);

#ifdef UTILISE_ENGRENAGE    
	engrenageMoteur.reset(new VictorSP(4));
    lw->AddActuator("Engrenage", "Moteur", std::static_pointer_cast<VictorSP>(engrenageMoteur));
    
    engrenageLimitSwitchFermeture.reset(new DigitalInput(ENGRENAGE_ENTREE_FERMETURE));
    lw->AddSensor("Engrenage", "Limit Switch Fermeture", engrenageLimitSwitchFermeture);
    
    engrenageLimitSwitchOuverture.reset(new DigitalInput(ENGRENAGE_ENTREE_OUVERTURE));
    lw->AddSensor("Engrenage", "Limit Switch Ouverture", engrenageLimitSwitchOuverture);
#endif
    
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	
}
