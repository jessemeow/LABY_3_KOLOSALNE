#include <stdio.h>      // Standardowe wejscie/wyjscie
#include <stdlib.h>     // Malloc
#include <stdbool.h>    // Bool

// KOM -fsanitize=undefined !!!

#define PLUS '+'
#define MINUS '-'
#define ILOCZYN '*'
#define POTEGA '^'

typedef struct kLiczba {
    int bit;
    struct kLiczba *poprzedni;
} kLiczba;

struct wezel {
    int wartosc;
    struct wezel *nastepny;
};

typedef struct wezel stos;


// STOS
void inicjalizujStos (stos **s) {
    *s = nullptr;
    // C23 pozwala na uzycie nullptr zamiast NULL.
}

bool czyPustyStos(const stos *s) {
    return s == nullptr;
}

void wlozNaStos(stos **s, const int x) {
    stos *nowyElement = malloc(sizeof(stos));
    if (!czyPustyStos(nowyElement)) {
        nowyElement->nastepny = *s;
        nowyElement->wartosc = x;
        *s = nowyElement;
    }
}

int zdejmijZeStosu(stos **s) {
    if (!czyPustyStos(*s)) {
        stos *pom = *s;
        const int zdjeta = (*s)->wartosc;
        *s = (*s)->nastepny;
        free(pom);
        return zdjeta;
    }
    return 0;
}

int goraStosu(const stos *s) {
    return s->wartosc;
}

void wyczyscStos(stos **s) {
    while (!czyPustyStos(*s)) {
        zdejmijZeStosu(s);
    }
}


// LICZBY KOLOSALNE
void inicjalizujKLiczbe(const kLiczba **liczba) {
    *liczba = nullptr;
}

bool czyPustaLiczba(const kLiczba **liczba) {
    return liczba == nullptr || *liczba == nullptr;
}


bool czyZnormalizowana(const kLiczba **liczba) {
    // KOM HANDLE KONCOWE ZERO!
    bool znormalizowana = true;
    if (!czyPustaLiczba(liczba)) {
        const kLiczba *obecnaCyfra = *liczba;
        const kLiczba *nastepnaCyfra = obecnaCyfra->poprzedni;

        while (nastepnaCyfra != nullptr && nastepnaCyfra->bit == 0) {
            nastepnaCyfra = nastepnaCyfra->poprzedni;
        }
        while (nastepnaCyfra != nullptr && nastepnaCyfra->bit == 1) {
            nastepnaCyfra = nastepnaCyfra->poprzedni;
        }

        bool czyRozne = false;
        // KOM DODAJ WARUNKI ABY SPRAWDZALY TYLKO PO DWIE CYFRY
        // W warunku nie dodajemy flagi !czyRozne, aby dotrzec do konca
        // danej cyfry (co ulatwi rekurencyjne wywolanie tej funkcji).
        while (nastepnaCyfra != nullptr && obecnaCyfra != nullptr) {
            if (obecnaCyfra->bit != nastepnaCyfra->bit) {
                czyRozne = true;
            }
            obecnaCyfra = obecnaCyfra->poprzedni;
            nastepnaCyfra = nastepnaCyfra->poprzedni;
        }
        if (czyRozne) {
            czyZnormalizowana(&nastepnaCyfra);
        } else {
           znormalizowana = false;
        }
    }
    return znormalizowana;
}

void normalizujKLiczbe(kLiczba **liczba) {
    // if (!czyPustaLiczba(liczba))
    liczba = nullptr;
}


// PARSOWANIE WEJSCIA
bool czyOperator(const int znak) {
    return znak ==  PLUS || znak == MINUS
        || znak == ILOCZYN || znak == POTEGA;
}

bool czyKoniecWejscia(const int znak) {
    return znak == '\0' || znak == '\n' || znak == '\r';
}

// KOM void na liste ?
void *wczytajWiersz() {
    int znak = getchar();
    int *wynik = malloc(sizeof(int)); // KOM free
    int i = 0;

    if (!czyKoniecWejscia(znak)) {
        wynik[i] = znak;
        znak = getchar();
    }

    free(wynik);
    return nullptr; // KOM idk...
}

// KOM DEBUG
// czysci stos!!!
void wypiszStos(stos **s) {
    while (!czyPustyStos(*s)) {
        printf("%d\n", zdejmijZeStosu(s));
    }
}

// MAIN
int main() {

    return 0;
}