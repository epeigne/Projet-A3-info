#ifndef COMMANDE_H
#define COMMANDE_H

#include <windows.h>
#include "../lib/ftd2xx.h"
#include "../define.h"

// commande = puissance chauffage en %
void commande(FT_HANDLE ftHandle, float commande);

#endif