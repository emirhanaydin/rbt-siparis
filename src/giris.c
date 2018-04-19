#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "giris.h"

int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 12 && girdi[i] != '\0'; i++) {
        if (!isdigit(girdi[i]))
            return 0;
    }
    if (i > 11) return 0;
    long sayi = strtol(girdi, NULL, 10);

    return sayi <= INT32_MAX;
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
    size_t boyut = strlen(girdi);
    int ilk, son;

    for (ilk = 0; ilk < boyut; ilk++) {
        if (girdi[ilk] != ' ') break;
    }

    for (son = boyut - 1; son > 0; son--) {
        if (girdi[son] != ' ') break;
    }

    size_t sonBoyut = (size_t) (son - ilk + 1);
    char *gecici = malloc(sizeof(char) * boyut);

    for (int i = 0; i < sonBoyut; i++) {
        gecici[i] = girdi[ilk + i];
    }

    memcpy(girdi, gecici, sonBoyut);
    girdi[sonBoyut] = '\0';

    free(gecici);
    return sonBoyut;
}

int giris_siparis_ekle_kontrol(const char *anahtar) {
    if (!sayi_mi(anahtar))
        return GIRIS_HATALI_ANAHTAR;

    return 0;
}

int giris_siparis_ekle_dosyadan(const char *girdi, Kayit kayit) {
    char *bosluksuz = strdup(girdi);

    if (bosluklari_sil(bosluksuz) < 5 || bosluksuz[3] != '<') {
        free(bosluksuz);
        return GIRIS_HATALI_PRO_KOMUTU;
    }

    kayit_ekle_dosyadan(kayit, &bosluksuz[4]);

    free(bosluksuz);
    return 0;
}

int giris_siparis_ara_kontrol(const char *anahtar) {
    if (!sayi_mi(anahtar))
        return GIRIS_HATALI_ANAHTAR;

    return 0;
}

int giris_siparisleri_yazdir_dosyadan(const char *dosyaAdi, Kayit kayit) {
    kayitlari_yazdir_dosyaya(kayit, dosyaAdi);

    return 0;
}

int giris_siparisleri_yazdir(Kayit kayit) {
    kayitlari_yazdir(kayit);

    return 0;
}

int girdiyi_cozumle(const char *girdi, Kayit kayit, char **bolumler, int *bolumSayisi, enum Islem *secilenIslem) {
    char *cizgi, *onceki = (char *) girdi;

    for (*bolumSayisi = 0; *bolumSayisi < 5; (*bolumSayisi)++) {
        cizgi = strchr(onceki, '|');

        if (cizgi == '\0') break;

        size_t boyut = cizgi - onceki;
        memcpy(bolumler[*bolumSayisi], onceki, boyut);
        bolumler[*bolumSayisi][boyut] = '\0';
        onceki = cizgi + 1;
    }
    (*bolumSayisi)++;

    if (*bolumSayisi < 2)
        strcpy(bolumler[0], girdi);
    else
        strcpy(bolumler[*bolumSayisi - 1], onceki);

    for (int i = 0; i < *bolumSayisi; ++i) {
        gereksiz_bosluklari_temizle(bolumler[i]);
    }

    int r = GIRIS_HATALI_GIRDI;
    if (strcmp(bolumler[0], "add") == 0) {
        if (*bolumSayisi != 5) return GIRIS_HATALI_EKLE_KOMUTU;

        r = giris_siparis_ekle_kontrol(bolumler[1]);
    } else if (memcmp(bolumler[0], "pro", 3) == 0) {
        if (*bolumSayisi != 1) return GIRIS_HATALI_PRO_KOMUTU;

        r = giris_siparis_ekle_dosyadan(bolumler[0], kayit) != 0;
    } else if (strcmp(bolumler[0], "search") == 0) {
        if (*bolumSayisi != 2) return GIRIS_HATALI_SEARCH_KOMUTU;

        r = giris_siparis_ara_kontrol(bolumler[1]);
    } else if (strcmp(bolumler[0], "write") == 0) {
        if (*bolumSayisi != 2) return GIRIS_HATALI_WRITE_KOMUTU;

        r = giris_siparisleri_yazdir_dosyadan(bolumler[1], kayit);
    } else if (strcmp(bolumler[0], "print") == 0) {
        if (*bolumSayisi != 1) return GIRIS_HATALI_PRINT_KOMUTU;

        r = giris_siparisleri_yazdir(kayit);
    } else if (strcmp(bolumler[0], "quit") == 0) {
        if (*bolumSayisi != 1) return GIRIS_HATALI_QUIT_KOMUTU;

        r = GIRIS_SONLANDIR;
    }

    return r;
}

void hata_mesaji_yazdir(int hata_kodu) {
    const char *komut_hata = "komutunu hatali kullandiniz. Kullanimi: ";

    switch (hata_kodu) {
        case 0: /* Hata yok */
        case GIRIS_SONLANDIR: /* Hata yok */
            break;
        case GIRIS_HATALI_GIRDI:
            fprintf(stderr, "Hatali bir giris yaptiniz.");
            break;
        case GIRIS_HATALI_ANAHTAR:
            fprintf(stderr, "Girilen anahtar degeri gecersiz.");
            break;
        case GIRIS_HATALI_EKLE_KOMUTU:
            fprintf(stderr, "add %sadd|anahtar|ad|malzeme|renk", komut_hata);
            break;
        case GIRIS_HATALI_PRO_KOMUTU:
            fprintf(stderr, "pro %spro < dosya_adi", komut_hata);
            break;
        case GIRIS_HATALI_SEARCH_KOMUTU:
            fprintf(stderr, "search %ssearch|anahtar", komut_hata);
            break;
        case GIRIS_HATALI_WRITE_KOMUTU:
            fprintf(stderr, "write %swrite|dosya_adi", komut_hata);
            break;
        case GIRIS_HATALI_PRINT_KOMUTU:
            fprintf(stderr, "print %sprint", komut_hata);
            break;
        case GIRIS_HATALI_QUIT_KOMUTU:
            fprintf(stderr, "quit %squit", komut_hata);
            break;
        default:
            break;
    }
}