#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "Inc/visualisationT.h"
#include "Inc/regulation.h"
#include "Inc/consigne.h"
#include "Inc/visualisationC.h"

#define CHOICE 2 // 1 pour la regulation TOR / 2 pour la regulation PID


int main(){

	temp_t temperature;
	temperature.exterieure = 12.0;
	temperature.interieure = 15.0;
	float integral = 0; // integral de l'erreur pour la regulation PID
	float previousConsigne = 0; // consigne precedente pour la regulation PID
	float previousEcart = 0; // ecart precedente pour la regulation PID
	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	float puissance = 0; // puissance de chauffage
	float temp_cons = 50; // consigne de temperature
	
	//int choice = 1;
	//printf("entrez 1 pour la régulation TOR / entrer 2 pour la régulation PID: "); // choix de la regulation
	//scanf("%d", &choice); // choix de la regulation
	
	while(1){

		temp_cons = consigne(temp_cons); // calcul de la consigne de temperature

		if(temp_cons < 5){ // si la consigne est inferieur a 5, on arrete le programme
			break;
		}
		// choix de la regulation

		if (CHOICE == 1){
			puissance = regulation(temp_cons, temperature.interieure); // calcul de la puissance de chauffage TOR
		} else if (CHOICE == 2) {
			puissance = regulationPID(temp_cons, temperature.interieure, &integral, &previousEcart, &previousConsigne); // calcul de la puissance de chauffage PID
		} else {
			break;
		}


		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement

		visualisationC(puissance); // visualisation de la puissance

		visualisationT(temperature); // visualisation de la temperature
		
	}
	simDestruct(monSimulateur_ps); // destruction de simulateur
	return EXIT_SUCCESS;
}
