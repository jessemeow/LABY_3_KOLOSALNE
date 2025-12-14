#include <stdio.h>      // Standardowe wejscie/wyjscie
#include <stdlib.h>     // Malloc

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

/* STOS */
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


/* LICZBY KOLOSALNE */
void inicjalizujKLiczbe(kLiczba **liczba) {
    *liczba = nullptr;
}

bool czyPustaLiczba(const kLiczba **liczba) {
    return liczba == nullptr || *liczba == nullptr;
}

const kLiczba *znajdzPoprzedniaCyfre(const kLiczba **liczba) {
    // KOM
    int licznik = 0;

    const kLiczba *obecnyBit = *liczba;
    const kLiczba *poprzedniBit = *liczba;
    if (!czyPustaLiczba(liczba)) {
        while (obecnyBit != nullptr && obecnyBit->bit == 0) {
            poprzedniBit = obecnyBit;
            obecnyBit = obecnyBit->poprzedni;
            licznik++;
        }

        while (obecnyBit != nullptr && obecnyBit->bit == 1) {
            poprzedniBit = obecnyBit;
            obecnyBit = obecnyBit->poprzedni;
            licznik++;
        }
    }
    printf("licznik: %d\n", licznik);
    return poprzedniBit;
}

bool czyZnormalizowana(const kLiczba **liczba) {
    if (!czyPustaLiczba(liczba)) {
        const kLiczba *obecnaCyfra = *liczba;
        const kLiczba *poprzedniaCyfra = znajdzPoprzedniaCyfre(liczba);

        bool rozne = false;
        while (!rozne && !czyPustaLiczba(&poprzedniaCyfra) && !czyPustaLiczba(&obecnaCyfra) && poprzedniaCyfra->bit == 1) {
            if (poprzedniaCyfra->bit != obecnaCyfra->bit) {
                rozne = true;
            }
            obecnaCyfra = poprzedniaCyfra;
            poprzedniaCyfra = poprzedniaCyfra->poprzedni;
        }
        if (rozne == false) {
            return rozne;
        }
        if (poprzedniaCyfra != nullptr) {
            return czyZnormalizowana(&obecnaCyfra);
        }
    }
    return true; // Liczbe pusta traktujemy jako znormalizowana.
}

void normalizujKLiczbe(const kLiczba **liczba) {
    if (!czyZnormalizowana(liczba)) {

    }
}

void dopiszDoKLiczby(kLiczba **liczba, const int bit) {
    kLiczba *nowyWezel = malloc(sizeof(kLiczba));
    if (nowyWezel != nullptr) {
        nowyWezel->bit = bit;
        nowyWezel->poprzedni = *liczba;
        *liczba = nowyWezel;
    }

}

void wypiszKLiczbeRek(const kLiczba *liczba) {
    if (liczba != nullptr) {
        wypiszKLiczbeRek(liczba->poprzedni);
        printf("%d", liczba->bit);
    }
}

void wypiszKLiczbe(const kLiczba *liczba) {
    wypiszKLiczbeRek(liczba);
    printf("0");
}

void wyczyscKLiczbe(kLiczba **liczba) {
    while (!czyPustaLiczba((const kLiczba**) liczba)) {
        kLiczba *doUsuniecia = *liczba;
        *liczba = (*liczba)->poprzedni;
        free(doUsuniecia);
    }
    *liczba = nullptr;
}

/* PARSOWANIE WEJSCIA */
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

/* DEBUG */
// czysci stos!!!
void wypiszStos(stos **s) {
    while (!czyPustyStos(*s)) {
        printf("%d\n", zdejmijZeStosu(s));
    }
}

void wypiszKLiczbeBW(const kLiczba *liczba) {
    while (liczba != nullptr) {
        printf("%d", liczba->bit);
        liczba = liczba->poprzedni;
    }
}

kLiczba *wczytajWierszLiczba(int *znak) {
    kLiczba *liczba;
    inicjalizujKLiczbe(&liczba);

    while (!czyKoniecWejscia(*znak)) {
        dopiszDoKLiczby(&liczba, *znak);
        *znak = getchar();
    }
    return liczba;
}

void czyZn() {
    kLiczba *liczba;
    inicjalizujKLiczbe(liczba);
    int znak = getchar();

    while (!czyOperator(znak)) {
        *liczba = wczytajWierszLiczba(&znak);
        printf("%d\n", czyZnormalizowana((const kLiczba**) &liczba));
        wyczyscKLiczbe(liczba);
    }
}

/* MAIN */
int main() {
    czyZn();
    return 0;
}