#include <siparis.h>
#include <stdlib.h>
#include "islem.h"

int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 11; i++) {
        if (girdi[i] < '0' || girdi[i] > '9')
            return 1;
    }

    if (girdi[12] != '\0')
        return 1;

    return 0;
}

int bosluklari_sil(char *girdi) {
    size_t l = strlen(girdi);
    char *tmp = malloc(sizeof(char) * l);
    char *c = girdi;
    int i;
    size_t j = 0;

    for (i = 0; i < l; i++) {
        if (*c == ' ') continue;

        tmp[j++] = *c;
    }

    memcpy(girdi, tmp, j);
    free(tmp);

    return j;
}

int
kayda_ekle(const char *anahtar, const char *ad, const char *malzeme, const char *renk, Siparis *siparis, Kayit kayit) {
    if (sayi_mi(anahtar) != 0)
        return 1;

    siparis->anahtar = strtol(anahtar, NULL, 10);
    strcpy(siparis->ad, ad);
    strcpy(siparis->malzeme, malzeme);
    strcpy(siparis->renk, renk);

    kayit_ekle(kayit, *siparis);

    return 0;
}

int kayda_ekle_dosyadan(const char *girdi, Kayit kayit) {
    char *bosluksuz = strdup(girdi);

    if (bosluklari_sil(bosluksuz) < 5 || bosluksuz[3] != '<') {
        free(bosluksuz);
        return 1;
    }

    kayit_ekle_dosyadan(kayit, &bosluksuz[4]);

    free(bosluksuz);
    return 0;
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

    if (strcmp(bolumler[0], "add") == 0) {
        if (kayda_ekle(bolumler[1], bolumler[2], bolumler[3], bolumler[4], siparis, kayit) != 0)
            return ISLEM_HATALI_ANAHTAR;
    } else if (memcmp(bolumler[0], "pro", 3) == 0) {
        if (kayda_ekle_dosyadan(bolumler[0], kayit) != 0)
            return ISLEM_HATALI_PRO_KOMUTU;
    }

    for (i = 0; i < 5; i++)
        free(bolumler[i]);
    free(bolumler);

    return 0;
}