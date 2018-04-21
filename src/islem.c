#include <islem.h>
#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <fields.h>

Islem islem_olustur() {
    Islem kayit = malloc(sizeof(struct islemstruct));
    kayit->jrb = make_jrb();
    kayit->siparisler = malloc(sizeof(Siparis *));
    kayit->adet = 0;
    kayit->kapasite = 1;
}

void islem_yoket(Islem islem) {
    jrb_free_tree(islem->jrb);

    Siparis **siparisler = islem->siparisler;
    for (int i = 0; i < islem->adet; ++i) {
        free(siparisler[i]->ad);
        free(siparisler[i]->malzeme);
        free(siparisler[i]->renk);
        free(siparisler[i]);
    }

    free(islem->siparisler);
    free(islem);
}

/* Fonksiyon çağrılmadan önce adet değiştirilmelidir. */
static void siparis_boyut_kontrolu(Islem islem) {
    if (islem->adet <= islem->kapasite) return;

    int yeniKapasite = islem->kapasite * 2;
    Siparis **yeni = malloc(sizeof(Siparis *) * yeniKapasite);

    for (int i = 0; i < islem->adet; ++i) {
        yeni[i] = islem->siparisler[i];
    }

    free(islem->siparisler);
    islem->siparisler = yeni;
    islem->kapasite = yeniKapasite;
}

static Siparis *yeni_siparis_olustur(Islem islem) {
    Siparis *siparis = malloc(sizeof(Siparis));
    siparis->anahtar = -1;
    siparis->ad = malloc(sizeof(char) * ISLEM_TAMPON_BOYUTU);
    siparis->malzeme = malloc(sizeof(char) * ISLEM_TAMPON_BOYUTU);
    siparis->renk = malloc(sizeof(char) * ISLEM_TAMPON_BOYUTU);

    islem->adet++;
    siparis_boyut_kontrolu(islem);
    islem->siparisler[islem->adet - 1] = siparis;

    return siparis;
}

static int siparis_ara(Islem islem, int anahtar) {
    int i;
    for (i = 0; i < islem->adet; ++i) {
        if (islem->siparisler[i]->anahtar == anahtar) {
            return i;
        }
    }

    return ISLEM_SIPARIS_BULUNAMADI;
}

int islem_siparis_ekle(Islem islem, const char *anahtar, const char *ad, const char *malzeme, const char *renk) {
    Siparis *siparis = yeni_siparis_olustur(islem);

    siparis->anahtar = strtol(anahtar, NULL, 10);
    strcpy(siparis->ad, ad);
    strcpy(siparis->malzeme, malzeme);
    strcpy(siparis->renk, renk);

    jrb_insert_int(islem->jrb, siparis->anahtar, new_jval_v(siparis));
}

int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi) {
    IS is = new_inputstruct(dosyaAdi);

    if (is == NULL) return ISLEM_DOSYA_OKUNAMIYOR;

    while (get_line(is) >= 0) {
        for (int i = 0; i < is->NF; ++i) {
            printf("%d: %s\n", is->line, is->fields[i]);
        }
    }

    jettison_inputstruct(is);

    return 0;
}

int islem_siparis_ara(Islem islem, int anahtar, Siparis **siparis) {
    int indeks = siparis_ara(islem, anahtar);
    if (indeks < 0) return indeks;

    JRB dugum = jrb_find_int(islem->jrb, anahtar);
    *siparis = dugum->val.v;

    return 0;
}

int islem_siparisleri_yazdir(Islem islem) {
    JRB gecici;

    jrb_traverse(gecici, islem->jrb) {
        Siparis *siparis = gecici->val.v;
        siparis_yazdir(*siparis);
    }

    return 0;
}

int islem_siparisleri_yazdir_dosyaya(Islem islem, const char *dosyaAdi) { return 0; }