#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "komut.h"
#include "yardimci.h"

#define TAMPON_BOYUTU 256 /* Programın tamamında stringler için kullanılan tampon boyutudur. */

int main() {
    char tampon[TAMPON_BOYUTU];
    Islem islem = islem_olustur();
    enum Komut komut;

    do {
        printf("> ");

        if (fgets(tampon, TAMPON_BOYUTU, stdin) == NULL) {
            perror("Konsol girdisi okunamiyor.");
            exit(1);
        }

        size_t len = strlen(tampon);
        /* Sondaki satır sonu karakteri silinir. */
        if (tampon[len - 1] == '\n')
            tampon[len - 1] = '\0';

        /* Her bir bölüm girilen komutun bir dilimlik bölgesini tutar. */
        char **girdi = string_dizisi_olustur(5, TAMPON_BOYUTU);

        /* Kullanıcı girdisi yorumlanarak hangi komutun verildiği sonucu "komut"a atılır. */
        int hataKodu = girdiyi_cozumle(tampon, girdi, &komut);

        if (hataKodu != 0) {
            hata_mesaji_yazdir(hataKodu);
            printf("\n");
        } else {
            /* Girilen komut alanları yeni bir siparişe aktarılır. */
            Siparis *siparis = siparis_doldur_yeni(TAMPON_BOYUTU, girdi[1], girdi[2], girdi[3], girdi[4]);

            switch (komut) {
                case SIPARIS_EKLE:
                    hataKodu = islem_siparis_ekle(islem, siparis);
                    break;
                case SIPARIS_EKLE_DOSYADAN:
                    hataKodu = islem_siparis_ekle_dosyadan(islem, girdi[1], TAMPON_BOYUTU);
                    break;
                case SIPARIS_ARA:
                    /* Arama sonucunda bulunan değer "siparis"e atılır. */
                    hataKodu = islem_siparis_ara(islem, (int) strtol(girdi[1], NULL, 10), &siparis);
                    if (hataKodu == 0) /* Hata yoksa sipariş bilgileri ekrana yazdırılır. */
                        siparis_yazdir(*siparis);
                    break;
                case SIPARISLERI_YAZDIR:
                    hataKodu = islem_siparisleri_yazdir(islem);
                    break;
                case SIPARISLERI_YAZDIR_DOSYAYA:
                    hataKodu = islem_siparisleri_yazdir_dosyaya(islem, girdi[1]);
                    break;
                case CIKIS:
                    break;
            }

            if (hataKodu != 0) {
                islem_hata_mesaji_yazdir(hataKodu);
                printf("\n");
            }
        }
        string_dizisi_yok_et(girdi, 5);
    } while (komut != CIKIS);

    islem_yoket(islem);

    exit(0);
}