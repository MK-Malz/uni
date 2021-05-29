#include <stdio.h>
#include <stdbool.h>

int LengthOfString(char s[]) //Funktion zum Bestimmen der Laenge einer Zeichenkette
{
    int length = 0;
    while (s[length] != '\0')
        length++;
    return length;
}

int readInt() // Funktion zum Einlesen der Tastatureingabe
{
    int number;
    scanf("%d", &number);
    return number;
}

//Aufgabe a)
int Wortzaehler(char zeichenkette[]) //Funktion zum Zählen der Woerter einer Zeichenkette
{
    int count = 1, i;
    for(i = 0; zeichenkette[i] != '\0' ;i++)
        {
            if(zeichenkette[i] == ' ')
            {
                count++;
            }
        }
    return count;
}

//Aufbage b)
int Worttrenner(char zeichenkette[], int ZeichenproZeile) //Funktion zum Formatieren einer Zeichenkette
{
    int zeilenanfang = 0, zeilenende = ZeichenproZeile-1, i;
    while(zeilenende < LengthOfString(zeichenkette))
    {
        if(zeichenkette[zeilenende] == ' ')
        {
            for(i = zeilenanfang;i<=zeilenende;i++)
                      putchar(zeichenkette[i]);
            printf("\n");
            zeilenanfang = zeilenende+1;
            zeilenende += (ZeichenproZeile+1);
        }
        else
            zeilenende--;
        if(zeilenende > LengthOfString(zeichenkette))
        {
                for(i = zeilenanfang;i<LengthOfString(zeichenkette);i++)
                      putchar(zeichenkette[i]);
                printf("\n");
        }
    }
}

//Aufgabe c)
int Wortloescher(char zeichenkette[], int loeschposition) //Funktion zum Loeschen eines Wortes aus einer Zeichenkette
{
    int count = 1, i;
    bool Wortsuche = true;
    if(loeschposition == 1)
    {
        for(i=0; zeichenkette[i]!=' '; i++)
            {
                putchar(zeichenkette[i]);
            }
            printf("\n");
            int loesch_ende = i+1;
            for(i=0; i != LengthOfString(zeichenkette)-(loesch_ende);i++)
                        zeichenkette[i] = zeichenkette[i+(loesch_ende)];
            zeichenkette[LengthOfString(zeichenkette)-(loesch_ende)] = '\0';
    }
    else
    {
        for(i=0; Wortsuche; i++)
        {
                if(zeichenkette[i] == ' ')
                count++;
                if(count == loeschposition)
                {
                    int loesch_anfang = i;
                    for(i=i+1; zeichenkette[i]!=' ' && zeichenkette[i]!='\0'; i++)
                        putchar(zeichenkette[i]);
                    printf("\n");
                    if(loeschposition == Wortzaehler(zeichenkette))
                        zeichenkette[loesch_anfang] = '\0';
                    else
                    {
                        int loesch_ende = i;
                        for(i=loesch_anfang+1; i != LengthOfString(zeichenkette)-(loesch_ende-loesch_anfang);i++)
                            zeichenkette[i] = zeichenkette[i+(loesch_ende-loesch_anfang)];
                        zeichenkette[LengthOfString(zeichenkette)-(loesch_ende-loesch_anfang)] = '\0';
                    }
                    Wortsuche = false;
                }
        }
    }

}

int main()
{
    char zeichenkette[] = "to be or not to be, that is the question: whether 'tis nobler in the mind to suffer the slings and arrows of outrageous fortune, or to take arms against a sea of troubles, and by opposing, end them? to die: to sleep; no more; and by a sleep to say we end the heartache and the thousand natural shocks that flesh is heir to, 'tis a consummation devoutly to be wish'd. to die, to sleep; to sleep: perchance to dream: ay, there's the rub; for in that sleep of death what dreams may come when we have shuffled off this mortal coil, must give us pause: there's the respect that makes calamity of so long life; for who would bear the whips and scorns of time, the oppressor's wrong, the proud man's contumely, the pangs of despised love, the law's delay, the insolence of office and the spurns that patient merit of the unworthy takes, when he himself might his quietus make with a bare bodkin?";
    int ZeichenproZeile, loeschposition;
    while(true) //Das Programm laeuft so lange, bis der Benutzer es durch eine ungueltige Eingabe beendet
    {
        printf("Geben Sie die Ausgabebreite ein (20-80): ");
        ZeichenproZeile = readInt();
        printf("\n");
        if(ZeichenproZeile < 20 || ZeichenproZeile > 80) //Pruefung der Eingabe
            return 0;
        Worttrenner(zeichenkette,ZeichenproZeile);
        printf("\nDas wievielte Wort soll geloescht werden? (1-%d) ", Wortzaehler(zeichenkette)); // Funktioniert Wortzarhlrt trotz Verscgiebung? einbauen!
        loeschposition = readInt();
        if(loeschposition > Wortzaehler(zeichenkette) || loeschposition < 1) //Pruefung der Eingabe
            return 0;
        printf("\nDas geloeschte Wort lautet: ");
        Wortloescher(zeichenkette,loeschposition);
        printf("\n");
    }
}

