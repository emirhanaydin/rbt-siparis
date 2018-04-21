#include <siparis.h>
#include <stdio.h>

extern void siparis_yazdir(Siparis siparis) {
    printf("%d, %s, %s, %s\n", siparis.anahtar, siparis.ad, siparis.malzeme, siparis.renk);
}
