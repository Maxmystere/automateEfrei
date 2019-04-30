#include <iostream>
#include <fstream>
#include "Automa.h"

using namespace std;

void completion(int y, Automate premier)//juste pour automate deterministe non complet
{
	char tab[y];
	for(int i=0; i<y; i++)
	{
		tab[i] = premier.getnbtransitions4(i);
	}
	for(int i=0; i<y; i++)
	{
		cout << tab[i] << tab[i+1] << tab[i+2] << endl;
		i = i + 2;
	}
	int j=0, nb=0, cpt=0, cpt2=0;
	char a, b;
	nb = premier.getnbetats();
	for(j=0; j<nb-1; j++)//2 donc 0 et 1
	{
		a = tabchar2(j);// ici 0 puis 1
		//cout << "a= " << a << endl;
		for(int k=1; k<nb; k++)
		{
			b = tabchar(k); // ici a puis b
			for(int u=0; u<y; u++)
			{
				//cout << "x= " << premier.getnbtransitions4(u) << " l= " << a << endl;
				//cout << "xx= " << premier.getnbtransitions4(u+1) << " ll= " << b << endl;
				if(premier.getnbtransitions4(u) == a && premier.getnbtransitions4(u+1) == b)//premier.getnbtransitions4(u) pour envoyer _tab3[u]
				{
					cpt++;
					//cout << "cpt= " << cpt << endl;
				}
				u = u + 2;

			}
			if(cpt == 1)
			{
				cpt2++;
				cpt = 0;
			}
			else
			{
				cout << "Il manque la liaison: " << a << b << "P" << endl;
				cpt = 0;
			}
			if(cpt2 == nb)
			{
				cpt2 = 0;
				//cout << "Partie finie" << endl;
			}
		}
	}
}

void langagecomplementaire(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere)
{
	int verif = 0;

	ifstream fichier("Z3AF01.txt", ios::in);  // on ouvre

	if(fichier)
	{
		while(fichier.get(caractere))  // on lit un caract�re et on le stocke dans caractere
		{
			cpt++;
			if(caractere == '\n')
			{
				fichier.get(caractere);
				cout << "\n";
			}
			if(caractere == 32) // 32 en code ascii signie espace
			{
				fichier.get(caractere);
				cout << " ";
			}
			if(cpt>=1 && cpt <=2)
			{
				premier.stocker(cpt, caractere);
			}
			else{
				if(cpt==3) // ligne 3
				{
					j = (caractere-48);
					premier.setetatinitiaux(j);
					numetatinitiaux = new int[j];
					x = j+3;
				}
				else if(cpt <= (j+3)) // leurs numeros
				{
					numetatinitiaux[i] = caractere-48;
					i++;
				}
				if(cpt == x+1) // ici x = 5 // cad ligne 4
				{
					i=0;
					k = (caractere-48); // k=2
					premier.setetaterminaux(k);
					numetatterminaux = new int[k];
					if(m==0)
					{
						m = cpt + caractere-48;// m=8
						//cout << "m= " << m << endl;
					}
				}
				if(cpt > x+1 && cpt <= m) // leurs numeros ligne 4 x=5 m=8
				{
					numetatterminaux[i] = caractere-48;
					i++;
				}
				if(cpt == m+1) //ligne 5
				{
					mem = caractere - 48; // mem sauvegarde la valeur initiale, si jamais le nb de transitions est un chiffre et non un nb
					if(caractere != '\n')
					{
						fichier.get(caractere);
						if(caractere == '\n')// cas ou c'est un chiffre, on garde donc la valeur sauvegarde mem
						{
							n = mem;
						}
						else// cas ou c'est un nb, alors sauvegarde le nb par l'op suivante
						{
							n = mem*10 + caractere-48 ;
						}
					}
					//n = caractere - 48; // ici n=5
					transitions = new char[n*3]; //ligne ici y
					y++;
				}
				else if(cpt > m+1 && cpt <= 3*n+m+1 ) //leurs numeros
				{
					transitions[y-1] = caractere;
					y++;
				}
			}
			if(n>9)//pour afficher le nb de transitions (=n)
			{
				if(verif==0)// pour pas afficher n pour toute les transitions, mais seulement une seule fois
				{
					cout << n;
					verif++;
				}
				else
				{
					cout << caractere;  // on l'affiche
				}
			}
			else
				cout << caractere;  // on l'affiche
		}
		fichier.close();
		cout << endl;
	}
	else
	cerr << "Impossible d'ouvrir le fichier !" << endl;

	premier.remplir1();
	premier.remplir2();

	premier.stockertab1(numetatinitiaux, j);
	premier.stockertab2(numetatterminaux, k);
	premier.stockertab3(transitions, y);



	premier.lireAutomate1(j);
	premier.lireAutomate2(k);

	//ici le langage complementaire, d'abord tout les T deviennent N puis tout les N deviennent T

	premier.setnbtransitions5(y);

	int tab123[10];
	{
		for(int h=0; h<10; h++)
		{
			tab123[h] = 123;
		}
	}
	int gg = premier.getnbetats();
	premier.transformer(tab123, gg);//fait le langage complementaire
	int h = premier.transformer2(tab123, gg);
	premier.lireAutomate2(h);

	//suite ici
	tabdeter tableau2[15][100];
		for(int yy=0; yy<100; yy++)
		{
			for(int ww=0; ww<15; ww++)
			{
				for(int zz=0; zz<10; zz++)
				{
					tableau2[ww][yy].tabtab[zz] = '.';
				}
			}
		}
		for(int yy=0; yy<100; yy++)
		{
			for(int ww=0; ww<15; ww++)
			{
				for(int zz=0; zz<10; zz++)
				{
					tableau2[ww][yy].tabtab[zz] = '.';
				}
			}
		}
		int cb = 0;
		for(cb=0; cb<premier.getetatinitiaux(); cb++)//2 ici remplace par le nombre d'etat initiaux ici 0,4
		{
			tableau2[0][0].tabtab[cb] = premier.getetatinitiaux2(cb)+48;
			//cout << "et la: " << tableau2[0][0].tabtab[cb] << endl;//important
		}
		premier.getnbsymboles();
		//cout << "n= " << n << endl;
		char a='o', b='u', c='i';
		int memoire = 0;
		char cara;
		char symb;
		int group=0;

		for(int q=1; q<=premier.getnbsymboles(); q++)
		{
			for(cb=0; cb<premier.getetatinitiaux(); cb++)// pour cb allant de 0 a 1 inclus donc pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(q);
					cara = tableau2[0][0].tabtab[cb];
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "tab2[][] " << group << endl;//important
							tableau2[q][0].tabtab[group] = c;
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
		}

		// maintenant automatisons ce processus pour tout le tableau

		int grandindice1 = 1;
		int grandindice2 = 0;
		int petitcompteur = 0;
		int compteur = 0;
		char tab[3];
		int taille = 0;
		int grand = 1;
		int w=0;
		int repetition = 0;
		//cout << "TAB =" <<  tableau2[2][0].tabtab[0] << endl;
		int erreur = 0;
		int g =0;
		i=0;
		do{
				a='o', b='u', c='i';
		do{
				if(w==2)
				{
					grandindice2++;
					w=-1;
				}
			w++;
			taille=0;
			for(compteur=0; compteur<=2; compteur++)
			{
				if(tableau2[w][grandindice2].tabtab[compteur] != '.')
				{
					tab[compteur] = tableau2[w][grandindice2].tabtab[compteur];// ici 1 2 4 apres faut 1 2 3
					taille++;//ici pour connaire le nombre d'etat dans la case donc 3
				}
				else
					tab[compteur] = '.';
			}
			if(tab[0] != '.')
				a = tab[0];
			if(tab[1] != '.')
				b = tab[1];
			if(tab[0] != '.')
				c = tab[2];
			//cout << "C'EST: " << a << b << c << endl;//important
			//manque l'ajout de l'etat pricipal a chaque fois apres verif
			repetition = 0;
			erreur = 0;
			for(g=0; g<20; g++)
			{
				//fonction verifi etat si deja existant !!! a ameliorer !!

					//cout << "tableau =" << tableau2[0][g].tabtab[0] << " suite = " << tableau2[0][g].tabtab[1] << "suite encore = " << tableau2[0][g].tabtab[2] << endl;
						if(tableau2[i][g].tabtab[0] == a)
						{
							if(tableau2[i][g].tabtab[1] == b)
							{
								if(tableau2[i][g].tabtab[2] == c)
								{
									repetition = 1;
									//cout << "c'est le cas BORDEL !" << a << b << c << endl;//important
								}
							}
						}
			}
			//cout << "g= " << g << endl;
			}while(repetition == 1);

			if(repetition==0)
				{
					//cout << "t= " << t << endl;//important
					//cout << "A= " << a << "B= " << b << "C= " << c << endl;//important
					//cout << "petit compteur = " << petitcompteur << "grandindice " << grandindice1 << endl;//important
					if(a != '.')
						tableau2[petitcompteur][grandindice1].tabtab[0] = a;//[0][1]
					if(b != '.')
						tableau2[petitcompteur][grandindice1].tabtab[1] = b;
					if(c != '.')
						tableau2[petitcompteur][grandindice1].tabtab[2] = c;
				}
				grandindice1++;
			a = 'o';
			b = 'u';
			c = 'i';
			if(erreur == 0)
			{

			for(int qq=1; qq<=premier.getnbsymboles(); qq++)// pour a puis b
			{
			for(cb=0; cb<taille; cb++)// pour pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(qq);
					cara = tab[cb];//1,2,4
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "c " << c << endl;//important
							tableau2[qq][grand].tabtab[group] = c;//tableau[0,1,2][1]
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
						//cout << "w= " << w << endl;//important

					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
				a='o', b='u', c='i';
			}

			}
			grand++;

		}while(grandindice2<3);

		int jjj =0;
		//completion
		for(int iii=0; iii<100; iii++)
		{
			//for(int jj=0; jj<3; jj++)
			//{
				if(tableau2[jjj][iii].tabtab[0] == '.')
				{
					tableau2[jjj][iii].tabtab[0] = 'P';
				}
				if(tableau2[jjj+1][iii].tabtab[0] == '.')
				{
					tableau2[jjj+1][iii].tabtab[0] = 'P';
				}
				if(tableau2[jjj+2][iii].tabtab[0] == '.')
				{
					tableau2[jjj+2][iii].tabtab[0] = 'P';
				}
			//}
		}

		cout << endl;

		int compteur2 = 0;
		int xxx = premier.getnbsymboles();
		if(xxx == 1)
		{
			cout << "Tableau determinise:\n     a" << endl;
		}
		if(xxx == 2)
		{
			cout << "Tableau determinise:\n     a    b" << endl;
		}
		if(xxx == 3)
		{
			cout << "Tableau determinise:\n     a     b     c" << endl;
		}
		if(xxx == 4)
		{
			cout << "Tableau determinise et complet:\n     a     b     c     d" << endl;
		}
		for(int aa=0; aa<7; aa++)
		{
			for(int bb=0; bb<15; bb++)
			{
				if(tableau2[bb][aa].tabtab[0] != '.')
				{
					//cout << "tableau2[" << aa << "][" << bb << "]= ";
					//compteur2++;
				}
				for(int qq=0; qq<10; qq++)
				{
					if(tableau2[bb][aa].tabtab[qq] == '0' || tableau2[bb][aa].tabtab[qq] == '1' || tableau2[bb][aa].tabtab[qq] == '2' || tableau2[bb][aa].tabtab[qq] == '3' || tableau2[bb][aa].tabtab[qq] == '4' || tableau2[bb][aa].tabtab[qq] == '5' || tableau2[bb][aa].tabtab[qq] == '6' || tableau2[bb][aa].tabtab[qq] == '7' || tableau2[bb][aa].tabtab[qq] == '8' || tableau2[bb][aa].tabtab[qq] == '9' || tableau2[bb][aa].tabtab[qq] == 'P')
					{
						cout << tableau2[bb][aa].tabtab[qq];
						compteur2++;
					}
				}
				if(compteur2!=0)
				{
					//cout << endl;
					compteur2=0;
					cout << " | ";
				}
			}
			cout << endl;
		}
}

void afficher_automate_deterministe_complet(Automate premier, char *txt, int y)
{
		tabdeter tableau2[15][100];
		int i;
		for(int yy=0; yy<100; yy++)
		{
			for(int ww=0; ww<15; ww++)
			{
				for(int zz=0; zz<10; zz++)
				{
					tableau2[ww][yy].tabtab[zz] = '.';
				}
			}
		}
		int cb = 0;
		for(cb=0; cb<premier.getetatinitiaux(); cb++)//2 ici remplace par le nombre d'etat initiaux ici 0,4
		{
			tableau2[0][0].tabtab[cb] = premier.getetatinitiaux2(cb)+48;
			//cout << "et la: " << tableau2[0][0].tabtab[cb] << endl;//important
		}
		premier.getnbsymboles();
		//cout << "n= " << n << endl;
		char a='o', b='u', c='i';
		int memoire = 0;
		char cara;
		char symb;
		int group=0;

		for(int q=1; q<=premier.getnbsymboles(); q++)
		{
			for(cb=0; cb<premier.getetatinitiaux(); cb++)// pour cb allant de 0 a 1 inclus donc pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(q);
					cara = tableau2[0][0].tabtab[cb];
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "tab2[][] " << group << endl;//important
							//cout << "C= " << c << endl;
							tableau2[q][0].tabtab[group] = c;
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
		}

		// maintenant automatisons ce processus pour tout le tableau

		int grandindice1 = 1;
		int grandindice2 = 0;
		int petitcompteur = 0;
		int compteur = 0;
		char tab[3];
		int taille = 0;
		int grand = 1;
		int w=0;
		int repetition = 0;
		//cout << "TAB =" <<  tableau2[2][0].tabtab[0] << endl;
		int erreur = 0;
		int g =0;
		i=0;
		do{
				a='o', b='u', c='i';
		do{
				if(w==2)
				{
					grandindice2++;
					w=-1;
				}
			w++;
			taille=0;
			for(compteur=0; compteur<=2; compteur++)
			{
				if(tableau2[w][grandindice2].tabtab[compteur] != '.')
				{
					tab[compteur] = tableau2[w][grandindice2].tabtab[compteur];// ici 1 2 4 apres faut 1 2 3
					taille++;//ici pour connaire le nombre d'etat dans la case donc 3
				}
				else
					tab[compteur] = '.';
			}
			if(tab[0] != '.')
				a = tab[0];
			if(tab[1] != '.')
				b = tab[1];
			if(tab[0] != '.')
				c = tab[2];

			repetition = 0;
			erreur = 0;
			for(g=0; g<20; g++)
			{
				if(tableau2[i][g].tabtab[0] == a)
				{
					if(tableau2[i][g].tabtab[1] == b)
					{
						if(tableau2[i][g].tabtab[2] == c)
						{
							repetition = 1;
							//cout << "c'est le cas BORDEL !" << a << b << c << endl;//important
						}
					}
				}
			}
			}while(repetition == 1);

			if(repetition==0)
				{
					//cout << "A= " << a << " B= " << b << " C= " << c << endl;
					if(a != '.' && a!='o' && a !='u' && a != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = a;//[0][1]
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = '.';
					}
					if(b != '.' && b!='o' && b !='u' && b != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = b;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = '.';
					}
					if(c != '.' && c!='o' && c !='u' && c != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = c;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = '.';
					}
				}
				grandindice1++;
			a = 'o';
			b = 'u';
			c = 'i';
			if(erreur == 0)
			{

			for(int qq=1; qq<=premier.getnbsymboles(); qq++)// pour a puis b
			{
			for(cb=0; cb<taille; cb++)// pour pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(qq);
					cara = tab[cb];//1,2,4
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "c " << c << endl;//important
							tableau2[qq][grand].tabtab[group] = c;//tableau[0,1,2][1]
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
						//cout << "w= " << w << endl;//important

					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
				a='o', b='u', c='i';
			}

			}
			grand++;

		}while(grandindice2<5);

		int jj =0;
		//completion
		for(int ii=0; ii<100; ii++)
		{
				if(tableau2[jj][ii].tabtab[0] == '.')
				{
					tableau2[jj][ii].tabtab[0] = 'P';
				}
				if(tableau2[jj+1][ii].tabtab[0] == '.')
				{
					tableau2[jj+1][ii].tabtab[0] = 'P';
				}
				if(tableau2[jj+2][ii].tabtab[0] == '.')
				{
					tableau2[jj+2][ii].tabtab[0] = 'P';
				}
		}
		//la vraie fonction afficher
		//faire ici affiche en tant que tableau
		cout << endl;

		int compteur2 = 0;
		int xx = premier.getnbsymboles();
		if(xx == 1)
		{
			cout << "Tableau determinise:\n     a" << endl;
		}
		if(xx == 2)
		{
			cout << "Tableau determinise:\n     a    b" << endl;
		}
		if(xx == 3)
		{
			cout << "Tableau determinise:\n     a     b     c" << endl;
		}
		if(xx == 4)
		{
			cout << "Tableau determinise et complet:\n     a     b     c     d" << endl;
		}
		for(int aa=0; aa<7; aa++)
		{
			for(int bb=0; bb<15; bb++)
			{
				if(tableau2[bb][aa].tabtab[0] != '.')
				{
					//cout << "tableau2[" << aa << "][" << bb << "]= ";
					//compteur2++;
				}
				for(int qq=0; qq<10; qq++)
				{
					if(tableau2[bb][aa].tabtab[qq] == '0' || tableau2[bb][aa].tabtab[qq] == '1' || tableau2[bb][aa].tabtab[qq] == '2' || tableau2[bb][aa].tabtab[qq] == '3' || tableau2[bb][aa].tabtab[qq] == '4' || tableau2[bb][aa].tabtab[qq] == '5' || tableau2[bb][aa].tabtab[qq] == '6' || tableau2[bb][aa].tabtab[qq] == '7' || tableau2[bb][aa].tabtab[qq] == '8' || tableau2[bb][aa].tabtab[qq] == '9' || tableau2[bb][aa].tabtab[qq] == 'P')
					{
						cout << tableau2[bb][aa].tabtab[qq];
						compteur2++;
					}
				}
				if(compteur2!=0)
				{
					//cout << endl;
					compteur2=0;
					cout << " | ";
				}
			}
			cout << endl;
		}
}

void determinisation_et_completion_automate_synchrone(Automate premier, char *txt, int y)
{
	tabdeter tableau2[15][100];
		int i;
		for(int yy=0; yy<100; yy++)
		{
			for(int ww=0; ww<15; ww++)
			{
				for(int zz=0; zz<10; zz++)
				{
					tableau2[ww][yy].tabtab[zz] = '.';
				}
			}
		}
		int cb = 0;
		for(cb=0; cb<premier.getetatinitiaux(); cb++)//2 ici remplace par le nombre d'etat initiaux ici 0,4
		{
			tableau2[0][0].tabtab[cb] = premier.getetatinitiaux2(cb)+48;
			//cout << "et la: " << tableau2[0][0].tabtab[cb] << endl;//important
		}
		premier.getnbsymboles();
		//cout << "n= " << n << endl;
		char a='o', b='u', c='i';
		int memoire = 0;
		char cara;
		char symb;
		int group=0;

		for(int q=1; q<=premier.getnbsymboles(); q++)
		{
			for(cb=0; cb<premier.getetatinitiaux(); cb++)// pour cb allant de 0 a 1 inclus donc pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(q);
					cara = tableau2[0][0].tabtab[cb];
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "tab2[][] " << group << endl;//important
							//cout << "C= " << c << endl;
							tableau2[q][0].tabtab[group] = c;
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
		}

		// maintenant automatisons ce processus pour tout le tableau

		int grandindice1 = 1;
		int grandindice2 = 0;
		int petitcompteur = 0;
		int compteur = 0;
		char tab[3];
		int taille = 0;
		int grand = 1;
		int w=0;
		int repetition = 0;
		//cout << "TAB =" <<  tableau2[2][0].tabtab[0] << endl;
		int erreur = 0;
		int g =0;
		i=0;
		do{
				a='o', b='u', c='i';
		do{
				if(w==2)
				{
					grandindice2++;
					w=-1;
				}
			w++;
			taille=0;
			for(compteur=0; compteur<=4; compteur++)
			{
				if(tableau2[w][grandindice2].tabtab[compteur] != '.')
				{
					tab[compteur] = tableau2[w][grandindice2].tabtab[compteur];// ici 1 2 4 apres faut 1 2 3
					taille++;//ici pour connaire le nombre d'etat dans la case donc 3
				}
				else
					tab[compteur] = '.';
			}
			if(tab[0] != '.')
				a = tab[0];
			if(tab[1] != '.')
				b = tab[1];
			if(tab[0] != '.')
				c = tab[2];

			repetition = 0;
			erreur = 0;
			for(g=0; g<20; g++)
			{
				if(tableau2[i][g].tabtab[0] == a)
				{
					if(tableau2[i][g].tabtab[1] == b)
					{
						if(tableau2[i][g].tabtab[2] == c)
						{
							repetition = 1;
							//cout << "c'est le cas BORDEL !" << a << b << c << endl;//important
						}
					}
				}
			}
			}while(repetition == 1);

			if(repetition==0)
				{
					//cout << "A= " << a << " B= " << b << " C= " << c << endl;
					if(a != '.' && a!='o' && a !='u' && a != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = a;//[0][1]
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = '.';
					}
					if(b != '.' && b!='o' && b !='u' && b != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = b;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = '.';
					}
					if(c != '.' && c!='o' && c !='u' && c != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = c;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = '.';
					}
				}
				grandindice1++;
			a = 'o';
			b = 'u';
			c = 'i';
			if(erreur == 0)
			{

			for(int qq=1; qq<=premier.getnbsymboles(); qq++)// pour a puis b
			{
			for(cb=0; cb<taille; cb++)// pour pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(qq);
					cara = tab[cb];//1,2,4
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "c " << c << endl;//important
							tableau2[qq][grand].tabtab[group] = c;//tableau[0,1,2][1]
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
						//cout << "w= " << w << endl;//important

					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
				a='o', b='u', c='i';
			}

			}
			grand++;

		}while(grandindice2<4);

		int jj =0;
		//completion
		for(int ii=0; ii<100; ii++)
		{
			if(tableau2[jj][ii].tabtab[0] == '.')
			{
				tableau2[jj][ii].tabtab[0] = 'P';
			}
			if(tableau2[jj+1][ii].tabtab[0] == '.')
			{
				tableau2[jj+1][ii].tabtab[0] = 'P';
			}
			if(tableau2[jj+2][ii].tabtab[0] == '.')
			{
				tableau2[jj+2][ii].tabtab[0] = 'P';
			}
		}
}

void determinisation_et_completion_automate_asynchrone(Automate premier, char *txt, int y)
{
	tabdeter tableau2[15][100];
		int i;
		for(int yy=0; yy<100; yy++)
		{
			for(int ww=0; ww<15; ww++)
			{
				for(int zz=0; zz<10; zz++)
				{
					tableau2[ww][yy].tabtab[zz] = '.';
				}
			}
		}
		int cb = 0;
		for(cb=0; cb<premier.getetatinitiaux(); cb++)//2 ici remplace par le nombre d'etat initiaux ici 0,4
		{
			tableau2[0][0].tabtab[cb] = premier.getetatinitiaux2(cb)+48;
			//cout << "et la: " << tableau2[0][0].tabtab[cb] << endl;//important
		}
		premier.getnbsymboles();
		//cout << "n= " << n << endl;
		char a='o', b='u', c='i';
		int memoire = 0;
		char cara;
		char symb;
		int group=0;

		for(int q=1; q<=premier.getnbsymboles(); q++)
		{
			for(cb=0; cb<premier.getetatinitiaux(); cb++)// pour cb allant de 0 a 1 inclus donc pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(q);
					cara = tableau2[0][0].tabtab[cb];
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "tab2[][] " << group << endl;//important
							//cout << "C= " << c << endl;
							tableau2[q][0].tabtab[group] = c;
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
		}

		// maintenant automatisons ce processus pour tout le tableau

		int grandindice1 = 1;
		int grandindice2 = 0;
		int petitcompteur = 0;
		int compteur = 0;
		char tab[3];
		int taille = 0;
		int grand = 1;
		int w=0;
		int repetition = 0;
		//cout << "TAB =" <<  tableau2[2][0].tabtab[0] << endl;
		int erreur = 0;
		int g =0;
		i=0;
		do{
				a='o', b='u', c='i';
		do{
				if(w==2)
				{
					grandindice2++;
					w=-1;
				}
			w++;
			taille=0;
			for(compteur=0; compteur<=4; compteur++)
			{
				if(tableau2[w][grandindice2].tabtab[compteur] != '.')
				{
					tab[compteur] = tableau2[w][grandindice2].tabtab[compteur];// ici 1 2 4 apres faut 1 2 3
					taille++;//ici pour connaire le nombre d'etat dans la case donc 3
				}
				else
					tab[compteur] = '.';
			}
			if(tab[0] != '.')
				a = tab[0];
			if(tab[1] != '.')
				b = tab[1];
			if(tab[0] != '.')
				c = tab[2];

			repetition = 0;
			erreur = 0;
			for(g=0; g<20; g++)
			{
				if(tableau2[i][g].tabtab[0] == a)
				{
					if(tableau2[i][g].tabtab[1] == b)
					{
						if(tableau2[i][g].tabtab[2] == c)
						{
							repetition = 1;
							//cout << "c'est le cas BORDEL !" << a << b << c << endl;//important
						}
					}
				}
			}
			}while(repetition == 1);

			if(repetition==0)
				{
					//cout << "A= " << a << " B= " << b << " C= " << c << endl;
					if(a != '.' && a!='o' && a !='u' && a != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = a;//[0][1]
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[0] = '.';
					}
					if(b != '.' && b!='o' && b !='u' && b != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = b;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[1] = '.';
					}
					if(c != '.' && c!='o' && c !='u' && c != 'i')
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = c;
					}
					else
					{
						tableau2[petitcompteur][grandindice1].tabtab[2] = '.';
					}
				}
				grandindice1++;
			a = 'o';
			b = 'u';
			c = 'i';
			if(erreur == 0)
			{

			for(int qq=1; qq<=premier.getnbsymboles(); qq++)// pour a puis b
			{
			for(cb=0; cb<taille; cb++)// pour pour 0 et 4
			{// pour la 1ere ligne du tableau determines
					symb = tabchar(qq);
					cara = tab[cb];//1,2,4
					//cout << "symb = " << symb << " , cara = " << cara << endl;//important
					do{
						if(a=='o' && b=='u' && c=='i')
						{

						}else
						{
							//cout << "c " << c << endl;//important
							tableau2[qq][grand].tabtab[group] = c;//tableau[0,1,2][1]
							group++;
						}
						a = premier.getnbtransitions(symb, 1, y, cara, memoire);//0
						b = premier.getnbtransitions(symb, 2, y, cara, memoire);//a
						c = premier.getnbtransitions(symb, 3, y, cara, memoire);//1  // ici memoire = 0
						memoire = premier.getnbtransitions(symb, 4, y, cara, memoire);
						memoire++;
						//cout << "1: " << a << " 2: " << b << " 3: " << c << endl;//important
						//cout << "w= " << w << endl;//important

					}while(a!='o' || b!='u' || c!='i');// probleme retourner le bon indice quand ca se trouve vers la fin
					memoire = 0;
				}
				group = 0;
				a='o', b='u', c='i';
			}

			}
			grand++;

		}while(grandindice2<4);

		int jj =0;
		//completion
		for(int ii=0; ii<100; ii++)
		{
			if(tableau2[jj][ii].tabtab[0] == '.')
			{
				tableau2[jj][ii].tabtab[0] = 'P';
			}
			if(tableau2[jj+1][ii].tabtab[0] == '.')
			{
				tableau2[jj+1][ii].tabtab[0] = 'P';
			}
			if(tableau2[jj+2][ii].tabtab[0] == '.')
			{
				tableau2[jj+2][ii].tabtab[0] = 'P';
			}
		}
}

char tabchar(int i)
{
	if(i==1)
		return 'a';
	if(i==2)
		return 'b';
	if(i==3)
		return 'c';
	if(i==4)
		return 'd';
	if(i==5)
		return 'e';
	if(i==6)
		return 'f';
	return '\n';
}

char tabchar2(int i)
{
	if(i==0)
		return '0';
	if(i==1)
		return '1';
	if(i==2)
		return '2';
	if(i==3)
		return '3';
	if(i==4)
		return '4';
	if(i==5)
		return '5';
	if(i==6)
		return '6';
	return '\n';
}

void determinisationetcompletion(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere) // j indice, i taille max du tab
{
	int verif = 0;

	ifstream fichier("Z3AF01.txt", ios::in);  // on ouvre

	if(fichier)
	{
		while(fichier.get(caractere))  // on lit un caract�re et on le stocke dans caractere
		{
			cpt++;
			if(caractere == '\n')
			{
				fichier.get(caractere);
				cout << "\n";
			}
			if(caractere == 32) // 32 en code ascii signie espace
			{
				fichier.get(caractere);
				cout << " ";
			}
			if(cpt>=1 && cpt <=2)
			{
				premier.stocker(cpt, caractere);
			}
			else{
				if(cpt==3) // ligne 3
				{
					j = (caractere-48);
					premier.setetatinitiaux(j);
					numetatinitiaux = new int[j];
					x = j+3;
				}
				else if(cpt <= (j+3)) // leurs numeros
				{
					numetatinitiaux[i] = caractere-48;
					i++;
				}
				if(cpt == x+1) // ici x = 5 // cad ligne 4
				{
					i=0;
					k = (caractere-48); // k=2
					premier.setetaterminaux(k);
					numetatterminaux = new int[k];
					if(m==0)
					{
						m = cpt + caractere-48;// m=8
						//cout << "m= " << m << endl;
					}
				}
				if(cpt > x+1 && cpt <= m) // leurs numeros ligne 4 x=5 m=8
				{
					numetatterminaux[i] = caractere-48;
					i++;
				}
				if(cpt == m+1) //ligne 5
				{
					mem = caractere - 48; // mem sauvegarde la valeur initiale, si jamais le nb de transitions est un chiffre et non un nb
					if(caractere != '\n')
					{
						fichier.get(caractere);
						if(caractere == '\n')// cas ou c'est un chiffre, on garde donc la valeur sauvegarde mem
						{
							n = mem;
						}
						else// cas ou c'est un nb, alors sauvegarde le nb par l'op suivante
						{
							n = mem*10 + caractere-48 ;
						}
					}
					//n = caractere - 48; // ici n=5
					transitions = new char[n*3]; //ligne ici y
					y++;
				}
				else if(cpt > m+1 && cpt <= 3*n+m+1 ) //leurs numeros
				{
					transitions[y-1] = caractere;
					y++;
				}
			}
			if(n>9)//pour afficher le nb de transitions (=n)
			{
				if(verif==0)// pour pas afficher n pour toute les transitions, mais seulement une seule fois
				{
					cout << n;
					verif++;
				}
			}
		}
		fichier.close();
		cout << endl;
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}

	premier.remplir1();
	premier.stockertab1(numetatinitiaux, j);
	premier.stockertab2(numetatterminaux, k);
	premier.stockertab3(transitions, y);

	premier.setnbtransitions5(y);
	//cout << "x = " << premier.getnbtransitions5() << endl;

	//tabdeter tableau2[3][100];
	// la commence la determinisation et completion
	if(premier.est_un_automate_asynchrone(y))
	{
		determinisation_et_completion_automate_asynchrone(premier, y);
		cout << "L'automate a ete determinise et complete !" << endl;
	}
	else//fin si automate asynchrone
	{
		cout << "L'automate est synchrone !" << endl;
		if(premier.est_un_automate_deterministe(y))
		{
			cout << "L'automate est deterministe !" << endl;
			if(premier.est_un_automate_complet(y))
			{
				cout << "L'automate est deterministe et complet, AFDC" << endl;
			}
			else
			{
				//cout << "L'automate n'est pas complet, pour les liaisons suivantes" << endl;
				completion(y, premier);
				cout << "L'automate est deterministe et a ete complete, AFDC" << endl;
			}
		}
		else
		{
			cout << "L'automate est non deterministe ! On va le determiniser et le completer !" << endl;
			determinisation_et_completion_automate_synchrone(premier, y);
			cout << "L'automate a ete determinise et complete !" << endl;
		}
	}
	afficher_automate_deterministe_complet(premier, y);
}

void reconnaissancemots(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere)
{
	int verif = 0;
	premier.remplir1();
	premier.remplir2();
	ifstream fichier("Z3AF01.txt", ios::in);  // on ouvre

	if(fichier)
	{
		while(fichier.get(caractere))  // on lit un caract�re et on le stocke dans caractere
		{
			cpt++;
			if(caractere == '\n')
			{
				fichier.get(caractere);
				cout << "\n";
			}
			if(caractere == 32) // 32 en code ascii signie espace
			{
				fichier.get(caractere);
				cout << " ";
			}
			if(cpt>=1 && cpt <=2)
			{
				premier.stocker(cpt, caractere);
			}
			else{
				if(cpt==3) // ligne 3
				{
					j = (caractere-48);
					premier.setetatinitiaux(j);
					numetatinitiaux = new int[j];
					x = j+3;
				}
				else if(cpt <= (j+3)) // leurs numeros
				{
					numetatinitiaux[i] = caractere-48;
					i++;
				}
				if(cpt == x+1) // ici x = 5 // cad ligne 4
				{
					i=0;
					k = (caractere-48); // k=2
					premier.setetaterminaux(k);
					numetatterminaux = new int[k];
					if(m==0)
					{
						m = cpt + caractere-48;// m=8
						//cout << "m= " << m << endl;
					}
				}
				if(cpt > x+1 && cpt <= m) // leurs numeros ligne 4 x=5 m=8
				{
					numetatterminaux[i] = caractere-48;
					i++;
				}
				if(cpt == m+1) //ligne 5
				{
					mem = caractere - 48; // mem sauvegarde la valeur initiale, si jamais le nb de transitions est un chiffre et non un nb
					if(caractere != '\n')
					{
						fichier.get(caractere);
						if(caractere == '\n')// cas ou c'est un chiffre, on garde donc la valeur sauvegarde mem
						{
							n = mem;
						}
						else// cas ou c'est un nb, alors sauvegarde le nb par l'op suivante
						{
							n = mem*10 + caractere-48 ;
						}
					}
					//n = caractere - 48; // ici n=5
					transitions = new char[n*3]; //ligne ici y
					y++;
				}
				else if(cpt > m+1 && cpt <= 3*n+m+1 ) //leurs numeros
				{
					transitions[y-1] = caractere;
					y++;
				}
			}
			if(n>9)//pour afficher le nb de transitions (=n)
			{
				if(verif==0)// pour pas afficher n pour toute les transitions, mais seulement une seule fois
				{
					cout << n;
					verif++;
				}
				else
				{
					cout << caractere;  // on l'affiche
				}
			}
			else
				cout << caractere;  // on l'affiche
		}
		fichier.close();
		cout << endl;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	premier.stockertab1(numetatinitiaux, j);
	premier.stockertab2(numetatterminaux, k);
	premier.stockertab3(transitions, y);

	premier.setnbtransitions5(y-1);
	// continuer ici pour reconnaissance de mot
	char mac2[20] = {'.'};
	string mots;
	cout << "Saisir le ou les mots que vous voulez reconnaitre, si vous voulez saisir plusieurs mots, alors separer chaque mot par un point, pour le mot vide saisir *" << endl;
	cin >> mac2;
	mots = mac2;
	cout << endl;
	int taille = mots.size();
	//cout << taille << endl;

	char mac[taille];
	int s = 0;
	for(s=0; s<taille; s++)
	{
		mac[s] = mac2[s];
	}
	if(premier.reconnaitre_mot(mac, taille))
	{
		cout << "Mot RECONNU" << endl;
	}
	else
	{
		cout << "Mot non reconnu" << endl;
	}
}

void afficher(Automate premier, char *txt, unsigned int &cpt, unsigned int &i, unsigned int &j, unsigned int &x, unsigned int &k, unsigned int &m, unsigned int &n, unsigned int &y, unsigned int &mem, unsigned int &choix, int* numetatinitiaux, int* numetatterminaux, char* transitions, char &caractere)
{
	int verif = 0;
	ifstream fichier(txt, ios::in);  // on ouvre

	if (!fichier)
		cout << "Error reading file" << endl;
	if(fichier)
	{
		while(fichier.get(caractere))  // on lit un caract�re et on le stocke dans caractere
		{
			cpt++;
			if(caractere == '\n')
			{
				fichier.get(caractere);
				cout << "\n";
			}
			if(caractere == 32) // 32 en code ascii signie espace
			{
				fichier.get(caractere);
				cout << " ";
			}
			if(cpt>=1 && cpt <=2)
			{
				premier.stocker(cpt, caractere);
			}
			else{
				if(cpt==3) // ligne 3
				{
					j = (caractere-48);
					premier.setetatinitiaux(j);
					numetatinitiaux = new int[j];
					x = j+3;
				}
				else if(cpt <= (j+3)) // leurs numeros
				{
					numetatinitiaux[i] = caractere-48;
					i++;
				}
				if(cpt == x+1) // ici x = 5 // cad ligne 4
				{
					i=0;
					k = (caractere-48); // k=2
					premier.setetaterminaux(k);
					numetatterminaux = new int[k];
					if(m==0)
					{
						m = cpt + caractere-48;// m=8
						//cout << "m= " << m << endl;
					}
				}
				if(cpt > x+1 && cpt <= m) // leurs numeros ligne 4 x=5 m=8
				{
					numetatterminaux[i] = caractere-48;
					i++;
				}
				if(cpt == m+1) //ligne 5
				{
					mem = caractere - 48; // mem sauvegarde la valeur initiale, si jamais le nb de transitions est un chiffre et non un nb
					if(caractere != '\n')
					{
						fichier.get(caractere);
						if(caractere == '\n')// cas ou c'est un chiffre, on garde donc la valeur sauvegarde mem
						{
							n = mem;
						}
						else// cas ou c'est un nb, alors sauvegarde le nb par l'op suivante
						{
							n = mem*10 + caractere-48 ;
						}
					}
					//n = caractere - 48; // ici n=5
					transitions = new char[n*3]; //ligne ici y
					y++;
				}
				else if(cpt > m+1 && cpt <= 3*n+m+1 ) //leurs numeros
				{
					transitions[y-1] = caractere;
					y++;
				}
			}
			if(n>9)//pour afficher le nb de transitions (=n)
			{
				if(verif==0)// pour pas afficher n pour toute les transitions, mais seulement une seule fois
				{
					cout << n;
					verif++;
				}
				else
				{
					cout << caractere;  // on l'affiche
				}
			}
			else
				cout << caractere;  // on l'affiche
		}
		fichier.close();
		cout << endl;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	premier.stockertab1(numetatinitiaux, j);
	premier.stockertab2(numetatterminaux, k);
	premier.stockertab3(transitions, y);

	premier.lireAutomate4();
	premier.lireAutomate1(j);
	premier.lireAutomate2(k);
	premier.lireAutomate3(y);

	premier.setnbtransitions5(y);
}

int main(int ac, char **av)
{
	Automate premier;

	if (ac != 2)
	{
		cout << "Please put a param" << endl;
		return (0);
	}
	char caractere = 'x';  // notre variable o� sera stock� le caract�re
	unsigned int cpt=0, i=0, j=0, x=0, k=0, m=0, n=0, y=0, mem=0, choix;
	int *numetatinitiaux = NULL, *numetatterminaux = NULL;
	char *transitions = NULL;
	do{
		cout << "                        -----------------------\n                       |                       |\n                       |          Menu:        |     \n    \n\n1)Lecture d'un automate et sauvegarde en memoire\n2)Determinisation et completion\n3)Reconnaissance de mots\n4)Langage complementaire\n0)Arreter le programme" << endl;
		cin>>choix;
		cout << endl;
		switch(choix)
		{
			case 0 : break;

			case 1 : afficher(premier, av[1], cpt, i, j, x, k, m, n, y, mem, choix, numetatinitiaux, numetatterminaux, transitions, caractere);
			cpt=0, i=0, j=0, x=0, k=0, m=0, n=0, y=0, mem=0, caractere = 'x', numetatinitiaux = NULL, numetatterminaux = NULL, transitions = NULL;
			break;

			case 2 : determinisationetcompletion(premier, av[1], cpt, i, j, x, k, m, n, y, mem, choix, numetatinitiaux, numetatterminaux, transitions, caractere);
			cpt=0, i=0, j=0, x=0, k=0, m=0, n=0, y=0, mem=0, caractere = 'x', numetatinitiaux = NULL, numetatterminaux = NULL, transitions = NULL;
			break;

			case 3 : reconnaissancemots(premier, av[1], cpt, i, j, x, k, m, n, y, mem, choix, numetatinitiaux, numetatterminaux, transitions, caractere);
			cpt=0, i=0, j=0, x=0, k=0, m=0, n=0, y=0, mem=0, caractere = 'x', numetatinitiaux = NULL, numetatterminaux = NULL, transitions = NULL;
			break;

			case 4 : langagecomplementaire(premier, av[1], cpt, i, j, x, k, m, n, y, mem, choix, numetatinitiaux, numetatterminaux, transitions, caractere);
			cpt=0, i=0, j=0, x=0, k=0, m=0, n=0, y=0, mem=0, caractere = 'x', numetatinitiaux = NULL, numetatterminaux = NULL, transitions = NULL;
			break;

		}

	}while (choix!=0);

	return 0;
}
