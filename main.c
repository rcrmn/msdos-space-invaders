/* Roc Ramon Currius */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "RutinesINVADERS_v1.h"




#define URL_PUNTS "puntuacions.txt"

////////////////////// Retras entre cada bucle //////////////////////
#define RETRAS 30

////////////////////// Mides de la pantalla //////////////////////
#define AMPLADA_PANTALLA (AmpladaPantalla)
#define ALTURA_PANTALLA (AlssadaPantalla)

////////////////////// Mida d'un personatge //////////////////////
#define TAMANY_PERSONATGE 3

////////////////////// Mides de la matriu d'aliens //////////////////////
#define FILES_ALIENS 5
#define COLUMNES_ALIENS 9
#define TAMANY_ALIEN TAMANY_PERSONATGE
#define SEPARACIO_ALIENS 2

#define AMPLADA_ALIENS (COLUMNES_ALIENS*TAMANY_ALIEN + (COLUMNES_ALIENS-1)* SEPARACIO_ALIENS)
#define ALTURA_ALIENS (FILES_ALIENS * TAMANY_ALIEN + (FILES_ALIENS-1)*SEPARACIO_ALIENS)

////////////////////// Mida del cano //////////////////////
#define TAMANY_CANO TAMANY_PERSONATGE

////////////////////// Mides del bunker //////////////////////
#define TAMANY_ESCUT TAMANY_PERSONATGE
#define MAX_ESCUTS 5
#define SEPARACIO_ESCUTS ((AMPLADA_PANTALLA-(TAMANY_ESCUT*MAX_ESCUTS))/(MAX_ESCUTS+1))
#define AMPLADA_BUNKER (MAX_ESCUTS * (TAMANY_ESCUT+SEPARACIO_ESCUTS) - SEPARACIO_ESCUTS)

////////////////////// Velocitats b�siques de moviment, en punts //////////////////////
#define VELOCITAT_ALIENS 1
#define VELOCITAT_ALIENS_BAIXADA 1
#define VELOCITAT_BALA 1
#define VELOCITAT_NAU 1

////////////////////// Propietats dels nivells //////////////////////
#define MAX_NIVELL 3
#define VIDES_ALIEN 3

#define DISTANCIA_TRETS_ALIEN_1 7
#define DISTANCIA_TRETS_ALIEN_2 5
#define DISTANCIA_TRETS_ALIEN_3 3

#define VIDES_JUGADOR_1 5
#define VIDES_JUGADOR_2 4
#define VIDES_JUGADOR_3 3

	////////////////////// Periode entre cada un dels moviments de cada objecte //////////////////////
#define TEMPS_ALIENS_1 8
#define TEMPS_ALIENS_2 6
#define TEMPS_ALIENS_3 4

#define TEMPS_BALA 1

#define TEMPS_CANO 4

#define TEMPS_UFO 6

#define ESPERA_UFO 55

////////////////////// Posici� inicial del joc //////////////////////
#define INICI_ALIENS_X 0
#define INICI_ALIENS_Y 0
#define INICI_CANO_X (AMPLADA_PANTALLA/2)
#define INICI_CANO_Y (ALTURA_PANTALLA - TAMANY_CANO/2 - 1)
#define INICI_BUNKER_X (SEPARACIO_ESCUTS + 1)
#define INICI_BUNKER_Y (ALTURA_PANTALLA - 2*TAMANY_CANO - TAMANY_ESCUT)

////////////////////// Puntuacions //////////////////////
#define PUNTUACIO_ALIEN_MORT 10
#define PUNTUACIO_UFO_MORT 100

////////////////////// Propietats de les bales de l'alien i el cano //////////////////////
#define CANO_BALES 100
#define CANO_TEMPS_CARREGANT 5
#define ALIENS_BALES 100
#define ALIENS_TEMPS_CARREGANT 3

////////////////////// Objectes //////////////////////
#define TEMPS_OBJECTE 5
#define TEMPS_OBJECTES 2
#define VELOCITAT_OBJECTE 1

#define MILLORA_BALES 1
#define TEMPS_MILLORA_BALES 150
#define PROVABILITATS_MILLORA_BALES 2

#define MILLORA_SUPERBALA 2
#define TEMPS_MILLORA_SUPERBALA 1000
#define PROVABILITATS_MILLORA_SUPERBALA 60
#define BALES_SUPERBALA 10
#define AMPLADA_SUPERBALA 10

#define PROVABILITATS_MILLORA_VIDES 30
#define MILLORA_VIDES 3

////////////////////// Raons per les que acabar� el joc //////////////////////
#define RAO_JOC_ACABAT_NO_ACABAT 0
#define RAO_JOC_ACABAT_SORTIR 1
#define RAO_JOC_ACABAT_PERDUT 2
#define RAO_JOC_ACABAT_GUANYAT 3
#define RAO_JOC_ACABAT_MORT 4

////////////////////// Inicialitzaci� dels dibuixos //////////////////////
#define DIBUIX_ALIEN_1 {{4,4,4}, {4,0,4}, {4,0,4}}
#define DIBUIX_ALIEN_2 {{4,4,4}, {4,0,4}, {0,0,0}}
#define DIBUIX_ALIEN_3 {{4,4,4}, {0,4,0}, {0,0,0}}
#define DIBUIX_NAU {{0,2,0}, {2,2,2}, {2,2,2}}
#define DIBUIX_ESCUT {{1,1,1}, {1,1,1}, {1,0,1}}
#define DIBUIX_UFO { {5,5,5}, {5,0,5}, {0,0,0} }


///////////////////// Frikades //////////////////////////////
#define DIBUIX_FSM { {0,0,8,8,8,0,0,8,8,8,0,0}, {0,0,8,0,8,0,0,8,0,8,0,0}, {0,0,0,8,0,0,0,0,8,0,0,0}, {0,0,0,8,8,8,8,8,8,0,0,0}, {0,0,8,0,0,0,0,0,0,8,0,0}, {8,8,8,0,0,0,0,0,0,8,8,8}, {8,0,8,8,8,8,8,8,8,8,0,8}, {0,0,8,0,8,0,0,8,0,8,0,0}, {0,8,8,0,8,0,0,8,0,8,8,0} }
#define AMPLADA_FSM 12
#define ALTURA_FSM 9
#define SFSMW 3
#define SFSMH 2
#define AMPLADA_SFSM (SFSMW*AMPLADA_FSM)
#define ALTURA_SFSM (SFSMH*ALTURA_FSM)

#define PLATETS_FSM 4
#define VIDES_PLATETS_FSM 5
#define TEMPS_BALES_PLATETS 5
#define TEMPS_ESPERA_PLATETS_FSM 500
#define VIDES_FSM 5

#define LF {{7,7,7,7}, {7,0,0,0}, {7,7,7,0}, {7,0,0,0}, {7,0,0,0}}
#define LS {{0,7,7,7}, {7,0,0,0}, {0,7,7,0}, {0,0,0,7}, {7,7,7,0}}
#define LM {{7,0,0,0,7}, {7,7,0,7,7}, {7,0,7,0,7}, {7,0,0,0,7}, {7,0,0,0,7}}

#define LC {{0,7,7,0}, {7,0,0,7}, {7,0,0,0}, {7,0,0,7}, {0,7,7,0}}
#define LA {{0,7,7,7}, {7,0,0,7}, {7,7,7,7}, {7,0,0,7}, {7,0,0,7}}
#define LN {{7,7,0,7}, {7,7,0,7}, {7,0,7,7}, {7,0,7,7}, {7,0,0,7}}
#define LT {{7,7,7,7}, {0,7,0,0}, {0,7,0,0}, {0,7,0,0}, {0,7,0,0}}

#define LD {{7,7,7,0}, {7,0,7,7}, {7,0,0,7}, {7,0,7,7}, {7,7,7,0}}
#define LI {{7,7,7,0}, {0,7,0,0}, {0,7,0,0}, {0,7,0,0}, {7,7,7,0}}
#define LE {{7,7,7,7}, {7,0,0,0}, {7,7,7,0}, {7,0,0,0}, {7,7,7,7}}
#define LADD {{7,0,7,0}, {7,0,7,0}, {7,0,7,0}, {0,0,0,0}, {7,0,7,0}}

////////////////////// Men� //////////////////////
#define OPCIO_SORTIR 0
#define MENU \
	"Tria una opcio:\n\
	1. TOP PLAYERS\n\
	2. Jugar\n\
	3. Triar nivell\n\
	4. Partida Multijugador\n\
	5. Nivell Multijugador\n\n\
	0. Sortir\n"






/****************************************************************************
*****************************************************************************
****************************************************************************/

#define MAX_JUGADORS 2
#define DIBUIX_NAU_2 {{0,5,0}, {5,5,5}, {5,5,5}}

#define L_VIDES_M 15

#define VIDES_M_1_X (DespC + 1)

#define VIDES_M_2_X (DespC + AmpladaTaulell - (L_VIDES_M + 2))


#define DISTANCIA_TRETS_ALIEN_1_M 7
#define DISTANCIA_TRETS_ALIEN_2_M 5
#define DISTANCIA_TRETS_ALIEN_3_M 3


/****************************************************************************
*****************************************************************************
****************************************************************************/



////////////////////// Estructures de dades //////////////////////
typedef struct {
	
	int punts[TAMANY_PERSONATGE][TAMANY_PERSONATGE];

} Taula_Dibuix;


typedef struct tObjecte {
	int tipus;
	int x;
	int y;
	int temps;
	int v_x;
	int v_y;
	int dibuix;
	struct tObjecte *seguent;
} Objecte;


typedef struct {
	int viu;
} Nau_Alien;


typedef struct {
	int x;
	int y;
	Taula_Dibuix forma;
	int v_x;
	int v_y;
	int bucles;
	int espera;
	int actiu;
} Platet;


typedef struct {
	int x;
	int y;
	int velocitat;
	Taula_Dibuix forma[VIDES_ALIEN];
	Nau_Alien naus[FILES_ALIENS][COLUMNES_ALIENS];
	int carregues;
	int carregant;
	int vius_files[FILES_ALIENS];
	int vius_columnes[COLUMNES_ALIENS];
	int vides;
	int max_bales;
	int temps;
	int bucles;
	int dmax_bales;
} Flota_Alien;


typedef struct {
	int x;
	int y;
	int carregues;
	int carregant;
	Taula_Dibuix forma;
	int vides;
	int punts;
	int max_bales;
	int temps;
	int max_vides;
	int millora;
	int temps_millora;
	Objecte *objectes;
} Nau_Propia;


typedef struct tBala{
	int x;
	int y;
	int velocitat;
	struct tBala *seguent;
} Bala;


typedef struct {
	Taula_Dibuix forma;
} Escut;


typedef struct {
	int x;
	int y;
	Escut escuts[MAX_ESCUTS];
} Bunker;


typedef struct TJugador{
	int puntuacio;
	char nom[30];
	char data[20];
	struct TJugador *seguent;
} Jugador;


typedef struct {
	int vides;
	int x;
	int y;
	int v_x;
	int v_y;
	int dibuix[ALTURA_SFSM][AMPLADA_SFSM];
	int bucles;
	int espera;
	int ulls[2];
} tFsm;





	//Funcions
void jugar(char *nomJugador, int *acabarJoc, int *raoJocAcabat, int *punts, int nivell);
void jugarPartida(int *punts, char *nomJugador);
void jugarNivell(int *punts, char *nomJugador);
void jugarNivell_4(char *nomJugador, int *acabarJoc, int *raoJocAcabat, int *punts);

int aleatori(int n);
void espera(int pantalla[][AMPLADA_PANTALLA]);

void dibuixarPantalla (int *pantalla, Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, Bala *bales);
void prepararJoc (int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA], Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *pausa, int *punts, int nivell);
void moureCano (int *pantalla, Nau_Propia *cano, int velocitat);
Bala *crearNovaBala (Bala *bales, int velocitat, int x, int y);
Bala *dispararBalaCano (int *pantalla, Bala *bales, Nau_Propia *cano);
Bala *dispararBalaAliens (int *pantalla, Bala *bales, Flota_Alien *aliens, Nau_Propia *cano);
Bala *ferAccionsTeclat (int *pantalla, Nau_Propia *cano, Bala *bales, int *acabarJoc, int *raoJocAcabat, int *pausa);
void moureAliens (int *pantalla, Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat, Bunker *bunker);
void comprovarAliensVius (Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat);
Bala *eliminaBala (Bala *bales, Bala *eliminada);
Bala *comprovarXocBalaAmbEscut (int *pantalla, Bala *bales, Bala *bala, Bunker *bunker, Nau_Propia *cano, Flota_Alien *aliens, int *balaActiva);
Bala *comprovarXocBalaAmbAlien (int *pantalla, Bala *bales, Bala *bala, Flota_Alien *aliens, Nau_Propia *cano);
Bala *comprovarXocBalaAmbCano (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat);
Bala *comprovarXocBalaAmbBala(int *pantalla, Bala *bales, Bala *bala, Bala *(*next), Nau_Propia *cano, Flota_Alien *aliens, int *balaActiva);
Bala *moureBales (int *pantalla, Bala *bales, Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *acabarJoc, int *raoJocAcabat);
void buidarBales (Bala *bales);

void creaUfo (Platet *ufo, int *pantalla);
void moureUfo (Platet *ufo, int *pantalla);
Bala *comprovarXocBalaAmbUfo (Platet *ufo, Nau_Propia *cano, Bala *bales, Bala *bala, int *pantalla, int *balaActiva);
void eliminaUfo (Platet *ufo, int *pantalla);

void inicialitzaDibuixCano(int dibuix[TAMANY_CANO][TAMANY_CANO]);
void inicialitzaDibuixAliens(Taula_Dibuix dibuix[VIDES_ALIEN]);
void inicialitzaDibuixEscut(int dibuix[TAMANY_ESCUT][TAMANY_ESCUT]);
void inicialitzaDibuixPlatet (int dibuix[TAMANY_ALIEN][TAMANY_ALIEN]);

Jugador *llegirFitxerPuntuacions(const char *url);
Jugador *afegirPuntuacioJugador(Jugador *primer, char *nom, int puntuacio);
void guardarFitxerPuntuacions(const char *url, Jugador *primer);
Jugador *netejaPuntuacions(Jugador *primer);
void escriurePuntuacions(Jugador *primer);



Objecte *moureObjectes (int *pantalla, Objecte *primer, Nau_Propia *cano, Bunker *bunker);
void activarMilloraCano(int *pantalla, Nau_Propia *cano, int millora);
void desactivarMilloresCano(int *pantalla, Nau_Propia *cano);
Objecte *crearNouObjecte (Objecte *primer, int v_x, int v_y, int x, int y, int tipus);
Objecte *eliminaObjecte (Objecte *primer, Objecte *eliminar);
void buidarObjectes (Objecte *primer);







/****************************************************************************
*****************************************************************************
****************************************************************************/

void CreaTaulell_m(void);
void MostraVides_m_1(int NVides, int MaxVides);
void MostraVides_m_2(int NVides, int MaxVides);

void jugarNivell_m(void);
void jugarPartida_m(void);
void jugar_m (int *acabarJoc, int *raoJocAcabat, int nivell);
void dibuixarPantalla_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, Bala *bales);
void inicialitzaDibuixCano_m(Nau_Propia cano[MAX_JUGADORS]);
void prepararJoc_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *pausa, int *punts, int nivell);
Bala *dispararBalaCano_m (int *pantalla, Bala *bales, Nau_Propia *cano);
Bala *ferAccionsTeclat_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Bala *bales, int *acabarJoc, int *raoJocAcabat, int *pausa);
Bala *dispararBalaAliens_m (int *pantalla, Bala *bales, Flota_Alien *aliens, Nau_Propia cano[MAX_JUGADORS]);
Bala *comprovarXocBalaAmbCano_m (int *pantalla, Bala *bales, Bala *bala, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat);
Bala *moureBales_m (int *pantalla, Bala *bales, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *acabarJoc, int *raoJocAcabat);

/****************************************************************************
*****************************************************************************
****************************************************************************/

void proves();
void jugarFSM();
void dibuixarPantallaFSM(int *pantalla, Nau_Propia *cano, Platet ufo[PLATETS_FSM], Platet *random, tFsm *fsm, Bala *bales, int linia[1][AMPLADA_PANTALLA]);
void prepararFSM (int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA], Nau_Propia *cano, Bunker *bunker, Platet *ufo, Platet *random, tFsm *fsm, int *pausa, int *punts);
void inicialitzaDibuixFSM(int dibuix[ALTURA_SFSM][AMPLADA_SFSM]);
Bala *moureBalesFSM (int *pantalla, Bala *bales, Nau_Propia *cano, Bunker *bunker, tFsm *fsm, Platet ufo[PLATETS_FSM], Platet *random, int top, int *acabarJoc, int *raoJocAcabat);
Bala *comprovarXocBalaAmbBalaFSM(int *pantalla, Bala *bales, Bala *bala, Bala *(*next), Nau_Propia *cano, int *balaActiva);
Bala *comprovarXocBalaAmbEscutFSM (int *pantalla, Bala *bales, Bala *bala, Bunker *bunker, Nau_Propia *cano, int *balaActiva);
Bala *comprovarXocBalaAmbCanoFSM (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, int *acabarJoc, int *raoJocAcabat);
Bala *comprovarXocBalaAmbAliensFSM (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, tFsm *fsm, Platet ufo[PLATETS_FSM]);
Bala *mourePlatetsFSM (int *pantalla, Platet ufo[PLATETS_FSM], Bala *bales, int temps);
Bala *comprovarXocBalaAmbFSM (tFsm *fsm, Nau_Propia *cano, Bala *bales, Bala *bala, int *pantalla);
Bala *moureRandom (int *pantalla, tFsm *fsm, Platet *random, Bala *bales);
Bala *moureFSM (int *pantalla, tFsm *fsm, Bala *bales);









int main (int argc, const char * argv[]) 
{
	
	Jugador *puntuacions;
	int opcio, sortir;
	int punts;
	char nomJugador[30];

	srand( (unsigned)time( NULL ) );
	
	puntuacions = llegirFitxerPuntuacions(URL_PUNTS);
	
	do {
		
		printf(MENU);
		
		do
		{
			scanf("%d", &opcio);
			
		} while(opcio > 5 && opcio != 1001);

		system("cls");
		
		punts = 0;
		sortir = FALSE;

		switch (opcio) 
		{
			case OPCIO_SORTIR:
				
				guardarFitxerPuntuacions(URL_PUNTS, puntuacions);
				netejaPuntuacions(puntuacions);
				
				sortir = TRUE;
				
				break;

			case 1:
			
				// Escriure les puntuacions guardades
				escriurePuntuacions(puntuacions);
				break;
			
			case 2:
				
				jugarPartida(&punts, nomJugador);
				puntuacions = afegirPuntuacioJugador(puntuacions, nomJugador, punts);

				break;
			
			case 3:
				
				jugarNivell(&punts, nomJugador);
				puntuacions = afegirPuntuacioJugador(puntuacions, nomJugador, punts);
				
				break;
			
			case 4:
				jugarPartida_m();
				break;

			case 5:
				jugarNivell_m();
				break;

			case 1001:
				jugarFSM();
				break;

		}

		printf("Prem ESPAI per continuar.\n");
		fflush(stdin);
		while(getch()!=' ');

		system("cls");
		
	} while (!sortir);
	
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Juga una partida al nivell especificat/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugarNivell(int *punts, char *nomJugador)
{

	int nivell, acabarJoc, raoJocAcabat;
	
	printf("Introdueix el teu nom.\n");
	scanf("%s", nomJugador);
	system("cls");
	
	printf("Quin nivell vols jugar?\n");
	scanf("%d", &nivell);
	system("cls");

	if (nivell > MAX_NIVELL)
		nivell = MAX_NIVELL;

	jugar(nomJugador, &acabarJoc, &raoJocAcabat, punts, nivell);

	if (raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		raoJocAcabat = RAO_JOC_ACABAT_GUANYAT;
		//Escriure la ra� per la que ha finalitzat el joc
	system("cls");
	switch (raoJocAcabat) 
	{
		case RAO_JOC_ACABAT_SORTIR:
			printf("Has aturat el joc.\n");
			break;
		case RAO_JOC_ACABAT_PERDUT:
			printf("Game Over: has perdut.\n");
			break;
		case RAO_JOC_ACABAT_GUANYAT:
			printf("Has destruit els aliens abans que arribessin!.\n");
			break;
		case RAO_JOC_ACABAT_MORT:
			printf("Has perdut totes les teves vides, els alien�genes han guanyat.\n");
			break;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Juga una partida amb tots els nivells//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugarPartida(int *punts, char *nomJugador)
{

	int acabarJoc, raoJocAcabat;
	
	printf("Introdueix el teu nom.\n");
	scanf("%s", nomJugador);
	system("cls");

	raoJocAcabat = -1;

	jugar(nomJugador, &acabarJoc, &raoJocAcabat, punts, 1);

	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		jugar(nomJugador, &acabarJoc, &raoJocAcabat, punts, 2);

	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		jugar(nomJugador, &acabarJoc, &raoJocAcabat, punts, 3);
	
		//Escriure la ra� per la que ha finalitzat el joc
	system("cls");
	
	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		raoJocAcabat = RAO_JOC_ACABAT_GUANYAT;
	
	switch (raoJocAcabat) 
	{
		case RAO_JOC_ACABAT_SORTIR:
			printf("Has aturat el joc.\n");
			break;
		case RAO_JOC_ACABAT_PERDUT:
			printf("Game Over: has perdut.\n");
			break;
		case RAO_JOC_ACABAT_GUANYAT:
			printf("Has destruit els aliens abans que arribessin!.\n");
			break;
		case RAO_JOC_ACABAT_MORT:
			printf("Has perdut totes les teves vides, els alien�genes han guanyat.\n");
			break;
	}
	

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Funcio del joc: bucle principal////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugar(char *nomJugador, int *acabarJoc, int *raoJocAcabat, int *punts, int nivell)
{
	
	Flota_Alien aliens;
	Nau_Propia cano;
	Bala *bales;
	Bunker bunker;
	Platet ufo;
	int pausa;
	int temps;
	int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA];
	char tecla;

	CreaTaulell();

	prepararJoc (pantalla, &cano, &aliens, &bunker, &ufo, &pausa, punts, nivell);

	bales = NULL;
	
	MostraPantalla(pantalla);
	
	espera(pantalla);

	temps = 0;
	*acabarJoc = FALSE;
	do {
		
		if (!pausa) 
		{
			
			if (temps%TEMPS_CANO == 0)
				bales = ferAccionsTeclat(pantalla, &cano, bales, acabarJoc, raoJocAcabat, &pausa);
			
			if(!pausa)
			{
				
				if (temps%aliens.bucles == 0)
					moureAliens(pantalla, &aliens, acabarJoc, raoJocAcabat, &bunker);

				if (temps%ufo.bucles == 0)
				{
					creaUfo(&ufo, pantalla);
					moureUfo(&ufo, pantalla);
				}

				if (temps%TEMPS_BALA == 0)
					bales = dispararBalaAliens(pantalla, bales, &aliens, &cano);
				
				if (temps%TEMPS_BALA == 0)
					bales = moureBales(pantalla, bales, &cano, &aliens, &bunker, &ufo, acabarJoc, raoJocAcabat);

				if (temps%TEMPS_OBJECTES == 0)
					cano.objectes = moureObjectes(pantalla, cano.objectes, &cano, &bunker);
				
				MostraPunts(cano.punts);
				MostraJugador(nomJugador);
				MostraNivell(nivell);
				
				if (temps%TEMPS_BALA == 0)
					MostraPantalla(pantalla);
				
				Sleep(RETRAS);

			}
		} else {
			
			if (_kbhit()) 
			{
				
				while(_kbhit()) tecla = getch();
				
				if (tecla == 'p' || tecla == 'P') 
				{
					system("cls");
					CreaTaulell();
					MostraPunts(cano.punts);
					MostraVides(cano.vides, cano.max_vides);
					MostraPantalla(pantalla);
					dibuixarPantalla (pantalla, &cano, &aliens, &bunker, &ufo, bales);
					pausa = FALSE;
					espera(pantalla);
				}
				
			}
			
		}
		
		temps++;

	} while (!(*acabarJoc));
	
		//Netejar el punter de bales
	buidarBales(bales);
	bales = NULL;

		//Actualitzar la puntuaci� general
	*punts = cano.punts;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Temps d'espera abans de jugar//////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void espera(int pantalla[][AMPLADA_PANTALLA])
{
	int tres[5][4] ={{0,15,15,0}, {15,0,0,15}, {0,0,15,0}, {15,0,0,15}, {0,15,15,0}};
	int dos[5][4] ={{0,15,15,0}, {15,0,0,15}, {0,0,15,0}, {0,15,0,0}, {15,15,15,15}};
	int u[5][4] ={{0,0,15,0}, {0,15,15,0}, {0,0,15,0}, {0,0,15,0}, {0,15,15,15}};

	PosaPersonatge2(tres, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);
	Sleep(1000);
	BorraPersonatge2(tres, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);


	PosaPersonatge2(dos, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);
	Sleep(1000);
	BorraPersonatge2(dos, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);


	PosaPersonatge2(u, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);
	Sleep(1000);
	BorraPersonatge2(u, pantalla, AMPLADA_PANTALLA/2 - 2, ALTURA_PANTALLA/2 - 2, 4, 5);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Retorna un aleatori entre [1,n]///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int aleatori(int n)
{
	int rnd;
	
	rnd = NumAleatori(n-1) + 1;
	
	return rnd;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Les seguents funcions inicialitzen els dibuixos////////////////////////////////
////////////////////////////////de cada personatge del joc ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void inicialitzaDibuixCano(int dibuix[TAMANY_CANO][TAMANY_CANO])
{
	int d[TAMANY_CANO][TAMANY_CANO] = DIBUIX_NAU;
	int f, c;

	for (f=0; f<TAMANY_CANO; f++)
		for (c=0; c<TAMANY_CANO; c++)
			dibuix[f][c] = d[f][c];

}



void inicialitzaDibuixAliens(Taula_Dibuix dibuix[VIDES_ALIEN])
{
	
	int d_1[TAMANY_ALIEN][TAMANY_ALIEN] = DIBUIX_ALIEN_1;
	int d_2[TAMANY_ALIEN][TAMANY_ALIEN] = DIBUIX_ALIEN_2;
	int d_3[TAMANY_ALIEN][TAMANY_ALIEN] = DIBUIX_ALIEN_3;
	int f, c;
	
	for (f=0; f<TAMANY_ALIEN; f++)
		for (c=0; c<TAMANY_ALIEN; c++)
			dibuix[0].punts[f][c] = d_1[f][c];

	for (f=0; f<TAMANY_ALIEN; f++)
		for (c=0; c<TAMANY_ALIEN; c++)
			dibuix[1].punts[f][c] = d_2[f][c];

	for (f=0; f<TAMANY_ALIEN; f++)
		for (c=0; c<TAMANY_ALIEN; c++)
			dibuix[2].punts[f][c] = d_3[f][c];
	
}



void inicialitzaDibuixEscut(int dibuix[TAMANY_ESCUT][TAMANY_ESCUT])
{
	
	int d[TAMANY_ESCUT][TAMANY_ESCUT] = DIBUIX_ESCUT;
	int f, c;
	
	for (f=0; f<TAMANY_ESCUT; f++)
		for (c=0; c<TAMANY_ESCUT; c++)
			dibuix[f][c] = d[f][c];
	
}

void inicialitzaDibuixPlatet (int dibuix[TAMANY_ALIEN][TAMANY_ALIEN])
{
		
	int d[TAMANY_ALIEN][TAMANY_ALIEN] = DIBUIX_UFO;
	int f, c;
	
	for (f=0; f<TAMANY_ALIEN; f++)
		for (c=0; c<TAMANY_ALIEN; c++)
			dibuix[f][c] = d[f][c];
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicialitzaci� de les variables generals per la partida////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void prepararJoc (int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA], Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *pausa, int *punts, int nivell)
{
	
	int i, j, tmpX, tmpY;
	

	for (i=0; i<ALTURA_PANTALLA; i++) {
		for (j=0; j<AMPLADA_PANTALLA; j++) {
			
			pantalla[i][j] = 0;
			
		}
	}


	switch (nivell)
	{
		case 1:
			cano->max_vides = VIDES_JUGADOR_1;
			aliens->bucles = TEMPS_ALIENS_1;
			aliens->temps = 3*ALIENS_TEMPS_CARREGANT + aleatori(3*ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_1;
			aliens->vides = 1;
			break;

		case 2:
			cano->max_vides = VIDES_JUGADOR_2;
			aliens->bucles = TEMPS_ALIENS_2;
			aliens->temps = 2*ALIENS_TEMPS_CARREGANT + aleatori(2*ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_2;
			aliens->vides = 2;
			break;

		case 3:
			cano->max_vides = VIDES_JUGADOR_3;
			aliens->bucles = TEMPS_ALIENS_3;
			aliens->temps = ALIENS_TEMPS_CARREGANT + aleatori(ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_3;
			aliens->vides = 3;
			break;
			
		default:
			cano->max_vides = VIDES_JUGADOR_3;
			aliens->bucles = TEMPS_ALIENS_3;
			aliens->temps = ALIENS_TEMPS_CARREGANT + aleatori(ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_3;
			aliens->vides = 3;
			break;
	}

	cano->x = INICI_CANO_X;
	cano->y = INICI_CANO_Y;
	inicialitzaDibuixCano(cano->forma.punts);

	cano->temps = CANO_TEMPS_CARREGANT;
	cano->max_bales = CANO_BALES;
	cano->carregues = cano->max_bales;
	cano->carregant = 0;
	cano->vides = cano->max_vides;
	cano->punts = *punts;
	cano->millora = 0;
	cano->temps_millora = 0;
	cano->objectes = NULL;
	MostraPunts(cano->punts);
	MostraVides(cano->vides, cano->max_vides);
	
		//Pintar el cano
	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);


	ufo->v_x = 0;
	ufo->v_y = 0;
	ufo->actiu = FALSE;
	ufo->x = -1;
	ufo->y = -1;
	ufo->bucles = TEMPS_UFO;
	ufo->espera = 30 + aleatori(ESPERA_UFO);

	inicialitzaDibuixPlatet(ufo->forma.punts);

	aliens->x = INICI_ALIENS_X;
	aliens->y = INICI_ALIENS_Y;
	aliens->velocitat = VELOCITAT_ALIENS;
	inicialitzaDibuixAliens(aliens->forma);

	aliens->max_bales = ALIENS_BALES;
	aliens->carregues = aliens->max_bales;
	aliens->carregant = aliens->temps + aleatori(aliens->temps);
	
	for (i=0; i<FILES_ALIENS; i++) 
	{
		aliens->vius_files[i] = COLUMNES_ALIENS;
	}
	for (i=0; i<COLUMNES_ALIENS; i++) 
	{
		aliens->vius_columnes[i] = FILES_ALIENS;
	}
	
	
		//Inicialitzar la matriu d'aliens i pintarlos a la pantalla
	for (i=0; i<FILES_ALIENS; i++) 
	{
		for (j=0; j<COLUMNES_ALIENS; j++) 
		{
			
			aliens->naus[i][j].viu = aliens->vides;
			tmpX = aliens->x + j*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
			tmpY = aliens->y + i*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
			PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpX, tmpY);
			
		}
	}
	
	bunker->x = INICI_BUNKER_X;
	bunker->y = INICI_BUNKER_Y;
	
	for (i=0; i<MAX_ESCUTS; i++) 
	{
		inicialitzaDibuixEscut(bunker->escuts[i].forma.punts);
		tmpX = bunker->x + i*(TAMANY_ESCUT + SEPARACIO_ESCUTS) + TAMANY_ESCUT/2;
		tmpY = bunker->y + TAMANY_ESCUT/2;
		PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, tmpX, tmpY);
	}
	
	*pausa = FALSE;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Posa tots els personatges a la pantalla////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void dibuixarPantalla (int *pantalla, Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, Bala *bales)
{
	Bala *tmp;
	int i, j, tmpX, tmpY;


		//Dibuixar el cano
	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);

		//Dibuixar els aliens
	for (i=0; i<FILES_ALIENS; i++) 
	{
		for (j=0; j<COLUMNES_ALIENS; j++) 
		{
			
			if(aliens->naus[i][j].viu)
			{
				tmpX = aliens->x + j*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
				tmpY = aliens->y + i*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
				PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpX, tmpY);
			}
		}
	}

		//Dibuixar el bunker
	for (i=0; i<MAX_ESCUTS; i++) 
	{
		tmpX = bunker->x + i*(TAMANY_ESCUT + SEPARACIO_ESCUTS) + TAMANY_ESCUT/2;
		tmpY = bunker->y + TAMANY_ESCUT/2;
		PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, tmpX, tmpY);
	}

		//Dibuixar el platet
	if(ufo->actiu)
	{
		PosaPersonatge (ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));
	}

		//Dibuixar les bales
	tmp = bales;
	while (tmp != NULL)
	{
		if(tmp->velocitat > 0)
			PosaTretAliens(pantalla, tmp->x, tmp->y);
		else
			PosaTretCano(pantalla, tmp->x, tmp->y);

		tmp = tmp->seguent;
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou el can�////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void moureCano (int *pantalla, Nau_Propia *cano, int velocitat)
{
	
	int tmpX;
	
	tmpX = cano->x + velocitat;
	
		//Actualitzar la posici� del can� si s'ha de moure
	if ( ((tmpX - TAMANY_CANO/2) >= 0) && ((tmpX + TAMANY_CANO/2) < AMPLADA_PANTALLA) ) 
	{
		
		BorraPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
		PosaPersonatge(cano->forma.punts, pantalla, tmpX, cano->y);
		cano->x = tmpX;
		
	}
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea un nou registre Bala. Retorna un punter///////////////////////////////////
/////////////////////////////////al nou registre /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *crearNovaBala (Bala *bales, int velocitat, int x, int y)
{
	
	Bala *tmp, *ultim, *anterior;
	int sortir = 0;
	
	tmp = (Bala *)malloc(sizeof(Bala));
	
		//Buscar la ultima bala
	if (bales != NULL) 
	{
		
		ultim = bales;
		anterior = NULL;
		while ((ultim->seguent != NULL) && !sortir) 
		{
			if(velocitat < 0)
			{
				if(velocitat == ultim->seguent->velocitat)
				{
					anterior = ultim;
					ultim = ultim->seguent;
					
				} else {
					
					if (anterior == NULL)
						bales = tmp;
					sortir = TRUE;
				}
				
			} else {
				ultim = ultim->seguent;
			}
			
		}
		
		tmp->seguent = ultim->seguent;
		ultim->seguent = tmp;
		
	} else {
		
		bales = tmp;
		tmp->seguent = NULL;
		
	}
	
		//Disparar-la
	tmp->x = x;
	tmp->y = y;
	tmp->velocitat = velocitat;
	
	
	return tmp;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Activa el platet volador i el situa////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void creaUfo(Platet *ufo, int *pantalla)
{

	int rnd;
	
	if(ufo->espera == 0 && ufo->actiu == FALSE)
	{
		
		rnd = aleatori(2)-1;

		ufo->x = rnd * (AMPLADA_PANTALLA-TAMANY_ALIEN);
		ufo->y = 1;
		ufo->v_y = 0;
		ufo->v_x = VELOCITAT_ALIENS - 2 * VELOCITAT_ALIENS * rnd;
		ufo->actiu = TRUE;

		PosaPersonatge(ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));
	}

	if (ufo->espera > 0)
	{
		ufo->espera -= 1;
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou el platet volador si esta actiu////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void moureUfo (Platet *ufo, int *pantalla)
{
	int tmpX, tmpY, rnd;

	if (ufo->actiu)
	{
		
		tmpX = ufo->x + ufo->v_x;
		tmpY = ufo->y + ufo->v_y;
		
		if (tmpY <= 0)
		{
			tmpY = 1;
		}
		
		if (tmpY > 4)
		{
			tmpY = 4;
		}

		if (tmpX >= 0 && tmpX < AMPLADA_PANTALLA-TAMANY_ALIEN)
		{
			//Moure'l
			BorraPersonatge (ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));
			ufo->x = tmpX;
			ufo->y = tmpY;
			PosaPersonatge (ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));

			//Nova velocitat vertical
			rnd = aleatori(2)-1;

			if (ufo->v_y > 0)
			{
				ufo->v_y = rnd;
			}
			else if (ufo->v_y < 0)
			{
				ufo->v_y = (-1)*rnd;
			}
			else
			{
				ufo->v_y = aleatori(3)-2;
			}

		}
		else
		{
			//Eliminar-lo
			eliminaUfo(ufo, pantalla);
		}
		
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala rebuda per la funci� xoca amb el platet, //////////////////
////////////////////////////////si aquest est� actiu. Retorna la llista de bales//////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbUfo (Platet *ufo, Nau_Propia *cano, Bala *bales, Bala *bala, int *pantalla, int *balaActiva)
{

	int tmpX, tmpY;
	if(ufo->actiu)
	{
		if ( (bala->x >= ufo->x) && (bala->x < ufo->x+TAMANY_ALIEN) && (bala->y >= ufo->y) && (bala->y < ufo->y+TAMANY_ALIEN) )
		{
			tmpX = bala->x - ufo->x;
			tmpY = bala->y - ufo->y;

			if (ufo->forma.punts[tmpY][tmpX] != 0)
			{
				eliminaUfo(ufo, pantalla);
				bales = eliminaBala(bales, bala);
				cano->punts += PUNTUACIO_UFO_MORT;
				cano->carregues += 1;
				*balaActiva = FALSE;
				if(!(aleatori(PROVABILITATS_MILLORA_BALES)-1))
					cano->objectes = crearNouObjecte(cano->objectes, 0, VELOCITAT_OBJECTE, 
										ufo->x+TAMANY_ALIEN/2, ufo->y+TAMANY_ALIEN/2, MILLORA_BALES);
			}
		}
	}

	return bales;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Desactiva el platet////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void eliminaUfo (Platet *ufo, int *pantalla)
{
	
	ufo->actiu = FALSE;
	ufo->espera = ESPERA_UFO + aleatori(ESPERA_UFO);
	BorraPersonatge(ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea i situa una nova bala pel can�. Retorna la llista de bales////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *dispararBalaCano (int *pantalla, Bala *bales, Nau_Propia *cano)
{
	
	Bala *tmp;
	int i,j;
	
	if ( (cano->carregues > 0) && (cano->carregant == 0) ) 
	{
		switch(cano->millora)
		{
			case MILLORA_BALES:
				tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x, (cano->y - 2));
				if (bales == NULL)
				{
					bales = tmp;
				}
				PosaTretCano(pantalla, tmp->x, tmp->y);
				tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x+1, (cano->y - 2));
				PosaTretCano(pantalla, tmp->x, tmp->y);
				tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x-1, (cano->y - 2));
				PosaTretCano(pantalla, tmp->x, tmp->y);
				break;

			case MILLORA_SUPERBALA:
				for(i=BALES_SUPERBALA-1; i>=0; i--)
				{
					for(j=-(AMPLADA_SUPERBALA/2); j<=AMPLADA_SUPERBALA/2; j++)
					{
						tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x + j, (cano->y - 2 - i));
						if (bales == NULL)
						{
							bales = tmp;
						}
						PosaTretCano(pantalla, tmp->x, tmp->y);
					}
					
				}
				desactivarMilloresCano(pantalla, cano);
				break;

			default:
				tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x, (cano->y - 2));
				if (bales == NULL)
				{
					bales = tmp;
				}
				PosaTretCano(pantalla, tmp->x, tmp->y);
				break;
		}
		cano->carregues = cano->carregues - 1;
		cano->carregant = cano->temps;
		
	}
	
	return bales;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea i situa una nova bala pels aliens. La situa tan a prop////////////////////
///////////////////////////////del can� com calgui. Retorna la llista de bales////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *dispararBalaAliens (int *pantalla, Bala *bales, Flota_Alien *aliens, Nau_Propia *cano)
{
	
	Bala *tmp;
	int rnd, columnesVius, maxColumnes, columnesMirades, i, j, k;
	int columna, primerViu, ultimViu, viuGran;
	int x, y, alienX;
	

	if ( (aliens->carregues > 0) && (aliens->carregant == 0) ) 
	{
		
		primerViu = 0;
		for(i=0; i<COLUMNES_ALIENS; i++)
			if (aliens->vius_columnes[i] > 0 && primerViu == 0) primerViu = i;

		alienX = min(COLUMNES_ALIENS-1, max(0, (cano->x - aliens->x)/(TAMANY_ALIEN+SEPARACIO_ALIENS)));

			//Buscar el total de columnes amb aliens vius
		columnesVius = 0;
		maxColumnes = 0;
		for (i=0; i<COLUMNES_ALIENS; i++) 
		{
			if (aliens->vius_columnes[i]>0) 
			{
				maxColumnes++;
				if ( abs(i-alienX) <= aliens->dmax_bales/2+aliens->dmax_bales%2)
				{
					columnesVius += 1;
				}
			}
		}
		
		rnd = aleatori(max(columnesVius, (aliens->dmax_bales/2 + aliens->dmax_bales%2)));
		
			//Buscar la columan des d'on es dispara
		columnesVius = 0;
		columnesMirades = 0;
		columna = -1;
		
		while ( columnesMirades < maxColumnes && columnesVius < rnd ) 
		{
			columna += 1;
			
			if (aliens->vius_columnes[columna] > 0) 
			{
				columnesMirades += 1;

				if ( abs(columna-alienX) <= aliens->dmax_bales/2+aliens->dmax_bales%2)
				{
					columnesVius += 1;
				}
			}

		}
		
			//Buscar l'ultim alien viu de la columna
		for (i=0; i<FILES_ALIENS; i++) 
		{
			if ( aliens->naus[i][columna].viu ) 
			{
				ultimViu = i;
			}
		}
		
		viuGran = 0;
		for (i=0; i<COLUMNES_ALIENS; i++)
			if (aliens->naus[ultimViu][i].viu)
				for(j=0; j<TAMANY_ALIEN; j++)
					for(k=0; k<TAMANY_ALIEN; k++)
						if(aliens->forma[aliens->vides - (aliens->naus[ultimViu][i].viu)].punts[k][j]!=0 && (k+1)>viuGran) 
							viuGran = k+1;
		
			//Disparar la bala
		x = aliens->x + columna*(TAMANY_ALIEN + SEPARACIO_ALIENS) + (TAMANY_ALIEN/2);
		y = aliens->y + (ultimViu)*(TAMANY_ALIEN + SEPARACIO_ALIENS) + TAMANY_ALIEN - aliens->vides + viuGran;
		tmp = crearNovaBala(bales, VELOCITAT_BALA, x, y);

		if(bales == NULL)
		{
			bales = tmp;
		}

		PosaTretAliens(pantalla, x, y);
		
		aliens->carregant = aliens->temps + aleatori(aliens->temps);
		aliens->carregues = aliens->carregues - 1;
		
	}
	
	return bales;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Llegeix si s'ha presionat alguna tecla i fa les accions que calgui/////////////
//////////////////////////////////Retorna la llista de bales//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *ferAccionsTeclat (int *pantalla, Nau_Propia *cano, Bala *bales, int *acabarJoc, int *raoJocAcabat, int *pausa)
{
	
	char tecla;
	int moviment = FALSE, disparat = FALSE;
	
		//Comprovar si s'ha pressionat alguna tecla
	if (_kbhit()) 
	{
		
		while(_kbhit()) 
		{
			tecla = getch();
			
			switch (tecla) 
			{
				case KEY_RIGHT:
					if(!moviment)
						moureCano(pantalla, cano, VELOCITAT_NAU);
					moviment = TRUE;
					break;
					
				case KEY_LEFT:
					if(!moviment)
						moureCano(pantalla, cano, (-1)*VELOCITAT_NAU);
					moviment = TRUE;
					break;
					
				case KEY_UP:
					if(!disparat)
						bales = dispararBalaCano(pantalla, bales, cano);
					disparat = TRUE;
					break;
				
				case 'p':
					*pausa = TRUE;
					moviment = TRUE;
					disparat = TRUE;
					system("cls");
					printf("Apreta P per sortir de la pausa.\n");
					break;
					
				case 'P':
					*pausa = TRUE;
					moviment = TRUE;
					disparat = TRUE;
					system("cls");
					printf("Apreta P per sortir de la pausa.\n");
					break;
					
				case KEY_ESC:
					moviment = TRUE;
					disparat = TRUE;
					*acabarJoc = TRUE;
					*raoJocAcabat = RAO_JOC_ACABAT_SORTIR;
					break;
					
			}

		}
		
	}

	return bales;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou la flota d'aliens cap els costats o avall, si cal//////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void moureAliens (int *pantalla, Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat, Bunker *bunker)
{
	
	int tmpX, tmpY, tmpAlienX, tmpAlienY, i, j, k, primerViu, ultimViu, viuGran;
	
		//Moure el bloc d'aliens
	tmpX = aliens->x + aliens->velocitat;
	tmpY = aliens->y;
	
		//Comprovar si els aliens estan a un cant� de la pantalla
	primerViu = -1;
	ultimViu = -1;
	
	for (i=0; i<COLUMNES_ALIENS; i++) 
	{
		
		if ( (primerViu < 0) && (aliens->vius_columnes[i] != 0) ) 
		{
			primerViu = i;
		}
		
		if ( aliens->vius_columnes[i] != 0 ) 
		{
			ultimViu = i;
		}
		
	}
	
		//Mirar si els aliens xoquen contra una paret
	if ( ((tmpX + (ultimViu+1)*(TAMANY_ALIEN+SEPARACIO_ALIENS) - SEPARACIO_ALIENS) > AMPLADA_PANTALLA) || ((tmpX + primerViu*(TAMANY_ALIEN + SEPARACIO_ALIENS)) < 0) ) 
	{
		
			//Comprovar si han arribat a baix de tot
		ultimViu = 0;
		for (i=0; i<FILES_ALIENS; i++) 
		{
			if (aliens->vius_files[i] != 0) 
			{
				ultimViu = i;
			}
		}
		viuGran = 0;
		for (i=0; i<COLUMNES_ALIENS; i++)
			if (aliens->naus[ultimViu][i].viu)
				for(j=0; j<TAMANY_ALIEN; j++)
					for(k=0; k<TAMANY_ALIEN; k++)
						if(aliens->forma[aliens->vides - (aliens->naus[ultimViu][i].viu)].punts[k][j]!=0 && (k+1)>viuGran) 
							viuGran = k+1;
			//Agafar la dist�ncia des del punt d'inici dels aliens a l'ultima fila amb un �lien viu
		tmpAlienY = aliens->y + (ultimViu)*(TAMANY_ALIEN+SEPARACIO_ALIENS) + TAMANY_ALIEN - aliens->vides + viuGran;
		
		
		//Fer-los moure avall enlloc de cap al costat
		tmpX = aliens->x;
		tmpY = aliens->y + VELOCITAT_ALIENS_BAIXADA;
		
		if ( tmpAlienY < (ALTURA_PANTALLA - TAMANY_CANO - 1) ) 
		{
			
			aliens->velocitat = aliens->velocitat * (-1);
			
				//Comprovar si toquen el bunker i borrar-ne una part si �s aix�
			if ( tmpAlienY >= bunker->y && tmpAlienY < (bunker->y + TAMANY_ESCUT) ) 
			{
				for (i=0; i<MAX_ESCUTS; i++) 
				{
					BorraPersonatge(bunker->escuts[i].forma.punts, pantalla, bunker->x + i*(TAMANY_ESCUT+SEPARACIO_ESCUTS) + TAMANY_ESCUT/2, bunker->y + TAMANY_ESCUT/2);
					for (j=0; j<TAMANY_ESCUT; j++) 
					{
						bunker->escuts[i].forma.punts[(tmpAlienY - bunker->y)][j] = 0;
					}
					PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, bunker->x + i*(TAMANY_ESCUT+SEPARACIO_ESCUTS) + TAMANY_ESCUT/2, bunker->y + TAMANY_ESCUT/2);
				}
			}
			
		} else {
			
				//Si han arribat a baix, acabar el joc
			tmpX = aliens->x;
			tmpY = aliens->y + VELOCITAT_ALIENS_BAIXADA;
			*acabarJoc = TRUE;
			*raoJocAcabat = RAO_JOC_ACABAT_PERDUT;
			
		}
	}
	
		//Borrar cada un dels anteriors i dibuixar els nous
	for (i=0; i<FILES_ALIENS; i++) 
	{
		for (j=0; j<COLUMNES_ALIENS; j++) 
		{
			if (aliens->naus[i][j].viu) 
			{
				
				tmpAlienX = aliens->x + j*(TAMANY_ALIEN+SEPARACIO_ALIENS)+TAMANY_ALIEN/2;
				tmpAlienY = aliens->y + i*(TAMANY_ALIEN+SEPARACIO_ALIENS)+TAMANY_ALIEN/2;
				BorraPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpAlienX, tmpAlienY);
				
				tmpAlienX = tmpX + j*(TAMANY_ALIEN+SEPARACIO_ALIENS)+TAMANY_ALIEN/2;
				tmpAlienY = tmpY + i*(TAMANY_ALIEN+SEPARACIO_ALIENS)+TAMANY_ALIEN/2;
				PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpAlienX, tmpAlienY);
			}
		}
	}
	
		//Actualitzar la posici� de la flota
	aliens->x = tmpX;
	aliens->y = tmpY;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si queda algun alien viu a la flota///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void comprovarAliensVius (Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat)
{
	
	int i, j;
	
	if (!(*acabarJoc)) 
	{
		
			//Comprovar si queden aliens vius
		
		*acabarJoc = TRUE;
		
		i = 0;
		do {
			
			j = 0;
			do {
				
				if (aliens->naus[i][j].viu) 
				{
					*acabarJoc = FALSE;
				}
				
				j++;
				
			} while (j<COLUMNES_ALIENS && acabarJoc);
			
			i++;
				
		} while (i<FILES_ALIENS && acabarJoc);
		
		if (*acabarJoc) 
		{
			*raoJocAcabat = RAO_JOC_ACABAT_NO_ACABAT;
		}
		
	}
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Elimina la bala especificada. Retorna la llista de bales///////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *eliminaBala (Bala *bales, Bala *eliminada)
{
	
	Bala *anterior;
	
	if (bales != eliminada) 
	{
		
			//Buscar la bala anterior
		anterior = bales;
		
		while (anterior->seguent != eliminada) 
		{
			anterior = anterior->seguent;
		}
		
		anterior->seguent = eliminada->seguent;
		
		free(eliminada);
		
		eliminada = NULL;
		
	} else {
		
		anterior = bales;
		bales = bales->seguent;
		free(anterior);
		eliminada = NULL;
		
	}
	
	return bales;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb un escut.////////////////////////////
/////////////////////////////////Retorna la llista de bales///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbEscut (int *pantalla, Bala *bales, Bala *bala, Bunker *bunker, Nau_Propia *cano, Flota_Alien *aliens, int *balaActiva)
{
	
	int tmpX, tmpBunkerX, tmpY, modX, x, y;
	
	if ( (bala->x < (bunker->x + (MAX_ESCUTS*(TAMANY_ESCUT+SEPARACIO_ESCUTS)-SEPARACIO_ESCUTS))) 
		&& (bala->x >= bunker->x) && (bala->y < (bunker->y + TAMANY_ESCUT)) && (bala->y >= bunker->y) ) 
	{
		
			//Mirar si est� sobre un escut
		tmpX = bala->x - bunker->x;
		tmpY = bala->y - bunker->y;
		
		modX = tmpX % (TAMANY_ESCUT + SEPARACIO_ESCUTS);
		
		if (modX < TAMANY_ESCUT) 
		{
			
				//Comprovar si toca una part de l'escut
			tmpBunkerX = tmpX/(TAMANY_ESCUT+SEPARACIO_ESCUTS);
			if ( bunker->escuts[tmpBunkerX].forma.punts[tmpY][modX]!=0 ) 
			{
				
				x = bunker->x + tmpX - modX + TAMANY_ESCUT/2;
				y = bunker->y + TAMANY_ESCUT/2;
				
				BorraPersonatge(bunker->escuts[tmpBunkerX].forma.punts, pantalla, x, y);
				
					//Borra la part de l'escut
				bunker->escuts[tmpBunkerX].forma.punts[tmpY][modX] = 0;
				
				PosaPersonatge(bunker->escuts[tmpBunkerX].forma.punts, pantalla, x, y);
				
					//Desactiva la bala
				if (bala->velocitat < 0) 
				{
					cano->carregues += 1;
				
				} else {
					
					aliens->carregues += 1;
				}
				
				*balaActiva = FALSE;
				bales = eliminaBala(bales, bala);
				
			}
			
		}
		
	}
	
	return bales;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb una nau alien�gena///////////////////
///////////////////////////////////Retorna la llista de bales/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbAlien (int *pantalla, Bala *bales, Bala *bala, Flota_Alien *aliens, Nau_Propia *cano)
{
	
	int tmpX, tmpY, modX, modY, tmpAlienX, tmpAlienY, i, j;
	
	PosaTretCano(pantalla, bala->x, bala->y);
	
		//Comprovar si xoca amb algun alien
	if ( (bala->x < (aliens->x + AMPLADA_ALIENS)) && (bala->x >= aliens->x) 
		&& (bala->y < (aliens->y + ALTURA_ALIENS)) && (bala->y >= aliens->y) ) 
	{
			//La bala est� a l'altura del bloc d'aliens
		
			//Obtenim la posici� relativa al bloc
		tmpX = bala->x - aliens->x;
		tmpY = bala->y - aliens->y;
		
			//Trobar quin �lien �s
		j = (tmpX / (TAMANY_ALIEN + SEPARACIO_ALIENS));
		i = (tmpY / (TAMANY_ALIEN + SEPARACIO_ALIENS));
		
			//Si l'alien encara �s viu
		if (aliens->naus[i][j].viu) 
		{
			
				//Agafem el m�dul de la posici� per saber si la bala coincideix
			modX = tmpX % (TAMANY_ALIEN + SEPARACIO_ALIENS);
			modY = tmpY % (TAMANY_ALIEN + SEPARACIO_ALIENS);
			
				//Comprovem si la bala est� sobre un �lien
			if ( (modX < TAMANY_ALIEN) && (modY < TAMANY_ALIEN) ) 
			{
				
					//Comprovar si TOCA l'alien
				if (aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts[modY][modX] != 0) 
				{
					
						//Desactivar, borrar la bala i carregar el can�
					BorraTret(pantalla, bala->x, bala->y);
					bales = eliminaBala(bales, bala);
					cano->carregues += 1;
					
						//Matar l'alien i borrar-lo de la pantalla
					aliens->naus[i][j].viu -= 1;
					
					tmpAlienX = aliens->x + j*(TAMANY_ALIEN+SEPARACIO_ALIENS) + TAMANY_ALIEN/2;
					tmpAlienY = aliens->y + i*(TAMANY_ALIEN+SEPARACIO_ALIENS) + TAMANY_ALIEN/2;
					BorraPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu+1)].punts, pantalla, tmpAlienX, tmpAlienY);
					
					if (aliens->naus[i][j].viu == 0) 
					{
							//Actualitzar la info dels aliens
						aliens->vius_files[i] -= 1;
						aliens->vius_columnes[j] -= 1;
						
							//Augmentar la puntuaci� del jugador
						cano->punts += PUNTUACIO_ALIEN_MORT;

						if(!(aleatori(PROVABILITATS_MILLORA_SUPERBALA)-1))
							cano->objectes = crearNouObjecte(cano->objectes, 0, VELOCITAT_OBJECTE, tmpAlienX, tmpAlienY, MILLORA_SUPERBALA);
						else
							if(!(aleatori(PROVABILITATS_MILLORA_VIDES)-1))
								cano->objectes = crearNouObjecte(cano->objectes, 0, VELOCITAT_OBJECTE, tmpAlienX, tmpAlienY, MILLORA_VIDES);
						
					} else {
						
						PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpAlienX, tmpAlienY);
					}
					
				}
				
			}
			
		}
		
	}
	
	return bales;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb el can�./////////////////////////////
/////////////////////////////////Retorna la llista de bales///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbCano (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat)
{
	
	int tmpX, tmpY, modX, modY;
	
	PosaTretAliens(pantalla, bala->x, bala->y);
	
		//Obtenim la posici� de la bala relativa al can�
	tmpX = bala->x - (cano->x - TAMANY_CANO/2);
	tmpY = bala->y - (cano->y - TAMANY_CANO/2);
	
		//Comprovar si toca el can�
	if ( (tmpX >= 0) && (tmpX < TAMANY_CANO) && (tmpY >= 0) ) 
	{
			//La bala est� sobre el can�
		
			//Agafem el m�dul de la posici� per saber si la bala coincideix amb el can�
		modX = tmpX % TAMANY_CANO;
		modY = tmpY % TAMANY_CANO;
		
			//Comprovem si TOCA el can�
		if (cano->forma.punts[modY][modX] != 0) 
		{
			
				//Desactivar i borrar la bala i carregar els aliens
			BorraTret(pantalla, bala->x, bala->y);
			bales = eliminaBala(bales, bala);
			aliens->carregues += 1;
			aliens->carregant = aliens->temps + aleatori(aliens->temps);
			PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
			
				//Baixar una vida
			cano->vides -= 1;
			MostraVides(cano->vides, cano->max_vides);
			
			if (cano->vides == 0) 
			{
				*acabarJoc = TRUE;
				*raoJocAcabat = RAO_JOC_ACABAT_MORT;
			}
			
		}
		
	}
	
	return bales;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si dues bales xoquen./////////////////////////////////////////////////
/////////////////////////////////Retorna la llista de bales///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbBala(int *pantalla, Bala *bales, Bala *bala, Bala *(*next), Nau_Propia *cano, Flota_Alien *aliens, int *balaActiva)
{
	Bala *tmp;

	tmp = bales;
	while(tmp != NULL && *balaActiva)
	{
		if(tmp != bala && tmp->x == bala->x && tmp->y == bala->y && tmp->velocitat != bala->velocitat)
		{
			if(*next == tmp)
			{
				*next = (*next)->seguent;
			}
			BorraTret(pantalla, bala->x, bala->y);
			BorraTret(pantalla, tmp->x, tmp->y);
			bales = eliminaBala(bales, bala);
			bales = eliminaBala(bales, tmp);
			*balaActiva = FALSE;
		}

		if(*balaActiva)
		{
			tmp = tmp->seguent;
		}

	}

	return bales;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou les bales i comprova si xoquen amb algun objecte.//////////////////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *moureBales (int *pantalla, Bala *bales, Nau_Propia *cano, Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *acabarJoc, int *raoJocAcabat)
{
	
	Bala *tmp, *seguent;
	int balaActiva;
	
	tmp = bales;
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		balaActiva = TRUE;
		
		if (tmp->velocitat<0) 
		{
			
				//Moure tret del can�
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a dal de tot
			if (tmp->y < 0) 
			{
				bales = eliminaBala(bales, tmp);
				
				cano->carregues += 1;
				
				balaActiva = FALSE;
				
			}
			
		} else {
			
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a baix de tot
			if (tmp->y >= ALTURA_PANTALLA) 
			{
				bales = eliminaBala(bales, tmp);
				
				aliens->carregues += 1;
				
				balaActiva = FALSE;
			}
			
		}
		
			//Comprovar si la bala segueix activa...
		if (balaActiva)
		{
			//Comprovar si xoca amb una altra bala
			bales = comprovarXocBalaAmbBala(pantalla, bales, tmp, &seguent, cano, aliens, &balaActiva);
			
			if (balaActiva) 
			{
					//Comprovar si xoca amb els escuts
				bales = comprovarXocBalaAmbEscut(pantalla, bales, tmp, bunker, cano, aliens, &balaActiva);
				
					//Si no s'ha desactivat per un escut
				if (balaActiva) 
				{
					
					if (tmp->velocitat < 0) 
					{
						bales = comprovarXocBalaAmbUfo(ufo, cano, bales, tmp, pantalla, &balaActiva);
						if (balaActiva)
							bales = comprovarXocBalaAmbAlien(pantalla, bales, tmp, aliens, cano);
						
					} else {
						
						bales = comprovarXocBalaAmbCano(pantalla, bales, tmp, cano, aliens, acabarJoc, raoJocAcabat);
					}

					
				}
				
			}
		
		}
		
		tmp = seguent;
		
	}
	
	comprovarAliensVius(aliens, acabarJoc, raoJocAcabat);
	
		//Actualitzar el temps d'espera per disparar les bales dels aliens i el cano
	if (cano->carregant > 0) 
	{
		cano->carregant -= 1;
	}
	if (aliens->carregant > 0) 
	{
		aliens->carregant -= 1;
	}
	
	return bales;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Elimina totes les bales de la llista///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void buidarBales (Bala *bales)
{
	
	Bala *tmp, *seguent;
	
	tmp = bales;
	
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		free(tmp);
		tmp = seguent;
		
	}
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Llegeix el fitxer on hi ha les puntuacions guardades.//////////////////////////
///////////////////////////////////Retorna la llista de puntuacions///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Jugador *llegirFitxerPuntuacions(const char *url)
{

	FILE *f;
	int punts;
	char data[20];
	char nom[30];
	Jugador *tmp, *primer, *ordenat;

	f = fopen(url, "a+");

	primer = NULL;
	while(fscanf(f, "%s", nom) != EOF)
	{
		fscanf(f, "%s", data);
		fscanf(f, "%d", &punts);

		tmp = (Jugador *)malloc(sizeof(Jugador));

		tmp->seguent = primer;
		primer = tmp;

		sprintf(tmp->nom, "%s", nom);
		sprintf(tmp->data, "%s", data);
		tmp->puntuacio = punts;
	}

		//Reordenar la llista
	ordenat = NULL;
	while(primer != NULL)
	{
		tmp = primer;
		primer = primer->seguent;
		tmp->seguent = ordenat;
		ordenat = tmp;
	}

	fclose(f);

	return ordenat;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Actualitza la llista de puntuacions amb la puntuacio especificada./////////////
//////////////////////////////////Retorna la llista de puntuacions////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Jugador *afegirPuntuacioJugador(Jugador *primer, char *nom, int puntuacio)
{
	Jugador *nou, *tmp, *borrar;
	struct tm *t;
	time_t sec;
	int sortir, n;

	nou = (Jugador *)malloc(sizeof(Jugador));

	sprintf(nou->nom, "%s", nom);
	nou->puntuacio = puntuacio;

	time(&sec);
	t = localtime(&sec);
	strftime(nou->data, 19, "%d/%m/%Y", t);

	//Buscar la posici� on ha d'anar
	if(primer == NULL)
	{
		primer = nou;
		nou->seguent = NULL;

	} else {

		if (primer->seguent == NULL && puntuacio > primer->puntuacio)
		{
			nou->seguent = primer;
			primer = nou;

		} else {
			
			sortir = FALSE;
			tmp = primer;
			while (tmp != NULL && !sortir)
			{
				if(tmp->seguent == NULL)
				{
					tmp->seguent = nou;
					nou->seguent = NULL;
				
				} else {
				
					if(tmp->seguent->puntuacio < puntuacio)
					{
						nou->seguent = tmp->seguent;
						tmp->seguent = nou;
						sortir = TRUE;
					}

				}

				tmp = tmp->seguent;

			}

		}

	}

		// Borrar totes les puntuacions adicionals d'aquest jugador
	n = 0;
	tmp = primer;
	while (tmp->seguent != NULL)
	{
		if (tmp == primer)
		{
			if (!strcmp(tmp->nom, nom))
			{
				n=1;
			}
		}
		if (!strcmp(tmp->seguent->nom, nom))
		{
			if(n)
			{ //Borrar-lo
				borrar = tmp->seguent;
				tmp->seguent = tmp->seguent->seguent;
				free(borrar);
			}
			else
				n=1;
		}
		if(tmp->seguent != NULL)
			tmp = tmp->seguent;
	}

	return primer;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Guarda les puntuacions en un fitxer////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void guardarFitxerPuntuacions(const char *url, Jugador *primer)
{

	FILE *f;
	Jugador *tmp;
	
	f = fopen(url, "w");

	tmp = primer;
	while (tmp != NULL)
	{
		fprintf(f, "%s\n%s\n%d", tmp->nom, tmp->data, tmp->puntuacio);
		tmp = tmp->seguent;
		if (tmp != NULL)
			fprintf(f, "\n");
	}

	fclose(f);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Elimina la llista de puntuacions.//////////////////////////////////////////////
////////////////////////////////Retorna NULL//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Jugador *netejaPuntuacions(Jugador *primer)
{
	Jugador *tmp;

	while (primer != NULL)
	{
		tmp = primer;
		primer = primer->seguent;
		free(tmp);
	}

	return primer;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Escriu les puntuacions de la llista a la pantalla//////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void escriurePuntuacions(Jugador *primer)
{
	Jugador *tmp;
	int index = 1;

	tmp = primer;
	while(tmp != NULL)
	{
		printf("%d. %d %s\n", index, tmp->puntuacio, tmp->nom);
		index++;
		tmp = tmp->seguent;
	}

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou tots els objectes i comprova si el can� n'agafa cap.///////////////////////
///////////////////////////////////Retorna la llista d'objectes///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Objecte *moureObjectes (int *pantalla, Objecte *primer, Nau_Propia *cano, Bunker *bunker)
{
	
	Objecte *tmp, *seguent;
	int objecteActiu;
	int tmpX, tmpY, dX, dY, modX;
	
		//Actualitzar les millores actives del can�
	if(cano->temps_millora > 0)
		cano->temps_millora -= 1;
	else
		if(cano->millora != 0)
			desactivarMilloresCano(pantalla, cano);


	tmp = primer;
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		objecteActiu = TRUE;
		
		BorraObjecte(pantalla, tmp->x, tmp->y);
		
		tmpX = tmp->x + tmp->v_x;
		tmpY = tmp->y + tmp->v_y;
		
		if(tmp->temps > 0)
			tmp->temps -= 1;
		
		if(tmp->temps == 0 && tmp->v_y == 0)
		{
				BorraObjecte(pantalla, tmp->x, tmp->y);
				primer = eliminaObjecte(primer, tmp);
				objecteActiu = FALSE;
		}
		else
		{
			if(tmpX<0 || tmpX>=AMPLADA_PANTALLA)
			{
				tmpX = tmp->x;
				tmp->v_x = 0;
			}

			if(tmpY >= ALTURA_PANTALLA)
			{
				tmpY = tmp->y;
				tmp->v_y = 0;
				tmp->v_x = 0;
				tmp->temps = TEMPS_OBJECTE;
			}
			else
			{
					//Mirar si est� sobre d'un bunker
				dX = tmpX - bunker->x;
				dY = (tmpY+1) - bunker->y;
				if(dX >= 0 && dX < AMPLADA_BUNKER && dY >= 0 && dY < TAMANY_ESCUT)
				{
					modX = dX%(TAMANY_ESCUT+SEPARACIO_ESCUTS);

					if(modX < TAMANY_ESCUT)
					{
						if(bunker->escuts[(dX/(TAMANY_ESCUT+SEPARACIO_ESCUTS))].forma.punts[dY][modX])
						{
							tmp->v_x = 0;
							tmp->v_y = 0;
							if(tmp->temps == 0)
								tmp->temps = TEMPS_OBJECTE;
						}
						else
						{
							tmp->v_y = VELOCITAT_OBJECTE;
							tmp->temps = 0;
						}
					}
				}
			}
			
				//Comprovar si l'agafa el cano
			dX = tmpX - (cano->x - TAMANY_CANO/2);
			dY = tmpY - (cano->y - TAMANY_CANO/2);
			if(dX >= 0 && dX < TAMANY_CANO && dY >= 0 && dY < TAMANY_CANO)
			{
				if(cano->forma.punts[dY][dX])
				{
					activarMilloraCano(pantalla, cano, tmp->tipus);
					BorraObjecte(pantalla, tmp->x, tmp->y);
					primer = eliminaObjecte(primer, tmp);
					objecteActiu = FALSE;
				}
			}
		}
		if(objecteActiu)
		{
			tmp->x = tmpX;
			tmp->y = tmpY;
			PosaObjecte(pantalla, tmp->x, tmp->y, tmp->dibuix);
		}
		
		tmp = seguent;
		
	}
	
	
	return primer;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Activa la millora especificada del can�////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void activarMilloraCano(int *pantalla, Nau_Propia *cano, int millora)
{
	cano->millora = millora;

	BorraPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
	cano->forma.punts[0][0] = 0;
	cano->forma.punts[0][2] = 0;
	cano->forma.punts[2][1] = cano->forma.punts[1][1];

	switch(millora)
	{
		case MILLORA_BALES:
			cano->temps_millora = TEMPS_MILLORA_BALES;
			cano->forma.punts[0][0] = 3;
			cano->forma.punts[0][2] = 3;
			break;

		case MILLORA_SUPERBALA:
			cano->temps_millora = TEMPS_MILLORA_SUPERBALA;
			cano->forma.punts[2][1] = 3;
			break;
		case MILLORA_VIDES:
			cano->vides = cano->max_vides;
			MostraVides(cano->vides, cano->max_vides);
			break;
	}

	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Desactiva totes les millores del can�//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void desactivarMilloresCano(int *pantalla, Nau_Propia *cano)
{
	cano->millora = 0;
	BorraPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
	inicialitzaDibuixCano(cano->forma.punts);
	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea un nou objecte del tipus especificat./////////////////////////////////////
//////////////////////////////////Retorna la llista d'objectes////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Objecte *crearNouObjecte (Objecte *primer, int v_x, int v_y, int x, int y, int tipus)
{
	
	Objecte *tmp, *ultim, *anterior;
	int dibuix = 20 + tipus;
	
	tmp = (Objecte *)malloc(sizeof(Objecte));
	
		
	if (primer != NULL) 
	{
		ultim = primer;
		while (ultim->seguent != NULL) 
		{
			ultim = ultim->seguent;
			
		}
		
		tmp->seguent = NULL;
		ultim->seguent = tmp;
		
	} else {
		
		primer = tmp;
		tmp->seguent = NULL;
		
	}
	
		//Disparar-la
	tmp->x = x;
	tmp->y = y;
	tmp->tipus = tipus;
	tmp->dibuix = dibuix;
	tmp->temps = 0;
	tmp->v_x = v_x;
	tmp->v_y = v_y;
	
	return primer;
	

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Elimina l'objecte especificat de la llista.////////////////////////////////////
/////////////////////////////////Retorna la llista d'objectes/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Objecte *eliminaObjecte (Objecte *primer, Objecte *eliminar)
{
		
	Objecte *anterior;
	
	if (primer != eliminar) 
	{
		
			//Buscar la bala anterior
		anterior = primer;
		
		while (anterior->seguent != eliminar) 
		{
			anterior = anterior->seguent;
		}
		
		anterior->seguent = eliminar->seguent;
		
		free(eliminar);
		
		eliminar = NULL;
		
	} else {
		
		anterior = primer;
		primer = primer->seguent;
		free(anterior);
		eliminar = NULL;
		
	}
	
	return primer;
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Elimina tots els objectes de la llista/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void buidarObjectes (Objecte *primer)
{
		
	Objecte *tmp, *seguent;
	
	tmp = primer;
	
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		free(tmp);
		tmp = seguent;
		
	}
	
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea el taulell per multijugador///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void CreaTaulell_m(void)
{
	// ------------------------------------------------------------------------------
	int C0, C1, F0, F1, FJugador, FPunts, FTaulell, FVides;
	char TXTjugador[10]="Jugador";
	char TXTpunts[10]="Punts";
	char TXTvides[10]="Jugador 1";
	char TXTvides_2[10]="Jugador 2";
	char TXTnivell[10]="Nivell";
	
	// ------------------------------------------------------------------------------
	C0=1+ DespC; // Columna inicial comptant el desplassament:
	C1=DespC+ AmpladaTaulell; // Columna final comptant el desplassament:
	F0=1+ DespF; // Fila inicial comptant el desplassament:
	F1=DespF+ AlssadaTaulell; // Fila final comptant el desplasament:

	// ------------------------------------------------------------------------------
	// Quadre de jugador:
	FJugador=F0;
	FPunts=F0;
	FTaulell=F0+4;
	FVides=F0+AlssadaTaulell+5;

	//CreaQuadre(C0,FJugador, LJugador, 3, TXTjugador);
	CreaQuadre(C0+AmpladaTaulell-LPunts,FPunts, LPunts, 3, TXTpunts);
	CreaQuadre( (C0+AmpladaTaulell/2),FJugador, LNivell, 3, TXTnivell);

	CreaQuadre(C0,FTaulell, AmpladaTaulell, AlssadaTaulell,NULL);

	CreaQuadre(VIDES_M_1_X, FVides, L_VIDES_M+2, 3, TXTvides);
	CreaQuadre(VIDES_M_2_X, FVides, L_VIDES_M+2, 3, TXTvides_2);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mostra les vides del jugador 1/////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void MostraVides_m_1(int NVides, int MaxVides)
{

	// ------------------------------------------------------------------------------
	int C0,F0,n, CAR;
	int vides;
	int STR[L_VIDES_M];

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);


	for(n=0;n<L_VIDES_M;n++)
		STR[n] = 0;

	vides = (int)(NVides/(float)MaxVides * L_VIDES_M);
	// ------------------------------------------------------------------------------
	C0=1+VIDES_M_1_X;
	F0=DespF+AlssadaTaulell+8;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,RED,screen);

	CAR = ObtenirCaracter(4);
	// ------------------------------------------------------------------------------
	for(n=1;n<=vides;n++)
		STR[n-1]=CAR; //COR.

	// ------------------------------------------------------------------------------
	for(n=0;n<L_VIDES_M;n++)
		printf("%c",STR[n]);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mostra les vides del jugador 2/////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void MostraVides_m_2(int NVides, int MaxVides)
{

	// ------------------------------------------------------------------------------
	int C0,F0,n, CAR;
	int vides;
	int STR[L_VIDES_M];

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);


	for(n=0;n<L_VIDES_M;n++)
		STR[n] = 0;

	vides = (int)(NVides/(float)MaxVides * L_VIDES_M);
	// ------------------------------------------------------------------------------
	C0=1+VIDES_M_2_X;
	F0=DespF+AlssadaTaulell+8;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,RED,screen);

	CAR = ObtenirCaracter(4);
	// ------------------------------------------------------------------------------
	for(n=1;n<=vides;n++)
		STR[n-1]=CAR; //COR.

	// ------------------------------------------------------------------------------
	for(n=0;n<L_VIDES_M;n++)
		printf("%c",STR[n]);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Juga una partida al nivell especificat/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugarNivell_m(void)
{

	int nivell, acabarJoc, raoJocAcabat;
	int punts;
	char nomJugador[30];
	
	system("cls");
	
	printf("Quin nivell vols jugar?\n");
	scanf("%d", &nivell);
	system("cls");

	if (nivell > MAX_NIVELL)
		nivell = MAX_NIVELL;

	jugar_m(&acabarJoc, &raoJocAcabat, nivell);

	if (raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		raoJocAcabat = RAO_JOC_ACABAT_GUANYAT;
		//Escriure la ra� per la que ha finalitzat el joc
	system("cls");
	switch (raoJocAcabat) 
	{
		case RAO_JOC_ACABAT_SORTIR:
			printf("Has aturat el joc.\n");
			break;
		case RAO_JOC_ACABAT_PERDUT:
			printf("Game Over: has perdut.\n");
			break;
		case RAO_JOC_ACABAT_GUANYAT:
			printf("Has destruit els aliens abans que arribessin!.\n");
			break;
		case RAO_JOC_ACABAT_MORT:
			printf("Has perdut totes les teves vides, els alien�genes han guanyat.\n");
			break;
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Juga una partida///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugarPartida_m(void)
{

	int acabarJoc, raoJocAcabat;
	char nomJugador[30];

	system("cls");

	raoJocAcabat = -1;

	jugar_m (&acabarJoc, &raoJocAcabat, 1);

	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		jugar_m (&acabarJoc, &raoJocAcabat, 2);

	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		jugar_m (&acabarJoc, &raoJocAcabat, 3);
	
		//Escriure la ra� per la que ha finalitzat el joc
	system("cls");
	
	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
		raoJocAcabat = RAO_JOC_ACABAT_GUANYAT;
	
	
	switch (raoJocAcabat) 
	{
		case RAO_JOC_ACABAT_SORTIR:
			printf("Has aturat el joc.\n");
			break;
		case RAO_JOC_ACABAT_PERDUT:
			printf("Game Over: has perdut.\n");
			break;
		case RAO_JOC_ACABAT_GUANYAT:
			printf("Has destruit els aliens abans que arribessin!.\n");
			break;
		case RAO_JOC_ACABAT_MORT:
			printf("Has perdut totes les teves vides, els alien�genes han guanyat.\n");
			break;
	}
	

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Funci� del joc: bucle principal////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugar_m (int *acabarJoc, int *raoJocAcabat, int nivell)
{
	
	Flota_Alien aliens;
	Nau_Propia cano[MAX_JUGADORS];
	Bala *bales;
	Bunker bunker;
	Platet ufo;
	int pausa;
	int temps;
	int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA];
	char tecla;
	int punts = 0;

	CreaTaulell_m();

	prepararJoc_m (pantalla, cano, &aliens, &bunker, &ufo, &pausa, &punts, nivell);

	bales = NULL;
	
	espera(pantalla);

	temps = 0;
	*acabarJoc = FALSE;
	do {
		
		if (!pausa) 
		{
			
			if (temps%TEMPS_CANO == 0)
				bales = ferAccionsTeclat_m(pantalla, cano, bales, acabarJoc, raoJocAcabat, &pausa);
			
			if(!pausa)
			{
				
				if (temps%aliens.bucles == 0)
					moureAliens(pantalla, &aliens, acabarJoc, raoJocAcabat, &bunker);

				if (temps%ufo.bucles == 0)
				{
					creaUfo(&ufo, pantalla);
					moureUfo(&ufo, pantalla);
				}

				if (temps%TEMPS_BALA == 0)
					bales = dispararBalaAliens_m(pantalla, bales, &aliens, cano);
				
				if (temps%TEMPS_BALA == 0)
					bales = moureBales_m(pantalla, bales, cano, &aliens, &bunker, &ufo, acabarJoc, raoJocAcabat);

				//Per a que els aliens no deixin objectes
				buidarObjectes(cano[0].objectes);
				cano[0].objectes = NULL;
				buidarObjectes(cano[1].objectes);
				cano[1].objectes = NULL;

				MostraPunts(cano[0].punts);
				
				Sleep(RETRAS);

			}
		} else {
			
			if (_kbhit()) 
			{
				
				while(_kbhit()) tecla = getch();
				
				if (tecla == 'p' || tecla == 'P') 
				{
					system("cls");
					CreaTaulell_m();
					MostraPunts(cano[0].punts);
					MostraVides_m_2(cano[0].vides, cano[0].max_vides);
					MostraVides_m_1(cano[1].vides, cano[0].max_vides);
					dibuixarPantalla_m (pantalla, cano, &aliens, &bunker, &ufo, bales);
					pausa = FALSE;
					espera(pantalla);
				}
				
			}
			
		}
		
		temps++;

	} while (!(*acabarJoc));
	
		//Netejar el punter de bales
	buidarBales(bales);
	bales = NULL;

		//Actualitzar la puntuaci� general

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Dibuixa tots els objectes a la pantalla////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void dibuixarPantalla_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, Bala *bales)
{
	Bala *tmp;
	int i, j, tmpX, tmpY;


		//Dibuixar el cano
	if (cano[0].vides)
		PosaPersonatge(cano[0].forma.punts, pantalla, cano[0].x, cano[0].y);
	if(cano[1].vides)
		PosaPersonatge(cano[1].forma.punts, pantalla, cano[1].x, cano[1].y);

		//Dibuixar els aliens
	for (i=0; i<FILES_ALIENS; i++) 
	{
		for (j=0; j<COLUMNES_ALIENS; j++) 
		{
			
			if(aliens->naus[i][j].viu)
			{
				tmpX = aliens->x + j*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
				tmpY = aliens->y + i*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
				PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpX, tmpY);
			}
		}
	}

		//Dibuixar el bunker
	for (i=0; i<MAX_ESCUTS; i++) 
	{
		tmpX = bunker->x + i*(TAMANY_ESCUT + SEPARACIO_ESCUTS) + TAMANY_ESCUT/2;
		tmpY = bunker->y + TAMANY_ESCUT/2;
		PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, tmpX, tmpY);
	}

		//Dibuixar el platet
	if(ufo->actiu)
	{
		PosaPersonatge (ufo->forma.punts, pantalla, (ufo->x+TAMANY_ALIEN/2), (ufo->y+TAMANY_ALIEN/2));
	}

		//Dibuixar les bales
	tmp = bales;
	while (tmp != NULL)
	{
		if(tmp->velocitat > 0)
			PosaTretAliens(pantalla, tmp->x, tmp->y);
		else
			PosaTretCano(pantalla, tmp->x, tmp->y);

		tmp = tmp->seguent;
	}

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicialitza els dibuixos del can�//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void inicialitzaDibuixCano_m(Nau_Propia cano[MAX_JUGADORS])
{
	int d[TAMANY_CANO][TAMANY_CANO] = DIBUIX_NAU;
	int e[TAMANY_CANO][TAMANY_CANO] = DIBUIX_NAU_2;
	int f, c;

	for (f=0; f<TAMANY_CANO; f++)
		for (c=0; c<TAMANY_CANO; c++)
			cano[0].forma.punts[f][c] = d[f][c];

	for (f=0; f<TAMANY_CANO; f++)
		for (c=0; c<TAMANY_CANO; c++)
			cano[1].forma.punts[f][c] = e[f][c];

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicialitza les variables per la partida///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void prepararJoc_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *pausa, int *punts, int nivell)
{
	
	int i, j, tmpX, tmpY;

	switch (nivell)
	{
		case 1:
			cano[0].max_vides = VIDES_JUGADOR_1;
			aliens->bucles = TEMPS_ALIENS_1;
			aliens->temps = 3*ALIENS_TEMPS_CARREGANT + aleatori(3*ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_1_M;
			aliens->vides = 1;
			break;

		case 2:
			cano[0].max_vides = VIDES_JUGADOR_2;
			aliens->bucles = TEMPS_ALIENS_2;
			aliens->temps = 2*ALIENS_TEMPS_CARREGANT + aleatori(2*ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_2_M;
			aliens->vides = 2;
			break;

		case 3:
			cano[0].max_vides = VIDES_JUGADOR_3;
			aliens->bucles = TEMPS_ALIENS_3;
			aliens->temps = ALIENS_TEMPS_CARREGANT + aleatori(ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_3_M;
			aliens->vides = 3;
			break;
			
		default:
			cano[0].max_vides = VIDES_JUGADOR_3;
			aliens->bucles = TEMPS_ALIENS_3;
			aliens->temps = ALIENS_TEMPS_CARREGANT + aleatori(ALIENS_TEMPS_CARREGANT);
			aliens->dmax_bales = DISTANCIA_TRETS_ALIEN_3_M;
			aliens->vides = 3;
			break;
	}

	cano[0].x = 3* INICI_CANO_X/2;
	cano[0].y = INICI_CANO_Y;
	cano[1].x = INICI_CANO_X/2;
	cano[1].y = INICI_CANO_Y;
	inicialitzaDibuixCano_m(cano);

	cano[0].temps = CANO_TEMPS_CARREGANT;
	cano[0].max_bales = CANO_BALES;
	cano[0].carregues = cano[0].max_bales;
	cano[0].carregant = 0;
	cano[0].vides = cano[0].max_vides;
	cano[0].punts = *punts;
	cano[0].objectes = NULL;
	MostraPunts(cano[0].punts);
	MostraVides_m_2(cano[0].vides, cano[0].max_vides);

	cano[1].temps = CANO_TEMPS_CARREGANT;
	cano[1].carregues = cano[0].max_bales;
	cano[1].carregant = 0;
	cano[1].vides = cano[0].max_vides;
	cano[1].objectes = NULL;
	MostraVides_m_1(cano[1].vides, cano[0].max_vides);
	
		//Pintar el cano
	PosaPersonatge(cano[0].forma.punts, pantalla, cano[0].x, cano[0].y);
	PosaPersonatge(cano[1].forma.punts, pantalla, cano[1].x, cano[1].y);

	ufo->v_x = 0;
	ufo->v_y = 0;
	ufo->actiu = FALSE;
	ufo->x = -1;
	ufo->y = -1;
	ufo->bucles = TEMPS_UFO;
	ufo->espera = 30 + aleatori(ESPERA_UFO);

	inicialitzaDibuixPlatet(ufo->forma.punts);

	aliens->x = INICI_ALIENS_X;
	aliens->y = INICI_ALIENS_Y;
	aliens->velocitat = VELOCITAT_ALIENS;
	inicialitzaDibuixAliens(aliens->forma);

	aliens->max_bales = ALIENS_BALES;
	aliens->carregues = aliens->max_bales;
	aliens->carregant = aliens->temps + aleatori(aliens->temps);
	
	for (i=0; i<FILES_ALIENS; i++) 
	{
		aliens->vius_files[i] = COLUMNES_ALIENS;
	}
	for (i=0; i<COLUMNES_ALIENS; i++) 
	{
		aliens->vius_columnes[i] = FILES_ALIENS;
	}
	
	
		//Inicialitzar la matriu d'aliens i pintarlos a la pantalla
	for (i=0; i<FILES_ALIENS; i++) 
	{
		for (j=0; j<COLUMNES_ALIENS; j++) 
		{
			
			aliens->naus[i][j].viu = aliens->vides;
			tmpX = aliens->x + j*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
			tmpY = aliens->y + i*(TAMANY_ALIEN + SEPARACIO_ALIENS)+(TAMANY_ALIEN/2);
			PosaPersonatge(aliens->forma[aliens->vides - (aliens->naus[i][j].viu)].punts, pantalla, tmpX, tmpY);
			
		}
	}
	
	bunker->x = INICI_BUNKER_X;
	bunker->y = INICI_BUNKER_Y;
	
	for (i=0; i<MAX_ESCUTS; i++) 
	{
		inicialitzaDibuixEscut(bunker->escuts[i].forma.punts);
		tmpX = bunker->x + i*(TAMANY_ESCUT + SEPARACIO_ESCUTS) + TAMANY_ESCUT/2;
		tmpY = bunker->y + TAMANY_ESCUT/2;
		PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, tmpX, tmpY);
	}
	
	*pausa = FALSE;
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea i situa una bala pel can� especificat.////////////////////////////////////
////////////////////////////////////Retorna la llista de bales////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *dispararBalaCano_m (int *pantalla, Bala *bales, Nau_Propia *cano)
{
	
	Bala *tmp;
	
	if (cano->carregant == 0) 
	{
		
		tmp = crearNovaBala(bales, VELOCITAT_BALA*(-1), cano->x, (cano->y - 2));
		if (bales == NULL)
		{
			bales = tmp;
		}
		PosaTretCano(pantalla, tmp->x, tmp->y);
		
		cano->carregant = cano->temps;
		
	}
	
	return bales;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si s'ha pressionat alguna tecla i fa les accions//////////////////////
///////////////////////////////////que calgui. Retorna la llista de bales/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *ferAccionsTeclat_m (int *pantalla, Nau_Propia cano[MAX_JUGADORS], Bala *bales, int *acabarJoc, int *raoJocAcabat, int *pausa)
{
	
	char tecla;
	int bales_1=FALSE, bales_2=FALSE, moviment_1=FALSE, moviment_2=FALSE;
	
		//Comprovar si s'ha pressionat alguna tecla
	if (_kbhit()) 
	{
		
		while(_kbhit() && !(*acabarJoc)) 
		{
			tecla = getch();
			
			switch (tecla) 
			{
				case KEY_RIGHT:
					if (!moviment_1 && cano[0].vides)
					{
						moureCano(pantalla, &(cano[0]), VELOCITAT_NAU);
						moviment_1 = TRUE;
					}
					break;
					
				case KEY_LEFT:
					if (!moviment_1 && cano[0].vides)
					{
						moureCano(pantalla, &(cano[0]), (-1)*VELOCITAT_NAU);
						moviment_1 = TRUE;
					}
					break;
					
				case KEY_UP:
					if (!bales_1 && cano[0].vides)
					{
						bales = dispararBalaCano_m(pantalla, bales, &(cano[0]));
						bales_1 = TRUE;
					}
					break;

				case 'd':
					if (!moviment_2 && cano[1].vides)
					{
						moureCano(pantalla, &(cano[1]), VELOCITAT_NAU);
						moviment_2 = TRUE;
					}
					break;

				case 'D':
					if (!moviment_2 && cano[1].vides)
					{
						moureCano(pantalla, &(cano[1]), VELOCITAT_NAU);
						moviment_2 = TRUE;
					}
					break;
					
				case 'a':
					if (!moviment_2 && cano[1].vides)
					{
						moureCano(pantalla, &(cano[1]), (-1)*VELOCITAT_NAU);
						moviment_2 = TRUE;
					}
					break;
					
				case 'A':
					if (!moviment_2 && cano[1].vides)
					{
						moureCano(pantalla, &(cano[1]), (-1)*VELOCITAT_NAU);
						moviment_2 = TRUE;
					}
					break;

				case 'w':
					if (!bales_2 && cano[1].vides)
					{
						bales = dispararBalaCano_m(pantalla, bales, &(cano[1]));
						bales_2 = TRUE;
					}
					break;

				case 'W':
					if (!bales_1 && cano[1].vides)
					{
						bales = dispararBalaCano_m(pantalla, bales, &(cano[1]));
						bales_2 = TRUE;
					}
					break;
				
				case 'p':
					*pausa = TRUE;
					system("cls");
					printf("Apreta P per sortir de la pausa.\n");
					break;
					
				case 'P':
					*pausa = TRUE;
					system("cls");
					printf("Apreta P per sortir de la pausa.\n");
					break;
					
				case KEY_ESC:
					*acabarJoc = TRUE;
					*raoJocAcabat = RAO_JOC_ACABAT_SORTIR;
					break;
					
			}

		}
		if(!(*pausa))
		{
			if(cano[0].vides)
				PosaPersonatge(cano[0].forma.punts, pantalla, cano[0].x, cano[0].y);
			if(cano[1].vides)
				PosaPersonatge(cano[1].forma.punts, pantalla, cano[1].x, cano[1].y);
		}

	}

	return bales;
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Crea i situa una bala pels aliens./////////////////////////////////////////////
///////////////////////////////////Retorna la llista de bales/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *dispararBalaAliens_m (int *pantalla, Bala *bales, Flota_Alien *aliens, Nau_Propia cano[MAX_JUGADORS])
{
	
	Bala *tmp;
	int rnd, columnesVius, maxColumnes, columnesMirades, i, j, k;
	int columna, primerViu, ultimViu, viuGran;
	int x, y, alienX_1, alienX_2;
	

	if ( (aliens->carregues > 0) && (aliens->carregant == 0) ) 
	{
		
		primerViu = 0;
		for(i=0; i<COLUMNES_ALIENS; i++)
			if (aliens->vius_columnes[i] > 0 && primerViu == 0) primerViu = i;

		alienX_1 = min(COLUMNES_ALIENS-1, max(0, (cano[0].x - aliens->x)/(TAMANY_ALIEN+SEPARACIO_ALIENS)));
		alienX_2 = min(COLUMNES_ALIENS-1, max(0, (cano[1].x - aliens->x)/(TAMANY_ALIEN+SEPARACIO_ALIENS)));

		if(!cano[0].vides)
			alienX_1 = alienX_2;
		
		if(!cano[1].vides)
			alienX_2 = alienX_1;

			//Buscar el total de columnes amb aliens vius
		columnesVius = 0;
		maxColumnes = 0;
		for (i=0; i<COLUMNES_ALIENS; i++) 
		{
			if (aliens->vius_columnes[i]>0) 
			{
				maxColumnes++;
				if ( (abs(i-alienX_1) <= aliens->dmax_bales/2+aliens->dmax_bales%2) 
					|| (abs(i-alienX_2) <= aliens->dmax_bales/2+aliens->dmax_bales%2) )
				{
					columnesVius += 1;
				}
			}
		}
		
		rnd = aleatori(max(columnesVius, (aliens->dmax_bales/2 + aliens->dmax_bales%2)));
		
			//Buscar la columan des d'on es dispara
		columnesVius = 0;
		columnesMirades = 0;
		columna = -1;
		
		while ( columnesMirades < maxColumnes && columnesVius < rnd ) 
		{
			columna += 1;
			
			if (aliens->vius_columnes[columna] > 0) 
			{
				columnesMirades += 1;

				if (  (abs(columna-alienX_1) <= aliens->dmax_bales/2+aliens->dmax_bales%2) 
					|| (abs(columna-alienX_2) <= aliens->dmax_bales/2+aliens->dmax_bales%2) )
				{
					columnesVius += 1;
				}
			}

		}
		
			//Buscar l'ultim alien viu de la columna
		for (i=0; i<FILES_ALIENS; i++) 
		{
			if ( aliens->naus[i][columna].viu ) 
			{
				ultimViu = i;
			}
		}
		
		viuGran = 0;
		for (i=0; i<COLUMNES_ALIENS; i++)
			if (aliens->naus[ultimViu][i].viu)
				for(j=0; j<TAMANY_ALIEN; j++)
					for(k=0; k<TAMANY_ALIEN; k++)
						if(aliens->forma[aliens->vides - (aliens->naus[ultimViu][i].viu)].punts[k][j]!=0 && (k+1)>viuGran) 
							viuGran = k+1;
		
			//Disparar la bala
		x = aliens->x + columna*(TAMANY_ALIEN + SEPARACIO_ALIENS) + (TAMANY_ALIEN/2);
		y = aliens->y + (ultimViu)*(TAMANY_ALIEN + SEPARACIO_ALIENS) + TAMANY_ALIEN - aliens->vides + viuGran;
		tmp = crearNovaBala(bales, VELOCITAT_BALA, x, y);

		if(bales == NULL)
		{
			bales = tmp;
		}

		PosaTretAliens(pantalla, x, y);
		
		aliens->carregant = aliens->temps + aleatori(aliens->temps);
		aliens->carregues = aliens->carregues - 1;
		
	}
	
	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si alguna bala xoca amb algun cano.///////////////////////////////////
///////////////////////////////////Retorna la llista de bales/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbCano_m (int *pantalla, Bala *bales, Bala *bala, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, int *acabarJoc, int *raoJocAcabat)
{
	
	int tmpX, tmpY, modX, modY, desactivarTret=FALSE;
	
	PosaTretAliens(pantalla, bala->x, bala->y);
	
	if(cano[0].vides)
	{
			//Obtenim la posici� de la bala relativa al can�
		tmpX = bala->x - (cano[0].x - TAMANY_CANO/2);
		tmpY = bala->y - (cano[0].y - TAMANY_CANO/2);
		
			//Comprovar si toca el can�
		if ( (tmpX >= 0) && (tmpX < TAMANY_CANO) && (tmpY >= 0) ) 
		{
				//La bala est� sobre el can�
			
				//Agafem el m�dul de la posici� per saber si la bala coincideix amb el can�
			modX = tmpX % TAMANY_CANO;
			modY = tmpY % TAMANY_CANO;
			
				//Comprovem si TOCA el can�
			if (cano[0].forma.punts[modY][modX] != 0) 
			{
				
				desactivarTret = TRUE;

					//Baixar una vida
				cano[0].vides -= 1;

				MostraVides_m_2(cano[0].vides, cano[0].max_vides);
				
			}
			
		}

	}

	if (cano[1].vides)
	{
			//Obtenim la posici� de la bala relativa al can� 2
		tmpX = bala->x - (cano[1].x - TAMANY_CANO/2);
		tmpY = bala->y - (cano[1].y - TAMANY_CANO/2);
		
			//Comprovar si toca el can�
		if ( (tmpX >= 0) && (tmpX < TAMANY_CANO) && (tmpY >= 0) ) 
		{
				//La bala est� sobre el can�
			
				//Agafem el m�dul de la posici� per saber si la bala coincideix amb el can�
			modX = tmpX % TAMANY_CANO;
			modY = tmpY % TAMANY_CANO;
			
				//Comprovem si TOCA el can�
			if (cano[1].forma.punts[modY][modX] != 0) 
			{
				
				desactivarTret = TRUE;

					//Baixar una vida
				cano[1].vides -= 1;

				MostraVides_m_1(cano[1].vides, cano[0].max_vides);
				
			}
			
		}
	
	}

	
	if (desactivarTret)
	{
			//Desactivar i borrar la bala i carregar els aliens
		BorraTret(pantalla, bala->x, bala->y);
		bales = eliminaBala(bales, bala);
		aliens->carregues += 1;
		if(cano[0].vides)
		{
			PosaPersonatge(cano[0].forma.punts, pantalla, cano[0].x, cano[0].y);
		}
		else
		{
			BorraPersonatge(cano[0].forma.punts, pantalla, cano[0].x, cano[0].y);
		}

		if(cano[1].vides)
		{
			PosaPersonatge(cano[1].forma.punts, pantalla, cano[1].x, cano[1].y);
		}
		else
		{
			BorraPersonatge(cano[1].forma.punts, pantalla, cano[1].x, cano[1].y);
		}
			
	}
	
	if (cano[0].vides < 1 && cano[1].vides < 1) 
	{
		*acabarJoc = TRUE;
		*raoJocAcabat = RAO_JOC_ACABAT_MORT;
	}

	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Multijugador///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou les bales i comprova si xoquen amb algun objecte.//////////////////////////
//////////////////////////////////////Retorna la llista de bales//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *moureBales_m (int *pantalla, Bala *bales, Nau_Propia cano[MAX_JUGADORS], Flota_Alien *aliens, Bunker *bunker, Platet *ufo, int *acabarJoc, int *raoJocAcabat)
{
	
	Bala *tmp, *seguent;
	int balaActiva;
	
	tmp = bales;
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		balaActiva = TRUE;
		
		if (tmp->velocitat<0) 
		{
			
				//Moure tret del can�
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a dal de tot
			if (tmp->y < 0) 
			{
				bales = eliminaBala(bales, tmp);
				
				balaActiva = FALSE;
				
			}
			
		} else {
			
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a baix de tot
			if (tmp->y >= ALTURA_PANTALLA) 
			{
				bales = eliminaBala(bales, tmp);
				
				aliens->carregues += 1;
				
				balaActiva = FALSE;
			}
			
		}
		
			//Comprovar si la bala segueix activa...
		if (balaActiva)
		{
			//Comprovar si xoca amb una altra bala
			bales = comprovarXocBalaAmbBala(pantalla, bales, tmp, &seguent, &(cano[0]), aliens, &balaActiva);
			
			if (balaActiva) 
			{
					//Comprovar si xoca amb els escuts
				bales = comprovarXocBalaAmbEscut(pantalla, bales, tmp, bunker, &(cano[0]), aliens, &balaActiva);
				
					//Si no s'ha desactivat per un escut
				if (balaActiva) 
				{
					
					if (tmp->velocitat < 0) 
					{
						bales = comprovarXocBalaAmbUfo(ufo, &(cano[0]), bales, tmp, pantalla, &balaActiva);
						if (balaActiva)
							bales = comprovarXocBalaAmbAlien(pantalla, bales, tmp, aliens, &(cano[0]));
						
					} else {
						
						bales = comprovarXocBalaAmbCano_m(pantalla, bales, tmp, cano, aliens, acabarJoc, raoJocAcabat);
					}

					
				}
				
			}
		
		}
		
		tmp = seguent;
		
	}
	
	comprovarAliensVius(aliens, acabarJoc, raoJocAcabat);
	
		//Actualitzar el temps d'espera per disparar les bales dels aliens i el cano
	if (cano[0].carregant > 0) 
	{
		cano[0].carregant -= 1;
	}
	if (cano[1].carregant > 0) 
	{
		cano[1].carregant -= 1;
	}

	if (aliens->carregant > 0) 
	{
		aliens->carregant -= 1;
	}
	
	return bales;

}








//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicia una partida al nivell extra del joc/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void jugarFSM()
{
	Nau_Propia cano;
	tFsm fsm;
	Bala *bales, *tmp;
	Platet naus[PLATETS_FSM];
	Platet alienRandom;
	Bunker bunker;
	int pausa;
	int temps, t;
	int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA];
	char tecla;
	int punts = 0;
	int acabarJoc;
	int raoJocAcabat;
	int i, j, f, c;
	int nivell = 0;
	int pos[4];
	int linia[1][AMPLADA_PANTALLA];

	system("cls");

	CreaTaulell();

	espera(pantalla);

	prepararFSM(pantalla, &cano, &bunker, naus, &alienRandom, &fsm, &pausa, &punts);

	for(i=0; i<AMPLADA_PANTALLA; i++)
		linia[0][i] = 1;

	bales = NULL;

	// Bucle d'inici

	temps = 0;
	acabarJoc = FALSE;

	MostraPunts(cano.punts);
	MostraNivell(nivell);


		// FASE 0
	do {
	
		if (temps == 20)
		{
			for(i=0; i<MAX_ESCUTS; i++)
			{
				for(f=0; f<TAMANY_ESCUT; f++)
				{
					for(c=0; c<TAMANY_ESCUT; c++)
					{
						if(bunker.escuts[i].forma.punts[f][c])
						{
							tmp = crearNovaBala(bales, 1, bunker.x + i*(TAMANY_ESCUT+SEPARACIO_ESCUTS)-c+TAMANY_ESCUT-1, fsm.y+ALTURA_SFSM-f+TAMANY_ESCUT-1);
							if(bales==NULL)
								bales = tmp;
						
						}
					}
				}
			}
		}

		if (temps%TEMPS_BALA == 0)
			bales = moureBalesFSM(pantalla, bales, &cano, &bunker, &fsm, naus, &alienRandom, 0, &acabarJoc, &raoJocAcabat);
		
		if(bales==NULL && temps>20)
			acabarJoc = TRUE;
		
		if (temps%TEMPS_BALA == 0)
			MostraPantalla(pantalla);
		
		Sleep(RETRAS);

		
		temps++;

	} while (!(acabarJoc));



		//---------------------------------
		// FASE 1
	PosaPersonatge2(linia, pantalla, 0, fsm.y+ALTURA_SFSM+2, AMPLADA_PANTALLA, 1);
	for(i=0; i<PLATETS_FSM; i++)
	{
		PosaPersonatge(naus[i].forma.punts, pantalla, naus[i].x + TAMANY_ALIEN/2, naus[i].y + TAMANY_ALIEN/2);
	}

	acabarJoc = FALSE;
	do {
		
		if (!pausa) 
		{
			
			if (temps%TEMPS_CANO == 0)
				bales = ferAccionsTeclat(pantalla, &cano, bales, &acabarJoc, &raoJocAcabat, &pausa);
			
			if(!pausa)
			{
				
				if (temps%TEMPS_ALIENS_3 == 0)
				{	
					bales = mourePlatetsFSM (pantalla, naus, bales, temps);
				}
				
				if (temps%TEMPS_BALA == 0)
					bales = moureBalesFSM(pantalla, bales, &cano, &bunker, &fsm, naus, &alienRandom, fsm.y+ALTURA_SFSM+3, &acabarJoc, &raoJocAcabat);
				
				MostraPunts(cano.punts);
				MostraNivell(nivell);
				
				if (temps%TEMPS_BALA == 0)
					MostraPantalla(pantalla);

				if(acabarJoc == FALSE)
				{
					acabarJoc = TRUE;
					for(i=0; i<PLATETS_FSM; i++)
					{
						if(naus[i].actiu)
						{
							acabarJoc = FALSE;
							raoJocAcabat = RAO_JOC_ACABAT_NO_ACABAT;
						}
					}
				}
				
				Sleep(RETRAS);

			}
		} else {
			
			if (_kbhit()) 
			{
				
				while(_kbhit()) tecla = getch();
				
				if (tecla == 'p' || tecla == 'P') 
				{
					system("cls");
					CreaTaulell();
					MostraPunts(cano.punts);
					MostraVides(cano.vides, cano.max_vides);
					dibuixarPantallaFSM(pantalla, &cano, naus, &alienRandom, &fsm, bales, linia);
					MostraPantalla(pantalla);
					pausa = FALSE;
				}
				
			}
			
		}
		
		temps++;

	} while (!(acabarJoc));
	
	


		//---------------------------------
		// FASE 2
	if(raoJocAcabat == RAO_JOC_ACABAT_NO_ACABAT)
	{

		alienRandom.actiu = 1;
		alienRandom.x = aleatori(AMPLADA_PANTALLA-TAMANY_ALIEN);
		alienRandom.y = aleatori(ALTURA_PANTALLA-(fsm.y+ALTURA_SFSM+2)-TAMANY_ALIEN-3*TAMANY_CANO) + (fsm.y+ALTURA_SFSM+1);
		PosaPersonatge(alienRandom.forma.punts, pantalla, alienRandom.x + TAMANY_ALIEN/2, alienRandom.y + TAMANY_ALIEN/2);

		BorraPersonatge2(linia, pantalla, 0, fsm.y+ALTURA_SFSM+2, AMPLADA_PANTALLA, 1);

		fsm.ulls[0] = TRUE;
		fsm.ulls[1] = FALSE;

		for(i=0; i<2; i++)
		{
			for(j=0;j<3;j++)
			{
				fsm.dibuix[i+2][j+9] = 9;
			}
		}
		PosaPersonatge2(fsm.dibuix, pantalla, fsm.x, fsm.y, AMPLADA_SFSM, ALTURA_SFSM);

		acabarJoc = FALSE;
		do {
			
			if (!pausa) 
			{
				
				if (temps%TEMPS_CANO == 0)
					bales = ferAccionsTeclat(pantalla, &cano, bales, &acabarJoc, &raoJocAcabat, &pausa);
				
				if(!pausa)
				{
					
					if (temps%TEMPS_BALA == 0)
						bales = moureBalesFSM(pantalla, bales, &cano, &bunker, &fsm, naus, &alienRandom, 0, &acabarJoc, &raoJocAcabat);
					if(temps%20 == 0 && alienRandom.actiu)
						bales = moureRandom (pantalla, &fsm, &alienRandom, bales);
					
					MostraPunts(cano.punts);
					MostraNivell(nivell);
					
					if (temps%TEMPS_BALA == 0)
						MostraPantalla(pantalla);
					
					if(fsm.vides == 0)
					{
						fsm.ulls[0]=FALSE;
						fsm.ulls[1]=FALSE;
						for(i=0; i<2; i++)
						{
							for(j=0;j<3;j++)
							{
								fsm.dibuix[i+2][j+9] = 10;
								fsm.dibuix[i+2][j+24] = 10;
								PosaPersonatge2(&(fsm.dibuix[i+2][j+9]), pantalla, fsm.x + j + 9, fsm.y+i+2, 1, 1);
								PosaPersonatge2(&(fsm.dibuix[i+2][j+24]), pantalla, fsm.x + j + 24, fsm.y+i+2, 1, 1);
							}
						}
						alienRandom.actiu = FALSE;
						BorraPersonatge(alienRandom.forma.punts, pantalla, alienRandom.x+1, alienRandom.y+1);
						pos[0] = 0;
						pos[1] = AMPLADA_PANTALLA/2;
						pos[2] = AMPLADA_PANTALLA/2;
						pos[3] = AMPLADA_PANTALLA;
						fsm.vides = -1;
						t = 0;
						tmp = bales;
						while(tmp!=NULL)
						{
							BorraTret(pantalla, tmp->x, tmp->y);
							tmp=tmp->seguent;
						}
						buidarBales(bales);
						bales = NULL;
						PosaPersonatge2(fsm.dibuix, pantalla, fsm.x, fsm.y, AMPLADA_SFSM, ALTURA_SFSM);
						cano.carregues = 0;

					}
					if (temps%TEMPS_BALA == 0)
					{
						if(fsm.vides == -1)
						{
							t++;
							if(t<300 && t%8==0)
							{
								tmp = crearNovaBala(bales, 1, 1, fsm.y+ALTURA_SFSM+1);
								if(bales==NULL)
									bales = tmp;
								tmp = crearNovaBala(bales, 1, 3, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 5, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 7, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 9, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 11, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 13, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 15, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, 17, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-18, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-16, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-14, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-12, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-10, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-8, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-6, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-4, fsm.y+ALTURA_SFSM+1);
								tmp = crearNovaBala(bales, 1, AMPLADA_PANTALLA-2, fsm.y+ALTURA_SFSM+1);
							}
							if(t >= 400)
							{
								tmp = crearNovaBala(bales, 1, pos[0], fsm.y+ALTURA_SFSM-1);
								if(bales==NULL)
									bales = tmp;
								tmp = crearNovaBala(bales, 1, pos[1], fsm.y+ALTURA_SFSM-1);
								tmp = crearNovaBala(bales, 1, pos[2], fsm.y+ALTURA_SFSM-1);
								tmp = crearNovaBala(bales, 1, pos[3], fsm.y+ALTURA_SFSM-1);
								for(i=0; i<4; i++)
								{
									if(pos[i]+(((i+1)%2)*2-1)*2 >= AMPLADA_PANTALLA || pos[i]+(((i+1)%2)*2-1)*2 < 0)
									{
										pos[i] = (i%2) * AMPLADA_PANTALLA;
									}
									else
									{
										pos[i]+= (((i+1)%2)*2-1)*2;
									}
								}
							}
						}
					}

					Sleep(RETRAS);

				}
			} else {
				
				if (_kbhit()) 
				{
					
					while(_kbhit()) tecla = getch();
					
					if (tecla == 'p' || tecla == 'P') 
					{
						system("cls");
						CreaTaulell();
						MostraPunts(cano.punts);
						MostraVides(cano.vides, cano.max_vides);
						dibuixarPantallaFSM(pantalla, &cano, naus, &alienRandom, &fsm, bales, linia);
						MostraPantalla(pantalla);
						pausa = FALSE;
					}
					
				}
				
			}
			
			temps++;

		} while (!(acabarJoc));

	}
	
	
	//********************************************************************
	//********************************************************************
	//***********************  FSM CAN'T DIE!!  **************************
	//********************************************************************
	//********************************************************************

	
	
	
		//Netejar el punter de bales
	buidarBales(bales);
	bales = NULL;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Dibuixa els objectes actius a la pantalla//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void dibuixarPantallaFSM(int *pantalla, Nau_Propia *cano, Platet ufo[PLATETS_FSM], Platet *random, tFsm *fsm, Bala *bales, int linia[1][AMPLADA_PANTALLA])
{
	int i;
	Bala *tmp;

	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
	
	if(random->actiu)
	{
		PosaPersonatge(random->forma.punts, pantalla, random->x+1, random->y+1);
	}
	else
	{
		for(i=0; i<PLATETS_FSM; i++)
		{
			if(ufo[i].actiu)
			{
				PosaPersonatge(ufo[i].forma.punts, pantalla, ufo[i].x+1, ufo[i].y+1);
				PosaPersonatge2(linia, pantalla, 0, fsm->y+ALTURA_SFSM+2, AMPLADA_PANTALLA, 1);
			}
		}
	}

	PosaPersonatge2(fsm->dibuix, pantalla, fsm->x, fsm->y, AMPLADA_SFSM, ALTURA_SFSM);

	tmp = bales;
	while(tmp!= NULL)
	{
		if(tmp->velocitat > 0)
			PosaTretAliens(pantalla, tmp->x, tmp->y);
		else
			PosaTretAliens(pantalla, tmp->x, tmp->y);

		tmp = tmp->seguent;
	}

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicialitza les variables del joc//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void prepararFSM (int pantalla[ALTURA_PANTALLA][AMPLADA_PANTALLA], Nau_Propia *cano, Bunker *bunker, Platet *ufo, Platet *random, tFsm *fsm, int *pausa, int *punts)
{
	
	int i, j, tmpX, tmpY;
	

	for (i=0; i<ALTURA_PANTALLA; i++) {
		for (j=0; j<AMPLADA_PANTALLA; j++) {
			
			pantalla[i][j] = 0;
			
		}
	}

	cano->max_vides = VIDES_JUGADOR_1;

	cano->x = INICI_CANO_X;
	cano->y = INICI_CANO_Y;
	inicialitzaDibuixCano(cano->forma.punts);

	cano->temps = CANO_TEMPS_CARREGANT;
	cano->max_bales = CANO_BALES;
	cano->carregues = cano->max_bales;
	cano->carregant = 0;
	cano->vides = cano->max_vides;
	cano->punts = *punts;
	cano->millora = 0;
	cano->temps_millora = 0;
	cano->objectes = NULL;
	MostraPunts(cano->punts);
	MostraVides(cano->vides, cano->max_vides);
	
		//Pintar el cano
	PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);

	inicialitzaDibuixFSM(fsm->dibuix);
	fsm->bucles = 3;
	fsm->espera = 3;
	fsm->v_x = 1;
	fsm->v_y = 0;
	fsm->vides = VIDES_FSM;
	fsm->x = AMPLADA_PANTALLA/2 - AMPLADA_SFSM/2;
	fsm->y = 1;
	fsm->ulls[0] = FALSE;
	fsm->ulls[1] = FALSE;
	
	PosaPersonatge2(fsm->dibuix, pantalla, fsm->x, fsm->y, AMPLADA_SFSM, ALTURA_SFSM);

	for(i=0; i<PLATETS_FSM; i++)
	{
		ufo[i].actiu = VIDES_PLATETS_FSM; //Vides restants del platet
		ufo[i].bucles = TEMPS_BALES_PLATETS; //Temps entre cada bala
		ufo[i].espera = 0; //Temps abans de sortir de nou

		inicialitzaDibuixPlatet(ufo[i].forma.punts);
	}
	ufo[0].v_x = 1;
	ufo[0].v_y = 0;
	ufo[0].x = 0;
	ufo[0].y = fsm->y + ALTURA_SFSM + 5;
	ufo[1].v_x = -1;
	ufo[1].v_y = 1;
	ufo[1].x = AMPLADA_PANTALLA/2 - TAMANY_ALIEN;
	ufo[1].y = fsm->y + ALTURA_SFSM + 7;
	ufo[2].v_x = 1;
	ufo[2].v_y = 1;
	ufo[2].x = AMPLADA_PANTALLA/2;
	ufo[2].y = fsm->y + ALTURA_SFSM + 7;
	ufo[3].v_x = -1;
	ufo[3].v_y = 0;
	ufo[3].x = AMPLADA_PANTALLA - TAMANY_ALIEN;
	ufo[3].y = fsm->y + ALTURA_SFSM + 5;
	

	random->actiu = 0;
	random->x = -1;
	random->y = -1;
	random->bucles = 0;
	for(i=0;i<TAMANY_ALIEN; i++)
		for(j=0; j<TAMANY_ALIEN; j++)
			random->forma.punts[i][j] = 9;
	random->forma.punts[2][0] = 0;
	random->forma.punts[2][2] = 0;
	random->forma.punts[2][1] = 0;
	
	bunker->x = INICI_BUNKER_X;
	bunker->y = INICI_BUNKER_Y;
	
	for (i=0; i<MAX_ESCUTS; i++) 
	{
		inicialitzaDibuixEscut(bunker->escuts[i].forma.punts);
		tmpX = bunker->x + i*(TAMANY_ESCUT + SEPARACIO_ESCUTS) + TAMANY_ESCUT/2;
		tmpY = bunker->y + TAMANY_ESCUT/2;
		PosaPersonatge(bunker->escuts[i].forma.punts, pantalla, tmpX, tmpY);
	}
	
	*pausa = FALSE;
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Inicialitza el dibuix del FSM//////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void inicialitzaDibuixFSM(int dibuix[ALTURA_SFSM][AMPLADA_SFSM])
{
	int FSM[ALTURA_FSM][AMPLADA_FSM] = DIBUIX_FSM;
	int f, c;
	int *pantalla = NULL;


	for(f=0; f<ALTURA_SFSM; f++)
		for(c=0; c<AMPLADA_SFSM; c++)
			dibuix[f][c] = FSM[f/SFSMH][c/SFSMW];

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou les bales i comprova si xoquen amb algun objecte.//////////////////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *moureBalesFSM (int *pantalla, Bala *bales, Nau_Propia *cano, Bunker *bunker, tFsm *fsm, Platet ufo[PLATETS_FSM], Platet *random, int top, int *acabarJoc, int *raoJocAcabat) //TOP = 0
{
	
	Bala *tmp, *seguent;
	int balaActiva;
	
	tmp = bales;
	while (tmp != NULL) 
	{
		
		seguent = tmp->seguent;
		balaActiva = TRUE;
		
		if (tmp->velocitat<0) 
		{
			
				//Moure tret del can�
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a dal de tot
			if (tmp->y < top) 
			{
				bales = eliminaBala(bales, tmp);
				
				cano->carregues += 1;
				
				balaActiva = FALSE;
				
			}
			
		} else {
			
			BorraTret(pantalla, tmp->x, tmp->y);
			
			tmp->y += tmp->velocitat;
			
				//Comprovar si ha arribat a baix de tot
			if (tmp->y >= ALTURA_PANTALLA) 
			{
				bales = eliminaBala(bales, tmp);
				
				balaActiva = FALSE;
			}
			
		}
		
			//Comprovar si la bala segueix activa...
		if (balaActiva)
		{
			//Comprovar si xoca amb una altra bala
			bales = comprovarXocBalaAmbBalaFSM(pantalla, bales, tmp, &seguent, cano, &balaActiva);
			
			if (balaActiva) 
			{
					//Comprovar si xoca amb els escuts
				bales = comprovarXocBalaAmbEscutFSM(pantalla, bales, tmp, bunker, cano, &balaActiva);
				
					//Si no s'ha desactivat per un escut
				if (balaActiva) 
				{
					
					if (tmp->velocitat < 0) 
					{
							// Comprovar el xoc de les bales del can�
						
						PosaTretCano(pantalla, tmp->x, tmp->y);

						if(random->actiu)
						{
								//Comprovar el xoc amb el FSM
							bales = comprovarXocBalaAmbFSM (fsm, &cano, bales, tmp, pantalla);
						}
						else
						{
							bales = comprovarXocBalaAmbAliensFSM(pantalla, bales, tmp, cano, fsm, ufo);
						}
						
					} else {
						
						bales = comprovarXocBalaAmbCanoFSM(pantalla, bales, tmp, cano, acabarJoc, raoJocAcabat);
					}

					
				}
				
			}
		
		}
		
		tmp = seguent;
		
	}
	
		//Actualitzar el temps d'espera per disparar les bales dels aliens i el cano
	if (cano->carregant > 0) 
	{
		cano->carregant -= 1;
	}
	
	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si dues bales xoquen entre elles./////////////////////////////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbBalaFSM(int *pantalla, Bala *bales, Bala *bala, Bala *(*next), Nau_Propia *cano, int *balaActiva)
{
	Bala *tmp;

	tmp = bales;
	while(tmp != NULL && *balaActiva)
	{
		if(tmp != bala && tmp->x == bala->x && tmp->y == bala->y && tmp->velocitat != bala->velocitat)
		{
			if(*next == tmp)
			{
				*next = (*next)->seguent;
			}
			BorraTret(pantalla, bala->x, bala->y);
			BorraTret(pantalla, tmp->x, tmp->y);
			bales = eliminaBala(bales, bala);
			bales = eliminaBala(bales, tmp);
			*balaActiva = FALSE;
		}

		if(*balaActiva)
		{
			tmp = tmp->seguent;
		}

	}

	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb un escut.////////////////////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbEscutFSM (int *pantalla, Bala *bales, Bala *bala, Bunker *bunker, Nau_Propia *cano, int *balaActiva)
{
	
	int tmpX, tmpBunkerX, tmpY, modX, x, y;
	
	if ( (bala->x < (bunker->x + (MAX_ESCUTS*(TAMANY_ESCUT+SEPARACIO_ESCUTS)-SEPARACIO_ESCUTS))) 
		&& (bala->x >= bunker->x) && (bala->y < (bunker->y + TAMANY_ESCUT)) && (bala->y >= bunker->y) ) 
	{
		
			//Mirar si est� sobre un escut
		tmpX = bala->x - bunker->x;
		tmpY = bala->y - bunker->y;
		
		modX = tmpX % (TAMANY_ESCUT + SEPARACIO_ESCUTS);
		
		if (modX < TAMANY_ESCUT) 
		{
			
				//Comprovar si toca una part de l'escut
			tmpBunkerX = tmpX/(TAMANY_ESCUT+SEPARACIO_ESCUTS);
			if ( bunker->escuts[tmpBunkerX].forma.punts[tmpY][modX]!=0 ) 
			{
				
				x = bunker->x + tmpX - modX + TAMANY_ESCUT/2;
				y = bunker->y + TAMANY_ESCUT/2;
				
				BorraPersonatge(bunker->escuts[tmpBunkerX].forma.punts, pantalla, x, y);
				
					//Borra la part de l'escut
				bunker->escuts[tmpBunkerX].forma.punts[tmpY][modX] = 0;
				
				PosaPersonatge(bunker->escuts[tmpBunkerX].forma.punts, pantalla, x, y);
				
					//Desactiva la bala
				if (bala->velocitat < 0) 
				{
					cano->carregues += 1;
				
				}

				*balaActiva = FALSE;
				bales = eliminaBala(bales, bala);
				
			}
			
		}
		
	}
	
	return bales;
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb el can�./////////////////////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbCanoFSM (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, int *acabarJoc, int *raoJocAcabat)
{
	
	int tmpX, tmpY, modX, modY;
	
	PosaTretAliens(pantalla, bala->x, bala->y);
	
		//Obtenim la posici� de la bala relativa al can�
	tmpX = bala->x - (cano->x - TAMANY_CANO/2);
	tmpY = bala->y - (cano->y - TAMANY_CANO/2);
	
		//Comprovar si toca el can�
	if ( (tmpX >= 0) && (tmpX < TAMANY_CANO) && (tmpY >= 0) ) 
	{
			//La bala est� sobre el can�
		
			//Agafem el m�dul de la posici� per saber si la bala coincideix amb el can�
		modX = tmpX % TAMANY_CANO;
		modY = tmpY % TAMANY_CANO;
		
			//Comprovem si TOCA el can�
		if (cano->forma.punts[modY][modX] != 0) 
		{
			
				//Desactivar i borrar la bala i carregar els aliens
			BorraTret(pantalla, bala->x, bala->y);
			bales = eliminaBala(bales, bala);
			PosaPersonatge(cano->forma.punts, pantalla, cano->x, cano->y);
			
				//Baixar una vida
			cano->vides -= 1;
			MostraVides(cano->vides, cano->max_vides);
			
			if (cano->vides == 0) 
			{
				*acabarJoc = TRUE;
				*raoJocAcabat = RAO_JOC_ACABAT_MORT;
			}
			
		}
		
	}
	
	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala especificada xoca amb algun dels aliens actius.////////////
/////////////////////////////////////Retorna la llista de bales///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbAliensFSM (int *pantalla, Bala *bales, Bala *bala, Nau_Propia *cano, tFsm *fsm, Platet ufo[PLATETS_FSM])
{
	
	int tmpX, tmpY, modX, modY, tmpAlienX, tmpAlienY, i, j, k;
	int balaActiva = TRUE;
	
		//Comprovar si xoca amb algun alien
	for(k=0; k<PLATETS_FSM; k++)
	{
		if(ufo[k].actiu)
		{
			if ( (bala->x >= ufo[k].x) && (bala->x < ufo[k].x+TAMANY_ALIEN) && (bala->y >= ufo[k].y) && (bala->y < ufo[k].y+TAMANY_ALIEN) )
			{
				tmpX = bala->x - ufo[k].x;
				tmpY = bala->y - ufo[k].y;

				if (ufo[k].forma.punts[tmpY][tmpX] != 0)
				{
					ufo[k].actiu -= 1;
					if(ufo[k].actiu == 0)
					{
						ufo[k].espera = TEMPS_ESPERA_PLATETS_FSM;
						BorraPersonatge(ufo[k].forma.punts, pantalla, (ufo[k].x+TAMANY_ALIEN/2), (ufo[k].y+TAMANY_ALIEN/2));
					}
					else
					{
						PosaPersonatge(ufo[k].forma.punts, pantalla, (ufo[k].x+TAMANY_ALIEN/2), (ufo[k].y+TAMANY_ALIEN/2));
					}
					bales = eliminaBala(bales, bala);
					cano->punts += PUNTUACIO_UFO_MORT;
					cano->carregues += 1;
					balaActiva = FALSE;
				}
			}
		}
	}
	
	return bales;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou i fa disparar els platets voladors de la primera fase./////////////////////
///////////////////////////////////Retorna la llista de bales/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *mourePlatetsFSM (int *pantalla, Platet ufo[PLATETS_FSM], Bala *bales, int temps)
{
	int i, tmpX, tmpY, rnd;
	Bala *tmp;

	for(i=0; i<PLATETS_FSM; i++)
	{
			
		tmpX = ufo[i].x + ufo[i].v_x;
		tmpY = ufo[i].y + ufo[i].v_y;
		

		if (tmpX >= 0 && tmpX <= AMPLADA_PANTALLA-TAMANY_ALIEN)
		{
			//Moure'l
			if (ufo[i].actiu>0)
			{	
				BorraPersonatge (ufo[i].forma.punts, pantalla, (ufo[i].x+TAMANY_ALIEN/2), (ufo[i].y+TAMANY_ALIEN/2));
				PosaPersonatge (ufo[i].forma.punts, pantalla, (tmpX+TAMANY_ALIEN/2), (tmpY+TAMANY_ALIEN/2));
			}
			ufo[i].x = tmpX;
			ufo[i].y = tmpY;
			
		}

		if (ufo[i].actiu)
		{
			if(ufo[i].bucles == 0)
			{
				//Disparar
				tmp = crearNovaBala(bales, 1, ufo[i].x+TAMANY_ALIEN/2, ufo[i].y+TAMANY_ALIEN/2);
				if(bales==NULL)
					bales = tmp;
			}
		}
		else
		{
			ufo[i].espera -= 1;
			if(ufo[i].espera == 0)
			{
				ufo[i].actiu = VIDES_PLATETS_FSM;
			}
		}

		if(ufo[i].bucles > 0)
			ufo[i].bucles -= 1;
		else
			ufo[i].bucles = TEMPS_BALES_PLATETS;

		if( ( (ufo[i].x == 0) || (ufo[i].x == AMPLADA_PANTALLA-TAMANY_ALIEN) || (ufo[i].x == (AMPLADA_PANTALLA/2-TAMANY_ALIEN)) || (ufo[i].x == AMPLADA_PANTALLA/2) ) && temps > 0)
			ufo[i].v_x *= (-1);
		
		if( ( (ufo[i].x == 0) || (ufo[i].x == AMPLADA_PANTALLA-TAMANY_ALIEN) || (ufo[i].x == (AMPLADA_PANTALLA/2-TAMANY_ALIEN)) || (ufo[i].x == (AMPLADA_PANTALLA/4-TAMANY_ALIEN/2)) || (ufo[i].x == (3*AMPLADA_PANTALLA/4-TAMANY_ALIEN/2)) || (ufo[i].x == AMPLADA_PANTALLA/2) ) && temps > 0)
			ufo[i].v_y *= (-1);

	}

	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Comprova si la bala espacificada xoca amb el FSM.//////////////////////////////
//////////////////////////////////Retorna la llista de bales//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *comprovarXocBalaAmbFSM (tFsm *fsm, Nau_Propia *cano, Bala *bales, Bala *bala, int *pantalla)
{

	int tmpX, tmpY;
	if ( (bala->x >= fsm->x) && (bala->x < fsm->x+AMPLADA_SFSM) && (bala->y >= fsm->y-1) && (bala->y < fsm->y+ALTURA_SFSM-1) )
	{
		tmpX = bala->x - fsm->x;
		tmpY = bala->y - fsm->y - bala->velocitat;
		PosaPersonatge2(&(fsm->dibuix[tmpY][tmpX]), pantalla, bala->x, bala->y-bala->velocitat, 1, 1);
	}

	if ( ((bala->x >= fsm->x+9) && (bala->x < fsm->x+9+3)&&(fsm->ulls[0]) || (bala->x >= fsm->x+24) && (bala->x < fsm->x+24+3)&&(fsm->ulls[1])) && (bala->y >= fsm->y+2) && (bala->y < fsm->y+2+2) )
	{
		tmpX = bala->x - fsm->x;
		tmpY = bala->y - fsm->y;
		PosaPersonatge2(&(fsm->dibuix[tmpY][tmpX]), pantalla, bala->x, bala->y, 1, 1);

		bales = eliminaBala(bales, bala);
		cano->punts += PUNTUACIO_UFO_MORT;
		fsm->espera = 0;
		bales = moureFSM(pantalla, fsm, bales);
		
		fsm->vides -= 1;

	}
	
		

	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Mou i fa disparar l'ull del FSM durant la segona fase//////////////////////////
//////////////////////////////////////Retorna la llista de bales//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *moureRandom (int *pantalla, tFsm *fsm, Platet *random, Bala *bales)
{
	int tmpX, tmpY, rnd;
	Bala *tmp;

	BorraPersonatge(random->forma.punts, pantalla, random->x + TAMANY_ALIEN/2, random->y + TAMANY_ALIEN/2);
	random->x = aleatori(AMPLADA_PANTALLA-TAMANY_ALIEN);
	random->y = aleatori(ALTURA_PANTALLA-(fsm->y+ALTURA_SFSM+2)-TAMANY_ALIEN-6*TAMANY_CANO) + (fsm->y+ALTURA_SFSM+1);
	PosaPersonatge(random->forma.punts, pantalla, random->x + TAMANY_ALIEN/2, random->y + TAMANY_ALIEN/2);

	tmp = crearNovaBala(bales, 1, random->x + TAMANY_ALIEN/2, random->y + TAMANY_ALIEN);
	if (bales == NULL)
		bales = tmp;

	return bales;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Nivell extra///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Intercanvia els ulls del FSM i dispara una superbala.//////////////////////////
///////////////////////////////////Retorna la llista de bales/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Bala *moureFSM (int *pantalla, tFsm *fsm, Bala *bales)
{
	int i, j, k, l;
	Bala *tmp;
	int tmpX, tmpY, rnd;

	if(fsm->espera == 0)
	{
		fsm->espera = aleatori(20)+20;

		if(fsm->ulls[0])
		{
			fsm->ulls[0] = FALSE;
			fsm->ulls[1] = TRUE;
			for(i=0; i<2; i++)
			{
				for(j=0;j<3;j++)
				{
					fsm->dibuix[i+2][j+9] = 0;
					fsm->dibuix[i+2][j+24] = 9;
				}
			}
		}
		else
		{
			fsm->ulls[0] = TRUE;
			fsm->ulls[1] = FALSE;
			for(i=0; i<2; i++)
			{
				for(j=0;j<3;j++)
				{
					fsm->dibuix[i+2][j+9] = 9;
					fsm->dibuix[i+2][j+24] = 0;
				}
			}
		}

		for(i=0; i<2; i++)
		{
			for(j=0;j<3;j++)
			{
				BorraPersonatge2(&(fsm->dibuix[i+2][j+9]), pantalla, fsm->x+9+j, fsm->y+2+i, 1, 1);
				BorraPersonatge2(&(fsm->dibuix[i+2][j+24]), pantalla, fsm->x+24+j, fsm->y+2+i, 1, 1);
			}
		}

		for(i=0; i<2; i++)
		{
			for(j=0;j<3;j++)
			{
				if(fsm->ulls[0])
				{
					fsm->dibuix[i+2][j+9] = 9;
					PosaPersonatge2(&(fsm->dibuix[i+2][j+9]), pantalla, fsm->x+9+j, fsm->y+2+i, 1, 1);

					for(k=0; k<BALES_SUPERBALA; k=k+2)
					{
						for(l=-(AMPLADA_SUPERBALA/2); l<=AMPLADA_SUPERBALA/2; l=l+2)
						{
							tmp = crearNovaBala(bales, VELOCITAT_BALA, fsm->x + 24 + l, fsm->y + ALTURA_SFSM + BALES_SUPERBALA - k);
							if (bales == NULL)
							{
								bales = tmp;
							}
							PosaTretAliens(pantalla, tmp->x, tmp->y);
						}
						
					}

				}

				if(fsm->ulls[1])
				{
					fsm->dibuix[i+2][j+24] = 9;
					PosaPersonatge2(&(fsm->dibuix[i+2][j+24]), pantalla, fsm->x+24+j, fsm->y+2+i, 1, 1);
					
					for(k=0; k<BALES_SUPERBALA; k = k+2)
					{
						for(l=-(AMPLADA_SUPERBALA/2); l<=AMPLADA_SUPERBALA/2; l=l+2)
						{
							tmp = crearNovaBala(bales, VELOCITAT_BALA, fsm->x + 9 + l, fsm->y + ALTURA_SFSM + BALES_SUPERBALA - k);
							if (bales == NULL)
							{
								bales = tmp;
							}
							PosaTretAliens(pantalla, tmp->x, tmp->y);
						}
						
					}
				}
			}
		}
	}
	else
	{
		fsm->espera -= 1;
	}

	return bales;
}
