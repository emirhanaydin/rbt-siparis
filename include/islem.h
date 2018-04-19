#ifndef ISLEM_H
#define ISLEM_H

#include <mem.h>
#include "kayit.h"
#include "siparis.h"

#define ISLEM_BOLUM_TAMPON_BOYUTU 256

#define ISLEM_CIKIS (-100)

#define ISLEM_HATALI_GIRDI (-101)
#define ISLEM_HATALI_ANAHTAR (-102)
#define ISLEM_HATALI_EKLE_KOMUTU (-103)
#define ISLEM_HATALI_PRO_KOMUTU (-104)
#define ISLEM_HATALI_SEARCH_KOMUTU (-105)
#define ISLEM_HATALI_WRITE_KOMUTU (-106)
#define ISLEM_HATALI_PRINT_KOMUTU (-107)
#define ISLEM_HATALI_QUIT_KOMUTU (-108)

extern int girdiyi_cozumle(const char *girdi, Siparis *siparis, Kayit kayit);

extern void hata_mesaji_yazdir(int hata_kodu);

#endif //ISLEM_H
