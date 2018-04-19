#ifndef KAYIT_H
#define KAYIT_H

#include <stdint.h>
#include "jrb.h"
#include "siparis.h"

#define KAYIT_SIPARIS_BULUNAMADI (-200)

typedef struct kayitstruct {
    JRB jrb;
    Siparis *siparisler;
    int adet;
    int kapasite;
} *Kayit;

/* Aşağıda bildirilen fonksiyonlar; işlem hatasız tamamlanırsa 0, aksi takdirde hata değeri döndürürler. */

extern Kayit kayit_olustur();

extern void kayit_yoket(Kayit kayit);

extern int kayit_ekle(Kayit kayit, Siparis siparis);

extern int kayit_ekle_dosyadan(Kayit kayit, const char *dosyaAdi);

extern int kayit_ara(Kayit kayit, int anahtar);

extern int kayitlari_yazdir(Kayit kayit);

extern int kayitlari_yazdir_dosyaya(Kayit kayit, const char *dosyaAdi);

#endif //KAYIT_H
