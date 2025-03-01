/* JUGARU Marius-Gabriel - 312 CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* definire lista dublu inlantuita cu santinela */

typedef struct celula2
{
    char info;
    struct celula2 *pre, *urm;
} TCelula2, *TL2;

/* implementare coada */

typedef struct celula
{
    char operatie[20];
    struct celula *urm;
} TCelula, *TLista;

typedef struct coada
{
    TLista inc, sf;
} TCoada;

typedef struct celst
{
    TL2 info;
    struct celst *urm;
} TCelulaStiva, *TStiva;


/* Implementare banda impreuna cu deget */

typedef struct BandaCuDeget
{
    TL2 lista, deget;
} TBanda;

/* Functii banda cu deget*/

TL2 AlocareCel();
TL2 InitL2();
void DistrugeLista2(TL2 *aL);
TBanda* Initbanda();

/* Functii coada */

TCoada* InitQ();
int  InserareQ(char s[20], TCoada* c);
void AfisareQ(TCoada *c);
void ExtrQ(TCoada *c);
void DistrQ(TCoada **c);

/* Functii stiva */

int Push(TStiva* vf, TL2 x);
int Pop(TStiva* vf, TL2* x);
void AfisareStiva(TStiva vf);
void DistrugeS(TStiva* vf);

/* Operatii */

int CitireOperatii(TBanda* banda, TCoada* c, FILE* out, TStiva* vf_undo, TStiva* vf_redo);
void Show(TBanda* banda, FILE* out);
void Move_Left(TBanda* banda, TStiva* vf_undo);
void Move_Right(TBanda* banda, TStiva* vf_undo);
void Write(TBanda* banda, char x);
void Move_Right_Char(TBanda* banda, char ref, FILE* out);
void Move_Left_Char(TBanda* banda, char ref, FILE* out);
void Insert_Left(TBanda* banda, char x, FILE* out);
void Insert_Right(TBanda* banda, char x, FILE* out);
void Execute(TBanda* banda, TCoada* c, FILE* out, TStiva* vf_undo);
void Show_Current(TBanda* banda, FILE* out);
int Undo(TBanda* banda, TStiva* vf_undo, TStiva* vf_redo);
int Redo(TBanda* banda, TStiva* vf_undo, TStiva* vf_redo);

