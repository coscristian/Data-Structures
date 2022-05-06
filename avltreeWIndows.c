#include <stdio.h>
#include <stdlib.h>

typedef struct avlnode
{
    int clave;
    int bal; /* Factor de balance -1,0,1 */
    struct avlnode *left, *right;
} nodo, *pnodo;

# define max(A,B) ((A)>(B)?(A):(B)) /* Definici�n de macros */
# define min(A,B) ((A)>(B)?(B):(A))
 

int flag; 	/* Marca para registrar cambios de altura. En rebalance ascendente */
			//flag = 1 indica que debe seguir el ascenso rebalanceando.
int key; 	/* Variable global, para disminuir argumentos */
int alto_avl = 0; /* Altura �rbol avl. N�mero de nodos desde la ra�z a las hojas.*/
int hubo_balanceo = 0, hubo_balanceo_eliminar = 0;

/* Rotaci�n Izquierda *
*  A           B
* / \         / \
* a  B ==>   A   c
*   / \     / \
*   b  c    a  b
* S�lo cambian los factores de balance de los nodos A y B
* Los factores de balance de los sub-�rboles no cambian. */
static pnodo lrot(pnodo t)
{
    printf("\tSe usara la rotacion a la izquierda\n");
    pnodo temp;
    int x,y;
    temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    //Recalcula factores de balance de los dos nodos
    x = temp->bal; 
    y = t->bal; 
    temp->bal = x-1-max(y, 0); 
    t->bal = min(x-2+min(y, 0), y-1);
    return t;
}

/* Rotaci�n derecha
*
*   A         B
*  / \       / \
*  B  c ==> a   A
* / \          / \
* a  b        b   c
*
*/
static pnodo rrot(pnodo t)
{
    printf("\tSe usara la rotacion a la derecha\n");
    pnodo temp = t;
    int x,y;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    x = temp->bal; 
    y = t->bal;    
    temp->bal = x+1-min(y, 0);  
    t->bal = max(x+2+max(y, 0), y+1); 
    return t;
}

static void Error(int tipo)
{
    if (tipo) printf("\nError en insercion\n");
    else printf("\nError\n");
}

int Altura(void)
{
    return alto_avl;
}

pnodo CreaNodo(int key)
{
    pnodo t;
    t = (pnodo) malloc(sizeof(nodo));
    t->clave=key;
    t->left=0;
    t->right=0;
    return t;
}

pnodo insertR(pnodo t)
{
    if (t == NULL)  	/* Lleg� a un punto de inserci�n */
    {
        t = CreaNodo(key);
        t->bal = 0; 	/* Los dos hijos son nulos */
        flag = 1; 		/* Marca necesidad de revisar balances */
        printf("Nodo agregado correctamente\n");
        return t; 		/* retorna puntero al insertado */
    }
    else if (t->clave < key)
    {
        //desciende por la derecha
        t->right = insertR(t->right);
        //se pasa por la siguiente l�nea en la revisi�n ascendente
        t->bal += flag; /* Incrementa factor de balance */
    }
    else if (t->clave > key)
    {
        //desciende por la izquierda
        t->left = insertR(t->left);
        //se corrige en el ascenso
        t->bal -= flag; /* Decrementa balance */
    }
    else   /* (t->k == key) Ya estaba en el �rbol */
    {
        Error(1);
        flag = 0;
    }

    if (flag == 0){ /* No hay que rebalancear. Sigue el ascenso */
        return t;
    }

    /*El c�digo a continuaci�n es el costo adicional para mantener propiedad AVL */
    /* Mantiene �rbol balanceado avl. S�lo una o dos rotaciones por inserci�n */
    if (t->bal < -1){
        printf("\nNodo desbalanceado: %d por la rama de la izquierda\n", t->clave);
        /* Qued� desbalanceado por la izquierda.*/
        if (t->left->bal > 0){
            /* Si hijo izquierdo est� cargado a la derecha */
            t->left = lrot(t->left);
        }
        t = rrot(t);
        flag = 0; /* El sub�rbol no aumenta su altura */
        hubo_balanceo = 1;
    }
    else if (t->bal > 1){
        printf("\nNodo desbalanceado: %d por la rama de la derecha\n", t->clave);
        /* Si qued� desbalanceado por la derecha.*/
        if (t->right->bal < 0){
            /* Si hijo derecho est� cargado a la izquierda */
            t->right = rrot(t->right);
        }
        t = lrot(t); 
        flag = 0; /* El sub�rbol no aumenta su altura */
        hubo_balanceo = 1;
    }
    else if (t->bal == 0){
        /* La inserci�n lo balanceo */
        flag = 0; /* El sub�rbol no aumenta su altura.*/
    }
    else{
         /* Qued� desbalanceado con -1 � +1 */
        flag = 1; /* Propaga ascendentemente la necesidad de rebalancear */
    }
    return t;
}

/* Mantiene variable global con el alto del �rbol. */
pnodo InsertarAVL(int clave, pnodo t)
{   
    system("cls");
    hubo_balanceo = 0;
    key = clave; //pasa argumento a global.
    t = insertR(t);
    if (flag == 1)
        alto_avl++;
    //si la propagaci�n llega hasta la ra�z, aumenta la altura.
    if (hubo_balanceo == 1){
        printf("\nBalanceo hecho correctamente\n");
    }else{
        printf("\nNo fue necesario balancear el arbol\n");
    }
    return t;
}


pnodo deleteR(pnodo t)
{
    system("cls");
    pnodo p;
    if (t == NULL)  /* No encontr� nodo a descartar */
    {
        Error(0);
        flag = 0;
    }
    else if (t->clave < key)
    {
        //Comienza el descenso por la derecha
        t->right = deleteR(t->right);
        //aqu� se llega en el retorno ascendente.
        t->bal -= flag; /* Se descart� por la derecha. Disminuye factor */
        //Se retorna despu�s de la revisi�n de los factores
    }
    else if (t->clave > key)
    {
        //Desciende por la izquierda
        t->left = deleteR(t->left);
        //o se llega por esta v�a si se descart� por la izquierda.
        t->bal += flag; /* se descart� por la izq. Aumenta factor de balance */
    }
    else   /* (t->clave == key) */
    {
        /* Encontr� el nodo a descartar */
        printf("\nNodo %d eliminado correctamente\n", t->clave);
        if (t->left == NULL)   /*Si hay hijo derecho debe ser hoja, por ser AVL */
        {
            p = t;
            t = t->right;
            free(p);
            flag = 1; /* Debe seguir revisando factores de balance */
            return t; /* ascendentemente */
        }
        else if (t->right == NULL)   /*Si hay hijo izquierdo debe ser hoja */
        {
            p = t;
            t = t->left;
            free(p);
            flag = 1; /* Asciende revisando factores de balance */
            return t; /* Corrigiendo */
        }
        else   /* Tiene dos hijos */
        {
            if (t->bal<0)
            {
                /* Si cargado a la izquierda, elimina mayor descendiente hijo izq */
                p = t->left;
                while (p->right != NULL) p = p->right;
                t->clave = p->clave;
                key = p->clave; //busca hoja a eliminar
                t->left = deleteR(t->left);
                t->bal += flag; /* incrementa factor de balance */
            }
            else   /* Si cargado a la derecha, elimina menor descendiente hijo der */
            {
                p = t->right;
                while (p->left != NULL)
                    p = p->left;
                t->clave = p->clave;
                key = p->clave;
                t->right = deleteR(t->right);
                t->bal -= flag; /* decrementa balance */
            }
        }
    }

    /* Mantiene �rbol balanceado avl. S�lo una o dos rotaciones por descarte */
    if (flag == 0 ) /* No hay que rebalancear. Sigue el ascenso, sin rebalancear */
        return t;

    /* Hay que revisar factores de balance en el ascenso*/
    if (t->bal < -1)  /* Si qued� desbalanceado por la izquierda y dej� de ser AVL */
    {   
        printf("\nNodo desbalanceado: %d por la rama de la izquierda\n", t->clave);
        if (t->left->bal > 0) 
        {
            /* Si el hijo izquierdo est� cargado a la derecha */
            t->left = lrot(t->left);
            flag = 1; /*Continuar revisando factores */
        }
        else if (t->left->bal == 0)
            flag = 0; /*No debe seguir el rebalance */
        else
            flag = 1;/* Debe seguir revisando factores de balance */
        t = rrot(t);
        hubo_balanceo_eliminar = 1;
    }
    else if (t->bal > 1)  /* Si qued� desbalaceado por la derecha */
    {
        printf("\nNodo desbalanceado: %d por la rama de la derecha\n", t->clave);
        if (t->right->bal < 0)
        {
            /* Si hijo derecho est� cargado a la izquierda */
            t->right = rrot(t->right);
            flag = 1; //debe seguir revisando.
        }
        else if (t->right->bal == 0)
            flag = 0; /* No debe seguir el rebalance. */
        else //positivo
            flag = 1;/* Debe seguir revisando factores de balance.  */
        t = lrot(t);
        hubo_balanceo_eliminar = 1;
    }
    else if (t->bal == 0) /* Si estaba en +1 � -1 y queda en cero */
        flag = 1; /* Debe seguir corrigiendo. */
    else /* Si estaba en cero y queda en -1 � +1 */
        flag = 0; /* No debe seguir rebalanceando. */
    return t;
}

pnodo DescartarAVL(int clave, pnodo t)
{
    hubo_balanceo_eliminar = 0;
    key = clave;
    t = deleteR(t);
    if (flag == 1) alto_avl--;
    if (hubo_balanceo_eliminar == 1){
        printf("\nBalanceo hecho correctamente\n");
    }else{
        printf("\nNo fue necesario balancear el arbol\n");
    }
    return t;
}

pnodo deltreeR(pnodo t)
{
    if (t != NULL)
    {
        t->left = deltreeR(t->left);
        t->right = deltreeR(t->right);
        free(t); //borra la ra�z sub�rbol
    }
    return NULL;
}


pnodo deltree(pnodo t)
{
    alto_avl = 0;
    return deltreeR(t);
}


void inorder(pnodo t, int profundidad)
{
    if (t != NULL)
    {
        inorder(t->left, profundidad+1);
        printf ("Dato= %d Nivel= %d F.E.= %d \n", t->clave, profundidad, t->bal);
        inorder(t->right, profundidad+1);
    }
}

void menu(){
    printf("ARBOLES AVL\n");
    printf("1. Insert a new node in AVL Tree\n");
    printf("2. Display AVL Tree\n");
    printf("3. Delete node in AVL Tree\n");
    printf("4. Exit\n");
    printf("Select an option: ");
}

int pedirDatoEliminar(){
    int data;
    printf("Input the data you want to delete: ");
    scanf("%d", &data); fflush(stdin);
    return data;
}


int pedirDato(){
    int data; 
    printf("Input the data you want to add to the AVL Tree: ");
    scanf("%d", &data); fflush(stdin);
    return data;
}


int main()
{
    pnodo t=NULL;

    int opc = 0;
    do{
        menu();
        scanf("%d", &opc); fflush(stdin);
        switch (opc){
        case 1: t = InsertarAVL(pedirDato(), t); break;
        case 2: inorder(t, 0); break;
        case 3: t = DescartarAVL(pedirDatoEliminar(), t); break;
        case 4: printf("\nGood bye\n"); break;
        default: printf("\nSelect a correct option\n"); break;
        }
        system("pause");
        system("cls");
    }while(opc != 4);
}
