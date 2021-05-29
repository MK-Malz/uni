#include <stdio.h>
#include <stdbool.h>

struct Sieb // Struktur um mit der Funktion Sieb_des_Eratosthenes P und S zurückzugeben
{
    int P;
    int S;
};

int potenz(int basis, int exponent) // Funktion zur Berechnung von Potenzen
{   int ergebnis = 1;
    while(exponent>0)
    {
        ergebnis *= basis;
        exponent--;
    }
    return ergebnis;
}

Sieb Sieb_des_Eratosthenes(int N) // Funktion zur Bestimmung der Primzahlen und Anzahl Streichungen beim Sieb des Eratosthenes
{
    bool* pFeld = new bool[N+1];
    Sieb Eratosthenes;
    Eratosthenes.P = 0;
    Eratosthenes.S = 0;
    for(int i = 0; i<=N; i++)
        *(pFeld+i) = false;
    for(int i = 2; i*i<N+1; i++)
    {
        if(!*(pFeld+i))
        {
           for(int j = i*i ; j<N+1; j=j+i)
            {
                Eratosthenes.S++;
                (*(pFeld+j)) = true;
            }
        }
    }
    for(int i =2; i<N+1; i++)
    {
        if(!*(pFeld+i))
            Eratosthenes.P++;
    }
    delete []pFeld;
    pFeld = NULL;
    return Eratosthenes;
}

int main()
{
    printf("         N         P         S\n");
    printf("------------------------------\n");
    for(int i = 2; i<=20; i++)
            printf("%10d%10d%10d\n", potenz(2,i), Sieb_des_Eratosthenes(potenz(2,i)).P, Sieb_des_Eratosthenes(potenz(2,i)).S);
    return 0;
}
