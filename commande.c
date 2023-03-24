#include "Inc/commande.h"

void commande(FT_HANDLE ftHandle, float commande){
    FT_STATUS ftStatus;

    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesWritten;
    DWORD EventDWord;

    char TxBuffer[1]; // contains the data to write to the device
    TxBuffer[1] |= 1<<7; // setting the bit 7 to 1 because heating is always on 
    int puis = (commande * 127) / 100; // converting command in % to a value between 0 and 127
    TxBuffer[1] |= (puis & 0x7F); // writting heating power in to the data
    
    //check if we can write data
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
 
    if (ftStatus != FT_OK) {
        printf("Error FT_GetStatus: %d", ftStatus);
        return;
    }
    else{
        //writing the data
        ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
        
        if (ftStatus != FT_OK) { // FT_Write failed
            printf("Error FT_GetStatus: %d", ftStatus);
            return;
        }
    }
}