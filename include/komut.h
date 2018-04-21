#ifndef KOMUT_H
#define KOMUT_H

#include "islem.h"
#include "siparis.h"

#define KOMUT_SONLANDIR (-100)

#define KOMUT_HATALI_GIRDI (-101)
#define KOMUT_HATALI_ANAHTAR (-102)
#define KOMUT_HATALI_EKLE (-103)
#define KOMUT_HATALI_PRO (-104)
#define KOMUT_HATALI_SEARCH (-105)
#define KOMUT_HATALI_WRITE (-106)
#define KOMUT_HATALI_PRINT (-107)
#define KOMUT_HATALI_QUIT (-108)

#define KOMUT_EKLE "add"
#define KOMUT_PRO "pro"
#define KOMUT_SEARCH "search"
#define KOMUT_WRITE "write"
#define KOMUT_PRINT "print"
#define KOMUT_QUIT "quit"

enum Komut {
    SIPARIS_EKLE,
    SIPARIS_EKLE_DOSYADAN,
    SIPARIS_ARA,
    SIPARIS_YAZDIR,
    SIPARIS_YAZDIR_DOSYAYA,
    CIKIS
};

extern int girdiyi_cozumle(const char *girdi, Islem islem, char **bolumler, int *bolumSayisi, enum Komut *secilenKomut);

extern void hata_mesaji_yazdir(int hata_kodu);

#endif //KOMUT_H
