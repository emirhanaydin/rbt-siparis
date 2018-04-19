#ifndef GIRIS_H
#define GIRIS_H

#include <mem.h>
#include "kayit.h"
#include "siparis.h"

#define GIRIS_BOLUM_TAMPON_BOYUTU 256

#define GIRIS_SONLANDIR (-100)

#define GIRIS_HATALI_GIRDI (-101)
#define GIRIS_HATALI_ANAHTAR (-102)
#define GIRIS_HATALI_EKLE_KOMUTU (-103)
#define GIRIS_HATALI_PRO_KOMUTU (-104)
#define GIRIS_HATALI_SEARCH_KOMUTU (-105)
#define GIRIS_HATALI_WRITE_KOMUTU (-106)
#define GIRIS_HATALI_PRINT_KOMUTU (-107)
#define GIRIS_HATALI_QUIT_KOMUTU (-108)

extern int girdiyi_cozumle(const char *girdi, Kayit kayit);

extern void hata_mesaji_yazdir(int hata_kodu);

#endif //GIRIS_H
