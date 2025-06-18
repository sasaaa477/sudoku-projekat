#include <bits/stdc++.h>  // Uključujemo biblioteku 
using namespace std;                  

// Definišemo konstantu za veličinu Sudoku table (9x9)
const int VELICINA = 9;

// Funkcija koja proverava da li je dozvoljeno postaviti određeni broj na datu poziciju
bool dozvoljeno(int tabla[VELICINA][VELICINA], int red, int kolona, int broj) {
    // Proveravamo da li broj već postoji u istom redu
    for (int i = 0; i < VELICINA; i++) {
        if (tabla[red][i] == broj)
            return false;             // Ako broj postoji u redu, nije dozvoljeno
    }

    // Proveravamo da li broj već postoji u istoj koloni
    for (int i = 0; i < VELICINA; i++) {
        if (tabla[i][kolona] == broj)
            return false;             // Ako broj postoji u koloni, nije dozvoljeno
    }

    // Određujemo početne indekse 3x3 kvadrata
    int pocetniRed = red - red % 3;               // Gornji levi red bloka
    int pocetnaKolona = kolona - kolona % 3;      // Gornja leva kolona bloka

    // Proveravamo da li broj postoji u 3x3 kvadratu
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {   
            if (tabla[pocetniRed + i][pocetnaKolona + j] == broj)
                return false;         // Ako postoji, nije dozvoljeno
        }
    }

    return true;                      // Ako broj ne krši nijedno pravilo, dozvoljen je
}

// Rekurzivna funkcija koja rešava Sudoku koristeći backtracking
bool resiSudoku(int tabla[VELICINA][VELICINA]) {
    // Prolazimo kroz sve ćelije
    for (int red = 0; red < VELICINA; red++) {
        for (int kolona = 0; kolona < VELICINA; kolona++) {
            // Ako je ćelija prazna (ima vrednost 0)
            if (tabla[red][kolona] == 0) {
                // Pokušavamo brojeve od 1 do 9
                for (int broj = 1; broj <= 9; broj++) {
                    // Ako je dozvoljeno staviti broj na tu poziciju
                    if (dozvoljeno(tabla, red, kolona, broj)) {
                        tabla[red][kolona] = broj;     // Privremeno upisujemo broj

                        // Rekurzivno pokušavamo da rešimo ostatak table
                        if (resiSudoku(tabla))
                            return true;               // Ako nađemo rešenje, vraćamo true

                        tabla[red][kolona] = 0;        // Ako nije bilo rešenje, vraćamo se nazad (backtrack)
                    }
                }

                return false;                          // Ako nijedan broj ne može da se stavi, vraćamo false
            }
        }
    }

    return true;                                       // Ako nema više praznih ćelija – rešenje je nađeno
}

// Funkcija za prikaz Sudoku table u konzoli
void prikaziTablu(int tabla[VELICINA][VELICINA]) {
    cout << "\nRešena Sudoku tabla:\n";                // Naslov

    // Prolazimo kroz redove
    for (int red = 0; red < VELICINA; red++) {
        // Ispisujemo horizontalnu liniju između 3x3 kvadrata
        if (red % 3 == 0 && red != 0)
            cout << "------+-------+------\n";

        // Prolazimo kroz kolone
        for (int kolona = 0; kolona < VELICINA; kolona++) {
            // Ispisujemo vertikalnu liniju između 3x3 kvadrata
            if (kolona % 3 == 0 && kolona != 0)
                cout << "| ";

            cout << tabla[red][kolona] << " ";         // Ispisujemo vrednost ćelije
        }

        cout << endl;                                  // Nova linija posle svakog reda
    }
}

// Glavna funkcija – ulazna tačka programa
int main() {
    int tabla[VELICINA][VELICINA];                     // Deklarišemo 9x9 matricu za Sudoku tablu

    cout << "Unesi Sudoku tablu (9 redova po 9 brojeva, koristi 0 za prazna polja):\n";

    // Učitavamo sve vrednosti u matricu
    for (int red = 0; red < VELICINA; red++) {
        for (int kolona = 0; kolona < VELICINA; kolona++) {
            cin >> tabla[red][kolona];                 // Unos jedne ćelije

            // Proveravamo da li je unos validan (broj između 0 i 9)
            if (tabla[red][kolona] < 0 || tabla[red][kolona] > 9) {
                cout << "Greška: brojevi moraju biti između 0 i 9.\n";
                return 1;                              // Prekida program ako je unos nevalidan
            }
        }
    }

    // Pokušavamo da rešimo unetu Sudoku tablu
    if (resiSudoku(tabla)) {
        prikaziTablu(tabla);                           // Ako uspe, prikazujemo rešenje
    } else {
        cout << "\nNema validnog rešenja za unetu Sudoku tablu!\n"; // Ako ne uspe, obaveštavamo korisnika
    }

    return 0;                                          // Kraj programa
}
