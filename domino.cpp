#include <stdio.h>

struct Dominostein //Datenstruktur für Dominostein
{
    int Zahl1;
    int Zahl2;
    bool verwendet;
    Dominostein* next;
};

struct Ringliste //Ringliste für die Domino-Kreise
{
    int Zahl_1;
    int Zahl_2;
    Ringliste* nextR;
};

struct Liste //Liste für den Zugriff auf die Ringlisten
{
    Ringliste* Ring;
    Liste* nextL;
};

void insertSteine(FILE* datei, Dominostein* & pHeadDominosteine, Dominostein* &pLastDominosteine, Dominostein* &pNewDominosteine)
{
        //Einfügen der Dominosteine aus Datei in einfach verkettete Liste
        int Zahl1, Zahl2, Anzahl;
        fscanf(datei, "%d", &Anzahl);
        fscanf(datei, "%d", &Zahl1);
        fscanf(datei, "%d", &Zahl2);
        pHeadDominosteine = new Dominostein;
        pHeadDominosteine->Zahl1 = Zahl1;
        pHeadDominosteine->Zahl2 = Zahl2;
        pHeadDominosteine->verwendet = false;
        pHeadDominosteine->next = NULL;
        pLastDominosteine = pHeadDominosteine;

        for(int i = 0; i<Anzahl-1; i++)
        {
            fscanf(datei, "%d", &Zahl1);
            fscanf(datei, "%d", &Zahl2);
            pNewDominosteine = new Dominostein;
            pNewDominosteine->Zahl1 = Zahl1;
            pNewDominosteine->Zahl2 = Zahl2;
            pNewDominosteine->verwendet = false;
            pNewDominosteine->next = NULL;
            pLastDominosteine->next = pNewDominosteine;
            pLastDominosteine = pNewDominosteine;
        }
}

void printSteine(Dominostein* pHeadDominosteine) //Ausgabe der Liste der eingelesenen Dominosteine
{
    printf("Liste:\n");
    Dominostein* temp = pHeadDominosteine;
    while(temp->next != NULL)
    {
        printf("[%d:%d]", temp->Zahl1, temp->Zahl2);
        temp = temp->next;
    }
    printf("[%d:%d]", temp->Zahl1, temp->Zahl2);
    printf("\n");
}

 void insertListe(Liste* &Listenkopf, Liste* &LetztesListenelement, Ringliste* Ringlistpointer) //Einfügen der Ringlisten in die Liste
{
        if(Listenkopf == NULL)
        {
            Listenkopf = new Liste;
            Listenkopf->Ring = Ringlistpointer;
            Listenkopf->nextL = NULL;
            LetztesListenelement = Listenkopf;
        }
        else
        {
            Liste *NeuesListenelement = new Liste;
            NeuesListenelement->Ring = Ringlistpointer;
            NeuesListenelement->nextL = NULL;
            LetztesListenelement->nextL = NeuesListenelement;
            LetztesListenelement = NeuesListenelement;
        }
}

void insertRing(Ringliste* &Ringkopf, int Zahl1, int Zahl2) //Einfügen eines Steines in die Ringliste
{
    if(Ringkopf == NULL)
    {
        Ringkopf = new Ringliste;
        Ringkopf->Zahl_1 = Zahl1;
        Ringkopf->Zahl_2 = Zahl2;
        Ringkopf->nextR = Ringkopf;
        return;
    }
    Ringliste* temp = Ringkopf;
    while(temp->nextR != Ringkopf)
    {
       temp = temp->nextR;
    }
    temp->nextR = new Ringliste;
    temp->nextR->nextR = Ringkopf;
    temp->nextR->Zahl_1 = Zahl1;
    temp->nextR->Zahl_2 = Zahl2;
}

void printRing(Ringliste* head)
{
    Ringliste* temp = head;
    while(temp->nextR != head)
    {
        printf("[%d:%d]", temp->Zahl_1, temp->Zahl_2);
        temp = temp->nextR;
    }
    printf("[%d:%d]\n", temp->Zahl_1, temp->Zahl_2);
}

bool AlleSteineVerwendet(Dominostein* pHeadDominosteine) //Prüfen, ob alle Steine bereits verwendet wurden
{
    Dominostein* temp = pHeadDominosteine;
    while(temp->next != NULL)
    {
        if(temp->verwendet == false)
        {
            return false;
        }
        temp = temp->next;
    }
    if(temp->verwendet == false)
    {
          return false;
    }
    return true;
}

void createAndInsertRinglists(Dominostein* pHeadDominosteine, Liste* &Listenkopf, Liste* &LetztesListenelement)
{
        //Erstellen der Ringlisten und anschließendes Einfügen der Ringliste in die Liste
        while(!AlleSteineVerwendet(pHeadDominosteine))
        {
            Ringliste* Ringkopf = NULL;
            Dominostein* tempDomino = pHeadDominosteine;
            bool ErstesEinfuegen = true;
            while(tempDomino->next!= NULL) // ersten unbenutzen Stein einfügen
            {
                if(tempDomino->verwendet == false && ErstesEinfuegen)
                {
                    insertRing(Ringkopf, tempDomino->Zahl1, tempDomino->Zahl2);
                    tempDomino->verwendet = true;
                    ErstesEinfuegen = false;
                }
                else
                    tempDomino = tempDomino->next;
            }
            tempDomino = pHeadDominosteine;
            Ringliste* tempRing = Ringkopf;
            int LetzteZahl = -1;
            while(Ringkopf->Zahl_1 != LetzteZahl) // passenedn Stein einfügen
            {
                if(tempDomino->Zahl1 == tempRing->Zahl_2 && tempDomino->verwendet == false)
                {
                    insertRing(Ringkopf, tempDomino->Zahl1, tempDomino->Zahl2);
                    LetzteZahl = tempDomino->Zahl2;
                    tempDomino->verwendet = true;
                    tempRing = tempRing->nextR;
                    tempDomino = pHeadDominosteine;
                }
                else
                {
                    if(tempDomino->Zahl2 == tempRing->Zahl_2 && tempDomino->verwendet == false )
                    {
                        insertRing(Ringkopf, tempDomino->Zahl2, tempDomino->Zahl1);
                        LetzteZahl = tempDomino->Zahl1;
                        tempDomino->verwendet = true;
                        tempRing = tempRing->nextR;
                        tempDomino = pHeadDominosteine;
                    }
                    else
                        tempDomino = tempDomino->next;
                }
            }
            insertListe(Listenkopf, LetztesListenelement, Ringkopf);
        }
}

void printRinglistListe(Liste* Listenkopf) //Zugriff auf die Liste der Ringlisten und Aufruf der print-Funktion für Ringlisten
{
        printf("Kreise:\n");
        Liste* tempListe = Listenkopf;
        while(tempListe->nextL != NULL)
        {
            printRing(tempListe->Ring);
            tempListe = tempListe->nextL;
        }
        printRing(tempListe->Ring);
}

void deleteRing(Ringliste* head)
{
    Ringliste* temp = head;
    Ringliste* headremember = head;
    while(temp->nextR != headremember)
    {

        temp = temp->nextR;
        delete head;
        head = temp;
    }
    delete head;
}

void deleteAllRinglists(Liste* Listenkopf)
{
        Liste* tempListe = Listenkopf;
        while(tempListe->nextL != NULL)
        {
            deleteRing(tempListe->Ring);
            tempListe = tempListe->nextL;
        }
        deleteRing(tempListe->Ring);
}

void deleteDominoliste(Dominostein* pHeadDominosteine)
{
        Dominostein * tempD = pHeadDominosteine;
        while(tempD)
        {
            tempD = tempD->next;
            delete pHeadDominosteine;
            pHeadDominosteine = tempD;
        }
        delete pHeadDominosteine;
}

void deleteListe(Liste* Listenkopf)
{
        Liste * tempL = Listenkopf;
        while(tempL)
        {
            tempL = tempL->nextL;
            delete Listenkopf;
            Listenkopf = tempL;
        }
        delete Listenkopf;
}

int main(int argc, const char * argv[])
{
    if (argc != 2)
    {
        printf("Ungueltige Anzahl Argumente. Das Programm wird beendet.");
        return 0;
    }
    FILE *datei = fopen(argv[1],"r");
    if(datei != NULL)
    {
        Dominostein *pHeadDominosteine, *pNewDominosteine, *pLastDominosteine;
        insertSteine(datei, pHeadDominosteine, pLastDominosteine, pNewDominosteine);
        printSteine(pHeadDominosteine);
        Liste *Listenkopf = NULL, *LetztesListenelement;
        createAndInsertRinglists(pHeadDominosteine, Listenkopf, LetztesListenelement);
        printRinglistListe(Listenkopf);

        deleteDominoliste(pHeadDominosteine);
        deleteAllRinglists(Listenkopf);
        deleteListe(Listenkopf);
    }
    else
        printf("Datei konnte nicht gefunden werden. Das Programm wird beendet.");
    fclose(datei);
    return 0;
}
