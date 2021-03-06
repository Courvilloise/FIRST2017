// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "../definitions.h"

#ifdef UTILISE_ENGRENAGE

#include "Engrenage.h"
#include "../RobotMap.h"
#include "../Commands/EngrenageStop.h" //pas necessairement une bonne fa�on de faire...

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Engrenage::Engrenage() : Subsystem("Engrenage") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    moteur = RobotMap::engrenageMoteur;
    limitSwitchFermeture = RobotMap::engrenageLimitSwitchFermeture;
    limitSwitchOuverture = RobotMap::engrenageLimitSwitchOuverture;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    Arrete();
}

void Engrenage::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
		SetDefaultCommand(new EngrenageStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Engrenage::Arrete()
{
	moteur->Set(0.0);
}

void Engrenage::Tourne(bool direction)
{
double vitesse;
	if (direction == ENGRENAGE_DIRECTION_OUVERTURE)
	{
		vitesse = ENGRENAGE_VITESSE_OUVERTURE;
	}
	else
	{
		vitesse = ENGRENAGE_VITESSE_FERMETURE;
	}
	moteur->Set(vitesse);
}

bool Engrenage::LimiteOuvertureAtteinte(void)
{
	return limitSwitchOuverture->Get();
}
bool Engrenage::LimiteFermetureAtteinte(void)
{
	return limitSwitchFermeture->Get();
}

#endif
