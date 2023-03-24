#include <stdbool.h>  
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "Inc/visualisationC.h"


void visualisationC(float puissance_f){
   if (access(".verrouData", F_OK) == 0) { // check if file .verrouData exist (if so we can't modify data.txt)
      // .verrouData exists
      // printf("data.txt locked !");
      return;
   }
   
   FILE* readingData = fopen("data.txt", "r"); // opening data.txt file in write/read mode
   if (readingData == NULL){ // if opening fails
      // printf("Error in opening file");
      return;
   }
   
   char chauffage[8]; // reading Tint and Text
   float Tint;
   float Text;
   fscanf(readingData, "%s", chauffage); // reading "true" or "false"
   fscanf(readingData, "%f", &Tint); // reading Tint
   fscanf(readingData, "%f", &Text);   // reading Text
   fclose(readingData); // closing data.txt
   
   FILE* lockfile = fopen(".verrouData","w"); // creating .verrouData file
   fclose(lockfile); // closing .verrouData
   
   FILE* writingData = fopen("data.txt", "w+"); // writing in data.txt 
   if (writingData == NULL){ // if opening fails
      // printf("Error in opening file");
      return;
   }
   
   if (puissance_f == 0){
      fprintf(writingData, "%s\n%.2f\n%.2f", "false", Tint, Text); // writing "false" in data.txt
   } else {
      fprintf(writingData, "%s\n%.2f\n%.2f", "true", Tint, Text); // writing "true" in data.txt
   }
   fclose(writingData); // closing data.txt
   
   remove(".verrouData"); // deleting .verrouData file
}
   
