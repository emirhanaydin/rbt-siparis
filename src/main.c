#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <islem.h>

int main() {
    char tampon[256];
    Kayit kayit = kayit_olustur();
    int r;

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

        r = girdiyi_cozumle(tampon, kayit);
        if (r != 0) {
            hata_mesaji_yazdir(r);
            printf("\n");
        }
    } while (r != ISLEM_CIKIS);

    kayit_yoket(kayit);

    exit(0);
}