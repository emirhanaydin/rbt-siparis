#include <malloc.h>

char **string_dizisi_olustur(size_t uzunluk, size_t tamponBoyutu) {
    char **dizi = malloc(sizeof(char *) * uzunluk);

    for (int i = 0; i < uzunluk; ++i) {
        dizi[i] = malloc(sizeof(char) * tamponBoyutu);
    }

    return dizi;
}

void string_dizisi_yok_et(char **dizi, size_t uzunluk) {
    for (int i = 0; i < uzunluk; ++i) {
        free(dizi[i]);
    }

    free(dizi);
}