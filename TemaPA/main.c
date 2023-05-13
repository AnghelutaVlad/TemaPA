#include"LANparty.h"
int main()
{
    int nr_echipe;
    Lista_de_echipe* head=NULL;
    Lista_de_echipe* Top8=NULL;
    Arbore* root=NULL;
    FILE* g;
    if((g=fopen("r.out","wt"))==NULL)
        printf("fisierul nu s-a putut deschide");
    head=citire_fisier(&nr_echipe);
    //afisare_echipe(head,g);
    eliminare_echipe_punctaj_minim(&head,&nr_echipe);
    afisare_echipe(head,g);
    matchmaker(&head,&Top8,&nr_echipe,g);
    root=generate_arbor(Top8,g);
    afisare_in_arbore_AVL(root,g);
    fclose(g);
}
