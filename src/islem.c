#include "islem.h"

Islem islem_olustur() {
    Islem islem = malloc(sizeof(struct islemstruct));
    islem->jrb = make_jrb();
}

void islem_yoket(Islem islem) {
    JRB gecici;

    jrb_traverse(gecici, islem->jrb) {
        siparis_yoket(gecici->val.v);
    }

    jrb_free_tree(islem->jrb);

    free(islem);
}

static int siparis_var_mi(Islem islem, int anahtar) {
    return jrb_find_int(islem->jrb, anahtar) != NULL;
}

static size_t islem_siparis_sayisi_al(Islem islem) {
    size_t uzunluk = 0;
    JRB gecici;

    jrb_traverse(gecici, islem->jrb) {
        uzunluk++;
    }

    return uzunluk;
}

int islem_siparis_ekle(Islem islem, Siparis *siparis) {
    if (siparis_var_mi(islem, siparis->anahtar))
        return ISLEM_ANAHTAR_ZATEN_VAR;

    jrb_insert_int(islem->jrb, siparis->anahtar, new_jval_v(siparis));

    return 0;
}

int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi, size_t tamponBoyutu) {
    IS is = new_inputstruct(dosyaAdi);

    if (is == NULL)
        return ISLEM_DOSYA_ACILAMADI;

    char **bolumler = string_dizisi_olustur(5, tamponBoyutu);

    size_t okunanSayisi = 0; /* Eğer hiçbir kayıt okunmamışsa hata değeri döndürmek için. */
    char sonEk[tamponBoyutu]; /* Hata mesajına anahtarı dahil etmek için. */
    while (get_line(is) >= 0) {
        enum Komut komut;
        int hataKodu = girdiyi_cozumle(is->text1, bolumler, &komut);
        if (hataKodu != 0) {
            fprintf(stderr, "Hatali giris: %s", is->text1);
            continue;
        }

        if (komut != SIPARIS_EKLE) {
            fprintf(stderr, "Hatali komut: %s", is->text1);
            continue;
        }

        Siparis *siparis = siparis_doldur_yeni(tamponBoyutu, bolumler[1], bolumler[2], bolumler[3], bolumler[4]);

        hataKodu = islem_siparis_ekle(islem, siparis);
        if (hataKodu != 0) {
            memcpy(sonEk, " (", 2);
            strcpy(sonEk + 2, bolumler[1]);
            memcpy(sonEk + strlen(sonEk), ")\n\0", 3);

            islem_hata_mesaji_yazdir(islem_siparis_ekle(islem, siparis), NULL, sonEk);
        } else
            okunanSayisi++;
    }

    string_dizisi_yok_et(bolumler, 5);
    jettison_inputstruct(is);

    if (okunanSayisi < 1)
        return ISLEM_DOSYA_ICERIGI_GECERSIZ;

    return 0;
}

int islem_siparis_ara(Islem islem, int anahtar, Siparis **siparis) {
    JRB dugum = jrb_find_int(islem->jrb, anahtar);

    if (dugum == NULL)
        return ISLEM_SIPARIS_BULUNAMADI;

    *siparis = dugum->val.v;

    return 0;
}

int islem_siparisleri_yazdir(Islem islem) {
    if (islem_siparis_sayisi_al(islem) < 1)
        return ISLEM_SIPARIS_YOK;

    JRB gecici;

    jrb_traverse(gecici, islem->jrb) {
        Siparis *siparis = gecici->val.v;
        siparis_yazdir(*siparis);
    }

    return 0;
}

int islem_siparisleri_yazdir_dosyaya(Islem islem, const char *dosyaAdi) {
    if (islem_siparis_sayisi_al(islem) < 1)
        return ISLEM_SIPARIS_YOK;

    JRB gecici;
    FILE *dosya = fopen(dosyaAdi, "w");

    if (dosya == NULL) {
        return ISLEM_DOSYA_ACILAMADI;
    }

    jrb_traverse(gecici, islem->jrb) {
        Siparis *siparis = gecici->val.v;

        fprintf(dosya, "%d, %s, %s, %s\n", siparis->anahtar, siparis->ad, siparis->malzeme, siparis->renk);
    }

    fclose(dosya);

    return 0;
}

void islem_hata_mesaji_yazdir(int hataKodu, const char *onEk, const char *sonEk) {
    if (hataKodu == 0) return;

    if (onEk != NULL) printf("%s", onEk);

    switch (hataKodu) {
        case ISLEM_SIPARIS_BULUNAMADI:
            fprintf(stderr, "Aranan siparis bulunamadi.");
            break;
        case ISLEM_DOSYA_ACILAMADI:
            fprintf(stderr, "Dosyaya erisim basarisiz.");
            break;
        case ISLEM_SIPARIS_YOK:
            fprintf(stderr, "Kayitli siparis yok.");
            break;
        case ISLEM_ANAHTAR_ZATEN_VAR:
            fprintf(stderr, "Girilen anahtar degerine sahip bir siparis onceden eklenmis.");
            break;
        case ISLEM_DOSYA_ICERIGI_GECERSIZ:
            fprintf(stderr, "Dosyada gecerli bir siparis bulunamadi.");
            break;
        default:
            break;
    }

    if (sonEk != NULL) printf("%s", sonEk);
}