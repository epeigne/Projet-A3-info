#ifndef REGULATION_H
#define REGULATION_H
#include <stdio.h>
#include <stdlib.h>
#include "define.h" 
    
   // Pensez à bien proteger vos .h avec des ifndef
	
float regulationTest(int regul,float consigne,float* tabT, int nT);
float regulation(float consigne, float tempInt);
float regulationPID(float consigne, float Tint, float* I, float* previousE, float* previousConsigne);

#endif
