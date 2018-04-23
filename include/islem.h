#ifndef ISLEM_H
#define ISLEM_H

#include "jrb.h"
#include "fields.h"
#include "siparis.h"
#include "komut.h"
#include "yardimci.h"

#define ISLEM_SIPARIS_BULUNAMADI (-200)
#define ISLEM_DOSYA_ACILAMADI (-201)
#define ISLEM_SIPARIS_YOK (-202)
#define ISLEM_ANAHTAR_ZATEN_VAR (-203)
#define ISLEM_DOSYA_ICERIGI_GECERSIZ (-204)

typedef struct islemstruct {
    JRB jrb;
} *Islem;

/* Aşağıda bildirilen fonksiyonlar; işlem hatasız tamamlanırsa 0, aksi takdirde hata değeri döndürürler. */

extern Islem islem_olustur();

extern void islem_yoket(Islem islem);

extern int islem_siparis_ekle(Islem islem, Siparis *siparis);

extern int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi, size_t tamponBoyutu);

extern int islem_siparis_ara(Islem islem, int anahtar, Siparis **siparis);

extern int islem_siparisleri_yazdir(Islem islem);

extern int islem_siparisleri_yazdir_dosyaya(Islem islem, const char *dosyaAdi);

extern void islem_hata_mesaji_yazdir(int hataKodu, const char *onEk, const char *sonEk);

#endif //ISLEM_H
