#ifndef ISLEM_H
#define ISLEM_H

#include <mem.h>
#include <stdio.h>
#include "siparis.h"
#include "kayit.h"

#define ISLEM_BOLUM_TAMPON_BOYUTU 256

#define ISLEM_HATALI_ANAHTAR 1
#define ISLEM_HATALI_PRO_KOMUTU 2

extern int girdiyi_cozumle(const char *girdi, Siparis *siparis, Kayit kayit);

#endif //ISLEM_H
