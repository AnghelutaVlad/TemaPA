#include"LANparty.h"
Nod_echipa createNode(FILE* f)
{
     char buf[50];
     int punctaj=0;
     Nod_echipa newnode;
     fscanf(f,"%d",&(newnode.nr_membri_echipa));
     fgetc(f);
     fgets(buf,50,f);
     buf[strcspn(buf,"\n")]=0;
     newnode.TeamName=(char*)malloc((strlen(buf))*sizeof(char));
     if(newnode.TeamName==NULL)
        printf("alocare esuata");
     strcpy(newnode.TeamName,buf);
     newnode.membri_echipa=(Player*)malloc((newnode.nr_membri_echipa)*sizeof(Player));
     if(newnode.membri_echipa==NULL)
     {
         printf("alocare esuata\n");
         exit(1);
     }
     for(int i=0;i<newnode.nr_membri_echipa;i++)
        {
            fscanf(f,"%s",buf);
            newnode.membri_echipa[i].firstName=(char*)malloc(strlen(buf)*sizeof(char));
            strcpy(newnode.membri_echipa[i].firstName,buf);
            fscanf(f,"%s",buf);
            newnode.membri_echipa[i].secondName=(char*)malloc(strlen(buf)*sizeof(char));
            strcpy(newnode.membri_echipa[i].secondName,buf);
            fscanf(f,"%d",&(newnode.membri_echipa[i].punctaj));
        }
     for(int i=0;i<newnode.nr_membri_echipa;i++)
        punctaj+=newnode.membri_echipa[i].punctaj;
     newnode.punctaj_echipa=(float)punctaj/(newnode.nr_membri_echipa);
     return newnode;
}
void push(Lista_de_echipe** top,Nod_echipa Team)
{
    Lista_de_echipe* newnode=(Lista_de_echipe*)malloc(sizeof(Lista_de_echipe));
    if(newnode==NULL)
    {
        printf("alocare esuata\n");
        exit(1);
    }
    newnode->Echipa=Team;
    newnode->next=(*top);
    (*top)=newnode;
    return;
}
Nod_echipa pop(Lista_de_echipe** top)
{
    Lista_de_echipe* node=(*top);
    Nod_echipa Team=node->Echipa;
    (*top)=(*top)->next;
    free(node);
    return Team;
}
void add_at_end(Lista_de_echipe** head,Nod_echipa Team)
{
    Lista_de_echipe* newnode=(Lista_de_echipe*)malloc(sizeof(Lista_de_echipe)),*p;
    if(newnode==NULL)
    {printf("alocare esuata");
     exit(1);}
    newnode->Echipa=Team;
    newnode->next=NULL;
    if((*head)==NULL)
        (*head)=newnode;
    else
    {
        p=(*head);
        while((p->next)!=NULL)
            p=p->next;
        p->next=newnode;
    }
    return;
}
Lista_de_echipe* citire_fisier(int* nr_echipe)
{
    Lista_de_echipe* cap_lista=NULL;
    FILE* f;
    Nod_echipa Team;
    if((f=fopen("d.in","rt"))==NULL)
        printf("Nu se poate deschide fisierul");
    fscanf(f,"%d",nr_echipe);
    for(int i=0;i<(*nr_echipe);i++)
    {
        Team=createNode(f);
        push(&cap_lista,Team);
    }
    fclose(f);
    return cap_lista;
}
int putere_maxima_a_lui_2(int n)
{
    int nr_final=1;
    while(nr_final<=n)
    {
        nr_final*=2;
    }
    return nr_final/2;
}
void delete_head(Lista_de_echipe** head)
{
    Lista_de_echipe* p=(*head);
    (*head)=(*head)->next;
    free(p);
    return;
}
void delete_node(Lista_de_echipe* head,Lista_de_echipe* nod_de_sters)
{
    Lista_de_echipe* p=head,*node;
    while(p->next!=nod_de_sters)
    {
        p=p->next;
    }
    node=p->next;
    p->next=node->next;
    free(node);
    return;
}
void eliminare_echipe_punctaj_minim(Lista_de_echipe** head,int* nr_echipe)
{
    int nr_final_echipe=putere_maxima_a_lui_2(*nr_echipe);
    Lista_de_echipe *p,*echipa_de_punctaj_minim;
    float punctaj_minim;
    while((*nr_echipe)>nr_final_echipe)
    {
        p=(*head);
        echipa_de_punctaj_minim=(*head);
        punctaj_minim=(p->Echipa).punctaj_echipa;
        while(p!=NULL)
        {
            if(p->Echipa.punctaj_echipa<punctaj_minim)
            {
                echipa_de_punctaj_minim=p;
                punctaj_minim=p->Echipa.punctaj_echipa;
            }
            p=p->next;
        }
        if(echipa_de_punctaj_minim==(*head))
            delete_head(head);
        else
            delete_node(*head,echipa_de_punctaj_minim);
        (*nr_echipe)--;
    }
    return;
}
void afisare_echipe(Lista_de_echipe* head,FILE* g)
{
    Lista_de_echipe* node=head;
    while(node!=NULL)
        {fprintf(g,"%s\n",node->Echipa.TeamName);
         node=node->next;}
    return;
}
Queue* createQueue()
{
    Queue* q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL)
    {
        printf("Alocare esuata\n");
        exit(1);
    }
    q->front=q->rear=NULL;
    return q;
}
void enqueue(Queue* q,Nod_echipa Echipa1,Nod_echipa Echipa2)
{
    Meci* newmatch=(Meci*)malloc(sizeof(Meci));
    if(newmatch==NULL)
    {
        printf("alocare esuata\n");
        exit(1);
    }
    newmatch->Echipa1=Echipa1;
    newmatch->Echipa2=Echipa2;
    newmatch->next=NULL;
    if(q->rear==NULL)
        q->rear=newmatch;
    else
    {
        (q->rear)->next=newmatch;
        q->rear=newmatch;
    }
    if(q->front==NULL)
        q->front=q->rear;
    return;
}
int isqueueempty(Queue* q)
{
    return (q->front)==NULL;
}
Meci* dequeue(Queue* q)
{
    if(isqueueempty(q))
        return NULL;
    else
    {
        Meci* aux=q->front;
        q->front=(q->front)->next;
        return aux;
    }
}
void delete_losers(Lista_de_echipe** stiva_pierzatori,int nr_echipe)
{
    Nod_echipa aux;
    while((*stiva_pierzatori)!=NULL)
        aux=pop(stiva_pierzatori);
    return;
}
void matchfiller(Queue* coada_de_meciuri,Lista_de_echipe* current)
{
    Nod_echipa Team1,Team2;
    while(current!=NULL)
    {
        Team1=current->Echipa;
        current=current->next;
        Team2=current->Echipa;
        current=current->next;
        enqueue(coada_de_meciuri,Team1,Team2);
    }
    return;
}
void matchprint(FILE* g,Meci* aux)
{
     fprintf(g,"%s",aux->Echipa1.TeamName);
     for(int i=0;i<33-strlen(aux->Echipa1.TeamName);i++)
        fprintf(g," ");
     fprintf(g,"-");
     for(int i=0;i<34-strlen(aux->Echipa2.TeamName);i++)
        fprintf(g," ");
    fprintf(g,"%s\n",aux->Echipa2.TeamName);
    return;
}
void teamprint(Nod_echipa Team,FILE* g)
{
    fprintf(g,"%s",Team.TeamName);
    for(int i=0;i<34-strlen(Team.TeamName);i++)
        fprintf(g," ");
    fprintf(g,"- ");
    fprintf(g,"%.2f\n",Team.punctaj_echipa);
    return;
}
void add_in_stacks(Lista_de_echipe** stiva_de_invingatori,Lista_de_echipe** stiva_de_pierzatori,Nod_echipa Team1,Nod_echipa Team2,int nr_echipe)
{
    for(int i=0;i<Team1.nr_membri_echipa;i++)
        Team1.membri_echipa[i].punctaj++;
    Team1.punctaj_echipa+=1;
    push(stiva_de_invingatori,Team1);
    push(stiva_de_pierzatori,Team2);
}
void matchmaker(Lista_de_echipe** head,Lista_de_echipe** Top8,int* nr_echipe,FILE* g)
{
    Queue* coada_de_meciuri=createQueue();
    Nod_echipa aux1,aux2;
    Lista_de_echipe* stiva_de_invingatori=NULL,*stiva_de_pierzatori=NULL;
    Meci* match;
    int round_number=1,nr=(*nr_echipe);
    matchfiller(coada_de_meciuri,*head);
    while(nr>1)
    {
        nr/=2;
        fprintf(g,"\n--- ROUND NO:%d\n",round_number);
        while(!isqueueempty(coada_de_meciuri))
        {
            match=dequeue(coada_de_meciuri);
            matchprint(g,match);
            if(match->Echipa1.punctaj_echipa>=match->Echipa2.punctaj_echipa)
               add_in_stacks(&stiva_de_invingatori,&stiva_de_pierzatori,match->Echipa1,match->Echipa2,nr);
            else
               add_in_stacks(&stiva_de_invingatori,&stiva_de_pierzatori,match->Echipa2,match->Echipa1,nr);
        }
        delete_losers(&stiva_de_pierzatori,nr);
        fprintf(g,"\nWINNERS OF ROUND NO:%d\n",round_number);
        round_number++;
        while(stiva_de_invingatori!=NULL)
        {
            if(nr==1)
            {
                aux1=pop(&stiva_de_invingatori);
                teamprint(aux1,g);
            }
            else
              {
                  aux1=pop(&stiva_de_invingatori);
                  teamprint(aux1,g);
                  aux2=pop(&stiva_de_invingatori);
                  teamprint(aux2,g);
                  enqueue(coada_de_meciuri,aux1,aux2);
                  if(nr==8)
                   {
                      add_at_end(Top8,aux1);
                      add_at_end(Top8,aux2);
                   }
              }
        }
    }
    return;
}
Arbore* new_node_in_tree(Nod_echipa Echipa)
{
    Arbore* newnode=(Arbore*)malloc(sizeof(Arbore));
    if(newnode==NULL)
    {
        printf("alocare esuata");
        exit(1);
    }
    newnode->Team=Echipa;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}
Arbore* insert_node_in_tree(Nod_echipa Echipa,Arbore* root)
{
     if(root==NULL)
        return new_node_in_tree(Echipa);
     if(Echipa.punctaj_echipa==root->Team.punctaj_echipa)
     {
         if(strcmp(Echipa.TeamName,root->Team.TeamName)>0)
            root->right=insert_node_in_tree(Echipa,root->right);
         else
            root->left=insert_node_in_tree(Echipa,root->left);
     }
     else if(Echipa.punctaj_echipa>root->Team.punctaj_echipa)
        root->right=insert_node_in_tree(Echipa,root->right);
     else
        root->left=insert_node_in_tree(Echipa,root->left);
     return root;
}
void inorder(Arbore* root,FILE* g)
{
    if(root)
    {
        inorder(root->right,g);
        fprintf(g,"%s",root->Team.TeamName);
        for(int i=0;i<34-strlen(root->Team.TeamName);i++)
            fprintf(g," ");
        fprintf(g,"-  %.2f\n",root->Team.punctaj_echipa);
        inorder(root->left,g);
    }
    return;
}
Arbore* generate_arbor(Lista_de_echipe* Top8,FILE* g)
{
    Arbore* root=NULL;
    Lista_de_echipe* p=Top8;
    while(p!=NULL)
    {
        root=insert_node_in_tree(p->Echipa,root);
        p=p->next;
    }
    fprintf(g,"\nTOP 8 TEAMS:\n");
    inorder(root,g);
    return root;
}
int height(AVL* root)
{
    int hs,hd;
    if(root==NULL)
        return -1;
    hs=height(root->left);
    hd=height(root->right);
    return 1+((hs>hd) ? hs:hd);
}
void printlevel(AVL* root,int level,FILE* g)
{
    if(root==NULL)
       return;
    if(level==0)
       fprintf(g,"%s\n",root->Team.TeamName);
    else if(level>0)
    {
        printlevel(root->right,level-1,g);
        printlevel(root->left,level-1,g);
    }
    return;
}
int maximum(int a,int b)
{
    if(a>=b)
        return a;
    else
        return b;
}
AVL* rightrotation(AVL* node)
{
    AVL* y=node->left;
    AVL* T3=y->right;
    y->right=node;
    node->left=T3;
    node->height=maximum(height(node->left),height(node->right))+1;
    y->height=maximum(height(y->left),height(y->right))+1;
    return y;
}
AVL* leftrotation(AVL* node)
{
    AVL* y=node->right;
    AVL* T3=y->left;
    y->left=node;
    node->right=T3;
    node->height=maximum(height(node->left),height(node->right))+1;
    y->height=maximum(height(y->left),height(y->right))+1;
    return y;
}
AVL* RLrotation(AVL* node)
{
    node->right=rightrotation(node->right);
    return leftrotation(node);
}
AVL* LRrotation(AVL* node)
{
    node->left=leftrotation(node->right);
    return rightrotation(node);
}
AVL* insert_in_AVL(AVL* root,Nod_echipa Echipa)
{
    if(root==NULL)
       {
           root=(AVL*)malloc(sizeof(AVL));
           root->Team=Echipa;
           root->right=NULL;
           root->left=NULL;
           root->height=0;
           return root;
       }
    if(root->Team.punctaj_echipa==Echipa.punctaj_echipa)
    {
        if(strcmp(Echipa.TeamName,root->Team.TeamName)>0)
            root->right=insert_in_AVL(root->right,Echipa);
        else
            root->left=insert_in_AVL(root->left,Echipa);
    }
    else if(root->Team.punctaj_echipa<Echipa.punctaj_echipa)
        root->right=insert_in_AVL(root->right,Echipa);
    else
        root->left=insert_in_AVL(root->left,Echipa);
    root->height=1+maximum(height(root->left),height(root->right));
    int k=((height(root->left))-height(root->right));
    if(k>1 && Echipa.punctaj_echipa<root->left->Team.punctaj_echipa)
        return rightrotation(root);
    if(k<-1 && Echipa.punctaj_echipa>root->left->Team.punctaj_echipa)
        return leftrotation(root);
    if(k>1 && Echipa.punctaj_echipa>root->left->Team.punctaj_echipa)
        return RLrotation(root);
    if(k<-1 && Echipa.punctaj_echipa<root->left->Team.punctaj_echipa)
        return LRrotation(root);
    return root;
}
AVL* generate_AVL(AVL* root,Arbore* radacina)
{
    if(radacina)
    {
        root=generate_AVL(root,radacina->right);
        root=insert_in_AVL(root,radacina->Team);
        root=generate_AVL(root,radacina->left);
    }
    return root;
}
void afisare_in_arbore_AVL(Arbore* radacina,FILE* g)
{
    AVL* root=NULL;
    root=generate_AVL(root,radacina);
    fprintf(g,"\nTHE LEVEL 2 TEAMS ARE:\n");
    printlevel(root,2,g);
    return;
}
