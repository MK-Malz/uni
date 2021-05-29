#include <stdio.h>

int readInt() // Funktion zum Einlesen der Tastatureingabe
{   int number;
    scanf("%d", &number);
    return number;
}

int altroemisch (int Zahl)
/* Funktion zur Ausgabe einer übergebenen natürlichen Zahl im altroemischen Zahlensystem:
Von der zu uebergebenden Zahl wird der Wert der groeßtmoeglichen roemischen Ziffer subtrahiert
und die entsprechende Ziffer auf dem Bildschirm ausgegeben. Der Vorgang wird so oft wiederholt,
bis die zu uebergebende Zahl gleich Null ist und somit vollstaendig in roemische Ziffern auf
dem Bildschirm ausgegeben wurde. */
{
    while (Zahl > 999)
    {
        printf("M");// M = 1000
        Zahl = Zahl - 1000;
    };
    while (Zahl > 499)
    {
        printf("D");// D = 500
        Zahl = Zahl - 500;
    };
    while (Zahl > 99)
    {
        printf("C");// C = 100
        Zahl = Zahl - 100;
    };
    while (Zahl > 49)
    {
        printf("L"); // L = 50
        Zahl = Zahl - 50;
    };
    while (Zahl > 9)
    {
        printf("X");// X = 10
        Zahl = Zahl - 10;
    };
    while (Zahl > 4)
    {
        printf("V");// V = 5
        Zahl = Zahl - 5;
    };
    while (Zahl > 0)
    {
        printf("I");// I = 1
        Zahl = Zahl - 1;
    };
return Zahl;
}

int neuroemisch (int Zahl)
/* Funktion zur Ausgabe einer übergebenen natürlichen Zahl im neuroemischen Zahlensystem:
Von der zu uebergebenden Zahl wird der Wert der groeßtmoeglichen roemischen Ziffer subtrahiert
und die entsprechende Ziffer auf dem Bildschirm ausgegeben. Der Vorgang wird so oft wiederholt,
bis die zu uebergebende Zahl gleich Null ist und somit vollstaendig in roemische Ziffern auf
dem Bildschirm ausgegeben wurde. */
{
    while (Zahl > 999 )
    {
        printf("M");// M = 1000
        Zahl = Zahl - 1000 ;
    };
    while (Zahl > 899 )
    {
        printf("CM");// CM = 900
        Zahl = Zahl - 900 ;
    };
    while (Zahl > 499)
    {
        printf("D");// D = 500
        Zahl = Zahl - 500;
    };
    while (Zahl > 399)
    {
        printf("CD");// CD = 400
        Zahl = Zahl - 400;
    };
    while (Zahl > 99)
    {
        printf("C");// C = 100
        Zahl = Zahl - 100;
    };
    while (Zahl > 89)
    {
        printf("XC");// XC = 90
        Zahl = Zahl - 90;
    };
    while (Zahl > 49)
    {
        printf("L");// L = 50
        Zahl = Zahl - 50;
    };
    while (Zahl > 39)
    {
        printf("XL");// XL = 40
        Zahl = Zahl - 40;
    };
    while (Zahl > 9)
    {
        printf("X");// X = 10
        Zahl = Zahl - 10;
    };
    while (Zahl > 8)
    {
        printf("IX");// IX = 9
        Zahl = Zahl - 9;
    };
    while (Zahl > 4)
    {
        printf("V");// V = 5
        Zahl = Zahl - 5;
    };
    while (Zahl > 3)
    {
        printf("IV");// IV = 4
        Zahl = Zahl - 4;
    };
    while (Zahl > 0)
    {
        printf("I");// I = 1
        Zahl = Zahl - 1;
    };
return Zahl;
}

int main()
{
int Zahlroemisch;
printf("Bitte geben Sie eine natuerliche Zahl < 4000 ein: ");
Zahlroemisch = readInt(); //Einlesen der umzuwandelnden Zahl
if (Zahlroemisch > 3999) // Vorbedingung Zahl < 4000
printf("Fehler: Die eingegebene Zahl ist nicht < 4000.");
else
    if (Zahlroemisch < 1) // Vorbedingung Zahl positiv und ungleich 0
    printf("Fehler: Die eingegebene Zahl ist keine natuerliche Zahl.");
    else
        {
        printf("Die Zahl %d im altroemischen System lautet: ", Zahlroemisch);
        altroemisch(Zahlroemisch);
        printf("\nDie Zahl %d im neuroemischen System lautet: ", Zahlroemisch);
        neuroemisch(Zahlroemisch);
        }
return 0;
}

