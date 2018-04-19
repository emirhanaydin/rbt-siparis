#ifndef GIRIS_H
#define GIRIS_H

#include "kayit.h"
#include "siparis.h"

#define GIRIS_SONLANDIR (-100)

#define GIRIS_HATALI_GIRDI (-101)
#define GIRIS_HATALI_ANAHTAR (-102)
#define GIRIS_HATALI_EKLE_KOMUTU (-103)
#define GIRIS_HATALI_PRO_KOMUTU (-104)
#define GIRIS_HATALI_SEARCH_KOMUTU (-105)
#define GIRIS_HATALI_WRITE_KOMUTU (-106)
#define GIRIS_HATALI_PRINT_KOMUTU (-107)
#define GIRIS_HATALI_QUIT_KOMUTU (-108)

enum Islem {
    SIPARIS_EKLE,
    SIPARIS_EKLE_DOSYADAN,
    SIPARIS_ARA,
    SIPARIS_YAZDIR,
    SIPARIS_YAZDIR_DOSYAYA,
    CIKIS
};

extern int girdiyi_cozumle(const char *girdi, Kayit kayit, char **bolumler, int *bolumSayisi, enum Islem *secilenIslem);

extern void hata_mesaji_yazdir(int hata_kodu);

#endif //GIRIS_H
