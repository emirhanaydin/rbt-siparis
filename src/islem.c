#include <islem.h>
#include <malloc.h>
#include <stdio.h>
#include <fields.h>
#include <komut.h>
#include <yardimci.h>

Islem islem_olustur() {
    Islem islem = malloc(sizeof(struct islemstruct));
    islem->jrb = make_jrb();
}

void islem_yoket(Islem islem) {
    jrb_free_tree(islem->jrb);

    free(islem);
}

int islem_siparis_ekle(Islem islem, Siparis *siparis) {
    jrb_insert_int(islem->jrb, siparis->anahtar, new_jval_v(siparis));
}

int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi, size_t tamponBoyutu) {
    IS is = new_inputstruct(dosyaAdi);

    if (is == NULL)
        return ISLEM_DOSYA_OKUNAMIYOR;

    char **bolumler = string_dizisi_olustur(5, tamponBoyutu);

    while (get_line(is) >= 0) {
        enum Komut komut;
        int hataKodu = girdiyi_cozumle(is->text1, islem, bolumler, &komut);
        if (hataKodu != 0) {
            fprintf(stderr, "Hatali giris: %s", is->text1);
            continue;
        }

        if (komut != SIPARIS_EKLE) {
            fprintf(stderr, "Hatali komut: %s", is->text1);
            continue;
        }

        Siparis *siparis = siparis_doldur_yeni(tamponBoyutu, bolumler[1], bolumler[2], bolumler[3], bolumler[4]);
        islem_siparis_ekle(islem, siparis);
    }

    string_dizisi_yok_et(bolumler, 5);
    jettison_inputstruct(is);

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
    JRB gecici;

    jrb_traverse(gecici, islem->jrb) {
        Siparis *siparis = gecici->val.v;
        siparis_yazdir(*siparis);
    }

    return 0;
}

int islem_siparisleri_yazdir_dosyaya(Islem islem, const char *dosyaAdi) { return 0; }