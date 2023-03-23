#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd;
	
	if (consigne == 5){ // stops the regulation when "consigne" == 5°C
		return 5;
	}
	
	if(regul == 1){
		for (int i = 0; i < nT; i++)
		{
			cmd = regulation(consigne,tabT[i-1], tabT[i]);
		}
	}
	
	if (regul == 2){
		float Kp = 1.1; // PID constants
		float oldConsigne;
		float newConsigne;
		float tabConsigne[nT];
		
		float I;
		
		/*struct temp_t temparature = 
		struct simParam_s* param_ps = simConstruct(temp_t temperature);*/
		
		for (int i = 0; i < nT; i++)
		{
			if (i == 0){
				newConsigne = simCalc(regulationPID(consigne, consigne, i, &I), param_ps);
				oldConsigne = consigne;
			} else {
				cmd = regulationPID(newConsigne, oldConsigne, i);
				oldConsigne = newConsigne;
				newConsigne = cmd;
			}
		}
	}

	return cmd;
}

float regulationPID(float newConsigne, float oldConsigne, int iterrationCount, float* I){
	float Kp = 1.1; // PID constants
	float Ki = 0.2;
	float Kd = 0.15;
	
	float P = newConsigne * Kp;
	
	if (iterrationCount == 0){
		return P; 
	}
	
	float e = newConsigne - oldConsigne;
	
	if (e > 0){
		
	}
	
	*I += Ki * ;
	
	
	
	float D;
	
	
	
	return P + *I + D;
}


float regulation(float consigne, float oldT, float newT){
	float cmd;

	if(consigne > 0){
		if(newT < oldT){
			cmd = 50;
		}
		else{
			cmd = 0;
		}
	}
	else{
		cmd = 0;
	}
	return cmd;
}

  
