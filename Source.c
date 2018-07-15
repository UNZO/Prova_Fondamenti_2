#define _CRT_SECURE_NO_WARNINGS
#define numFilm 6
#define numNoleggi 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//mie funzioni

char Elimina(char S[], char C);

int PrecedenteConsonante(char S[], char C);

int PrecedenteConsonante_RIC(char S[], char C);

int NumeroFilm(char Genere[], int CodiceCliente);

void Bubble();

int durataMagMin(int a, int b);

void StampaOgniGenere();

void getGenereGiorni(int codFilm, char Genere[], int *tempo);

int eNoleggiato(int CodFilm);

void Minima();

//meistruct

typedef struct {
	int CodFilm;
	char Genere[31];
	int Durata;
}TipoFilm;

typedef struct {
	int CodCliente;
	int CodFilm;
	int NumGiorni;
}TipoNoleggio;

TipoFilm Film[numFilm] = {
	{100,"AZIONE",120},
{ 101,"AZIONE",130 },
{ 102,"AZIONE",120 },
{ 103,"COMICO",120 },
{ 104,"COMICO",130 },
{ 105,"GIALLO",120 },
};

TipoNoleggio Noleggio[numNoleggi] = {
	{13,100,10},
	{13,104,21},
{13,102,31},
{13,105,10},
{55,104,1},
{23,102,4},
{55,102,7},
{23,101,9},
{55,105,6},
{23,104,4},
};

void main()
{
	//ESERCIZIO 1
	int cEliminato;
	int c;
	int tempo = 0;
	char Genere[100];
	cEliminato=Elimina("premio", 'g');
	printf("Il carattere eliminato e :%c", cEliminato);
	//ESERCIZIO 2

	c=PrecedenteConsonante_RIC("azz", 'z');
	printf("Il risultato bool è :%d", c);
	//ESERCIZIO 3

	c=NumeroFilm("COMICO", 13);
	printf("Il numero di film e :%d", c);

	//esercizio 4

	Bubble();
	
	//esercizio 5

	StampaOgniGenere();

	Minima();

	printf("**********************************");
	int x;
	x = 2;
	printf("%d", (x % 5));

	getchar();
	getchar();
}

char Elimina(char S[], char C)
{
	//modifica la stringa S eliminando solo il pimo carattere che precede alfabeticamente il carattere C altrimenti S rimane inalterat
	//returna il carattere eliminato oppure @ se resta inalterata
	int len = strlen(S);
	int i,j=0,primoEliminato=0;
	char cEliminato = '@';
	char temp[100];
	for (i = 0;i < len;i++)//scannerizzo tutta la stringa
	{
		if (S[i] >= C)//se il carattere non va eliminato
		{
			//copio in temp
			temp[j] = S[i];
			j++;
		}
		if ((S[i] < C)&&(!primoEliminato))//se devo eliminre
		{
			//non copio in temp
			primoEliminato = 1;//dopo la prima eliminazione mi chiudo fuori
			cEliminato = S[i];//salvo il carattere eliminato
		}
	}
	return cEliminato;
}

int PrecedenteConsonante(char S[], char C)
{
	//restituisce 1 se il carattere Cè in S immediatamente prima di una consonante altrimenti returna 0
	int bool=0;
	int len = strlen(S);
	int i;
	
	for (i = 0;i < len;i++)
	{
		if ((S[i] == C) && (S[i + 1] != 'a') && (S[i + 1] != 'e') && (S[i + 1] != 'i') && (S[i + 1] != 'o') && (S[i + 1] != 'u'))//se  è la situazione giusta
		{
			bool = 1;//ovvero trovato
			break;
		}
	}
	return bool;
}

int PrecedenteConsonante_RIC(char S[], char C)
{
	int bool = 0;

	if (S[0] == '\0')//stringa è vuota?
	{
		return bool;
	}

	if ((S[0] == C) && (S[1] != 'a') && (S[1] != 'e') && (S[1] != 'i') && (S[1] != 'o') && (S[1] != 'u'))//se  è la situazione giusta
	{
		bool = 1;
		return bool;
	}

	//se non ho trovato ancora nulla vado avanti di 1
	PrecedenteConsonante_RIC(S+1, C);

}

int NumeroFilm(char Genere[], int CodiceCliente)
{
	//dato un genere e un codice cliente restituisca il numero di film di uel genere con durata maggiore di 120 noleggiati dal cliente dato
	int numDurata120 = 0;
	int i,j;

	for (i = 0;i < numNoleggi;i++)
	{
		if (Noleggio[i].CodCliente == CodiceCliente)//se ho trovato un noleggio fatto dal cliente giusto vado a controllare tra tutti i film per il genree e anche per il codice film
		{
			for (j = 0; j < numFilm;j++)//controllo tutti i film con  quel codice
			{
				if ((strcmp(Film[j].Genere, Genere) == 0)&&(Film[j].CodFilm==Noleggio[i].CodFilm))//se il genere è giusto e anche il codice
				{
					//aggiorno il numero di film don durata maggiore di 120
					if (Film[j].Durata > 120)
					{
						numDurata120++;
					}
				}
			}
		}
	}
	return numDurata120;
}

void Bubble()
{
	int i, j;
	TipoFilm temp;
	TipoNoleggio tempNol;
	
	for (i = 0;i < numFilm - 1;i++)//bubble ordino per durata in ordine dal più grande al più piccolo
	{
		for (j = 0;j < numFilm- 1 - i;j++)
		{
			if (Film[j].Durata<Film[j + 1].Durata)
			{
				temp = Film[j];
				Film[j] = Film[j + 1];
				Film[j + 1] = temp;
			}
		}
	}

	//adesso mi sposto in noleggi

	for (i = 0;i < numNoleggi-1;i++)//passo tra tutti i noleggi
	{
		for (j = 0;j < numNoleggi - 1 - i;j++)
		{
			if ((Noleggio[j].CodCliente>Noleggio[j+1].CodCliente)||(durataMagMin(Noleggio[j].CodFilm, Noleggio[j+1].CodFilm)))//effettuo uno scambiop se il codice cliente 1 è > del 2 oppure se il primo dura < del secondo 
			{
				tempNol = Noleggio[j];
				Noleggio[j] = Noleggio[j + 1];
				Noleggio[j + 1] = tempNol;
			}
		}
	}
}//non funziona//non funziona pace

int durataMagMin(int a, int b)
{
	int bool=0;
	int i;
	int d1=0, d2=0;

	for (i = 0;i < numFilm;i++)
	{
		if (Film[i].CodFilm==a)//trovato film1
		{
			d1 = Film[i].Durata;
		}
	}
	for (i = 0;i < numFilm;i++)
	{
		if (Film[i].CodFilm == b)//trovato film1
		{
			d2 = Film[i].Durata;
		}
	}
	//ora che so le 2 durate 
	if (d1 < d2)//bisogna effettuare lo scambio
	{
		bool = 1;
		return bool;
	}
	if (d1 >= d2)//bisogna effettuare lo scambio
	{
		bool = 0;
		return bool;
	}
}//non funziona pace

void StampaOgniGenere()
{
	//ordino per genere con il bubble
	int i, j;
	int bool;
	int tempo,tempoTot=0;
	int numero,numeroTot=0;
	char Genere[100];
	TipoFilm temp;
	for (i = 0;i < numFilm - 1;i++)
	{
		for (j = 0;j < numFilm - 1 - i;j++)
		{
			if (strcmp(Film[j].Genere, Film[j+1].Genere)<0)
			{
				temp = Film[j];
				Film[j] = Film[j + 1];
				Film[j + 1] = temp;
			}
		}
	}
	//una volta ordinato controllo fino a che non cambio e stampo quando cambia
	for (i = 0;i < numFilm;i++)
	{	
		//calcolo le volte che un film di un determinato genere viene noleggiato
		if (eNoleggiato(Film[i].CodFilm))
		{
			//se è noleggiato incremento il contatore
			numeroTot++;
		}

		if (strcmp(Film[i].Genere, Film[i + 1].Genere) == 0)
		{
			tempo = 0;
			numero = 0;
			getGenereGiorni(Film[i].CodFilm, Genere, &tempo);

			tempoTot = tempoTot + tempo;

		}

		
		if (strcmp(Film[i].Genere, Film[i + 1].Genere) != 0)//ho finito tutti i genere uguli sono pronto per stampare la stringa SOLO QUANDO CAMBIA
		{
			//calcolo noleggio sommativo con funzione
			tempo = 0;
			numero = 0;
			getGenereGiorni(Film[i].CodFilm, Genere, &tempo);

			tempoTot = tempoTot + tempo;

				//ora stampo perchè ho uttto
				printf("\nGenere= %s:  %d film noleggiati,  per un totale di %d giorni", Film[i].Genere,numeroTot,tempoTot);

				tempoTot = 0;
				numeroTot = 0;

		}
	}
}

void getGenereGiorni(int codFilm, char Genere[], int *tempo)
{
	//trovo prima di tutto il genere del film
	int i;
	for (i = 0;i < numFilm;i++)
	{
		if (Film[i].CodFilm == codFilm)
		{
			strcpy(Genere, Film[i].Genere);
		}
	}
	//adesso calcolo il numero di giorni totali di noleggio
	for (i = 0;i < numNoleggi;i++)
	{
		if (Noleggio[i].CodFilm == codFilm)
		{
			//se trovo che il film è stato noleggiato
			*tempo = *tempo + Noleggio[i].NumGiorni;
		}
	}
}


int eNoleggiato(int CodFilm)
{
	int i;
	int bool=0;

	for (i = 0;i < numNoleggi;i++)
	{
		if (Noleggio[i].CodFilm==CodFilm)//allora il film è stato noleggiato almeno una volta	
		{
			bool = 1;
			return bool;
		}
	}
	return bool;
}

void Minima()
{
	int minimo = 999990;
	int i=0,x,k,contGnere=0;
	char genere[100];
	int bool = 1;//va a 0 se non ci sono piu film da controllare

	for(x=0;(x<numFilm)&&(i<numFilm);x++)
	{
		for (;(i < numFilm)&&(bool);i++)
		{
			//calcolo durata minima di un singolo genere
			if (Film[i].Durata < minimo)//aggiorno minimo
			{
				minimo = Film[i].Durata;
			}	
			if (strcmp(Film[i].Genere, Film[i + 1].Genere) != 0)//se sto per cambiare genere esco
			{
				strcpy(genere, Film[i].Genere);
				bool = 0;
			}
			//ora che ho il genere e la durata minima stampo òla prima stringa
		}
		printf("\n\nGenere = %s  Durata Minima del Film= %d", Film[i-1].Genere, minimo);
		//ora cerco i codice film di quel genere e di quella durata minimna
		for (k = 0;k < numFilm;k++)
		{
			if ((Film[k].Durata == minimo) && (strcmp(Film[k].Genere, genere)==0))
			{
				printf("\nFilm %d", Film[k].CodFilm);
			}
		}
		genere[0] = '\0';
		minimo = 999999;
		bool = 1;
	}
}