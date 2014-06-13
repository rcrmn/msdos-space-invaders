/* Roc Ramon Currius 1241370, Gerardo Felix Reichl 1245142 */
//===================================================================================
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

//===================================================================================
// Definicio de colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

//===================================================================================
// Definicio de tecles
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

//===================================================================================
// Desplassament del taulell respecte la cantonada superior esquerre
#define DespF 2
#define DespC 5

//===================================================================================
// Els diferent tipus de linia (per dibuixar el taulell):
#define SUP 1
#define MID 0
#define INF -1

//===================================================================================
// Aparenssa de les caixes d'informaci\'f3: Jugador, Punts, Vides
#define LJugador 15
#define LPunts 10
#define LVides 32
#define LNivell 5

//===================================================================================
// Definicio de puntuacions
#define Punts 1
#define MegaPunts 10

//===================================================================================
// Dimensions del Personatge
#define MidaPers 3
#define tamany_aliens_alt 25
#define tamany_aliens_ample 45

//===================================================================================
// Dimensions del taulell.
#define AlssadaTaulell 60
#define AmpladaTaulell 60

//===================================================================================
// Dimensions del taulell.
#define AlssadaPantalla (AlssadaTaulell-2)
#define AmpladaPantalla (AmpladaTaulell-2)

//===================================================================================
// Per tal que quan pintem qualsevol cosa el cursor no quedi al final, el mourem a
// aquesta posició:
#define Cfinal 1
#define Ffinal DespF+AlssadaTaulell+15

//===================================================================================
// Definim els marges dels requadres:
#define CV 186 //Contorn vertical.
#define CIE 200 //Cantonada inferior esquerre.
#define CID 188 //Cantonada inferior dreta.
#define CH  205 //Contorn horitzontal.
#define CSE 201 //Cantonada superior esquerre
#define CSD 187 // Cantonada superior dreta



//===================================================================================
// Declaracio de funcions
int NumAleatori(int);
void gotoxy(int,int,HANDLE);
void TextColor(int,int,HANDLE);

char* LiniaEspecial(int,int);
void CreaQuadre(int,int,int,int,char*);
void CreaTaulell(void);
void MostraPantalla(int [AlssadaPantalla][AmpladaPantalla]);
int ObtenirColor(int);
char ObtenirCaracter(int);
void PosaPersonatge(int Personatge[MidaPers][MidaPers],int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y);
void MostraJugador(char*);
void MostraPunts(int);
void MostraVides(int, int);
void MostraNivell(int nivell);
void CursorAlFinal(void);
void PosaPersonatge2(int *Personatge,int Pantalla[AlssadaPantalla][AmpladaPantalla], int x, int y, int width, int height);
void PosaTretCano(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y);
void PosaTretAliens(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y);
void BorraPersonatge2(int*,int [AlssadaPantalla][AmpladaPantalla], int x, int y, int width, int height);
void BorraTret(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y);
void BorraPersonatge(int [MidaPers][MidaPers],int [AlssadaPantalla][AmpladaPantalla],int,int);

void PosaObjecte(int Pantalla[AlssadaPantalla][AmpladaPantalla], int x, int y, int chr);
void BorraObjecte(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y);

//===================================================================================
// Declarem la matriu que representa la pantalla. En aquesta pràctica, la 
// considerarem com a variable global. Vosaltres NO podeu declarar variables globals!

