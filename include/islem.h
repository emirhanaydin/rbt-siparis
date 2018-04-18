#ifndef ISLEM_H
#define ISLEM_H

#include <mem.h>
#include <stdio.h>
#include "siparis.h"
#include "kayit.h"

#define ISLEM_BOLUM_TAMPON_BOYUTU 256

#define ISLEM_CIKIS 1

#define ISLEM_HATALI_ANAHTAR 101
#define ISLEM_HATALI_EKLE_KOMUTU 102
#define ISLEM_HATALI_PRO_KOMUTU 103
#define ISLEM_HATALI_SEARCH_KOMUTU 104
#define ISLEM_HATALI_WRITE_KOMUTU 105
#define ISLEM_HATALI_PRINT_KOMUTU 106
#define ISLEM_HATALI_QUIT_KOMUTU 107

extern int girdiyi_cozumle(const char *girdi, Siparis *siparis, Kayit kayit);

#endif //ISLEM_H
