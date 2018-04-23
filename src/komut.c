#include "komut.h"

static int sayi_mi(const char *girdi) {
    int i;

    for (i = 0; i < 12 && girdi[i] != '\0'; i++) {
        if (girdi[i] < '0' || girdi[i] > '9')
            return 0;
    }
    if (i > 11) return 0;
    long sayi = strtol(girdi, NULL, 10);

    return sayi <= INT32_MAX;
}

size_t karakterleri_sil(char *girdi, char *karakterler) {
    char *oku = girdi, *yaz = girdi;
    size_t boyut = 0;

    while (*oku) {
        *yaz = *oku++;
        if (strchr(karakterler, *yaz) == NULL) {
            yaz++;
            boyut++;
        }
    }
    *yaz = '\0';
}

static int gereksiz_bosluklari_temizle(char *girdi) {
    size_t boyut = strlen(girdi);
    int ilk, son;

    for (ilk = 0; ilk < boyut; ilk++) {
        if (girdi[ilk] != ' ') break;
    }

    for (son = (int) (boyut - 1); son > 0; son--) {
        if (girdi[son] != ' ') break;
    }

    size_t sonBoyut = (size_t) son - ilk + 1;
    char *gecici = malloc(sizeof(char) * boyut);

    for (int i = 0; i < sonBoyut; i++) {
        gecici[i] = girdi[ilk + i];
    }

    memcpy(girdi, gecici, sonBoyut);
    girdi[sonBoyut] = '\0';

    free(gecici);
    return (int) sonBoyut;
}

int komut_siparis_ekle_kontrol(const char *anahtar) {
    if (!sayi_mi(anahtar))
        return KOMUT_HATALI_ANAHTAR;

    return 0;
}

int komut_siparis_ekle_dosyadan_kontrol(const char *girdi, char *dosyaAdi) {
    char *bosluksuz = strdup(girdi);
    int r = 0;

    if (karakterleri_sil(bosluksuz, " ") < 5)
        r = KOMUT_HATALI_PRO;

    char *arguman = strchr(bosluksuz, '<');
    if (arguman - bosluksuz < 3)
        r = KOMUT_HATALI_PRO;
    else if (*(++arguman) == '\0')
        r = KOMUT_HATALI_PRO;
    else
        strcpy(dosyaAdi, arguman);

    free(bosluksuz);
    return r;
}

int komut_siparis_ara_kontrol(const char *anahtar) {
    if (!sayi_mi(anahtar))
        return KOMUT_HATALI_ANAHTAR;

    return 0;
}

int girdiyi_cozumle(const char *girdi, char **bolumler, enum Komut *secilenKomut) {
    char *cizgi, *onceki = (char *) girdi;
    int bolumSayisi = 0;

    for (bolumSayisi = 0; bolumSayisi < 5; bolumSayisi++) {
        cizgi = strchr(onceki, '|');

        if (cizgi == '\0') break;

        size_t boyut = cizgi - onceki;
        memcpy(bolumler[bolumSayisi], onceki, boyut);
        bolumler[bolumSayisi][boyut] = '\0';
        onceki = cizgi + 1;
    }

    if (bolumSayisi > 4)
        return KOMUT_HATALI_GIRDI;

    bolumSayisi++;

    if (bolumSayisi < 2)
        strcpy(bolumler[0], girdi);
    else
        strcpy(bolumler[bolumSayisi - 1], onceki);

    for (int i = 0; i < bolumSayisi; ++i) {
        gereksiz_bosluklari_temizle(bolumler[i]);
        karakterleri_sil(bolumler[i], "\r\n");
    }

    int r = KOMUT_HATALI_GIRDI;
    if (strcmp(bolumler[0], KOMUT_EKLE) == 0) {
        if (bolumSayisi != 5) return KOMUT_HATALI_EKLE;

        r = komut_siparis_ekle_kontrol(bolumler[1]);
        *secilenKomut = SIPARIS_EKLE;
    } else if (memcmp(bolumler[0], KOMUT_PRO, 3) == 0) {
        if (bolumSayisi != 1) return KOMUT_HATALI_PRO;

        r = komut_siparis_ekle_dosyadan_kontrol(bolumler[0], bolumler[1]);
        *secilenKomut = SIPARIS_EKLE_DOSYADAN;
    } else if (strcmp(bolumler[0], KOMUT_SEARCH) == 0) {
        if (bolumSayisi != 2) return KOMUT_HATALI_SEARCH;

        r = komut_siparis_ara_kontrol(bolumler[1]);
        *secilenKomut = SIPARIS_ARA;
    } else if (strcmp(bolumler[0], KOMUT_WRITE) == 0) {
        if (bolumSayisi != 2) return KOMUT_HATALI_WRITE;

        r = 0;
        *secilenKomut = SIPARISLERI_YAZDIR_DOSYAYA;
    } else if (strcmp(bolumler[0], KOMUT_PRINT) == 0) {
        if (bolumSayisi != 1) return KOMUT_HATALI_PRINT;

        r = 0;
        *secilenKomut = SIPARISLERI_YAZDIR;
    } else if (strcmp(bolumler[0], KOMUT_QUIT) == 0) {
        if (bolumSayisi != 1) return KOMUT_HATALI_QUIT;

        r = 0;
        *secilenKomut = CIKIS;
    }

    return r;
}

void komut_hata_mesaji_yazdir(int hataKodu, const char *onEk, const char *sonEk) {
    if (hataKodu == 0) return;

    const char *komut_hata = "komutunu hatali kullandiniz. \n\nKullanim\n\n  ";

    if (onEk != NULL) printf("%s", onEk);

    switch (hataKodu) {
        case KOMUT_SONLANDIR: /* Hata yok */
            break;
        case KOMUT_HATALI_GIRDI:
            fprintf(stderr, "Hatali bir giris yaptiniz.");
            break;
        case KOMUT_HATALI_ANAHTAR:
            fprintf(stderr, "Girilen anahtar degeri gecersiz.");
            break;
        case KOMUT_HATALI_EKLE:
            fprintf(stderr, "%s %sadd|anahtar|ad|malzeme|renk", KOMUT_EKLE, komut_hata);
            break;
        case KOMUT_HATALI_PRO:
            fprintf(stderr, "%s %spro < dosya_adi", KOMUT_PRO, komut_hata);
            break;
        case KOMUT_HATALI_SEARCH:
            fprintf(stderr, "%s %ssearch|anahtar", KOMUT_SEARCH, komut_hata);
            break;
        case KOMUT_HATALI_WRITE:
            fprintf(stderr, "%s %swrite|dosya_adi", KOMUT_WRITE, komut_hata);
            break;
        case KOMUT_HATALI_PRINT:
            fprintf(stderr, "%s %sprint", KOMUT_PRINT, komut_hata);
            break;
        case KOMUT_HATALI_QUIT:
            fprintf(stderr, "%s %squit", KOMUT_QUIT, komut_hata);
            break;
        default:
            break;
    }

    if (sonEk != NULL) printf("%s", sonEk);
}