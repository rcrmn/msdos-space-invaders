/* Roc Ramon Currius 1241370 */
#include "RutinesINVADERS_v1.h"


//===================================================================================
// NOM: NumAleatori
//===================================================================================
// DESCRIPCIO:  Funcio per generar un nombra aleatori entre 0 i max
//===================================================================================
int NumAleatori(int max)
{
	int num;

	num=((int)ceil(((double)rand()/RAND_MAX)*(max+1)))%(max+1);

	return num;
}


//===================================================================================
// NOM: Gotoxy
//===================================================================================
// DESCRIPCIO: Permet posar el cursor en una posicio donada
//===================================================================================
void gotoxy(int c,int f,HANDLE screen)
{
 COORD position = { c, f };
 SetConsoleCursorPosition(screen,position);
}


//===================================================================================
// NOM: TextColor
//===================================================================================
// DESCRIPCIO: Funcio per canviar els colors de texte i fons de la consola DOS
//===================================================================================
void TextColor(int fontcolor,int backgroundcolor,HANDLE screen)
{
   unsigned short color_attribute;
   color_attribute = backgroundcolor;
   color_attribute = _rotl(color_attribute,4) | fontcolor;
   SetConsoleTextAttribute(screen,color_attribute);
}


//===================================================================================
// NOM: LiniaEspecial
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: Funcio que permet crear linies. Va be per crear el tauell. Les linies podran ser de 3 tipus: 
// SUP, MIG o INF.
//===================================================================================
char* LiniaEspecial(int Longitud, int Tipus)
{

	// ------------------------------------------------------------------------------
	char *Linia;
	int n;

	// ------------------------------------------------------------------------------
	Linia=(char*)malloc((Longitud+1)*sizeof(char));

	// ------------------------------------------------------------------------------	
	switch(Tipus)
	{
		case SUP:
			Linia[0]=CSE;
			Linia[Longitud-1]=CSD;
			for(n=1;n<Longitud-1;n++)
				Linia[n]=CH;
			break;
		case MID:
			Linia[0]=CV;
			Linia[Longitud-1]=CV;
			for(n=1;n<Longitud-1;n++)
				Linia[n]=' '; // Aixo es un espai en blanc.
			break;
		case INF:
			Linia[0]=CIE;
			Linia[Longitud-1]=CID;
			for(n=1;n<Longitud-1;n++)
				Linia[n]=CH;
			break;
	}

	// ------------------------------------------------------------------------------	
	// Al final SEMPRE CAL posar el caracter '\0'!!!!!!!!!!!!!.....
	Linia[Longitud]='\0';

	// ------------------------------------------------------------------------------
	return(Linia);

}


//===================================================================================
// NOM: CreaQuadre
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: Funcio que permet crear quadres, amb un possible texte a sobre...
//===================================================================================
void CreaQuadre(int CantonadaSupEsq_x, int CantonadaSupEsq_y, int W, int H, char *TXT)
{

	// ------------------------------------------------------------------------------
	char * LiniaSUP, * LiniaMID, * LiniaINF;
	int n,dy=0;

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Si el punter (strin, de fet...) es diferent de NULL, mostrem
	// un missatge dins quadre:
	if (TXT!=NULL)
	{
		gotoxy(CantonadaSupEsq_x, CantonadaSupEsq_y,screen);
		puts(TXT);
	}
	
	// ------------------------------------------------------------------------------
	gotoxy(CantonadaSupEsq_x, CantonadaSupEsq_y+dy,screen);

	// ------------------------------------------------------------------------------
	LiniaSUP=LiniaEspecial(W,SUP);
	LiniaMID=LiniaEspecial(W,MID);
	LiniaINF=LiniaEspecial(W,INF);

	// ------------------------------------------------------------------------------
	gotoxy(CantonadaSupEsq_x, CantonadaSupEsq_y+(++dy),screen);
	puts(LiniaSUP);
	for(n=1;n<=H-2;n++)
	{
		gotoxy(CantonadaSupEsq_x, CantonadaSupEsq_y+(++dy),screen);
		puts(LiniaMID);
	}
	gotoxy(CantonadaSupEsq_x, CantonadaSupEsq_y+(++dy),screen);
	puts(LiniaINF);	

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//===================================================================================
// NOM: CreaTaulell
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: Funcio que permet mostrar el tauler de joc.
//===================================================================================
void CreaTaulell(void)
{
	// ------------------------------------------------------------------------------
	int C0, C1, F0, F1, FJugador, FPunts, FTaulell, FVides;
	char TXTjugador[10]="Jugador";
	char TXTpunts[10]="Punts";
	char TXTvides[10]="Vides";
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

	CreaQuadre(C0,FJugador, LJugador, 3, TXTjugador);
	CreaQuadre( (C0+AmpladaTaulell/2),FJugador, LNivell, 3, TXTnivell);
	CreaQuadre(C0+AmpladaTaulell-LPunts,FPunts, LPunts, 3, TXTpunts);
	CreaQuadre(C0,FTaulell, AmpladaTaulell, AlssadaTaulell,NULL);
	CreaQuadre(C0+(AmpladaTaulell/2)-(LVides/2),FVides, LVides, 3, TXTvides);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//===================================================================================
// NOM: MostraPantalla
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: Funcio que pinta el laberint del joc dins els limits del taulell.
// ALERTA! Ara els personatges estan pintats sobre la pantalla!!
//===================================================================================
void MostraPantalla(int Pantalla[AlssadaPantalla][AmpladaPantalla])
{
	/*// ------------------------------------------------------------------------------
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	for(f=0;f<AlssadaPantalla;f++)
	{
		gotoxy(C0,F0+f,screen);
		for(c=0;c<AmpladaPantalla;c++)
		{
			//COL=ObtenirColor(Pantalla[f*AmpladaPantalla+c]);
			//CAR=ObtenirCaracter(Pantalla[f*AmpladaPantalla+c]);		
			COL=ObtenirColor(Pantalla[f][c]);
			CAR=ObtenirCaracter(Pantalla[f][c]);		
			TextColor(COL,BLACK,screen);
			printf("%c",CAR);
		}
	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();*/

}


//===================================================================================
// NOM: ObtenirColor
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
int ObtenirColor(int IntIN)
{
	// ------------------------------------------------------------------------------
	int COL;

	// ------------------------------------------------------------------------------
	switch(IntIN)
	{
		case 0: // Buit
			COL = BLACK;
			break;
		case 1: // bunker
			COL = BROWN;
			break;
		case 2: // cano
			COL = LIGHTGREY;
			break;
		case 3: // trets
			COL =CYAN;
			break;
		case 4: // alienigenes
			COL = YELLOW;
			break;
		case 5: // plat volador
			COL = RED;
			break;
		case 6: // trets2r
			COL =DARKGREY;
			break;
		case 7:
			COL = RED;
			break;
		case 8: // fsm
			COL = RED;
			break;
		case 9: //AlienRandom
			COL = LIGHTGREEN;
			break;
		case 10: //Ulls AlienRandom
			COL = LIGHTRED;
			break;

		case 15:
			COL = LIGHTRED;
			break;
		
		case 21: // MILLORA_BALES
			COL=RED;
			break;
		case 22: // MILLORA_SUPERBALA
			COL=CYAN;
			break;
		case 23:
			COL=LIGHTGREEN;
			break;
		
		default:
			COL = WHITE;
			break;
	}
	// ------------------------------------------------------------------------------
	return(COL);

}


//===================================================================================
// NOM: ObtenirColor
//===================================================================================
// DATA: 22 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
char ObtenirCaracter(int IntIN)
{
  // ------------------------------------------------------------------------------
	char SHP;

  // ------------------------------------------------------------------------------
	switch(IntIN)
	{
		case 0: // Buit
			SHP=176;
			break;
		case 1: // Mur
			SHP=177;
			break;
		case 2: // cano
			SHP=178;
			break;
		case 3: // trets1
			SHP=24;
			break;
		case 4: // alienigenes
			SHP = 219;
			break;
		case 5: // platvolador
			SHP = 178;
			break;
		case 6: // trets2
			SHP = 25;
			break;
		case 7:
			SHP = 219;
			break;
		case 8:
			SHP = 219;
			break;
		case 9: //AlienRandom
			SHP = 219;
			break;
		case 10: //Ulls AlienRandom
			SHP = 219;
			break;

		case 15: // NUMEROS
			SHP = 219;
			break;

		case 21: // MILLORA_BALES
			SHP='H';
			break;
		case 22: // MILLORA_SUPERBALA
			SHP='S';
			break;
		case 23:
			SHP='+';
			break;

		default:
			SHP = IntIN;
			break;
	}

	// ------------------------------------------------------------------------------
	return(SHP);

}


//===================================================================================
// NOM: PosaPersonatge
//===================================================================================
// DATA: 02 / 12 / 2008
//===================================================================================
// DESCRIPCIO: ALERTA!! Aquesta versi� �s nova!! Abans la funci� PosaPersonatge 
// situava directament el personatge sobre el monitor, mentre que ara el posa a la 
// matriu. Vegeu, per tant, que ara passem un par�metre extra a fla funci�: la matriu
// de pantalla!
//===================================================================================
void PosaPersonatge(int Personatge[MidaPers][MidaPers],int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
		int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x-1 >= 0 && x+1 <= AmpladaPantalla && y-1 >= 0 && y+1 <= AlssadaPantalla)
	{
		for(f=-1;f<=1;f++)
		{
			for(c=-1;c<=1;c++)
			{
				
				if(Personatge[f+1][c+1] > 0)
				{
					gotoxy(C0+x+c,F0+y+f,screen);
			
					COL=ObtenirColor(Personatge[f+1][c+1]);
					CAR=ObtenirCaracter(Personatge[f+1][c+1]);		
					TextColor(COL,BLACK,screen);
					printf("%c",CAR);
				}
			}
		}

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}

void BorraPersonatge(int Personatge[MidaPers][MidaPers],int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x-1 >= 0 && x+1 <= AmpladaPantalla && y-1 >= 0 && y+1 <= AlssadaPantalla)
	{
		for(f=-1;f<=1;f++)
		{
			for(c=-1;c<=1;c++)
			{
				
				if(Personatge[f+1][c+1] > 0)
				{
					gotoxy(C0+x+c,F0+y+f,screen);
			
					COL=ObtenirColor(0);
					CAR=ObtenirCaracter(0);		
					TextColor(COL,BLACK,screen);
					printf("%c",CAR);
				}
			}
		}

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}

void PosaPersonatge2(int *Personatge,int Pantalla[AlssadaPantalla][AmpladaPantalla], int x, int y, int width, int height)
{

	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x+width <= AmpladaPantalla && y >= 0 && y+height <= AlssadaPantalla)
	{
		for(f=0;f<height;f++)
		{
			for(c=0;c<width;c++)
			{
				
				if(Personatge + f*width + c > 0)
				{
					gotoxy(C0+x+c,F0+y+f,screen);
			
					COL=ObtenirColor(*(Personatge + f*width + c));
					CAR=ObtenirCaracter(*(Personatge + f*width + c));		
					TextColor(COL,BLACK,screen);
					printf("%c",CAR);
				}
			}
		}

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}



void BorraPersonatge2(int *Personatge,int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y, int width, int height)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x+width <= AmpladaPantalla && y >= 0 && y+height <= AlssadaPantalla)
	{
		for(f=0;f<height;f++)
		{
			for(c=0;c<width;c++)
			{
				
				if(Personatge + f*width + c > 0)
				{
					gotoxy(C0+x+c,F0+y+f,screen);
			
					COL=ObtenirColor(0);
					CAR=ObtenirCaracter(0);		
					TextColor(COL,BLACK,screen);
					printf("%c",CAR);
				}
			}
		}

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}

void PosaTretCano(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x < AlssadaPantalla && y >= 0 && y < AmpladaPantalla)
	{
		gotoxy(C0+x,F0+y,screen);
				
		COL=ObtenirColor(3);
		CAR=ObtenirCaracter(3);		
		TextColor(COL,BLACK,screen);
		printf("%c",CAR);

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();
}


void PosaTretAliens(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x < AlssadaPantalla && y >= 0 && y < AmpladaPantalla)
	{
		gotoxy(C0+x,F0+y,screen);
				
		COL=ObtenirColor(6);
		CAR=ObtenirCaracter(6);		
		TextColor(COL,BLACK,screen);
		printf("%c",CAR);

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();
}

void BorraTret(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x < AlssadaPantalla && y >= 0 && y < AmpladaPantalla)
	{
		gotoxy(C0+x,F0+y,screen);
				
		COL=ObtenirColor(0);
		CAR=ObtenirCaracter(0);		
		TextColor(COL,BLACK,screen);
		printf("%c",CAR);

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();
}


//===================================================================================
// NOM: MostraJugador
//===================================================================================
// DATA: 24 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
void MostraJugador(char *NomJugador)
{

	// ------------------------------------------------------------------------------
	int C0,F0;

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	C0=3+DespC;
	F0=3+DespF;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,BLACK,screen);
	puts(NomJugador);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//===================================================================================
// NOM: MostraPunts
//===================================================================================
// DATA: 24 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
void MostraPunts(int NPunts)
{

	// ------------------------------------------------------------------------------
	int C0,F0;

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	C0=8+AmpladaTaulell-LPunts;
	F0=3+DespF;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,BLACK,screen);
	printf("%d",NPunts);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


//===================================================================================
// NOM: MostraPunts
//===================================================================================
// DATA: 24 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
void MostraVides(int NVides, int MaxVides)
{

	// ------------------------------------------------------------------------------
	int C0,F0,n, CAR;
	int vides;
	int STR[LVides];

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);


	for(n=0;n<LVides;n++)
		STR[n] = 0;

	vides = (int)(NVides/(float)MaxVides * (LVides-2));
	// ------------------------------------------------------------------------------
	C0=3+DespC + AmpladaPantalla/2 - LVides/2;
	F0=DespF+AlssadaTaulell+8;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,RED,screen);

	CAR = ObtenirCaracter(4);
	// ------------------------------------------------------------------------------
	for(n=1;n<=vides;n++)
		STR[n-1]=CAR; //COR.

	// ------------------------------------------------------------------------------
	for(n=0;n<LVides-2;n++)
		printf("%c",STR[n]);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}


void MostraNivell(int nivell)
{

	// ------------------------------------------------------------------------------
	int C0,F0;

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	C0=DespC+AmpladaTaulell/2+3;
	F0=3+DespF;
	gotoxy(C0,F0,screen);

	// ------------------------------------------------------------------------------
	TextColor(YELLOW,BLACK,screen);
	printf("%d",nivell);

	// ------------------------------------------------------------------------------
	CursorAlFinal();

}



//===================================================================================
// NOM: CursorAlFinal
//===================================================================================
// DATA: 24 / 10 / 2008
//===================================================================================
// DESCRIPCIO: 
//===================================================================================
void CursorAlFinal(void)
{

	// ------------------------------------------------------------------------------
	HANDLE  screen= GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	TextColor(LIGHTGREY,BLACK,screen);

	// ------------------------------------------------------------------------------
	gotoxy(Cfinal,Ffinal,screen);

}






void BorraObjecte(int Pantalla[AlssadaPantalla][AmpladaPantalla],int x,int y)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x < AlssadaPantalla && y >= 0 && y < AmpladaPantalla)
	{
		gotoxy(C0+x,F0+y,screen);
				
		COL=ObtenirColor(0);
		CAR=ObtenirCaracter(0);		
		TextColor(COL,BLACK,screen);
		printf("%c",CAR);

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();
}

void PosaObjecte(int Pantalla[AlssadaPantalla][AmpladaPantalla], int x, int y, int chr)
{
	int f,c, dy=0, COL, C0, F0;
	char CAR;

	// ------------------------------------------------------------------------------
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// ------------------------------------------------------------------------------
	// Fila i columna inicial de la pantalla:
	C0=DespC+2;
	F0=DespF+7;

	// ------------------------------------------------------------------------------
	if(x >= 0 && x < AlssadaPantalla && y >= 0 && y < AmpladaPantalla)
	{
		gotoxy(C0+x,F0+y,screen);
				
		COL=ObtenirColor(chr);
		CAR=ObtenirCaracter(chr);		
		TextColor(COL,BLACK,screen);
		printf("%c",CAR);

	}

	// ------------------------------------------------------------------------------
	CursorAlFinal();
}



