/* JUGARU Marius-Gabriel - 312 CB*/
#include "lista.h"

/* Implementare banda cu deget */

/* Alocare celula care contine caracterul "#" */

TL2 AlocareCel()
{
    TL2 init;
    init = (TL2)malloc(sizeof(TCelula2));
    if (!init) return NULL;

    init->info = '#';      
    init->urm = NULL;
    init->pre = NULL;

    return init;
}

/* Initializare banda */

TL2 InitL2()
{
    TL2 s, init;
    s = (TL2)malloc(sizeof(TCelula2));
    if (!s) return NULL;

    init = AlocareCel();
    if (!init) {
        free(s);
        return NULL;
    }

    s->info = 0;        // Informatia din santinela are valoarea 0
    s->urm = init;
    s->pre = NULL;
    init->pre = s;

    return s;
}

/* Distrugere lista din banda */

void DistrugeLista2(TL2 *aL) {
    TL2 p = (*aL)->urm, aux;
    /* distrugere elementele listei */
    while (p != NULL) {         
        aux = p;
        p = p->urm;
        free(aux);
    }

    /* distrugere santinela */
    free(*aL);                  
    *aL = NULL;
}

TBanda* Initbanda()
{
    TBanda* banda = (TBanda*)malloc(sizeof(TBanda));
    if (banda == NULL) return NULL;

    banda->lista = InitL2();
    if (banda->lista == NULL) return NULL;

    banda->deget = banda->lista->urm;
    return banda;
}

/* Implementare coada */

/* Initializare coada vida */

TCoada* InitQ()
{
    TCoada* c;
    c = (TCoada*)malloc(sizeof(TCoada));
    c->inc = NULL;
    c->sf = NULL;
    return c;
}

/* Inserare elemente in coada */

int InserareQ(char s[20], TCoada* c)
{
    TLista aux = (TLista)malloc(sizeof(TCelula));
    if(!aux) return 0;
    strcpy(aux->operatie, s);
    aux->urm = NULL;

    if (c->inc == NULL) {
        c->inc = aux;
    } else {
        c->sf->urm = aux;
    }
    c->sf = aux;
    return 1;
}

/* Extragere elemente din coada */

void ExtrQ(TCoada *c)
{
    char operatie[20];
    TLista aux;
    
    aux = c->inc;
    strcpy(operatie, aux->operatie);

    if (c->inc->urm != NULL) {
        c->inc = aux->urm;
    } else {
        c->inc = NULL;
        c->sf = NULL;
    }

    free(aux);

    printf("%s\n", operatie);
}

/* Afisare coada - pentru debugging */

void AfisareQ(TCoada *c)  /* afisare elementele cozii */
{
  TLista p;
  if(c->inc == NULL)  /* coada vida */
  {
    printf("Coada vida\n");
    return;
  } 
  printf("Elementele cozii: ");
  for(p = c->inc; p != NULL; p = p->urm)
    printf("%s ", p->operatie);
  printf("\n");
}

/* Distrugere coada */

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p, aux;
  p = (*c)->inc;
  while(p)
  {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}

/* Implementare stiva */

/* Introducere element in stiva */

int Push(TStiva* vf, TL2 x)
{
    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva));
    if (!aux) return 0;
    aux->info = x;

    aux->urm = *vf;
    *vf = aux;
    return 1;
}

/* Extragere element din stiva */

int Pop(TStiva* vf, TL2* x)
{
    TStiva aux;
    if (*vf == NULL) return 0;
    *x = (*vf)->info;

    aux = *vf;
    *vf = aux->urm;
    free(aux);
    return 1;
}

/* Afisare stiva - pentru debugging */

void AfisareStiva(TStiva vf)
{
    for(; vf != NULL; vf = vf->urm)
        printf("%p\n", vf->info);
}

/* Distrugere stiva */

void DistrugeS(TStiva* vf)
{
    TStiva aux;
    while (*vf) {
        aux = *vf;
        *vf = (*vf)->urm;
        free(aux);
    }
}

/* Citire operatii */

int CitireOperatii(TBanda* banda, TCoada* c, FILE* out, TStiva* vf_undo, TStiva* vf_redo)
{
    char input_filename[] = "tema1.in";
    FILE *in = fopen(input_filename, "r");

    if (in == NULL) return -1;

    int nr_op = 0; // numar de operatii
    fscanf(in, "%d", &nr_op);

    char operatie[20], caracter[1];
    int i;
    for (i = 0; i < nr_op; i++) {
        fscanf(in, "%s", operatie);

        if (strcmp(operatie, "MOVE_LEFT") == 0) {
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "MOVE_RIGHT") == 0) {
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "MOVE_LEFT_CHAR") == 0) {
            fscanf(in, "%s", caracter);
            strcat(operatie, caracter);
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "MOVE_RIGHT_CHAR") == 0) {
            fscanf(in, "%s", caracter);
            strcat(operatie, caracter);
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "WRITE") == 0) {
            DistrugeS(vf_undo);
            DistrugeS(vf_redo);
            fscanf(in, "%s", caracter);
            strcat(operatie, caracter);
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "INSERT_LEFT") == 0) {
            fscanf(in, "%s", caracter);
            strcat(operatie, caracter);
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "INSERT_RIGHT") == 0) {
            fscanf(in, "%s", caracter);
            strcat(operatie, caracter);
            InserareQ(operatie, c);
        } else if (strcmp(operatie, "SHOW_CURRENT") == 0) {
            Show_Current(banda, out);
        } else if (strcmp(operatie, "SHOW") == 0) {
            Show(banda, out);
        } else if (strcmp(operatie, "UNDO") == 0) {
            Undo(banda, vf_undo, vf_redo);
        } else if (strcmp(operatie, "REDO") == 0) {
            Redo(banda, vf_undo, vf_redo);
        } else if (strcmp(operatie, "EXECUTE") == 0) {
            Execute(banda, c, out, vf_undo);
        } else {
            printf("ERROR\n Operatie introdus gresit");
            return -1;
        }
    }

    fclose(in);
}

void Move_Left(TBanda* banda, TStiva* vf_undo)
{
    if (banda->deget->pre->pre != NULL) {
        Push(vf_undo, banda->deget);
        banda->deget = banda->deget->pre;
    }
        
}

void Move_Right(TBanda* banda, TStiva* vf_undo)
{
    Push(vf_undo, banda->deget);
    if (banda->deget->urm != NULL) {
        banda->deget = banda->deget->urm;
    } else {
        TL2 aux = AlocareCel();
        banda->deget->urm = aux;
        aux->pre = banda->deget;
        banda->deget = aux;
    }
    
}

void Write(TBanda* banda, char x)
{
    banda->deget->info = x;
}

void Move_Right_Char(TBanda* banda, char ref, FILE* out)
{
    TL2 p, ant;
    ant = banda->deget;
    p = banda->deget;

    while (p != NULL) {
        if (p->info == ref) break;

        ant = p;
        p = p->urm;
    }

    if (p == NULL) {
        TL2 aux = AlocareCel();
        if (aux) {
            ant->urm = aux;
            aux->pre = ant;
            banda->deget = aux;
        } else {
            //  printf("ERROR\n");
            fprintf(out, "ERROR\n");
        }
        
    } else {
        banda->deget = p;
    }
}

void Move_Left_Char(TBanda* banda, char ref, FILE* out)
{
    TL2 p;

    for (p = banda->deget; p->pre != NULL; p = p->pre) {
        if (p->info == ref) break;
    }

    if (p->pre == NULL) {
        fprintf(out, "ERROR\n");
        //  printf("ERROR\n");
    } else {
        banda->deget = p;
    }
}

void Insert_Left(TBanda* banda, char x, FILE* out)
{
    if (banda->deget->pre->pre != NULL) {
        TL2 aux = AlocareCel();
        if (aux) {
            banda->deget->pre->urm = aux;
            aux->urm = banda->deget;
            aux->pre = banda->deget->pre;
            banda->deget->pre = aux;
            banda->deget = aux;
            Write(banda, x);
        } else {
            //  printf("ERROR\n");
            fprintf(out, "ERROR\n");
        }
    } else {
        //  printf("ERROR\n");
        fprintf(out, "ERROR\n");
    }
}

void Insert_Right(TBanda* banda, char x, FILE* out)
{
    TL2 aux = AlocareCel();
    if (aux) {
        if (banda->deget->urm != NULL) {
            aux->urm = banda->deget->urm;
            aux->urm->pre = aux;
        }

        banda->deget->urm = aux;
        aux->pre = banda->deget;
        banda->deget = aux;
        Write(banda, x);
    } else {
        //  printf("ERROR\n");
        fprintf(out, "ERROR\n");
    }
}

/* Afisare elemente banda */

void Show(TBanda* banda, FILE* out)
{

    TL2 p;
    for(p = banda->lista->urm; p != NULL; p = p->urm) {
        if (p == banda->deget) {
            //  printf("|%c|", p->info);
            fprintf(out, "|%c|", p->info);
        } else {
            //  printf("%c", p->info);
            fprintf(out, "%c", p->info);
        }
    }
    //  printf("\n");
    fprintf(out, "\n");
}

/* Afisare element curent */

void Show_Current(TBanda* banda, FILE* out)
{
    //  printf("%c\n", banda->deget->info);
    fprintf(out, "%c\n", banda->deget->info);
}

int Undo(TBanda* banda, TStiva* vf_undo, TStiva* vf_redo)
{
    TL2 p;
    if (vf_undo == NULL) return 0;

    Pop(vf_undo, &p);
    Push(vf_redo, banda->deget);
    banda->deget = p;



    return 1;
}

int Redo(TBanda* banda, TStiva* vf_undo, TStiva* vf_redo)
{
    TL2 p;
    if (vf_redo == NULL) return 0;

    Pop(vf_redo, &p);
    Push(vf_undo, banda->deget);

    banda->deget = p;

    return 1;
}

void Execute(TBanda* banda, TCoada* c, FILE* out, TStiva* vf_undo)
{
    char operatie[20], caracter;
    TLista aux;
    
    aux = c->inc;
    strcpy(operatie, aux->operatie);

    if (c->inc->urm != NULL) {
        c->inc = aux->urm;
    } else {
        c->inc = NULL;
        c->sf = NULL;
    }

    free(aux);

    if (strcmp(operatie, "MOVE_LEFT") == 0) {
        Move_Left(banda, vf_undo);
    } else if (strcmp(operatie, "MOVE_RIGHT") == 0) {
        Move_Right(banda, vf_undo);
    } else if (strstr(operatie, "MOVE_LEFT_CHAR") != NULL) {
        caracter = operatie[14];
        Move_Left_Char(banda, caracter, out);
    } else if (strstr(operatie, "MOVE_RIGHT_CHAR") != NULL) {
        caracter = operatie[strlen(operatie) - 1];
        Move_Right_Char(banda, caracter, out);
    } else if (strstr(operatie, "WRITE") != NULL) {
        caracter = operatie[strlen(operatie) - 1];
        Write(banda, caracter);
    } else if (strstr(operatie, "INSERT_LEFT") != NULL) {
        caracter = operatie[strlen(operatie) - 1];
        Insert_Left(banda, caracter, out);
    } else if (strstr(operatie, "INSERT_RIGHT") != NULL) {
        caracter = operatie[strlen(operatie) - 1];
        Insert_Right(banda, caracter, out);
    }

}