#ifndef SIPARIS_H
#define SIPARIS_H

#include <stddef.h>

typedef struct {
    int anahtar;
    char *ad;
    char *malzeme;
    char *renk;
} Siparis;

extern Siparis *siparis_olustur(size_t tamponBoyutu);

extern void siparis_yoket(Siparis *siparis);

extern void
siparis_doldur(Siparis *siparis, const char *anahtar, const char *ad, const char *malzeme, const char *renk);

extern void siparis_yazdir(Siparis siparis);

#endif //SIPARIS_H
