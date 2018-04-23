#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "komut.h"
#include "yardimci.h"

#define TAMPON_BOYUTU 256 /* Programın tamamında stringler için kullanılan tampon boyutudur. */

int main() {
    char tampon[TAMPON_BOYUTU];
    enum Komut komut;

    /* RBT işlemleri için kullanılır. */
    Islem islem = islem_olustur();

    /* Her bir bölüm girilen komutun bir dilimlik bölgesini tutar. */
    char **girdi = string_dizisi_olustur(5, TAMPON_BOYUTU);

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

        /* Kullanıcı girdisi yorumlanarak hangi komutun verildiği sonucu "komut"a atılır. */
        int hataKodu = girdiyi_cozumle(tampon, girdi, &komut);

        if (hataKodu != 0) {
            komut_hata_mesaji_yazdir(hataKodu, "\n", "\n\n");
            continue;
        }

        Siparis *siparis; /* SIPARIS_EKLE işlemi için kullanılır. */
        switch (komut) {
            case SIPARIS_EKLE:
                /* Girilen komut alanları yeni bir siparişe aktarılır. */
                siparis = siparis_doldur_yeni(TAMPON_BOYUTU, girdi[1], girdi[2], girdi[3], girdi[4]);
                hataKodu = islem_siparis_ekle(islem, siparis);

                if (hataKodu == 0)
                    printf("Siparis eklendi.\n");
                else
                    siparis_yoket(siparis);
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

                if (hataKodu == 0)
                    printf("Siparisler dosyaya yazildi.\n");
                break;
            case CIKIS:
                break;
        }

        islem_hata_mesaji_yazdir(hataKodu, "\n", "\n");

        printf("\n");
    } while (komut != CIKIS);

    string_dizisi_yok_et(girdi, 5);
    islem_yoket(islem);

    exit(0);
}