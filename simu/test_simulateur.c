#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "../code/visualisationT.h"
#include "../code/regulation.h"
#include "../code/consigne.h"
#include "../code/visualisationC.h"

int main(){

	temp_t temperature;
	temperature.exterieure = 12.0;
	temperature.interieure = 15.0;
	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	float puissance = 0; // puissance de chauffage
	float temp_cons = 0; // consigne de temperature
	while(1){

		temp_cons = consigne(temp_cons); // calcul de la consigne de temperature

		if(temp_cons < 5){ // si la consigne est inferieur a 5, on arrete le programme
			break;
		}

		puissance = regulation(temp_cons, temperature.interieure); // calcul de la puissance de chauffage


		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement

		visualisationC(puissance); // visualisation de la puissance

		visualisationT(temperature); // visualisation de la temperature
		
	}
	simDestruct(monSimulateur_ps); // destruction de simulateur
	return EXIT_SUCCESS;
}
