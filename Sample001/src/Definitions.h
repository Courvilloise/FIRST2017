/*
 * Definitions.h
 *
 *  Created on: Feb 18, 2017
 *      Author: franc
 */

#ifndef SRC_DEFINITIONS_H_
#define SRC_DEFINITIONS_H_

//definition pour les boutons de manette
#define BOUTON_CARRE							1
#define BOUTON_X								2
#define BOUTON_O								3
#define BOUTON_TRIANGLE							4
#define BOUTON_L1								5
#define BOUTON_R1								6
#define BOUTON_L2								7
#define BOUTON_R2								8
#define BOUTON_SHARE							9
#define BOUTON_OPTION							10
#define BOUTON_L3								11	//bouton du joystick gauche
#define BOUTON_R3								12  //bouton du joystick droit
#define BOUTON_PLAYSTATION						13
#define BOUTON_PAD								14
#define BOUTON_POV								0
#define POV_ID									0
#define POV_HAUT								0
#define POV_HAUT_DROIT							45
#define POV_DROIT								90
#define POV_DROIT_BAS							135
#define POV_BAS									180
#define POV_BAS_GAUCHE							225
#define POV_GAUCHE								270
#define POV_GAUCHE_HAUT							315
#define THUMBSTICK_LEFT_HORIZONTAL				0
#define THUMBSTICK_LEFT_VERTICAL				1
#define THUMBSTICK_RIGHT_HORIZONTAL				2
#define THUMBSTICK_RIGHT_VERTICAL				5
#define GACHETTE_L2								3
#define GACHETTE_R2								4

/////////////////////////////////////////////////////////////////////////////////
// ABOUT THE GEARGATE
#define GEARGATE_BUTTON_TOGGLE					(BOUTON_O)

/////////////////////////////////////////////////////////////////////////////////
// ABOUT THE CATAPULT
#define CATAPULT_BUTTON_RECORD_SPEED			(BOUTON_SHARE)
#define CATAPULT_POV							(POV_ID)
#define CATAPULT_BUTTON_RESTORE_SPEED			(POV_DROIT)
#define CATAPULT_BUTTON_INCREASE_SPEED			(POV_HAUT)
#define CATAPULT_BUTTON_DESCREASE_SPEED			(POV_BAS)
#define CATAPULT_BUTTON_STOP_SPEED				(POV_GAUCHE)

#define CATAPULT_AGITATOR_SPEED					(0.3f)
#define CATAPULT_DEFAULT_RESTORE_SAVED_SPEED	(0.5f)
#define CATAPULT_INCREASE_SPEED_DELTA			(0.01f)

/////////////////////////////////////////////////////////////////////////////////
// ABOUT THE VEHICLE
#define VEHICLE_GACHETTE_FORWARD				(GACHETTE_L2)
#define VEHICLE_GACHETTE_REVERSE				(GACHETTE_R2)
#define VEHICLE_DIRECTION						(THUMBSTICK_LEFT_HORIZONTAL)

#define VEHICLE_MINIMUM_ANGLE_FOR_AUTORATION	0.05f
#define VEHICLE_AUTORATION_SPEED_THRESHOLD		0.001f

/////////////////////////////////////////////////////////////////////////////////
// ANOUT THE WINCH
#define WINCH_DIRECTION							(THUMBSTICK_RIGHT_VERTICAL)

/////////////////////////////////////////////////////////////////////////////////
// ABOUT THE RECORDER
#define RECORDER_START_RECORD					(BOUTON_OPTION)
#define RECORDER_STOP_RECORD					(BOUTON_X)
#define RECORDER_REPLAY_RECORD					(BOUTON_CARRE)

#endif /* SRC_DEFINITIONS_H_ */
