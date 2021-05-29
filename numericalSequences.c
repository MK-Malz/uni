#include <stdio.h>

int readInt() // Funktion zum Einlesen der Tastatureingabe
{
    int number;
    scanf("%d", &number);
    return number;
}

int abs(int x) // Funktion zum Bestimmen des Betrags einer Zahl
{
    int betrag;
    if (x < 0)
        betrag = -x;
    else
        betrag = x;
    return betrag;
}

int Sternenraster (int maxZiffer)  // Funktion zur Ausgabe des Sternenrasters
{
    int Zeichen, AnzahlLeer, AnzahlZeile;
    int Zeilenabstand = 0;
    while (Zeilenabstand < 26)
    {
        Zeichen = 0;
        while (Zeichen < 51)
        {
            printf("*");
            Zeichen = Zeichen +1;
            AnzahlLeer = maxZiffer - 1;
                while (AnzahlLeer > 0)
                {
                    printf(" ");
                    Zeichen = Zeichen +1;
                    AnzahlLeer = AnzahlLeer - 1;
                }
    }
    AnzahlZeile = maxZiffer;
    while (AnzahlZeile > 0)
    {
        printf("\n");
        Zeilenabstand = Zeilenabstand + 1;
        AnzahlZeile = AnzahlZeile - 1;
    }
    }
}

int Minimum (int min, int number)  // Bestimmung des Minimum von zwei Zahlen
{
    if (min < number)
            return min;
    else    return number;
}

int Maximum(int max, int number) // Bestimmung des Maximums von zwei Zahlen
{
    if (max > number)
            return max;
    else    return number;
}

int BestimmungZiffernzahl (int number) // Bestimmung der Ziffernanzahl einer Zahl
{
    int Ziffern = 0;
    number = abs(number);
    while (number > 0)
    {
        number = number / 10;
        Ziffern = Ziffern +1;
    }
    return Ziffern;
}

int main ()
{
    int number, Summe = 0, n = 0, Mittelwert, ZiffernZahl, maxZiffer = 0, maxAbweichung;
    printf("Zahlenfolge: ");
    number = readInt();
    int max = number;
    int min = number;
    while (number != 0 )
    {
        Summe = Summe + number;
        n = n + 1;
        Mittelwert = Summe / n;
        max = Maximum (max, number);
        min = Minimum (min, number);
        ZiffernZahl = BestimmungZiffernzahl(number);
        maxZiffer = Maximum (maxZiffer, ZiffernZahl);
        number = readInt();
    };
    maxAbweichung = Maximum(abs(Mittelwert - min),abs (Mittelwert - max));
    printf("Mittelwert der Folge: %d\nGroesste Abweichung zum Mittelwert: %d\nMaximale Ziffernanzahl: %d\n", Mittelwert, maxAbweichung, maxZiffer);
    Sternenraster (maxZiffer);
    return 0;
}

