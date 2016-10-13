#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define MAX 100000
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
	int i,j, anzahlZuege, Umsteigzeit, von, zu;
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
	printf("%d",anzahlSendung);
	
	for(i=1;i<=anzahlSendung;i++){
		// Erstellen Matrix für DAG
		int * Eingangsgrad = GenerateIntVect( anzahlKnoten+1 );
		int ** AdjMat = GenerateIntMat( anzahlKnoten+1, anzahlKnoten+1 );
		int ** Kantengewicht = GenerateIntMat( anzahlKnoten + 1, anzahlKnoten + 1 );
		//Typ A Kanten setzten
		for(j=1;j<=anzahlFahrlagen;j++){
			if(Zug[j].start==Sendung[i].start && Zug[j].zeitStart>Sendung[i].zeitStart){
				von=(2*anzahlFahrlagen+1);
				AdjMat[von][0]++;
				AdjMat[von][AdjMat[von][0]]=j;
				Eingangsgrad[j]++;
			}
		}
		printf("\nZug Nummer:%d",i);
		ShowIntMat ( 1, anzahlFahrlagen, 0, anzahlFahrlagen, AdjMat, " AdjMat" );
		ShowIntMat ( 1, anzahlFahrlagen, 0, anzahlFahrlagen, Kantengewicht, "Kantengewicht" );
		ShowIntVect ( 1, anzahlFahrlagen, Eingangsgrad, "Eingansgrad" );
		FreeIntMat( anzahlKnoten+1, Kantengewicht );
		FreeIntMat( anzahlKnoten+1, AdjMat );
		free ( Eingangsgrad );
	}
		
		
		
		

		//Typ B Kanten setzten
		//Typ C Kanten setzten
		//Typ D Kanten setzten
		


	

	
	
	
	
/*



// Typ A Kanten
// im Startbahnhof	suche Ereignis welche von frühste start zeit aus möglich


// Typ B Kanten
	for(i=1;i<=anzahlZuege;i++){
		AdjMat[i][0]=1;
		AdjMat[i][1]=anzahlZuege+i;
		Eingangsgrad[anzahlZuege+i]++; //601-1200
	}
// Typ C Kanten
	for(i=1;i<=anzahlZuege;i++){
		for(j=1;j<=anzahlZuege;j++){
			if(Zug[i].zeitZiel+Umsteigzeit<Zug[j].zeitStart && Zug[i].ziel==Zug[j].start){
				AdjMat[anzahlZuege+i][0]++;
				Eingangsgrad[j]++; //1-600
				AdjMat[anzahlZuege+i][AdjMat[anzahlZuege+i][0]]=j;
			}	
		}
	}
// Typ D Kanten 
//im Zielbahnhof suche ereignis welche ereignis noch zeitlich ankommt
	for(i=1;i<=anzahlZuege;i++){
		if(Zug[i].ziel==Sendung.ziel && Zug[i].zeitZiel<Sendung.zeitZiel){
			von = i+anzahlZuege;
			zu = 2*anzahlZuege+2; 
			AdjMat[von][0]++;
			AdjMat[von][AdjMat[von][0]]=zu;
			Eingangsgrad[zu]++; //1202
			Kantengewicht[von][zu]=Zug[i].zeitZiel;
		}
	}


// DAG

	int startKnoten = 2*anzahlZuege+1;
	int * WeglaengeZuKnoten = GenerateIntVect ( anzahlKnoten + 1 );
	int * Vorgaenger = GenerateIntVect ( anzahlKnoten+1 );

	DAG ( anzahlKnoten, AdjMat, Kantengewicht, Eingangsgrad, startKnoten, -1, Vorgaenger, WeglaengeZuKnoten, 0 );


	ShowShortestPath ( anzahlKnoten, AdjMat, startKnoten, 1202, Vorgaenger, WeglaengeZuKnoten );
	
	
	free (WeglaengeZuKnoten);
	free (Vorgaenger);

*/
	free(Sendung);
	free(Zug); 
	return 0; 
}

