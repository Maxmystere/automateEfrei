#include <iostream>
#include "Automa.h"

using namespace std;

void Automate::lireAutomate1(int i)
{
    int j=0;
    cout << "\n" << i << " etats initiaux:\nI={";
    while(j<i){
            if(_tab1[j] != 123)
            {
                cout << _tab1[j] << ",";
            }
            j++;
    }
    cout << "}" << endl;
}

void Automate::lireAutomate2(int i)
{
    int j=0;
    cout << i << " etats terminaux:\nT={";
    while(j<i){
            if(_tab2[j] != 123)
            {
                cout << _tab2[j] << ",";
            }
        j++;
    }
    cout << "}" << endl;
}

void Automate::lireAutomate3(int i)
{
    int j=0;
    cout << i/3 << " transitions:" << endl;
    while(j<i-1){
        cout << _tab3[j] << _tab3[j+1] << _tab3[j+2] << endl;
        j=j+3;
    }
}

void Automate::lireAutomate4()
{
    cout << "\n" << _nbsymboles << " symboles dans l'alphabet:\nA= {";
    if(_nbsymboles == 1)
        cout << "a}";
    if(_nbsymboles == 2)
        cout << "a,b}";
    if(_nbsymboles == 3)
        cout << "a,b,c}";
    if(_nbsymboles == 4)
        cout << "a,b,c,d}";
    if(_nbsymboles == 5)
        cout << "a,b,c,d,e}";
    if(_nbsymboles == 6)
        cout << "a,b,c,d,e,f}";
    if(_nbsymboles == 7)
        cout << "a,b,c,d,e,f,g}";
    if(_nbsymboles == 8)
        cout << "a,b,c,d,e,f,g,h}";
    if(_nbsymboles == 9)
        cout << "a,b,c,d,e,f,g,h,i}";
    if(_nbsymboles == 10)
        cout << "a,b,c,d,e,f,g,h,i,j}";
    if(_nbsymboles == 11)
        cout << "a,b,c,d,e,f,g,h,i,j,k}";
    if(_nbsymboles == 12)
        cout << "a,b,c,d,e,f,g,h,i,j,k,l}";
    if(_nbsymboles == 13)
        cout << "a,b,c,d,e,f,g,h,i,j,k,l,m}";

    cout << "\n" << _nbetats << " etats:\nQ={";
    if(_nbetats == 1)
        cout << "0}";
    if(_nbetats == 2)
        cout << "0,1}";
    if(_nbetats == 3)
        cout << "0,1,2}";
    if(_nbetats == 4)
        cout << "0,1,2,3}";
    if(_nbetats == 5)
        cout << "0,1,2,3,4}";
    if(_nbetats == 6)
        cout << "0,1,2,3,4,5}";
    if(_nbetats == 7)
        cout << "0,1,2,3,4,5,6}";
    if(_nbetats == 8)
        cout << "0,1,2,3,4,5,6,7}";
    if(_nbetats == 9)
        cout << "0,1,2,3,4,5,6,7,8}";
    if(_nbetats == 10)
        cout << "0,1,2,3,4,5,6,7,8,9}";
    if(_nbetats == 11)
        cout << "0,1,2,3,4,5,6,7,8,9,10}";
    if(_nbetats == 12)
        cout << "0,1,2,3,4,5,6,7,8,9,10,11}";
    if(_nbetats == 13)
        cout << "0,1,2,3,4,5,6,7,8,9,10,11,12}";
    if(_nbetats == 14)
        cout << "0,1,2,3,4,5,6,7,8,9,10,11,12,13}";
}

void Automate::setetatinitiaux(int i)
{
    _nbetatsinitiaux = i;
}

void Automate::setetaterminaux(int i)
{
    _nbetatsterminaux = i;
}

void Automate::stocker(unsigned int cpt, char caractere)
{
    if(cpt == 1)
    {
        _nbsymboles = caractere-48;
    }
    else if(cpt == 2)
    {
        _nbetats = caractere-48;
    }
}

void Automate::stockertab1(int tab[], int i)
{
    for (int j=0; j<i; j++)
    {
        _tab1[j] = tab[j];
        //cout << "tab1[1]: " << _nbetatsinitiaux << endl;
    }
}

void Automate::stockertab2(int tab[], int i)
{
    for (int j=0; j<i; j++)
    {
        _tab2[j] = tab[j];
    }
}

void Automate::stockertab3(char tab[], int i)
{
    for (int j=0; j<i-1; j++)
    {
        _tab3[j] = tab[j];
    }
}

bool Automate::est_un_automate_asynchrone(int y)
{
    int cpt = 0;
    for(int j=0; j<y-1; j++)
    {
        if('*' == _tab3[j+1])
        {
            cpt++;
            //return true;
        }
        j=j+2;
    }
    if(cpt == 0)
    {
        return false;
    }
    cout << "\nL'automate est asynchrone car nous avons les liaisons suivantes: " << endl;
    for(int j=0; j<y-1; j++)
    {
        if('*' == _tab3[j+1])
        {
            cout << _tab3[j] << _tab3[j+1] << _tab3[j+2] << endl;
        }
        j=j+2;
    }
    return true;
}

int Automate::getetatinitiaux()
{
    return _nbetatsinitiaux;
}

char Automate::getetaterminaux(int i)
{
    return _tab2[i];
}

int Automate::getetatinitiaux2(int i)
{
    return _tab1[i];
}

int Automate::getnbsymboles()
{
    return _nbsymboles;
}

void Automate::setnbtransitions5(int i)
{
    _nbtransitions = i;
}

int Automate::getnbtransitions5()
{
    return _nbtransitions;
}

int Automate::getnbtransitions2()
{
    int cpt = 0;
    for(int i=0; i<100; i++)
    {
        if(_tab3[i] != '.')
        {
            cpt++;
        }
    }
    return cpt;
}

char Automate::getnbtransitions4(int i)
{
    return _tab3[i];
}

int Automate::getnbetats()
{
    return _nbetats;
}

int Automate::getnbetatsterminaux()
{
    return _nbetatsterminaux;
}

char Automate::getnbtransitions(char i, int cpt, int p, char cara, int memoire)// p=30
{
    int y=0;
    int compteur=0;
        do
        {
            //cout << "memoire = " << memoire << endl;
            while(compteur<memoire)
            {
                y = y + 3;
                compteur++;
            }
            //cout << "tab3 = " << cara << endl;
            if(_tab3[y] == cara && _tab3[y+1] == i)//ici i = 0
            {
                if(cpt==1)
                {
                    //cout << "1) " << i << endl;
                    return cara;
                }
                else if(cpt==2)
                {
                    //cout << "2) " << _tab3[y+1] << endl;
                    return i;
                    //return _tab3[y+1];
                }
                else if(cpt==3)
                {
                    //cout << "3) " << _tab3[y+2] << endl;
                    return _tab3[y+2];
                }
                else if(cpt==4)
                {
                    return compteur;
                }
            }
            y = y + 3;
            compteur++;
            //cout << "LE Y= " << y << endl;
        }while(y<30);
        if(cpt==1)
            {
                //cout << "1) " << i << endl;
                return 'o';
            }
            else if(cpt==2)
            {
                //cout << "2) " << _tab3[y+1] << endl;
                return 'u';
                //return _tab3[y+1];
            }
            else if(cpt==3)
            {
                //cout << "3) " << _tab3[y+2] << endl;
                return 'i';
            }
    return 'x';
}

bool Automate::est_un_automate_deterministe(int i)
{
    int j = 0;
    char a,b;
    int cpt =0;
    if(_nbetatsinitiaux != 1)
    {
        return false;
    }
    else
    {
        for(j=0; j<i; j++)
        {
            a = _tab3[j];
            b = _tab3[j+1];
            for(int k=0; k<i; k++)
            {
                if(a == _tab3[k] && b == _tab3[k+1])
                {
                    cpt++;
                }
                k = k + 2;
            }
            if(cpt > 1)
            {
                return false;
            }
            else
            {
                cpt = 0;
            }
            j = j + 2;
        }
    }
    return true;
}


bool Automate::est_un_automate_complet(int i)
{
    int j = 0;
    char a,b;
    int cpt =0;
    int k =1;
    int c = _nbetats;
    int d = _nbetatsterminaux;
    int e = _nbsymboles;

    for(int h=0; h<c; h++)// pour le nb etat ici 0 a 2
    {
        a = tabchar2(h);// 0 puis 1 etc jusqu'a
        b = tabchar(k);//ici a puis b etc
        for(int q=0; q<d; q++)
        {
            if(a-48 == _tab2[q])
            {
                h++;
                if(h==c)
                {
                    return true;
                }
                a = tabchar2(h);
            }
        }
            do{
                k = 1;
                for(j=0; j<i; j++)
                {
                    //cout << "a= " << a << endl;
                    //cout << "b= " << b << endl;
                    if(a == _tab3[j] && b == _tab3[j+1])
                    {
                        k++;
                        b = tabchar(k);
                        cpt++;
                        if(k == e+1)
                        {
                            j = i+1;
                            k = 1;
                        }
                    }
                    j = j + 2;
                }
            }while(k==e);
            if(cpt!=e)
            {
                return false;
            }
            else
            {
                cpt = 0;
            }
    }
    return true;
}

bool Automate::reconnaitre_mot(char* mac, int taille)
{
    int cpt = 0;
    for(int ii=0; ii<6; ii++)//d'abord on va prendre les etats initiaux
    {
        if(_tab1[ii] != 123)//d'abord on va prendre les etats initiaux
        {
            char a = _tab1[ii]+48;
            for(int i=0; i<taille; i++)//pour lire le mot
            {
                //if(mac[i] != '.')//pour eventuellement stoper apres 1 mot voir faire les mots suivants si saisis
                //{
                    for(int j=0; j<_nbtransitions*3; j=j+3)//y max de transitions
                    {
                        //if(mac[i] != '.')
                        //{
                            //cout << "FJHDJ" << _tab3[j] << endl;
                            if(a == _tab3[j] && mac[i] == _tab3[j+1])//d'abord l'etat
                            {
                                cpt++;
                            }
                            if(cpt == 1)
                            {
                                //cout << "HBD" << endl;
                                i++;
                                if(taille==i)
                                {
                                    return true;
                                }
                                cpt = 0;
                                a = _tab3[j+2];
                                j = 0;
                            }
                            else
                            {
                                if(j == 27)
                                {
                                    return false;
                                }
                            }
                        //}
                        if(j == _nbtransitions*3-3)
                        {
                            if(cpt == 0)
                            {
                                return false;
                            }
                        }
                    }
                //}
            }
        }
    }
}

/*bool Automate::reconnaitre_mot(char* mac, int taille)
{
    int i = 0, d, e, f, cpt=0;
    char a;
    int u = 0;
    d = _nbetatsinitiaux;
    f = _nbtransitions;
    for(e=0; e<d; e++)//nombre d'etat initiaux ici 1
    {
        a = _tab2[e]+46;//code ascii pour passer de
        int k = i;
        for(i=0; i<f; i++)// ici taille = 2
        {
            //cout << "tab[]= " << _tab3[i] << " a= " << a << endl;
            //cout << "mac[]= " << mac[u] << " _tab3[]= " << _tab3[i+1] << endl;
            //cout << "DGJHD" << endl;
            if(a == _tab3[i] && mac[u] == _tab3[i+1])
            {
                cpt++;
                a = _tab3[i+2];
                k++;
                i = 0;
                u++;
                if(u==taille-1)
                {
                    if(cpt == taille)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                if(cpt == taille)
                {
                    return false;
                }
                i = i + 2;
            }
        }
        //cout << "taille= " << cpt << endl;
        if(cpt == taille)
        {
            return true;
        }
    }
    return false;
}*/

void Automate::remplir1()
{
    int i=0;
    for(i=0; i<100; i++)
    {
        _tab1[i] = 123;
    }
}

void Automate::remplir2()
{
    int i=0;
    for(i=0; i<100; i++)
    {
        _tab2[i] = 123;
    }
}

void Automate::transformer(int* tab, int gg)
{
        int grandcompteur = 0;
        int compteur = 0;
        int c = _nbetatsterminaux;
        for(int i=0; i<gg; i++)
        {
            for(int p=0; p<c; p++)
            {
                if(_tab2[p] == i)
                {
                    compteur++;
                }
            }
            if(compteur == 0)
            {
                tab[grandcompteur] = i;
                grandcompteur++;
            }
            compteur = 0;
        }
        for(int i=0; i<100; i++)
        {
            _tab2[i] = 123;
        }
        for(int i=0; i<=grandcompteur; i++)
        {
            if(tab[i] != 123)
                _tab2[i] = tab[i];
        }
}

int Automate::transformer2(int* tab, int gg)
{
        int grandcompteur = 0;
        int compteur = 0;
        int c = _nbetatsterminaux;
        for(int i=0; i<gg; i++)
        {
            for(int p=0; p<c; p++)
            {
                if(_tab2[p] == i)
                {
                    compteur++;
                }
            }
            if(compteur == 0)
            {
                tab[grandcompteur] = i;
                grandcompteur++;
            }
            compteur = 0;
        }
        return grandcompteur;
}

Automate::Automate()
{

}
