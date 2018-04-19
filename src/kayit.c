#include <kayit.h>
#include <malloc.h>
#include <mem.h>

Kayit kayit_olustur() {
    Kayit kayit = malloc(sizeof(struct kayitstruct));
    kayit->jrb = make_jrb();
    kayit->siparisler = malloc(sizeof(Siparis));
    kayit->adet = 0;
    kayit->kapasite = 1;
}

void kayit_yoket(Kayit kayit) {
    jrb_free_tree(kayit->jrb);

    Siparis *siparisler = kayit->siparisler;
    for (int i = 0; i < kayit->adet; ++i) {
        free(siparisler[i].ad);
        free(siparisler[i].malzeme);
        free(siparisler[i].renk);
    }

    free(kayit->siparisler);
    free(kayit);
}

/* Fonksiyon çağrılmadan önce adet değiştirilmelidir. */
static void siparis_boyut_kontrolu(Kayit kayit) {
    if (kayit->adet <= kayit->kapasite) return;

    int yeniKapasite = kayit->kapasite * 2;
    Siparis *yeni = malloc(sizeof(Siparis) * yeniKapasite);

    for (int i = 0; i < kayit->adet; ++i) {
        yeni[i] = kayit->siparisler[i];
    }

    free(kayit->siparisler);
    kayit->siparisler = yeni;
    kayit->kapasite = yeniKapasite;
}

static Siparis yeni_siparis_olustur(Kayit kayit) {
    Siparis siparis;
    siparis.anahtar = -1;
    siparis.ad = malloc(sizeof(char) * KAYIT_TAMPON_BOYUTU);
    siparis.malzeme = malloc(sizeof(char) * KAYIT_TAMPON_BOYUTU);
    siparis.renk = malloc(sizeof(char) * KAYIT_TAMPON_BOYUTU);

    kayit->adet++;
    siparis_boyut_kontrolu(kayit);
    kayit->siparisler[kayit->adet - 1] = siparis;

    return siparis;
}

static int siparis_ara(Kayit kayit, int anahtar) {
    int i;
    for (i = 0; i < kayit->adet; ++i) {
        if (kayit->siparisler[i].anahtar == anahtar) {
            return i;
        }
    }

    return KAYIT_SIPARIS_BULUNAMADI;
}

static int siparis_karsilastir(Jval j1, Jval j2) {
    Siparis *s1 = j1.v;
    Siparis *s2 = j2.v;

    if (s1->anahtar < s2->anahtar) return -1;
    if (s1->anahtar > s2->anahtar) return 1;
    if (s1->anahtar == s2->anahtar) return 0;
}

int kayit_siparis_ekle(Kayit kayit, const char *anahtar, const char *ad, const char *malzeme, const char *renk) {
    Siparis siparis = yeni_siparis_olustur(kayit);

    siparis.anahtar = strtol(anahtar, NULL, 10);
    strcpy(siparis.ad, ad);
    strcpy(siparis.malzeme, malzeme);
    strcpy(siparis.renk, renk);

    jrb_insert_gen(kayit->jrb, new_jval_v(yeni_siparis_olustur(kayit)), new_jval_v(NULL), &siparis_karsilastir);
}

int kayit_ekle_dosyadan(Kayit kayit, const char *dosyaAdi) { return 0; }

int kayit_siparis_ara(Kayit kayit, int anahtar) {
    int indeks = siparis_ara(kayit, anahtar);
    if (indeks < 0) return indeks;

    JRB dugum = jrb_find_int(kayit->jrb, anahtar);

    return ((Siparis *) dugum->key.v)->anahtar;
}

int kayitlari_yazdir(Kayit kayit) { return 0; }

int kayitlari_yazdir_dosyaya(Kayit kayit, const char *dosyaAdi) { return 0; }