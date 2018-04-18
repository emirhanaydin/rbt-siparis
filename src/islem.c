#include <siparis.h>
#include <stdlib.h>
#include "islem.h"

int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 11; i++) {
        if (girdi[i] < '0' || girdi[i] > '9')
            return 0;
    }

    if (girdi[12] != NULL)
        return 0;

    return 1;
}

int calistir(const char *girdi, Siparis *siparis) {
    int i;
    char *ggirdi = strdup(girdi);

    // İlk dik çizgi karakteri
    char *bolum = strtok(ggirdi, "|");

    for (i = 0; i < 4 && bolum != NULL; i++) {
        switch (i) {
            case 0:
                if (!sayi_mi(bolum)) {
                    free(ggirdi);
                    return 0;
                }

                siparis->anahtar = strtol(bolum, NULL, 10);
                break;
            case 1:
                strcpy(siparis->ad, bolum);
                break;
            case 2:
                strcpy(siparis->malzeme, bolum);
                break;
            case 3:
                strcpy(siparis->renk, bolum);
                break;
            default:
                break;
        }

        bolum = strtok(NULL, "|");
    }

    if (i < 4) {
        free(ggirdi);
        return 0;
    }

    return 1;
}