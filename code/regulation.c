    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		
		if(regul == 1){
			for (int i = 0; i < nT; i++)
			{
				cmd = regulation(consigne,tabT[i-1], tabT[i]);
			}
		}

		return cmd;
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
    
  
