#include <islem.h>
#include <malloc.h>
#include <stdio.h>
#include <fields.h>

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

int islem_siparis_ekle_dosyadan(Islem islem, const char *dosyaAdi) {
    IS is = new_inputstruct(dosyaAdi);

    if (is == NULL)
        return ISLEM_DOSYA_OKUNAMIYOR;

    while (get_line(is) >= 0) {
        for (int i = 0; i < is->NF; ++i) {
            printf("%d: %s\n", is->line, is->fields[i]);
        }
    }

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