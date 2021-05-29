#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double Zufallszahl()    // liefert Zufallszahl zwischen 0 und 1
    {
     double r = rand();
     return r / RAND_MAX;
    }

double Maxdouble(double Wert1, double Wert2)    //liefert den grüßten Wert von zwei double-Zahlen
    {
    if (Wert1>Wert2)
         return Wert1;
    else return Wert2;
    }

int Maxint(int Wert1, int Wert2)    //liefert den grüßten Wert von zwei integer-Zahlen
    {
    if (Wert1>Wert2)
         return Wert1;
    else return Wert2;
    }

double ErgebnisRoulette(double Setzbetrag, int Zahl, int AnzahlRunden) // Aufgbe a): Ermittelt den Gewinn/Verlust beim Roulette
    {
    double Ergebnis = 0.0;
    while(AnzahlRunden>0)
        {
        int Zufall = (int)(Zufallszahl()*100)%37;
        if (Zahl == Zufall)
              Ergebnis += (Setzbetrag * 36);
        else  Ergebnis -= Setzbetrag;
        AnzahlRunden--;
        }
    return Ergebnis;
    }

int Million (double Setzbetrag)     // Aufgabe b): Simuliert den Gewinn einer Million beim Roulette
    {
    double Gewinn = 0.0, Einsatz = Setzbetrag, MaxEinsatz = Setzbetrag;
    int Spielrunden = 0, Glueckszaehler = 0, Pechzaehler = 0, Gluecksstraehne = 0, Pechstraehne = 0, Pech = 0, Glueck = 0;
    while(Gewinn<1000000)
        {
        int Zufall = (int)(Zufallszahl()*1000)%37;
        if (Zufall == 1||Zufall == 3||Zufall == 5||Zufall == 7||Zufall == 9||Zufall == 12||Zufall == 14||Zufall == 16||Zufall == 18||Zufall == 19||Zufall == 21||Zufall == 23||Zufall == 25||Zufall == 27||Zufall == 30||Zufall == 32||Zufall == 34||Zufall == 36)
            {
            Gewinn += Einsatz;
            Einsatz = Setzbetrag;
            Spielrunden++;
            Pech = 0;
            Glueck = 1;
            }
        else
            {
            Gewinn -= Einsatz;
            Einsatz *= 2;
            Spielrunden++;
            Glueck = 0;
            Pech = 1;
            }
        MaxEinsatz = Maxdouble(Einsatz, MaxEinsatz);
        Gluecksstraehne = Maxint(Gluecksstraehne, Glueckszaehler);
        Glueckszaehler++;
        Pechstraehne = Maxint(Pechstraehne, Pechzaehler);
        Pechzaehler ++;
        if (Pech == 0)
            Pechzaehler = 0;
        if (Glueck == 0)
            Glueckszaehler = 0;
        }
    printf("%12.2f | %8d | %5d  | %3d  | %13.2f  | %7.2f\n", Setzbetrag, Spielrunden, Gluecksstraehne, Pechstraehne, MaxEinsatz, Gewinn);
    }


int main()
    {
    srand((int)time(0)); // Initialisierung des Zufallszahlengenerators
    double Setzbetrag1 = 11.11, Setzbetrag2 = 0.75;
    int Zahl = 0, AnzahlRunden = 37;
    //Aufgabe c)
    while (Zahl<37)
        {
        printf("Der Gewinn fuer die Zahl %2d betraegt %7.2f.\n", Zahl, ErgebnisRoulette(Setzbetrag1, Zahl, AnzahlRunden));
        Zahl++;
        }
    //Aufgabe d)
    printf("\n\nBasiseinsatz |  Runden  | Glueck | Pech |  Max. Einsatz  | Gewinn  \n-------------+----------+--------+------+----------------+-----------\n");
    while (Setzbetrag2<100000)
        {
        Million(Setzbetrag2);
        Setzbetrag2 *= 2;
        }
    return 0;
    }


