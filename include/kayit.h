#ifndef KAYIT_H
#define KAYIT_H

#include "jrb.h"
#include "siparis.h"

typedef struct {
    JRB rbt;
} *Kayit;

/* Aşağıda bildirilen fonksiyonlar; işlem hatasız tamamlanırsa 1, aksi takdirde 0 döndürürler. */

extern int ekle(Kayit kayit, Siparis siparis);

extern int dosyadan_ekle(Kayit kayit, const char *dosyaadi);

extern int ara(Kayit kayit, int anahtar);

extern int dosyaya_yazdir(Kayit kayit);

extern int ekrana_yazdir(Kayit kayit);

#endif //KAYIT_H
