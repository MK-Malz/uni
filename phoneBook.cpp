/*
1. Belegaufgabe Grundlagen der Informatik

Name:           Klane
Vorname:        Malte
Matrikelnummer: 377346

Kurzbeschreibung des Entwurfs
Dieses Programm stellt ein elektronisches Telefonbuch dar. Das Telefonbuch umfasst 130 Eintraege, wobei jeder Eintrag aus
Familiennamen, Vornamen und Telefonnummer besteht. Diese Eintraege sind in einer Matrix der Groeße 26 x 5 gespeichert.
Es lassen sich sowohl neue Eintraege hinzufuegen, als auch bereits bestehende Eintraege suchen. Fuer einen schnelleren Zugriff auf
die abgespeicherten Eintraege werden den Familiennamen mit Hilfe einer Hashfunktion Hashwerte zugeteilt, die der Zeile des
abgespeicherten Eintrages in dem Telefonbuch entsprechen. Durch die Sortierung der Eintraege nach ihrem Hashwert ergibt sich
annaehernd eine Gleichverteilung, die bei einer alphabetischen Sortierung aufgrund der ungleichen Verteilung der Anfangsbuchstaben
nicht gegeben waere. Der Hashwert wird mit Hilfe der Werte des ASCII-Codes der ersten drei Buchstaben des Familiennamens berechnet.

Hinweise zur Nutzung
-Bei der Eingabe und Suche ist auf Groß- und Kleinschreibung zu achten, da diese unterschiedliche Hashwerte erzeugt.
-Einmal angelegte Einträge lassen sich nicht löschen oder ändern.
-Es lassen sich pro Hashwert nur 5 Einträge speichern.
-Wenn 130 Eintraege erreicht sind, lassen sich keine neuen mehr hinzufuegen.
-Bei der Eingabe von Familienname, Vorname und Telefonnummer  lassen sich Zahlen, Buchstaben und Sonderzeichen eingeben.
-Das Hauptmenue muss mindestens 10 mal aufgerufen werden. Wird das Programm beendet, stehen die
 eingegebenen Einträge beim nächsten Start des Programms nicht mehr zur Verfügung.
-Verwendetes Entwicklungssysem: Code::Blocks 13.12
-Es wurde die Eingabe von einzelnen Zahlen, einzelnen Buchtstaben, mehreren Zahlen, mehreren Buchstaben,
 Leerzeichen, Sonderzeichen und Kombinationen der zuvor genannten getestet.
*/

#include <iostream>
#include <string>
using namespace std;

int hashing (string Familienname)  //Die hashfunktion ordnet jedem eingegebenem Familiennamen einen integer-Wert zu
    {
    return (int(Familienname[0])*100+int(Familienname[1])*10+int(Familienname[2])*1)%26;
    }

int main()
    {
    struct Telefonbucheintrag
        {
        string Familienname;
        string Vorname;
        string Telefonnummer;
        };

    Telefonbucheintrag Telefonmatrix[26][5];
    int n = 1, m = 1, optionen;
    string FamiliennameEingabe, VornameEingabe, TelefonnummerEingabe, optionenEingabe;

    for(int j=0;j<26;j++) //Belegung der Telefonbucheinträge mit "x" um später zu erkennen, welche Plätze noch frei sind
        for(int i=0;i<5;i++)
            Telefonmatrix[j][i].Familienname = "x";

    while (n)
        {
        int Erfolg = 0;
        cout << endl << "Hauptmenue" << endl << "[1] Neuen Telefonbucheintrag anlegen" << endl << "[2] Telefonbucheintrag suchen" << endl << "[3] Hauptmenue beenden";
        cout << endl << "Bitte geben Sie [1], [2] oder [3] ein: ";
        cin >> optionenEingabe;
        optionen = optionenEingabe[0] - '0';

        while (optionen < 1 || optionen > 3 || optionenEingabe.length() > 1)
            {
            cout << "Ihre Eingabe war nicht korrekt."<< endl;
            cout << "Bitte geben Sie [1], [2] oder [3] ein: ";
            cin >> optionenEingabe;
            optionen = optionenEingabe[0] - '0';
            }

        if (optionen == 1) // Option 1: Neuen Telefobucheintrag anlegen
            {
            cout << endl << "Bitte geben Sie den Familiennamen des neuen Eintrages ein: ";
            cin >> FamiliennameEingabe;
            while(FamiliennameEingabe.length()<3)
                {
                cout << "Der Familienname muss aus mindestens 3 Zeichen bestehen." << endl;
                cout << "Bitte geben Sie den Familiennamen des neuen Eintrages ein: ";
                cin >> FamiliennameEingabe;
                }
            cout << "Bitte geben Sie den Vornnamen des neuen Eintrages ein: ";
            cin >> VornameEingabe;
            cout << "Bitte geben Sie die Telefonnummer des neuen Eintrages ein: ";
            cin >> TelefonnummerEingabe;
            for(int i=0;i<5;i++)
                {
                if (Telefonmatrix[hashing(FamiliennameEingabe)][i].Familienname == "x")
                    {
                    Telefonmatrix[hashing(FamiliennameEingabe)][i].Familienname = FamiliennameEingabe;
                    Telefonmatrix[hashing(FamiliennameEingabe)][i].Vorname = VornameEingabe;
                    Telefonmatrix[hashing(FamiliennameEingabe)][i].Telefonnummer = TelefonnummerEingabe;
                    Erfolg = 1;
                    i = 5;
                    }
                }
             if(Erfolg)
                        cout << endl << "Der Eintrag wurde erfolgreich dem Telefonbuch hinzugefuegt." << endl;
                else    cout << endl << "Der Eintrag konnte dem Telefonbuch nicht hinzugefuegt werden." << endl;
            }

        if (optionen == 2) // Option 2: Telefonbucheintrag suchen
            {
            cout << endl << "Bitte geben Sie den Familiennamen des gesuchten Eintrages ein: ";
            cin >> FamiliennameEingabe;
            while(FamiliennameEingabe.length()<3)
                {
                cout << "Der Familienname muss aus mindestens 3 Zeichen bestehen." << endl;
                cout << "Bitte geben Sie den Familiennamen des gesuchten Eintrages ein: ";
                cin >> FamiliennameEingabe;
                }
            for(int i=0;i<5;i++)
                {
                 if (Telefonmatrix[hashing(FamiliennameEingabe)][i].Familienname == FamiliennameEingabe)
                    {
                    cout << endl << Telefonmatrix[hashing(FamiliennameEingabe)][i].Familienname << endl;
                    cout <<Telefonmatrix[hashing(FamiliennameEingabe)][i].Vorname << endl;
                    cout <<Telefonmatrix[hashing(FamiliennameEingabe)][i].Telefonnummer<< endl;
                    Erfolg = 1;
                    }
                }
            if (Erfolg) ;
            else cout << "Es exisitiert kein Eintrag mit dem Familiennamen " << FamiliennameEingabe <<"." << endl;
            }

        if (optionen == 3) // Option 3: Hauptmenue beenden
            {
            if(m<10)
                cout << endl << "Das Hauptmenue muss mindestens 10 mal aufgerufen werden." << endl;
            else
                {
                n = 0;
                cout << endl << "Das Hauptmenue wurde beendet." << endl;
                }
            }

        m++;
        }
    return 0;
    }
