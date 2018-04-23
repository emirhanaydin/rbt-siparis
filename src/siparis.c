#include "siparis.h"

Siparis *siparis_olustur(size_t tamponBoyutu) {
    Siparis *siparis = malloc(sizeof(Siparis));

    siparis->anahtar = -1;
    siparis->ad = malloc(sizeof(char) * tamponBoyutu);
    siparis->malzeme = malloc(sizeof(char) * tamponBoyutu);
    siparis->renk = malloc(sizeof(char) * tamponBoyutu);

    return siparis;
}

void siparis_yoket(Siparis *siparis) {
    free(siparis->ad);
    free(siparis->malzeme);
    free(siparis->renk);

    free(siparis);
}

void siparis_doldur(Siparis *siparis, const char *anahtar, const char *ad, const char *malzeme, const char *renk) {
    siparis->anahtar = (int) strtol(anahtar, NULL, 10);
    strcpy(siparis->ad, ad);
    strcpy(siparis->malzeme, malzeme);
    strcpy(siparis->renk, renk);
}

Siparis *
siparis_doldur_yeni(size_t tamponBoyutu, const char *anahtar, const char *ad, const char *malzeme, const char *renk) {
    Siparis *siparis = siparis_olustur(tamponBoyutu);
    siparis_doldur(siparis, anahtar, ad, malzeme, renk);

    return siparis;
}

void siparis_yazdir(Siparis siparis) {
    printf("%d, %s, %s, %s\n", siparis.anahtar, siparis.ad, siparis.malzeme, siparis.renk);
}
