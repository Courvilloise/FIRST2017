// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "definitions.h"

#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"

#ifdef UTILISE_ENGRENAGE
#include "Commands/EngrenageFerme.h"
#include "Commands/EngrenageOuvre.h"
#include "Commands/EngrenageStop.h"
#endif

#include "Commands/GamePadDrive.h"
#include "Commands/Test_StartVehicle.h"
#include "Commands/Test_StopVehicle.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.

//	gamePad = new XboxController();

//	JoystickButton* button1 = new JoystickButton(gamePad, 1);


    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    joystick.reset(new Joystick(0));
#ifdef UTILISE_ENGRENAGE
    joystickButtonEngrenageFermeture.reset(new JoystickButton(joystick.get(), ENGRENAGE_BOUTON_FERMETURE));
    joystickButtonEngrenageFermeture->WhenPressed(new EngrenageFerme());
    joystickButtonEngrenageOuverture.reset(new JoystickButton(joystick.get(), ENGRENAGE_BOUTON_OUVERTURE));
    joystickButtonEngrenageOuverture->WhenPressed(new EngrenageOuvre());
    joystickButtonEngrenageArret.reset(new JoystickButton(joystick.get(), ENGRENAGE_BOUTON_ARRET));
    joystickButtonEngrenageArret->WhenPressed(new EngrenageStop());
#endif

    // SmartDashboard Buttons
#ifdef UTILISE_ENGRENAGE
    SmartDashboard::PutData("Engrenage Ferme", new EngrenageFerme());
    SmartDashboard::PutData("Engrenage Ouvre", new EngrenageOuvre());
    SmartDashboard::PutData("Engrenage Stop", new EngrenageStop());
#endif    

    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    SmartDashboard::PutData("Test_StartVehicle", new Test_StartVehicle());
    SmartDashboard::PutData("Test_StopVehicle", new Test_StopVehicle());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getJoystick() {
   return joystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS