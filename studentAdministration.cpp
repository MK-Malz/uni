#include <iostream>
using namespace std;

#define AnzahlLehrv 30
#define Anzahlstudenten 1000

char getchar()  //Funktion zum Einlesen von char
{
    char buchstabe;
    cin >> buchstabe;
    return buchstabe;
}

char* readString() //Funktion zum dynamischen Erzeugen von Zeichenketten
{
    char buchstabe;
    int count = 0;
    char* string_old = 0, *string_new = 0;
    do
    {
        buchstabe = getchar();
        string_new = new char[count+1];
        for (int i=0; i<count; i++)
        {
            string_new[i] = string_old[i];
        }
        string_new[count] = buchstabe;
        count++;
        delete[] string_old;
        string_old = string_new;
    }while(buchstabe != '0');
    string_new[count-1] = 0;
    return string_new;
}

class student  //Datenstruktur zur Verwaltung von Studenten
{
    char* name;
    char* Lehrveranstaltungen[AnzahlLehrv];
    int BesuchteVeranstaltungen;
    int matrikelnummer;
public:
    student()
    {
        matrikelnummer = 0;
        BesuchteVeranstaltungen = 0;
        for(int i = 0; i < AnzahlLehrv; i++)
            Lehrveranstaltungen[i] = NULL;
    }
    void set(char studiname[], int matrikel, char Veranstaltung[])
    {
        matrikelnummer = matrikel;
        name = studiname;
        Lehrveranstaltungen[BesuchteVeranstaltungen] = Veranstaltung;
        BesuchteVeranstaltungen++;
    }
    int getMatrikel()
    {
        return this->matrikelnummer;
    }
};

void bubblesort(student* const studenten[], int n) //Sortierfunktoin
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = n - 1; j > i; j--)
        {
            if(studenten[j]->getMatrikel() < studenten[j-1]->getMatrikel())
            {
                student temp = *studenten[j-1];
                *studenten[j-1] = *studenten[j];
                *studenten[j] = temp;
            }
        }
    }
}

bool binarySearch(student* studenten[], int matrikel, int left, int right) //Suchfunktion
{
    if(left > right)
    {
         return false;
    }
    int middle = ((right + left) / 2) ;
    if(matrikel == studenten[middle]->getMatrikel())
    {
        return true;
    }
    if(matrikel < studenten[middle]->getMatrikel())
            return binarySearch(studenten, matrikel, left, middle-1);
    if(matrikel > studenten[middle]->getMatrikel())
            return binarySearch(studenten, matrikel, middle+1, right);
}

void Studentaufnehmen(student* studenten[], int derzeitigeStudenten)  //Funktion zum Erfassen der Daten eines Studenten
{
    if(derzeitigeStudenten < 1000)
    {
            studenten[derzeitigeStudenten] = new student;
            char* studiname;
            int matrikel;
            cout << "Bitte Namen des Studenten nullterminiert eingeben: ";
            studiname = readString();
            cout << "Matrikelnummer des Studenten: ";
            cin >> matrikel;
            while(matrikel < 1 || matrikel > 999999)
            {
                cout << "Die Matrikelnummer muss zwischen 1 und 999999 liegen. Bitte erneut eingeben: ";
                cin >> matrikel;
            }
            while(binarySearch(studenten, matrikel, 0, derzeitigeStudenten-1))
            {
                cout << "Die Matrikelnummer " << matrikel << " existiert bereits. Bitte erneut eingeben: ";
                cin >> matrikel;
            }
            cout << "Anzahl der besuchten Veranstaltungen: ";
            int Anzahl;
            cin >> Anzahl;
            while(Anzahl < 0 || Anzahl > 30)
            {
                cout << "Die Anzahl der Veranstaltungen muss zwischen 0 und 30 liegen. Bitte erneut eingeben: ";
                cin >> Anzahl;
            }
            if(Anzahl>0)
            {
               for(int j = 0; j < Anzahl; j++)
                {
                    char* Veranstaltung;
                    cout << "Bitte Namen der "<< j+1 <<". Lehrveranstaltung nullterminiert eingeben: ";
                    Veranstaltung = readString();
                    studenten[derzeitigeStudenten]->set(studiname, matrikel, Veranstaltung);
                }
            }
            else
                studenten[derzeitigeStudenten]->set(studiname, matrikel, NULL);
            cout << endl << "Der Student wurde erfolgreich angelegt." << endl;
            return;
    }
    else
        cout << "Es können momentan keine neue Studenten mehr hinzugefügt werden." << endl;
}

bool deleteStudent(student* const studenten[], int matrikel, int left, int right, int &derzeitigeStudenten) //Funktion zum Löschen eines Studenten
{
    if(left > right)
    {
        return false;
    }
    int middle = ((right + left) / 2) ;
    if(matrikel == studenten[middle]->getMatrikel())
    {
        derzeitigeStudenten--;
        student temp = *studenten[middle];
        *studenten[middle] = *studenten[derzeitigeStudenten];
        *studenten[derzeitigeStudenten] = temp;
        delete studenten[derzeitigeStudenten];
        return true;
    }
    if(matrikel < studenten[middle]->getMatrikel())
            return deleteStudent(studenten, matrikel, left, middle-1, derzeitigeStudenten);
    if(matrikel > studenten[middle]->getMatrikel())
            return deleteStudent(studenten, matrikel, middle+1, right, derzeitigeStudenten);
}

int main()
{
    student* studenten[Anzahlstudenten];
    int derzeitigeStudenten = 0;
    for(int i = 0; i < Anzahlstudenten; i++)
        studenten[i] = NULL;

    char Eingabe = 'N'; // N wie Neutral;
    while(Eingabe != 'E') //Wiederjolter Aufruf des Menues
    {
        cout << endl;
        cout << "Studentenverwaltung" << endl << "===================" << endl << "Auswahlmenue:" << endl;
        cout << "A - Anlegen eines neuen Studenten und der bisher belegten Lehrveranstaltungen" << endl;
        cout << "S - Suchen eines Studenten" << endl;
        cout << "L - Loeschen eines Studenten" << endl;
        cout << "E - Programmende" << endl << endl;
        cout << "Eingabe: ";
        cin >> Eingabe;
        cout << endl;
        switch(Eingabe)
        {
            case 'A':   Studentaufnehmen(studenten, derzeitigeStudenten);
                        derzeitigeStudenten++;
                        bubblesort(studenten, derzeitigeStudenten);
                        break;
            case 'S':   int matrikelSearch;
                        cout << "Eingabe der zu suchenden Matrikelnummer: ";
                        cin >> matrikelSearch;
                        if(binarySearch(studenten, matrikelSearch, 0, derzeitigeStudenten-1))
                            cout << "Es existiert ein Student mit der Matrikelnummer " << matrikelSearch <<"." << endl;
                        else
                            cout << "Es existiert kein Student mit der Matrikelnummer " << matrikelSearch <<"." << endl;
                        break;
            case 'L':   int matrikelDelete;
                        cout << "Eingabe der zu loeschenden Matrikelnummer: ";
                        cin >> matrikelDelete;
                        if(deleteStudent(studenten, matrikelDelete, 0, derzeitigeStudenten-1, derzeitigeStudenten))
                            cout << "Der Student mit der Matrikelnummer " << matrikelDelete << " wurde erfolgreich geloescht." << endl;
                        else
                            cout << "Es existiert kein Student mit der Matrikelnummer " << matrikelDelete <<"." << endl;
                        studenten[derzeitigeStudenten] = NULL;
                        bubblesort(studenten, derzeitigeStudenten);
                        break;
            case 'E':   cout << "Das Programm wird beendet." << endl;
                        break;
            default:    cout << "Ungueltige Eingabe." << endl;
        }
    }
    return 0;
}
