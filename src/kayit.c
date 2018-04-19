#include <kayit.h>
#include <malloc.h>

Kayit kayit_olustur() {
    Kayit kayit = malloc(sizeof(struct kayitstruct));
    kayit->jrb = make_jrb();
}

void kayit_yoket(Kayit kayit) {
    jrb_free_tree(kayit->jrb);
    free(kayit);
}

int kayit_ekle(Kayit kayit, Siparis siparis) { return 0; }

int kayit_ekle_dosyadan(Kayit kayit, const char *dosyaAdi) { return 0; }

int kayit_ara(Kayit kayit, int anahtar) { return 0; }

int kayitlari_yazdir(Kayit kayit) { return 0; }

int kayitlari_yazdir_dosyaya(Kayit kayit, const char *dosyaAdi) { return 0; }