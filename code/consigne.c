#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
   
      float thermostat_f=0;

      if(access(".verrouConsigne", F_OK) != 0){

         FILE* readFile = fopen("consigne.txt", "r");

         if (readFile == NULL) //check if consigne.txt exists
         {
            printf("Fichier consigne.txt inexistant\n");
            return 0;
         }

         fscanf(readFile, "%f", &thermostat_f);
         fclose(readFile);

         FILE* lockfile = fopen(".verrouConsigne", "w");
         fclose(lockfile);
         remove(".verrouConsigne"); //remove .verrouConsigne
      }
      else{
         return thermostatPrec_f;
      }

         
     
      return thermostat_f;
   
   }
