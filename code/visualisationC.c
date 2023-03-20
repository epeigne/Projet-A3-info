#include <stdbool.h>  
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "visualisationC.h"


void visualisationC(float puissance_f){
   // check if file .verrouData exist (if so we can't modify data.txt)
   if (access(".verrouData", F_OK) == 0) {
      // .verrouData exists
      return;
   }
   
   // creating .verrouData file
   FILE* verrou = fopen(".verrouData","a");
   fclose(verrou);
   
   FILE* data;
   data = fopen("data.txt", "w+"); // opening data.txt file in write/read mode
   if (data == NULL){ // if opening fails
      printf("Error in opening file");
      return;
   }
   
   // reading Tint and Text
   char chauffage[6];
   float Tint;
   float Text;
   fscanf(data,"%s\n%f\n%f", chauffage, Tint, Text);
   
   // writing in data.txt 
   if (puissance_f == 0){
      fprintf(data, "%s\n%f\n%f", "false", Tint, Text);
   } else {
      fprintf(data, "%s\n%f\n%f", "true", Tint, Text);
   }
   
   fclose(data);
   
   // deleting .verrouData file
   remove(".verrouData");
}
   
