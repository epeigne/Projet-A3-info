#include <stdio.h>
#include <stdlib.h>
#include "Inc/visualisationT.h"
#include "Inc/regulation.h"
#include "Inc/consigne.h"
#include "Inc/visualisationC.h"
#include "Inc/releve.h"
#include "Inc/commande.h"

#define CHOICE 2 // 1 pour la regulation TOR / 2 pour la regulation PID


int main(){

    FT_STATUS ftStatus;
    FT_HANDLE ftHandle;

    //Open the device (device #0 for first device found)
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("Error opening device");
        return 0;
    }
    
    //Set the baud rate
    ftStatus = FT_SetBaudRate(ftHandle, FT_BAUD_115200);
    if (ftStatus != FT_OK) {
        printf("Error setting baud rate");
        return 0;
    }

    //Set the data characteristics
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus != FT_OK) {
        printf("Error setting data characteristics");
        return 0;
    }

    //Set the flow control
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        printf("Error setting flow control");
        return 0;
    }
    

	temp_t temperature;
	temperature.exterieure = 12.0;
	temperature.interieure = 15.0;
	float integral = 0; // integral de l'erreur pour la regulation PID
	float previousConsigne = 0; // consigne precedente pour la regulation PID
	float previousEcart = 0; // ecart precedente pour la regulation PID
	float puissance = 0; // puissance de chauffage
	float temp_cons = 50; // consigne de temperature
	
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


		releve(ftHandle, temperature); // releve de la temperature

		visualisationC(puissance); // visualisation de la puissance

		visualisationT(temperature); // visualisation de la temperature

        commande(ftHandle, puissance); // commande de la puissance de chauffage (non fonctionnel
		
	}
	//Close the device
    ftStatus = FT_Close(ftHandle);
    if (ftStatus != FT_OK) {
        printf("Error closing device");
        return 0;
    }
	return EXIT_SUCCESS;
}
