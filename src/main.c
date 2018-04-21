#include <stdlib.h>
#include <stdio.h>
#include <komut.h>
#include <mem.h>
#include <yardimci.h>

#define TAMPON_BOYUTU 256

int main() {
    char tampon[TAMPON_BOYUTU];
    Islem islem = islem_olustur();
    enum Komut komut;

    do {
        printf("> ");

        if (fgets(tampon, sizeof(tampon), stdin) == NULL) {
            perror("Konsol girdisi okunamiyor.");
            exit(1);
        }

        size_t len = strlen(tampon);
        if (len < 1) {
            perror("Bos giris yapildi.");
            exit(1);
        }

        /* Sondaki satır sonu karakteri silinir. */
        if (tampon[len - 1] == '\n') tampon[len - 1] = '\0';

        char **bolumler = string_dizisi_olustur(5, TAMPON_BOYUTU);
        int hataKodu = girdiyi_cozumle(tampon, bolumler, &komut);
        if (hataKodu != 0) {
            hata_mesaji_yazdir(hataKodu);
            printf("\n");
        } else {
            Siparis *siparis = siparis_doldur_yeni(TAMPON_BOYUTU, bolumler[1], bolumler[2], bolumler[3], bolumler[4]);

            switch (komut) {
                case SIPARIS_EKLE:
                    hataKodu = islem_siparis_ekle(islem, siparis);
                    break;
                case SIPARIS_EKLE_DOSYADAN:
                    hataKodu = islem_siparis_ekle_dosyadan(islem, bolumler[1], TAMPON_BOYUTU);
                    break;
                case SIPARIS_ARA:
                    hataKodu = islem_siparis_ara(islem, strtol(bolumler[1], NULL, 10), &siparis);
                    if (hataKodu == 0)
                        siparis_yazdir(*siparis);
                    break;
                case SIPARISLERI_YAZDIR:
                    hataKodu = islem_siparisleri_yazdir(islem);
                    break;
                case SIPARISLERI_YAZDIR_DOSYAYA:
                    hataKodu = islem_siparisleri_yazdir_dosyaya(islem, bolumler[1]);
                    break;
                case CIKIS:
                    break;
            }

            if (hataKodu != 0) {
                islem_hata_mesaji_yazdir(hataKodu);
                printf("\n");
            }
        }
        string_dizisi_yok_et(bolumler, 5);
    } while (komut != CIKIS);

    islem_yoket(islem);

    exit(0);
}