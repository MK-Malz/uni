#include <stdio.h>

class Matrix
{
private:
    int** Werte;
    int Zeilen;
    int Spalten;
public:
    Matrix();
    Matrix(int Zeilen, int Spalten);
    ~Matrix();
    int getZeilen();
    int getSpalten();
    int getMatrixwert(int Zeile, int Spalte);
    void set(int* a);
    void out();
    void trp();
    void add(Matrix& m);
    void mul(Matrix& m);
    bool sym();
    bool ort();
};

Matrix::Matrix()
{
    Werte = NULL;
}

Matrix::Matrix(int Zeile, int Spalte)
{
    Zeilen = Zeile;
    Spalten = Spalte;
    Werte = new int*[Zeilen];
    for(int i = 0; i < Zeilen; i++)
        Werte[i] = new int[Spalten];
}

Matrix::~Matrix()
{
    for(int i = 0; i < Zeilen; i++)
        delete []Werte[i];
    delete []Werte;
}

int Matrix::getZeilen()
{
    return Zeilen;
}

int Matrix::getSpalten()
{
    return Spalten;
}

int Matrix::getMatrixwert(int Zeile, int Spalte)
{
    return Werte[Zeile][Spalte];
}

void Matrix::out()
{
    for(int i = 0; i<Zeilen; i++)
    {
       for(int j =0; j<Spalten; j++)
            printf("%4d ", Werte[i][j]);
        printf("\n");
    }
    printf("\n");
}

void Matrix::set(int* a)
{
    int k = 0;
    for(int i = 0; i<Zeilen; i++)
    {
       for(int j = 0; j<Spalten; j++)
       {
           Werte[i][j] = a[k];
           k++;
       }
    }
}

void Matrix::add(Matrix& m)
{
    if(this->Spalten == m.getSpalten() && this->Zeilen == m.getZeilen())
    {
        printf("Addition:\n\n");
        for(int i = 0; i<Zeilen; i++)
        {
            for(int j = 0; j<Spalten; j++)
            {
               Werte[i][j] = Werte[i][j] + m.getMatrixwert(i,j);
            }
        }
    }
    else
        printf("Matrizenaddition aufgrund inkompatibler Dimensionierung nicht moeglich.\n\n");
}

void Matrix::mul(Matrix& m)
{
    if(this->Spalten == m.getZeilen())
    {
        printf("Multiplikation:\n\n");
		Matrix result(Zeilen, m.getSpalten());
        int* Nullfueller = new int[Zeilen*m.getSpalten()];
		for (int h = 0; h < Zeilen*m.getSpalten();h++)
            Nullfueller[h] = 0;
        result.set(Nullfueller);
            for(int i=0;i<Zeilen;i++)
            {
				for(int j=0;j<m.getSpalten();j++)
				{
					for(int k=0;k<m.getZeilen();k++)
					{
						result.Werte[i][j] = result.Werte[i][j] + Werte[i][k]* m.getMatrixwert(k,j);
					}
				}
			}
        result.out();
        delete [] Nullfueller;
    }
    else
        printf("Matrizenmultiplikation aufgrund inkompatibler Dimensionierung nicht moeglich.\n\n");
}

void Matrix::trp()
{
    int* Fueller = new int[Spalten*Zeilen];
    int k = 0;
    for(int i = 0; i < Spalten; i++)
    {
        for(int j = 0; j < Zeilen; j++)
        {
            Fueller[k] = Werte[j][i];
            k++;
        }
    }

    int temp = Zeilen;
    Zeilen = Spalten;
    Spalten = temp;

    for(int i = 0; i < Zeilen; i++)
        delete []Werte[i];
    delete []Werte;

    Werte = new int*[Zeilen];
    for(int i = 0; i < Zeilen; i++)
        Werte[i] = new int[Spalten];
    this->set(Fueller);
    delete []Fueller;
}

int main(int argc, const char * argv[])
{
    if (argc != 3)
    {
        printf("Ungueltige Anzahl Argumente. Das Programm wird beendet.");
        return 0;
    }
    FILE *datei1 = fopen(argv[1],"r");
    FILE *datei2 = fopen(argv[2],"r");
    if(datei1 != NULL && datei2 != NULL)
    {
        int Zeilen1, Zeilen2, Spalten1, Spalten2;
        fscanf(datei1, "%d", &Zeilen1);
        fscanf(datei1, "%d", &Spalten1);
        fscanf(datei2, "%d", &Zeilen2);
        fscanf(datei2, "%d", &Spalten2);
        Matrix Matrix1(Zeilen1, Spalten1);
        Matrix Matrix2(Zeilen2, Spalten2);

        int* Wertefeld1 = new int[Zeilen1*Spalten1];
        int* Wertefeld2 = new int[Zeilen2*Spalten2];
        for (int i= 0; i< Zeilen1*Spalten1; i++)
            fscanf(datei1, "%d", &Wertefeld1[i]);
        for (int i= 0; i< Zeilen2*Spalten2; i++)
            fscanf(datei2, "%d", &Wertefeld2[i]);

        Matrix1.set(Wertefeld1);
        Matrix2.set(Wertefeld2);
        printf("Ausgabe Matrix 1:\n\n");
        Matrix1.out();
        printf("Ausgabe Matrix 2:\n\n");
        Matrix2.out();
        Matrix1.add(Matrix2);
        Matrix1.out();
        Matrix2.mul(Matrix1);
        printf("Transponierung von Matrix 1:\n\n");
        Matrix1.trp();
        Matrix1.out();
        delete[] Wertefeld1;
        delete[] Wertefeld2;
    }
    else
        printf("Eine Datei konnte nicht gefunden werden. Das Programm wird beendet.");
    fclose(datei1);
    fclose(datei2);
    return 0;
}
