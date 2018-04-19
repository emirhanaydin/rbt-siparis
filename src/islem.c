#include <siparis.h>
#include <stdlib.h>
#include "islem.h"

int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 11; i++) {
        if (girdi[i] < '0' || girdi[i] > '9')
            return 1;
    }

    if (girdi[12] != '\0')
        return 1;

    return 0;
}

int bosluklari_sil(char *girdi) {
    size_t boyut = strlen(girdi);
    char *gecici = malloc(sizeof(char) * boyut);
    size_t sonBoyut = 0;

    for (int i = 0; i < boyut; i++) {
        if (girdi[i] == ' ') continue;

        gecici[sonBoyut++] = girdi[i];
    }

    memcpy(girdi, gecici, sonBoyut);
    free(gecici);

    return sonBoyut;
}

int gereksiz_bosluklari_temizle(char *girdi) {
    size_t len = strlen(girdi);
    int ilk, son;

    for (ilk = 0; ilk < len; ilk++) {
        if (girdi[ilk] != ' ') break;
    }

    for (son = len; son > 0; son--) {
        if (girdi[son] != ' ') break;
    }

    size_t sonBoyut = (size_t) (son - ilk);
    char *gecici = malloc(sizeof(char) * len);

    for (int i = 0; i < sonBoyut; i++) {
        gecici[i] = girdi[ilk + i];
    }

    memcpy(girdi, gecici, sonBoyut);

    free(gecici);
    return sonBoyut;
}

int
kayit_ekle_islemi(const char *anahtar, const char *ad, const char *malzeme, const char *renk, Siparis *siparis,
                  Kayit kayit) {
    if (sayi_mi(anahtar) != 0)
        return ISLEM_HATALI_ANAHTAR;

    siparis->anahtar = strtol(anahtar, NULL, 10);
    strcpy(siparis->ad, ad);
    strcpy(siparis->malzeme, malzeme);
    strcpy(siparis->renk, renk);

    kayit_ekle(kayit, *siparis);

    return 0;
}

int kayit_ekle_dosyadan_islemi(const char *girdi, Kayit kayit) {
    char *bosluksuz = strdup(girdi);

    if (bosluklari_sil(bosluksuz) < 5 || bosluksuz[3] != '<') {
        free(bosluksuz);
        return ISLEM_HATALI_PRO_KOMUTU;
    }

    kayit_ekle_dosyadan(kayit, &bosluksuz[4]);

    free(bosluksuz);
    return 0;
}

int kayit_ara_islemi(const char *anahtar, Kayit kayit) {
    if (sayi_mi(anahtar) != 0)
        return ISLEM_HATALI_ANAHTAR;

    kayit_ara(kayit, strtol(anahtar, NULL, 10));

    return 0;
}

int kayitlari_yazdir_dosyaya_islemi(const char *dosyaAdi, Kayit kayit) {
    kayitlari_yazdir_dosyaya(kayit, dosyaAdi);

    return 0;
}

int kayitlari_yazdir_islemi(Kayit kayit) {
    kayitlari_yazdir(kayit);

    return 0;
}

int girdiyi_cozumle(const char *girdi, Siparis *siparis, Kayit kayit) {
    char *cizgi, *onceki = (char *) girdi;
    char *bolumler[5];

    for (int i = 0; i < 5; i++) bolumler[i] = malloc(sizeof(char) * ISLEM_BOLUM_TAMPON_BOYUTU);

    int bolumSayisi;
    for (bolumSayisi = 0; bolumSayisi < 5; bolumSayisi++) {
        cizgi = strchr(onceki, '|');

        if (cizgi == '\0') break;

        memcpy(bolumler[bolumSayisi], onceki, cizgi - onceki);
        onceki = cizgi + 1;
    }

    if (bolumSayisi < 1)
        strcpy(bolumler[0], girdi);
    else
        strcpy(bolumler[bolumSayisi], onceki);

    for (int i = 0; i < bolumSayisi; ++i) {
        gereksiz_bosluklari_temizle(bolumler[i]);
    }

    int r = ISLEM_HATALI_GIRDI;
    if (strcmp(bolumler[0], "add") == 0) {
        if (bolumSayisi != 5) return ISLEM_HATALI_EKLE_KOMUTU;

        r = kayit_ekle_islemi(bolumler[1], bolumler[2], bolumler[3], bolumler[4], siparis, kayit);
    } else if (memcmp(bolumler[0], "pro", 3) == 0) {
        if (bolumSayisi != 1) return ISLEM_HATALI_PRO_KOMUTU;

        r = kayit_ekle_dosyadan_islemi(bolumler[0], kayit) != 0;
    } else if (strcmp(bolumler[0], "search") == 0) {
        if (bolumSayisi != 2) return ISLEM_HATALI_SEARCH_KOMUTU;

        r = kayit_ara_islemi(bolumler[1], kayit);
    } else if (strcmp(bolumler[0], "write") == 0) {
        if (bolumSayisi != 2) return ISLEM_HATALI_WRITE_KOMUTU;

        r = kayitlari_yazdir_dosyaya_islemi(bolumler[1], kayit);
    } else if (strcmp(bolumler[0], "print") == 0) {
        if (bolumSayisi != 1) return ISLEM_HATALI_PRINT_KOMUTU;

        r = kayitlari_yazdir_islemi(kayit);
    } else if (strcmp(bolumler[0], "quit") == 0) {
        if (bolumSayisi != 1) return ISLEM_HATALI_QUIT_KOMUTU;

        r = ISLEM_CIKIS;
    }

    for (bolumSayisi = 0; bolumSayisi < 5; bolumSayisi++)
        free(bolumler[bolumSayisi]);

    return r;
}
