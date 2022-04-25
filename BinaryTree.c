/* 
Cristian Quesada Cossio
Programa Arbol Binario preguntando al usuario por que lado quiere ingrear el nodo
UTP
*/
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>

struct nodo{
	int info;
	struct nodo *izq;
	struct nodo *der;
};

struct nodo *raiz = NULL;

void gotoxy(int x, int y){
	HANDLE Manipulador;
	COORD Coordenadas;
	Manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
	Coordenadas.X = x;
	Coordenadas.Y = y;
	SetConsoleCursorPosition(Manipulador, Coordenadas);
}


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


void imprimirIn(struct nodo *reco){
	if (reco != NULL){
		imprimirIn(reco->izq);
		printf("%d - ", reco->info);
		imprimirIn(reco->der);
	}
}


void agregar_nodo(){
	system("cls");
	char lado[2], izq[2] = "i", der[2] = "d";
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
    	system("cls");
        struct nodo *anterior, *reco;
        anterior = NULL;
        reco = raiz;
		while(reco != NULL){
			anterior = reco;
			printf("Ingresar nodo por izquierda (i) o derecha (d)...?: ");
			scanf("%s", &lado); fflush(stdin);
			if ( strcmp(lado, izq) == 0){
				if (reco->izq == NULL){
					reco = reco->izq;
					anterior->izq = nuevo;
				}else{
					system("cls");
					printf("\nNodo ocupado, se ha avanzado al nodo ocupado (Se ha avanzado por la izquierda).\n");
					reco = reco->izq;
					
				}
			}else if(strcmp(lado, der) == 0){
				if (reco->der == NULL){
					reco = reco->der;
					anterior->der = nuevo;
				}else{
					system("cls");
					printf("\nNodo ocupado, se ha avanzado al nodo ocupado (Se ha avanzado por la derrecha).\n");
					reco = reco->der;
					
				}
			}else{
				printf("Ingrese un lado valido debe ser (i) o (d).\n");
			}
		}
    }
}


void menu(){
	printf("MENU DE OPCIONES: ARBOLES BINARIOS\n");
	printf("1. Agregar un nodo a un arbol binario. El arbol almacenara un numero entero en cada nodo.\n");
	printf("2. Mostrar el contenido del arbol en Inorden\n");
	printf("3. Mostrar el arbol\n");
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
			case 3: imp_arbol(raiz, 40, 10); break;
			case 4: ; break;
			default: printf("Ingrese una opcion valida...\n");
		}
		printf("\n");
		system("pause");
		system("cls");
	}while(opc != 4);
	return 0;
}
