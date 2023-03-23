#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd = 100.0;
	
	if(regul == 1){ // tout ou rien
		for (int i = 0; i < nT; i++)
		{
			cmd = regulation(consigne,tabT[i]);
		}
	}
	
	if (regul == 2){ // PID
		float integral = 0;
		float previousE = 0;
		float previousConsigne = 0;
		
		for (int i = 0; i < nT; i++)
		{
			cmd = regulationPID(consigne, tabT[i], &integral, &previousE, &previousConsigne);
		}
	}

	return cmd;
}

float regulationPID(float consigne, float Tint, float* I, float* previousE, float* previousConsigne){
	float Kp = 1.1; // PID constants
	float Ki = 0.2;
	float Kd = 0.15;
	int deltaT = 10;
	
	float e = consigne - Tint;
	
	// proportional term 
	float P = Kp * e; 
	
	// intergral term 
	if (*previousE < e){
		*I += Ki * (deltaT * *previousE + (deltaT * (e - *previousE)) / 2);
	} else {
		*I += Ki * (deltaT * e + (deltaT * (*previousE - e)) / 2);
	}
	
	// derivate term
	float D = Kd * (e - *previousE) / deltaT;

	if (consigne != *previousConsigne){
	    *I = 0;
		D = 0;
	}
	
	*previousE = e;
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

  
