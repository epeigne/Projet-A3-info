#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

#define DELTA_T 10 // PID constants
#define K_P 1.1
#define K_I 0.2
#define K_D 0.15

	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd = 100.0;
	
	if(regul == 1){ // tout ou rien
		for (int i = 0; i < nT; i++)
		{
			cmd = regulation(consigne,tabT[i]);
		}
	}
	
	if (regul == 2){ // PID
		float integral = 0; // integral de l'erreur pour la regulation PID
		float previousE = 0; // ecart precedente pour la regulation PID
		float previousConsigne = 0; // consigne precedente pour la regulation PID
		
		for (int i = 0; i < nT; i++)
		{
			cmd = regulationPID(consigne, tabT[i], &integral, &previousE, &previousConsigne);
		}
	}

	return cmd;
}

float regulationPID(float consigne, float Tint, float* I, float* previousE, float* previousConsigne){	
	float e = consigne - Tint; // compute gap between consigne and current temp
	
	// proportional term 
	float P = K_P * e; 
	
	// intergral term 
	if (*previousE < e){
		*I += K_I * (DELTA_T * *previousE + (DELTA_T * (e - *previousE)) / 2); // trapezoidal rule
	} else {
		*I += K_I * (DELTA_T * e + (DELTA_T * (*previousE - e)) / 2); // trapezoidal rule
	}
	
	// derivate term
	float D = K_D * (e - *previousE) / DELTA_T; 

	if (consigne != *previousConsigne){ // reseting integral and derivate value if consigna has changed or if it is the first iteration
	    *I = 0;
		D = 0;
	}
	
	*previousE = e; // updating previous gap and consigne
	*previousConsigne = consigne;

	float cmd = P + *I + D; 

	if (cmd > 100){ // in case if the cmd is too big or too small
		return 100;
	}
	if (cmd < 0){
		return 0;
	}
	return cmd;
}

float regulation(float consigne, float tempInt){

	// check if the temperature is lower than the consigne
	// if yes, return 50 else return 0

	float cmd;

	if(tempInt < consigne){
		cmd = 50;
	}else{
		cmd = 0;
	}

	return cmd;

}

  
