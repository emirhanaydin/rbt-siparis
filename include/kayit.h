#ifndef KAYIT_H
#define KAYIT_H

#include "jrb.h"
#include "siparis.h"

typedef struct {
    JRB rbt;
} *Kayit;

/* Aşağıda bildirilen fonksiyonlar; işlem hatasız tamamlanırsa 1, aksi takdirde 0 döndürürler. */

extern int kayit_ekle(Kayit kayit, Siparis siparis);

extern int kayit_ekle_dosyadan(Kayit kayit, const char *dosyaadi);

extern int kayit_ara(Kayit kayit, int anahtar);

extern int kayitlari_yazdir(Kayit kayit);

extern int kayitlari_yazdir_dosyaya(Kayit kayit);

#endif //KAYIT_H
