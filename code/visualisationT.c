#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    if (access(".verrouData", F_OK) != 0) //check if .verrouData exists
    {
        FILE* readFile = fopen("data.txt", "r");
        
        if (readFile == NULL) //check if data.txt exists
        {
            printf("Fichier data.txt inexistant\n");
            exit(1);
        }

        char heat[8];
        fscanf(readFile, "%[^\n]", heat); //get first line of data.txt
        fclose(readFile);

        //open files
        FILE* dataFile = fopen("data.txt", "w");
        FILE* lockfile = fopen(".verrouData", "w");

        fprintf(dataFile,"%s\n%.2f\n%.2f",heat,myTemp.interieure,myTemp.exterieure); //write new data in data.txt
        fclose(dataFile);
        fclose(lockfile);
        remove(".verrouData"); //remove .verrouData
        
    }
    
}
