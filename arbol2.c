#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct nodo{
	int info;
	struct nodo *izq;
	struct nodo *der;
};

struct nodo *raiz = NULL;

/*
void imp_arbol( struct nodo *ptrArbol,int x,int y ){ 
   if ( ptrArbol!=NULL){
      gotoxy(x,y);
      printf("%d",ptrArbol->info);
      x=x-4;
      y=y+1;
      imp_arbol(ptrArbol->izq,x,y);
      x=x+11;
      imp_arbol(ptrArbol->der,x,y);
      y=y-1;
   }

}
*/

void imprimirIn(struct nodo *reco){
	if (reco != NULL){
		imprimirIn(reco->izq);
		printf("%i - ", reco->info);
		imprimirIn(reco->der);
	}
}


void agregar_nodo(){

	char lado;
	int x;
	printf("Ingrese el elemento a agregar al arbol: "); scanf("%d", &x); fflush(stdin);

	struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = x;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    if (raiz == NULL)
        raiz = nuevo;
    else{
        struct nodo *anterior, *reco;
        anterior = NULL;
        reco = raiz;
		while(reco != NULL){
			anterior = reco;
			//do{
				printf("Ingresar nodo por izquierda (i) o derecha (d) ?");
				scanf("%s", &lado); fflush(stdin);
			//}while(lado != 'i' || lado != 'd');
			if (lado == 'i'){
				if (reco->izq == NULL){
					reco = reco->izq;
					anterior->izq = nuevo;
				}else{
					printf("Nodo ocupado, se ha avanzado al nodo ocupado (Se ha avanzado por la izquierda)");
					reco = reco->izq;
					system("pause");
				}
			}else{
				if (reco->der == NULL){
					reco = reco->der;
					anterior->der = nuevo;
				}else{
					printf("Nodo ocupado, se ha avanzado al nodo ocupado (Se ha avanzado por la derrecha)");
					reco = reco->der;
					system("pause");
				}
			}
		}
    }
}


void menu(){
	printf("MENU DE OPCIONES: ARBOLES BINARIOS\n");
	printf("1. Agregar un nodo a un árbol binario. El árbol almacenará un número entero en cada nodo.\n");
	printf("2. Mostrar el contenido del árbol en Inorden\n");
	printf("3. Mostrar el árbol\n ");
	printf("4. Salir\n");
}




int main(){

	int opc;

	do{
		menu();
		scanf("%d", &opc); fflush(stdin);
		switch(opc){
			case 1: agregar_nodo(); break;
			case 2: imprimirIn(raiz); break;
			//case 3: imp_arbol(raiz, 40, 10); break;
			case 4: ; break;
			default: printf("Ingrese una opcion valida...");
		}

	}while(opc != 4);

	system("pause");
	return 0;
}
