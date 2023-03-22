    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		
		if(regul == 1){
			for (int i = 0; i < nT; i++)
			{
				cmd = regulation(consigne,tabT, nT);
			}
		}


		return cmd;
	}

	float regulation(float consigne, float* tabT, int nT){
		float cmd;

		if(consigne > 0){
			for(int i = 1; i < nT; i++){
				if(tabT[i] <= tabT[i-1]){
					cmd = 50;
				}
				else{
					cmd = 0;
				}
			}
		}
		else{
			cmd = 0;
		}
		return cmd;
	}
    
  
