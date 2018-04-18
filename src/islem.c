#include <siparis.h>
#include <stdlib.h>
#include "islem.h"

int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 11; i++) {
        if (girdi[i] < '0' || girdi[i] > '9')
            return 0;
    }

    if (girdi[12] != '\0')
        return 0;

    return 1;
}

int kayda_ekle(const char *anahtar, const char *ad, const char *malzeme, const char *renk, Siparis *siparis) {
    if (!sayi_mi(anahtar))
        return 0;

    siparis->anahtar = strtol(anahtar, NULL, 10);
    strcpy(siparis->ad, ad);
    strcpy(siparis->malzeme, malzeme);
    strcpy(siparis->renk, renk);

    return 1;
}

int girdiyi_cozumle(const char *girdi, Siparis *siparis, Kayit kayit) {
    int i;
    char *t, *s = (char *) girdi;
    char *bolumler[5];

    for (i = 0; i < 5; i++) bolumler[i] = malloc(sizeof(char) * ISLEM_BOLUM_TAMPON_BOYUTU);

    for (i = 0; i < 5; i++) {
        t = strchr(s, '|');

        if (t == '\0') break;

        memcpy(bolumler[i], s, t - s);
        s = t + 1;
    }

    if (i < 1)
        strcpy(bolumler[0], girdi);
    else
        strcpy(bolumler[i], s);

    for (i = 0; i < 5; i++)
        free(bolumler[i]);
    free(bolumler);

    return 1;
}