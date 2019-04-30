#ifndef AUTOMA_H_INCLUDED
#define AUTOMA_H_INCLUDED


typedef struct tabsymboles tabsymboles;
struct tabsymboles
{
    int ind[100] = {0};
    int tabequivalent[100] = {0};
};

typedef struct tabdeter tabdeter;
struct tabdeter
{
    char tabtab[20] = {'.'};
};

class Automate
{
    public:

    Automate();
    void lireAutomate1(int i);
    void lireAutomate2(int i);
    void lireAutomate3(int i);
    void lireAutomate4();
    void stocker(unsigned int cpt, char caractere);
    void stockertab1(int tab[], int);
    void stockertab2(int tab[], int);
    void stockertab3(char tab[], int);
    bool est_un_automate_asynchrone(int i);
    bool est_un_automate_deterministe(int i);
    bool est_un_automate_complet(int i);
    int getetatinitiaux();
    int getetatinitiaux2(int i);
    char getetaterminaux(int i);
    int getnbsymboles();
    char getnbtransitions(char i, int cpt, int p, char cara, int memoire);
    void setetatinitiaux(int i);
    void setetaterminaux(int i);
    int getnbtransitions2();
    char getnbtransitions4(int i);
    void setnbtransitions5(int i);
    int getnbtransitions5();
    bool reconnaitre_mot(char* mac, int taille);
    int getnbetats();
    int getnbetatsterminaux();
    void transformer(int* tab3, int i);
    int transformer2(int* tab3, int i);
    void remplir1();
    void remplir2();

    private:

    unsigned int _nbsymboles;
    unsigned int _nbetats;
    unsigned int _nbetatsinitiaux;
    int _tab1[100];
    unsigned int _nbetatsterminaux;
    int _tab2[100];
    unsigned int _nbtransitions;
    char _tab3[100];

};

char tabchar(int i);
char tabchar2(int i);
void afficher(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere);
void determinisationetcompletion(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere);
void completion(tabdeter tableau2);
void reconnaissancemots(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere);
void determinisation_et_completion_automate_asynchrone(Automate premier, int y);
void completion(int y, Automate premier);
void determinisation_et_completion_automate_synchrone(Automate premier, int y);
void afficher_automate_deterministe_complet(Automate premier, int y);
void langagecomplementaire(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere);

#endif // AUTOMA_H_INCLUDED
