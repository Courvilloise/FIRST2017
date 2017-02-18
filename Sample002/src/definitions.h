// definitions
//
// fichier utilise pour definir des definitions
// il doit etre inclus dans tous les fichiers .h et .c du programme pour que son contenu
// soit pris en compte de facon coherente


#ifndef DEFINITION_H
#define DEFINITION_H


//definition pour les boutons de manette
#define BOUTON_CARRE			1
#define BOUTON_X				2
#define BOUTON_O				3
#define BOUTON_TRIANGLE			4
#define BOUTON_L1				5
#define BOUTON_R1				6
#define BOUTON_L2				7
#define BOUTON_R2				8
#define BOUTON_SHARE			9
#define BOUTON_OPTION			10
#define BOUTON_L3				11	//bouton du joystick gauche
#define BOUTON_R3				12  //bouton du joystick droit
#define BOUTON_PLAYSTATION		13
#define BOUTON_PAD				14
#define BOUTON_POV				0
#define POV_HAUT				0
#define POV_HAUT_DROIT			45
#define POV_DROIT				90
#define POV_DROIT_BAS			135
#define POV_BAS					180
#define POV_BAS_GAUCHE			225
#define POV_GAUCHE				270
#define POV_GAUCHE_HAUT			315

//definition liees a l'utilisation des entrees
#define ENGRENAGE_ENTREE_FERMETURE		0
#define ENGRENAGE_ENTREE_OUVERTURE		1

//selection des modules a utiliser
#define UTILISE_ENGRENAGE  //mettre en commentaire pour ne pas avoir d'engrenage
//usage:
//#ifdef UTILISE_ENGRENAGE
//... //code pour l'emploi de l'engrenage
//#endif
//#ifndef UTILISE_ENGRENAGE
//... //code s'il n'y a pas d'engrenage
//#endif

//definitions globales qui dependent du materiel
//ENGRENAGE
#define ENGRENAGE_BOUTON_OUVERTURE		BOUTON_O
#define ENGRENAGE_BOUTON_FERMETURE		BOUTON_CARRE
#define ENGRENAGE_BOUTON_ARRET			BOUTON_X


#define ENGRENAGE_VITESSE_OUVERTURE 	-0.75f
#define ENGRENAGE_VITESSE_FERMETURE		0.75f
#define ENGRENAGE_DIRECTION_OUVERTURE	1
#define ENGRENAGE_DIRECTION_FERMETURE	0
#define ENGRENAGE_LIMITE_OUVERTURE_ATTEINTE 1
#define ENGRENAGE_LIMITE_FERMETURE_ATTEINTE	1



#endif
