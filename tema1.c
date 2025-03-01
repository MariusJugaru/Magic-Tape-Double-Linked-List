/* JUGARU Marius-Gabriel - 312 CB*/
#include "lista.h"

int main()
{
    char output_filename[] = "tema1.out";
    FILE *out = fopen(output_filename, "w");

    TBanda* banda;
    banda = Initbanda();

    TCoada* c = InitQ();
    TStiva vf_undo = NULL, vf_redo = NULL;

    CitireOperatii(banda, c, out, &vf_undo, &vf_redo);
    
    fclose(out);
    DistrugeLista2(&banda->lista);
    DistrugeS(&vf_redo);
    DistrugeS(&vf_undo);
    free(banda);
    DistrQ(&c);

    return 0;
}