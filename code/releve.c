#include "releve.h"


void releve(FT_HANDLE ftHandle, temp_t myTemp){
    int SOT_int = 0; 
    int SOT_ext = 0;

    FT_STATUS ftStatus;

    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReturned;
    DWORD EventDWord;

    char RxBuffer[64];

   //check if there is data to read
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
 
    if (ftStatus != FT_OK) {
        printf("Error FT_GetStatus: %d", ftStatus);
        return;
    }
    else{

        //if there is data to read
        if(RxBytes > 0){

            //read the data
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReturned);

            //check if there is an error
            if (ftStatus != FT_OK) {
                printf("Error FT_Read: %d", ftStatus);
                return;
            }
            else{
                int oct_read = 0; //number of octet read

                //get the data from the buffer and create SOTs values
                for(int i = 0; i < BytesReturned; i++){
                    //check last 4 bits of the octet and remap it to the right place
                    switch (RxBuffer[i]&0xF0 >> 4)
                    {
                        case 0b0000: //bits 0 to 3 of SOT_ext
                            SOT_ext |= (RxBuffer[i]&0x0F);
                            oct_read++;
                            break;
                        case 0b0001: //bits 4 to 7 of SOT_ext
                            SOT_ext |= (RxBuffer[i]&0x0F) << 4;
                            oct_read++;
                            break;
                        case 0b0100: //bits 8 to 11 of SOT_ext
                            SOT_ext |= (RxBuffer[i]&0x0F) << 8;
                            oct_read++;
                            break;

                        case 0b1000: //bits 0 to 3 of SOT_int
                            SOT_int |= (RxBuffer[i]&0x0F);
                            oct_read++;
                            break;

                        case 0b1001: //bits 4 to 7 of SOT_int
                            SOT_int |= (RxBuffer[i]&0x0F) << 4;
                            oct_read++;   
                            break;

                        case 0b1100: //bits 8 to 11 of SOT_int
                            SOT_int |= (RxBuffer[i]&0x0F) << 8; 
                            oct_read++;       
                            break;
                        default:
                            break;
                    }
                }

                //if all the octets have been read
                if(oct_read == 6){
                    //convert SOTs to temperature
                    myTemp.interieure = -39.64 + 0.04*SOT_int;
                    myTemp.exterieure = -39.64 + 0.04*SOT_ext;
                }
            }
        }
    }
}