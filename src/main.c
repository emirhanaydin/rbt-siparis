#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

#define GIRDI_TAMPON_BOYUTU 256

int main() {
    char tampon[GIRDI_TAMPON_BOYUTU];

    do {
        printf("> ");
        scanf("%s", tampon);
    } while (strcmp(tampon, "exit") != 0);

    exit(0);
}