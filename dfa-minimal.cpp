/* Pentru minimizarea DFA-ului vom utiliza Teorema Myhill Nerode */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define N 1005

using namespace std;

ifstream fin("dfa.in");

int n, m;                   //nr de noduri = m, respectiv muchii = n
int q0;                     //starea initiala
int nr_finale, SFinale[N];   //starile finale
bool matrice_MN[N][N];      //matricea pe care o folosi pentru teorema
int tabel_tranzitii[N][2];  //tabelul de tranzitii dintre puncte
bool unmarked[100];         //punctele la care nu se poate ajunge
int grupe[N], nr_grupe, grupa_initiala;     //gruparile de la final
bool grupa_finala[N];       //grupele care contin stari finale
bool grunreachablestate[N]; //grupe unmarked
char GRUP[N][N];            //grupele pe care le vom afisa
int tabDFA[N][2];           //tabelul dfa-ului minimal

void unmarked_finder(int i)
{
    unmarked[i] = 0;
    if(unmarked[tabel_tranzitii[i][0]] != 0)
        unmarked_finder(tabel_tranzitii[i][0]);
    if(unmarked[tabel_tranzitii[i][1]] != 0)
        unmarked_finder(tabel_tranzitii[i][1]);
}


int main()
{
    int i, j, x, y;

    ///citim graful aferent limbajului
    fin >> m >> n;
    for(i = 0; i < n; i++)
    {
        int st, dr;
        char e;
        fin >> st >> dr >> e;
        tabel_tranzitii[st][e - 97] = dr;
    }
    
    ///citim starea initiala si starile finale (marcam nodurile cu 1)
    fin >> q0;

    for(i = 0; i <= n / 2; i++)
        unmarked[i] = 1;
    unmarked[q0] = 0;
    unmarked_finder(q0);
    for(i = 0; i <= n / 2; i++)
        if(tabel_tranzitii[i][0] == i && tabel_tranzitii[i][1] == i)
            unmarked[i] = 1;

    fin >> nr_finale;
    for(i = 1; i <= nr_finale; i++)
    {
        int f;
        fin >> f;
        SFinale[f] = 1;
    }

    ///vom face primul pas, si anume
    ///vom marca in matrice perechile (Qa, Qb) si (Qb, Qa) = 1
    ///unde Qa este stare finala, iar Qb nu este stare finala
    n = n / 2;
    for(i = 1; i <= n; i++)
        for(j = 1; j < i; j++)
            if(SFinale[i] != SFinale[j])
                matrice_MN[i][j] = matrice_MN[j][i] = 1;

    ///vom reveni asupra matricei si vom marca si restul 
    ///perechilor care sunt posibile
    ///repetand acest proces pana ce nu vom mai modifica matricea
    bool valid = 0;
    while(!valid)
    {
        valid = 1;
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j < i; j++)
                if(matrice_MN[i][j] == 0)
                {
                    if(matrice_MN[tabel_tranzitii[i][0]][tabel_tranzitii[j][0]] == 1 || matrice_MN[tabel_tranzitii[i][1]][tabel_tranzitii[j][1]] == 1)
                    {
                        matrice_MN[i][j] = matrice_MN[j][i] = 1;
                        valid = 0;      //am facut modificari -> repetam procesul
                    }
                }
        }
    }

    ///vom grupa starile in functie de valorile nule din matrice
    ///matrice_MN[i][j] == 0 -> grupam i cu j
    for(i = 1; i <= n; i++)
        for(j = 1; j < i; j++)
            if(matrice_MN[i][j] == 0)
            {
                if(!grupe[i] && !grupe[j])
                {
                    nr_grupe++;
                    grupe[i] = grupe[j] = nr_grupe;
                }
                else if(grupe[j] == 0)
                    grupe[j] = grupe[i];
                else grupe[i] = grupe[j];
            }

    ///vom trece si grupele formate dintr-o singura stare
    for(i = 1; i <= n; i++)
        if(grupe[i] == 0)
            grupe[i] = ++nr_grupe;
    
    ///cautam grupa ce contine starea initiala
    ///si o marcam ca fiind grupa initiala
    q0 = grupe[q0];

    int ct = 0;
    for(i = 1; i <= nr_grupe; i++)
    {
        stringstream ss;
        ss << "(";
        for(j = 1; j <= n; j++)
        {
            if(grupe[j] == i)
            {
                tabDFA[i][0] = grupe[tabel_tranzitii[j][0]];
                tabDFA[i][1] = grupe[tabel_tranzitii[j][1]];
                ss << j;
                if(SFinale[j] == 1 && grupa_finala[i] == 0)
                {
                    grupa_finala[i] = 1;
                    ct ++;
                }
                if(unmarked[j] == 1)
                    grunreachablestate[i] = 1;
            }
        }
        ss << ")";
        ss >> GRUP[i];
    } 

    cout << "AFD-ul minimal are urmatoarea forma: \n";
    for(i = 1; i <= nr_grupe; i++)
    {
        if(grunreachablestate[i] != 1)
        {
            if(grunreachablestate[tabDFA[i][0]] != 1)
                cout << GRUP[i] << " " << GRUP[tabDFA[i][0]] << " a" << "\n";
            if(grunreachablestate[tabDFA[i][1]] != 1)
                cout << GRUP[i] << " " << GRUP[tabDFA[i][1]] << " b" << "\n";
        }
    }
    cout << "\nGrupa initiala este: " << GRUP[q0] << "\n";
    if(ct > 1)
        cout << "Punctele finale sunt grupele: ";
    else cout << "Punctul final este grupa: ";
    for(i = 0; i <= n; i++)
        if(grupa_finala[i] == 1)
            cout << GRUP[i] << " ";
    cout << "\n";

    return 0;
}

/*
Forma inputului:
nr. noduri
nr. muchii
muchiile
........
stare initiala
nr. stari finale
starile finale
........
*/

/*
6 12
1 4 a
1 3 b
2 1 a
2 4 b
3 5 a
3 6 b
4 5 a
4 6 b
5 5 a
5 6 b
6 6 a
6 6 b
1
3
3 4 5
*/

/*
5 10
1 2 a
1 3 b
2 2 a
2 4 b
3 3 b
3 2 a
4 2 a
4 5 b
5 2 a
5 3 b
1
1
5
*/

/*
14
1 2 a
1 3 b
2 4 1
2 5 b
3 4 b
3 5 a
4 7 a
4 7 b
5 7 a
5 7 b
6 4 a
6 5 b
7 7 a
7 7 b
1
2 3 7
*/