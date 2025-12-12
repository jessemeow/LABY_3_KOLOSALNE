#include <stdio.h>      // Standardowe wejscie/wyjscie
#include <stdlib.h>     // Malloc
#include <stdbool.h>    // Bool

#define DLUGOSC_STOSU 6

 struct wezel {
    int wartosc;
    struct wezel *nast;
};

typedef struct wezel stos;

void inicjalizuj(stos **s) {
    *s = nullptr;
    // C23 pozwala na uzycie nullptr zamiast NULL.
}

bool pusty(const stos *s) {
    return s == nullptr;
}


bool wloz(stos **s, const int x) {
    stos *nowyElement = malloc(sizeof(stos));
    if (nowyElement != NULL) {
        nowyElement->nast = *s;
        nowyElement->wartosc = x;
    }
    return false;
}

int main() {

    return 0;
}