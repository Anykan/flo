#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define MAX 1000000
#include "conv.h"
#include "dag.h"


struct Zuege{
	int start;
	int ziel;
	int zeitStart;
	int zeitZiel;
	int maxAnzahlWagen;
	int restKap;
	int anzahlSendungen;
	int * Sendungen;
};
struct Sendungen{
	int start;
	int ziel;
	int zeitStart;
	int zeitZiel;
	int anzahlWagen;
	int anzahlZuege;
};


int main(int  argc, char ** argv )
{
	int i,j,s, anzahlZuege, Umsteigzeit, von, zu, fahrzeit;
	int anzahlFahrlagen, anzahlSendung;
	system("cls");
	//Überprüfe Argumente
	if ( 2 != argc ) 
	{
		printf("\nProgrammaufruf: flo.exe datei.txt \n"); 
		return 1; 
	}

	//Einlesen aus Datei
	FILE * file_data = fopen( argv[ 1 ], "r" );
	if( file_data == 0 )
	{
		printf("\n Problem: Datei %s konnte nicht geoeffnet werden.\n", argv[ 1 ] );
		return 1;
	}
	
	// Schreibe Daten in Sturktur
	fscanf(file_data, "%d", &anzahlFahrlagen );
	struct Zuege * Zug = ( struct Zuege * ) calloc ( anzahlFahrlagen+1, sizeof( struct Zuege ) );
	for( i = 1; i <= anzahlFahrlagen; i++ ){
		fscanf(file_data,"%d", &(Zug[i]).start);
		fscanf(file_data,"%d", &(Zug[i]).ziel);
		fscanf(file_data,"%d", &(Zug[i]).zeitStart);
		fscanf(file_data,"%d", &(Zug[i]).zeitZiel);
		fscanf(file_data,"%d", &(Zug[i]).maxAnzahlWagen);
		Zug[i].restKap = Zug[i].maxAnzahlWagen;
	}
	fscanf( file_data, "%d", &anzahlSendung );
	struct Sendungen * Sendung = ( struct Sendungen * ) calloc ( anzahlSendung+1, sizeof( struct Sendungen ) );
	for( i = 1; i <= anzahlSendung; i++ ){
		fscanf(file_data, "%d",&(Sendung[i]).start);
		fscanf(file_data,"%d", &(Sendung[i]).ziel);
		fscanf(file_data,"%d", &(Sendung[i]).zeitStart);
		fscanf(file_data,"%d", &(Sendung[i]).zeitZiel);
		fscanf(file_data,"%d", &(Sendung[i]).anzahlWagen);		
	}
	fscanf(file_data, "%d", &Umsteigzeit);
	fclose( file_data );
	int anzahlKnoten = (2*anzahlFahrlagen)+2;
	
	for(s=1;s<=anzahlSendung;s++){
	// Erstellen Matrix für DAG
		int * Eingangsgrad = GenerateIntVect( anzahlKnoten+1 );
		int ** AdjMat = GenerateIntMat( anzahlKnoten+1, anzahlKnoten+1 );
		int ** Kantengewicht = GenerateIntMat( anzahlKnoten + 1, anzahlKnoten + 1 );
		//Start Typ A
		for(j=1;j<=anzahlFahrlagen;j++){
			if(Zug[j].start==Sendung[s].start && Zug[j].zeitStart>Sendung[s].zeitStart){
				von=(2*anzahlFahrlagen+1);
				AdjMat[von][0]++;
				AdjMat[von][AdjMat[von][0]]=j;
				Eingangsgrad[j]++;
			}
		}
		//Ende Typ A
		//Start Typ B
		for(i=1;i<=anzahlFahrlagen;i++){
			fahrzeit=Zug[i].zeitZiel-Zug[i].zeitStart;
			zu = anzahlFahrlagen+i;
			AdjMat[i][0]=1;
			AdjMat[i][1]=zu;
			Eingangsgrad[zu]++; 
			Kantengewicht[i][zu]=fahrzeit;
		}
		//Ende Typ B
		//Start Typ C
		for(i=1;i<=anzahlFahrlagen;i++){
			for(j=1;j<=anzahlFahrlagen;j++){
				if(Zug[i].zeitZiel+Umsteigzeit<Zug[j].zeitStart && Zug[i].ziel==Zug[j].start){
					AdjMat[anzahlFahrlagen+i][0]++;
					Eingangsgrad[j]++;
					AdjMat[anzahlFahrlagen+i][AdjMat[anzahlFahrlagen+i][0]]=j;
				}	
			}
		}
		//Ende Typ C
		//Start Typ D
		for(i=1;i<=anzahlFahrlagen;i++){
			fahrzeit=Zug[i].zeitZiel-Zug[i].zeitStart;
			von = i+anzahlFahrlagen;
			zu = 2*anzahlFahrlagen+2; 
			if(Zug[i].ziel==Sendung[s].ziel && Zug[i].zeitZiel<Sendung[s].zeitZiel){
				AdjMat[von][0]++;
				AdjMat[von][AdjMat[von][0]]=zu;
				Eingangsgrad[zu]++;
				Kantengewicht[von][zu]=fahrzeit;
			}else{
				Kantengewicht[von][zu]=MAX; // wenn kein direkter weg
			}
		}
		//Ende Typ D
		
		// Start setzte Kosten Zugfahrkanten
		for (i=1;i<=anzahlZuege;i++){

			if (Sendung[s].anzahlWagen<=Zug[i].restKap<Zug[i].maxAnzahlWagen){
			printf ("penis");
			}
		}
		ShowIntMat ( 1, 2*anzahlFahrlagen+2, 0, 2*anzahlFahrlagen+2, AdjMat, " AdjMat" );
		ShowIntMat ( 1, 2*anzahlFahrlagen, 0, 2*anzahlFahrlagen+2, Kantengewicht, "Kanten" );
//	Break();
		
		
		// DAG
		int startKnoten = 2*anzahlFahrlagen+1;
		int zielKnoten = 2*anzahlFahrlagen+2;
		int * WeglaengeZuKnoten = GenerateIntVect ( anzahlKnoten + 1 );
		int * Vorgaenger = GenerateIntVect ( anzahlKnoten+1 );
		DAG ( anzahlKnoten, AdjMat, Kantengewicht, Eingangsgrad, startKnoten, -1, Vorgaenger, WeglaengeZuKnoten, 0 );
		printf("\n\n********************************************************************\n");
		printf("\nSendung Nr.:%d\n",s);
		printf("Trassen: ");
		ShowShortestPath ( anzahlKnoten, AdjMat, startKnoten, zielKnoten, Vorgaenger, WeglaengeZuKnoten );

		free (WeglaengeZuKnoten);
		free (Vorgaenger);
		FreeIntMat( anzahlKnoten+1, Kantengewicht );
		FreeIntMat( anzahlKnoten+1, AdjMat );
		free ( Eingangsgrad );
	}
	free(Sendung);
	free(Zug); 
	return 0; 
}


/*



*/


