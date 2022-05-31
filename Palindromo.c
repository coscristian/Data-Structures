/*
Programa que determina si una palabra es palindromo o no usando la lógica de pilas.
Construya un programa que mediante la lógica de pilas determine si una palabra o frase es palíndroma. Considere cada caracter 
de la palabra o frase como la información contenida en cada nodo de la pila (ignore los espacios y tildes, logré además que su 
programa capture la cadena en forma normal).  Su programa debe permitir ingresar la palabra o frase a evaluar, mostrar SI es 
palíndroma, o si NO lo es.

Cristian QUesada Cossio UTP
*/



#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct nodo{
	char caracter;
	struct nodo *sig; 	
};


int cadena_son_iguales(struct nodo *pila, struct nodo *pilaAux){
	while(pila != NULL){
		if (pila->caracter != pilaAux->caracter) return 0;
		pila = pila->sig;
		pilaAux = pilaAux->sig;
	}
	return 1;
}


struct nodo *enpilarAux(struct nodo *pila, struct nodo *pilaAux){   //Agrego cadena de la pila orig a la pila Aux(La cadena quedara en orden normal)
	struct nodo *nuevo;
	while(pila != NULL){
		nuevo = malloc(sizeof(struct nodo));
		nuevo->caracter = pila->caracter;
		if (pilaAux == NULL){
			nuevo->sig = NULL;
			pilaAux = nuevo;
		}else{
			nuevo->sig = pilaAux;
			pilaAux = nuevo;
		}
		pila = pila->sig;
	}
	return pilaAux;
}


struct nodo *enpilar(char caracter, struct nodo *pila){
	
	struct nodo *nuevo;
	nuevo = malloc(sizeof(struct nodo));
	nuevo->caracter = caracter;
	if (pila == NULL){
		nuevo->sig = NULL;
		pila = nuevo;
	}else{
		nuevo->sig = pila;
		pila = nuevo;
	}
	return pila;
}


void verif_palindromo(){
	system("cls");
	
	int i;
	struct nodo *pila = NULL;
	struct nodo *pilaAux = NULL;
	char c, vocal_sin[5] = "aeiou", vocal_con[5] = {160, 130, 161, 162, 163};  // Ascii de las vocales con tilde
	
	printf("Ingrese la frase: "); 
	while( (c = getch()) != 13){
		fflush(stdin);
		printf("%c", c);
		if (c != ' '){
			c = tolower(c);
			for(i = 0; i < 5; i++){
				if (c == vocal_con[i]){
					c = vocal_sin[i];  
				}
			}
			pila = enpilar(c, pila);  //Agrego a la pila la cadena original (La cadena o frase quedara invertida)
			pilaAux = enpilarAux(pila, pilaAux); //En la pila Aux quedara la cadena en orden original(normal)
		}
	}
	system("cls");
	if( cadena_son_iguales(pila, pilaAux) == 1){
		printf("La frase ingresada es palindroma.\n\n");
	}else{
		printf("La frase ingresada no es palindroma.\n\n");
	}
}

void menu(){
	printf("\t\t\tPrograma que identifica si es palindromo\n");
	printf("1. Ingresar palabra o frase y verificar si es palindroma\n");
	printf("2. Salir\n");
	printf("Ingrese la opcion deseada: ");
}

int main(){
	int opcion;
	do{
		menu();
		scanf("%d", &opcion);
		fflush(stdin);
		switch(opcion){
			case 1: verif_palindromo(); break;
			case 2: printf("\nSaliendo...\n"); break;
			default: printf("Ingrese una opcion valida"); break;
		}
		system("pause");
		system("cls");
	}while(opcion != 2);
	return 0;
}
