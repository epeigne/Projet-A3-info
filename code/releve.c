#include "releve.h"


void releve(FT_HANDLE *card, temp_t myTemp){
    int SOT_int = 0; 
    int SOT_ext = 0;

    FT_STATUS ftStatus;

    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    DWORD EventDWord;

    char RxBuffer[64];


    ftStatus = FT_GetStatus(card, &RxBytes, &TxBytes, &EventDWord);

    //check if there is data to read
    if (ftStatus != FT_OK) {
        printf("Error FT_GetStatus: %d", ftStatus);
        return;
    }
    else{

        //if there is data to read
        if(RxBytes > 0){

            //read the data
            ftStatus = FT_Read(card, RxBuffer, RxBytes, &BytesReceived);

            //check if there is an error
            if (ftStatus != FT_OK) {
                printf("Error FT_Read: %d", ftStatus);
                return;
            }
            else{
                int oct_read = 0; //number of octet read

                //get the data from the buffer and create SOTs values
                for(int i = 0; i < BytesReceived; i++){
                    //check last 4 bits of the octet
                    switch (RxBuffer[i]&0xF0 >> 4)
                    {
                        case 0b0000:
                            SOT_ext |= (RxBuffer[i]&0x0F);
                            oct_read++;
                            break;
                        case 0b0001:
                            SOT_ext |= (RxBuffer[i]&0x0F) << 4;
                            oct_read++;
                            break;
                        case 0b0100:
                            SOT_ext |= (RxBuffer[i]&0x0F) << 8;
                            oct_read++;
                            break;

                        case 0b1000:
                            SOT_int |= (RxBuffer[i]&0x0F);
                            oct_read++;
                            break;

                        case 0b1001:
                            SOT_int |= (RxBuffer[i]&0x0F) << 4;
                            oct_read++;   
                            break;

                        case 0b1100:
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