#ifndef ISLEM_H
#define ISLEM_H

#include <stdint.h>
#include "jrb.h"
#include "siparis.h"

#define ISLEM_SIPARIS_BULUNAMADI (-200)
#define ISLEM_DOSYA_OKUNAMIYOR (-201)

typedef struct islemstruct {
    JRB jrb;
} *Islem;

/* Aşağıda bildirilen fonksiyonlar; işlem hatasız tamamlanırsa 0, aksi takdirde hata değeri döndürürler. */

extern Islem islem_olustur();

extern void islem_yoket(Islem islem);

extern int islem_siparis_ekle(Islem islem, Siparis *siparis);

extern int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi);

extern int islem_siparis_ara(Islem islem, int anahtar, Siparis **siparis);

extern int islem_siparisleri_yazdir(Islem islem);

extern int islem_siparisleri_yazdir_dosyaya(Islem islem, const char *dosyaAdi);

#endif //ISLEM_H
