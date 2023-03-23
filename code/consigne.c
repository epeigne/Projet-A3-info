#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
   
      float thermostat_f=0;

      //check if .verrouConsigne exists
      if(access(".verrouConsigne", F_OK) != 0){

         //open consigne.txt
         FILE* readFile = fopen("consigne.txt", "r");

         if (readFile == NULL) //check if consigne.txt exists
         {
            printf("Fichier consigne.txt inexistant\n");
            return 0;
         }

         fscanf(readFile, "%f", &thermostat_f); //read consigne.txt
         fclose(readFile); //close consigne.txt

         //create .verrouConsigne
         FILE* lockfile = fopen(".verrouConsigne", "w");
         fclose(lockfile); //close .verrouConsigne
         remove(".verrouConsigne"); //remove .verrouConsigne
      }
      else{
         return thermostatPrec_f; //if .verrouConsigne exists, return the previous value
      }

      return thermostat_f;
   
   }
