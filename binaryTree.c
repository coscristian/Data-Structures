/*
Binary Tree
Cristian Quesada Cossio - UTP
*/

#include<stdlib.h>
#include<stdio.h>

struct nodo{
	int info;
	struct nodo *izq;
	struct nodo *der;
	struct nodo *anterior;
};

struct nodo *raiz = NULL;

struct nodo *minimo(struct nodo *raiz);
void destruir_nodo(struct nodo *nodo_a_destruir);
void reemplazar_nodo(struct nodo *raiz, struct nodo *nuevo);
struct nodo *maximo(struct nodo *raiz);


void reemplazar_nodo(struct nodo *raiz, struct nodo *nuevo){
	if (raiz->anterior != NULL){
		if (raiz->anterior->izq != NULL){
			if (raiz->info == raiz->anterior->izq->info){
				if (nuevo == NULL){
					free(raiz->anterior->izq);
				}
				raiz->anterior->izq = nuevo;
			}
		}
		if (raiz->anterior->der != NULL){
			if(raiz->info == raiz->anterior->der->info){
				if (nuevo == NULL){
					free(raiz->anterior->der);
				}
				raiz->anterior->der = nuevo;
			}
		}
	}
	if (nuevo != NULL){
		nuevo->anterior = raiz->anterior;
	}
}


void eliminar_nodo(struct nodo *raiz){
	if ( (raiz->izq != NULL) & (raiz->der != NULL) ){ //Si el nodo a eliminar tiene dos hijos
		struct nodo *menor;
		menor = minimo(raiz->der);
		raiz->info = menor->info;
		eliminar_nodo(menor);
	}else if(raiz->izq != NULL){   //Si el nodo a eliminar tiene solo hijo izquierdo
		struct nodo *mayor;
		mayor = maximo(raiz->izq);
		raiz->info = mayor->info;
		eliminar_nodo(mayor);
	}else if (raiz->der != NULL){  //Si el nodo a eliminar tiene solo hijo derecho
		struct nodo *menor;
		menor = minimo(raiz->der);
		raiz->info = menor->info;
		eliminar_nodo(menor);
	}else{                        //Si el nodo a eliminar es nodo hoja
		reemplazar_nodo(raiz, NULL);
	}
}


void buscar_para_eliminar(struct nodo *raiz, int dato_eliminar){
	if (raiz != NULL){
		if (dato_eliminar < raiz->info){
			buscar_para_eliminar(raiz->izq, dato_eliminar);
		}else if (dato_eliminar > raiz->info){
			buscar_para_eliminar(raiz->der, dato_eliminar);
		}else{
			if ( (raiz->info == dato_eliminar) & (cant_nodos(raiz) == 1)){
				free(raiz);
				raiz = NULL;
			}else{
				eliminar_nodo(raiz);
			}
		}
	}
}


int pedir_dato(){
	int dato;
	printf("\nIngrese el elemento a eliminar: "); scanf("%d", &dato); fflush(stdin);
	return dato;
}


void mostrar_max(struct nodo *max){
	if (max == NULL){
		printf("\n\nEL arbol esta vacio\n");
	}else{
		printf("\n\nEL valor maximo del arbol es: %d\n", max->info);
	}
}


struct nodo *maximo(struct nodo *raiz){
	if (raiz == NULL){
		return NULL;
	}else if(raiz->der != NULL){
		return maximo(raiz->der);
	}else{
		return raiz;
	}
}


void mostrar_min(struct nodo *min){
	if (min == NULL){
		printf("\n\nEL arbol esta vacio\n");
	}else{
		printf("\n\nEL valor minimo del arbol es: %d\n", min->info);
	}
}


struct nodo *minimo(struct nodo *raiz){
	if (raiz == NULL){
		return NULL;
	}else if(raiz->izq != NULL){
		return minimo(raiz->izq);
	}else{
		return raiz;
	}
}


int cant_nodos(struct nodo *raiz){
	if (raiz == NULL){
		return 0;
	}else{
		return (cant_nodos(raiz->izq) + 1 + cant_nodos(raiz->der));
	}
}


void mostrar_cant(int cant_nodos){
	printf("\n\nLa cantidad de nodos del arbol es: %d\n", cant_nodos);
}


void imp_arbol(struct nodo *raiz, int cont){
	int i;
	if (raiz != NULL){
		imp_arbol(raiz->der, cont+1);
		for(i = 0; i < cont; i++){
			printf("    ");
		}
		printf("%d\n", raiz->info);
		imp_arbol(raiz->izq, cont+1);
	}
}

void imprimirPre(struct nodo *reco)
{
    if (reco != NULL)
    {
        printf("%d-",reco->info);
        imprimirPre(reco->izq);
        imprimirPre(reco->der);
    }
}


void imprimirIn(struct nodo *reco){
	if (reco != NULL){
		imprimirIn(reco->izq);
		printf("%d - ", reco->info);
		imprimirIn(reco->der);
	}
}


void imprimirPost(struct nodo *reco)
{
    if (reco != NULL)
    {
        imprimirPost(reco->izq);
        imprimirPost(reco->der);
        printf("%d-",reco->info);
    }
}


int dato_en_arbol(struct nodo *raiz, int dato){

	struct nodo *reco = raiz;
	while(reco != NULL){
		if (dato < reco->info){
			reco = reco->izq;
		}else if(dato > reco->info){
			reco = reco->der;
		}else{
			return 1;
		}
	}
	return 0;

}

void agregar_nodo(){

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
		if (dato_en_arbol(raiz, x) == 0){
			struct nodo *anterior, *reco;
			anterior = NULL;
			reco = raiz;
			while(reco != NULL){
				anterior = reco;
				if (x < reco->info){
					reco = reco->izq;
				}else{
					reco = reco->der;
				}
			}
			if (x < anterior->info){
				anterior->izq = nuevo;
			}else{
				anterior->der = nuevo;
			}
			nuevo->anterior = anterior;
		}else{
			printf("\nEse dato ya se encuentra en el arbol\n");
		}
    }
}


void menu(){
	printf("\n\nMENU DE OPCIONES: ARBOLES BINARIOS\n");
	printf("1. Agregar un nodo a un árbol binario. El árbol almacenará un número entero en cada nodo.\n");
	printf("2. Mostrar el contenido del árbol en Inorden\n");
	printf("3. Mostrar el contenido del árbol en Preorden\n");
	printf("4. MOstrar el contenido del arbol en Postorden\n");
	printf("5. Calcular el numero de nodos del arbol\n");
	printf("6. Mostrar el valor minimo del arbol\n");
	printf("7. Mostrar el valor maximo del arbol\n");
	printf("8. ELiminar un nodo del arbol\n");
	printf("9. Mostrar el árbol (Se mostrará de forma horizontal)\n ");
	printf("10. Salir\n");
}


int main(){
	int opc;
	do{
		menu();
		scanf("%d", &opc); fflush(stdin);
		switch(opc){
			case 1: agregar_nodo(); break;
			case 2: imprimirIn(raiz); break;
			case 3: imprimirPre(raiz); break;
			case 4: imprimirPost(raiz); break;
			case 5: mostrar_cant(cant_nodos(raiz)); break;
			case 6: mostrar_min(minimo(raiz)); break;
			case 7: mostrar_max(maximo(raiz)); break;
			case 8: buscar_para_eliminar(raiz, pedir_dato()); break;
			case 9: imp_arbol(raiz, 0); break;
			case 10: printf("Saliendo....\n"); break;
			default: printf("Ingrese una opcion valida...");
		}
	}while(opc != 10);
	return 0;
}