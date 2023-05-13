#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
                 char* firstName;
                 char* secondName;
                 int punctaj;
              }Player;
typedef struct {
                 int nr_membri_echipa;
                 char* TeamName;
                 Player* membri_echipa;
                 float punctaj_echipa;
             }Nod_echipa;
struct lista_echipe{
                      Nod_echipa Echipa;
                      struct lista_echipe* next;
                   };
typedef struct lista_echipe Lista_de_echipe;
struct meci{
               Nod_echipa Echipa1;
               Nod_echipa Echipa2;
               struct meci* next;
           };
typedef struct meci Meci;
typedef struct{
                 Meci* front;
                 Meci* rear;
              }Queue;
struct arbore{
                 Nod_echipa Team;
                 struct arbore* left;
                 struct arbore* right;
             };
typedef struct arbore Arbore;
struct avl{
               Nod_echipa Team;
               int height;
               struct avl* left;
               struct avl* right;
          };
typedef struct avl AVL;
Lista_de_echipe* citire_fisier(int* nr_echipe);
Nod_echipa createNode(FILE* f);
Nod_echipa pop(Lista_de_echipe** top);
void add_at_end(Lista_de_echipe** head,Nod_echipa Team);
void afisare_echipe(Lista_de_echipe* head,FILE* g);
void push(Lista_de_echipe** top,Nod_echipa Team);
void eliminare_echipe_punctaj_minim(Lista_de_echipe** head,int* nr_echipe);
int putere_maxima_a_lui_2(int n);
void delete_head(Lista_de_echipe** head);
void delete_node(Lista_de_echipe* head,Lista_de_echipe* nod_de_sters);
Queue* createQueue();
void enqueue(Queue* q,Nod_echipa Echipa1,Nod_echipa Echipa2);
int isqueueempty(Queue* q);
Meci* dequeue(Queue* q);
void matchmaker(Lista_de_echipe** head,Lista_de_echipe** Top8,int* nr_echipe,FILE* g);
void matchfiller(Queue* coada_de_meciuri,Lista_de_echipe* current);
void matchprint(FILE* g,Meci* aux);
void teamprint(Nod_echipa Team,FILE* g);
void add_in_stacks(Lista_de_echipe** stiva_de_invingatori,Lista_de_echipe** stiva_de_pierzatori,Nod_echipa Team1,Nod_echipa Team2,int nr_echipe);
Arbore* generate_arbor(Lista_de_echipe* Top8,FILE* g);
Arbore* new_node_in_tree(Nod_echipa Echipa);
Arbore* insert_node_in_tree(Nod_echipa Team,Arbore* root);
void inorder(Arbore* root,FILE* g);
int height(AVL* root);
void printlevel(AVL* root,int level,FILE* g);
int maximum(int a,int b);
AVL* rightrotation(AVL* node);
AVL* leftrotation(AVL* node);
AVL* RLrotation(AVL* node);
AVL* LRrotation(AVL* node);
AVL* insert_in_AVL(AVL* root,Nod_echipa Echipa);
AVL* generate_AVL(AVL* root,Arbore* radacina);
void afisare_in_arbore_AVL(Arbore* radacina,FILE* g);
