    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		
		if(regul == 1){ //regulation TOR
			for (int i = 0; i < nT; i++)
			{
				cmd = regulation(consigne,tabT[i]);
			}
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
    
  
