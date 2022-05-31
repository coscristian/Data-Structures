/*
Sistema de Urgencias 
Construya un programa que gestione la consulta médica en una unidad de urgencias. Los pacientes llegan a la unidad de 
urgencias donde son atendidos por el médico de Triage quien de acuerdo con la evaluación que realiza asigna a cada 
paciente un identificador de prioridad para la consulta médica. Existen 3 niveles de prioridad (1, 2, 3), siendo 1 
el de mas alta prioridad, 3 el de mas baja prioridad.Su sistema debe permitir a un auxiliar médico ingresar los datos
básicos del paciente (identificación, nombre, apellido, id_prioridad), consultar los datos (todos los datos) del 
siguiente paciente a ser pasado a consulta médica, consultar el listado de pacientes en espera (todos sus datos) y, 
salir del sistema.La gestión de información del sistema debe manejarse mediante la lógica de colas, considerando para 
la asignación de la consulta médica la prioridad asignada a cada paciente así: Para la consulta médica se asigna al paciente 
con mayor prioridad, teniendo en cuenta que se atienden consecutivamente máximo 3 pacientes de prioridad 1, máximo 2 de 
prioridad 2, máximo 1 de prioridad 3. Cuando el nivel de prioridad llega al máximo, automáticamente se reinicia a cero, además, 
mientras no haya llegado al máximo sigue siendo la prioridad que se busca para asignar cita. Esta restricción será superada por 
otra que obliga a que los pacientes de prioridad1 siempre sean menores o iguales que los de prioridad2 y estos menores o iguales 
que los de prioridad3. Es decir, se obvia la primera restricción siempre en favor de la segunda (si se da el caso).

Cristian Quesada Cossio UTP
*/

#include<stdio.h>
#include<stdlib.h>

struct paciente{
	char id[11], nombre[15], apellido[15];
	int prioridad;
	struct paciente *sig;
};

//Cola Original para pacientes
struct paciente *cola = NULL;
struct paciente *ultimoCola = NULL;

//Cola Auxiliar
struct paciente *colaAux = NULL;
struct paciente *ultimoColaAux = NULL;

//Cantidad de pacientes totales por prioridad
int cant_p1 = 0;
int cant_p2 = 0;
int cant_p3 = 0;

//Contadores para cantidad de pacientes atendidos consecutivamente por prioridad
int cont_atendidos_p1 = 0;
int cont_atendidos_p2 = 0;
int cont_atendidos_p3 = 0;

//Bandera para saber si la cantidad de pacientes por prioridad en espera esta nivelado
int nivelado = 0;

//Banderas para saber si cada nivel de prioridad llego al tope
int tope_p1 = 0;
int tope_p2 = 0;
int tope_p3 = 0;


void consultar_lista_espera(){
	int cont = 1;
	struct paciente *temp = cola;
	
	system("cls");
	if (cola != NULL){
		printf("\t\tLista de Espera\n");
		while(temp != NULL){
			printf("Paciente %d\n", cont);
			printf("\tIdentificacion: %s\n", temp->id);
			printf("\tNombre: %s\n", temp->nombre);
			printf("\tApellido: %s\n", temp->apellido);
			printf("\tPrioridad: %d\n", temp->prioridad);
			temp = temp->sig;
			cont++;
		}
	}else{
		printf("No hay pacientes en lista de espera\n\n");
	}
}


void encolarAux(){

	if (colaAux == NULL){
		colaAux = cola;
		cola = cola->sig;
		ultimoColaAux = colaAux;
		ultimoColaAux->sig = NULL;
	}else{
		ultimoColaAux->sig = cola;
		ultimoColaAux = cola;
		cola = cola->sig;
		ultimoColaAux->sig = NULL;
	}
}


void mostrar_paciente(struct paciente *pac){
	printf("Paciente\n");
	printf("\tIdentificacion: %s\n", pac->id);
	printf("\tNombre: %s\n", pac->nombre);
	printf("\tApellido: %s\n", pac->apellido);
	printf("\tPrioridad: %d\n", pac->prioridad);
}

void seleccionar_paciente(int prioridad_consul, int *mostrado){
	while(cola != NULL){
		if (cola->prioridad == prioridad_consul && *mostrado == 0){
			mostrar_paciente(cola);
			*mostrado = 1;
			if (cola->prioridad == 1){
				cant_p1--;
			}else if (cola->prioridad == 2){
				cant_p2--;
			}else{
				cant_p3--;
			}
			cola = cola->sig;
		}else{
			encolarAux();
		}
	}
}


void consultar_sig_paciente(){

	int mostrado = 0; // Bandera para saber si debo mostrar consecutivamente los 3 de prioridad 1, 2 de prioridad 2 y 1 de prioridad 3
	
	/* Inicialmente se tiene prioridad por el nivel con mas pacientes en espera,
	cuando se nivelen la cantidad de pacientes en los niveles, se procede a tomar consecutivamente 3
	de prioridad 1, luego 2 de prioridad 2 y luego 1 de prioridad 3 */
	system("cls");
	if (cola != NULL){
		if (cant_p1 > cant_p2 && cant_p1 > cant_p3 && nivelado != 1){       
			seleccionar_paciente(1, &mostrado);
		}else if(cant_p2 > cant_p1 && cant_p2 > cant_p3 && nivelado != 1){
			seleccionar_paciente(2, &mostrado);
		}else if (cant_p3 > cant_p1 && cant_p3 > cant_p2 && nivelado != 1){
			seleccionar_paciente(3, &mostrado);
		}else{
			nivelado = 1;
			if (cont_atendidos_p1 < 3 && cant_p1 > 0){
				while(cola != NULL){
					if (cola->prioridad == 1 && mostrado == 0){
						mostrar_paciente(cola);
						mostrado = 1;
						cant_p1--;
						cola = cola->sig;
						cont_atendidos_p1++;
					}else{
						encolarAux();
					}
				}
			}
			if (cont_atendidos_p2 < 2 && cant_p2 > 0){
				while(cola != NULL){
					if (cola->prioridad == 2 && mostrado == 0){
						mostrar_paciente(cola);
						mostrado = 1;
						cant_p2--;
						cola = cola->sig;
						cont_atendidos_p2++;
					}else{
						encolarAux();
					}
				}
			}
			if (cont_atendidos_p3 < 1 && cant_p3 > 0){
				while(cola != NULL){
					if (cola->prioridad == 3 && mostrado == 0){
						mostrar_paciente(cola);
						mostrado = 1;
						cant_p3--;
						cola = cola->sig;
						cont_atendidos_p3++;
					}else{
						encolarAux();
					}
				}
			}
		}
					
		if (cont_atendidos_p1 == 3){
			tope_p1 = 1;
		}
		if (cont_atendidos_p2 == 2){
			tope_p2 = 1;
		}
		if(cont_atendidos_p3 == 1){
			tope_p3 = 1;
		}
		
		int condicion1 = cant_p1 != 0 && cant_p2 == 0 && cant_p3 == 0;
		int condicion2 = cant_p2 != 0 && cant_p1 == 0 && cant_p3 == 0;
		int condicion3 = cant_p3 != 0 && cant_p1 == 0 && cant_p2 == 0;
		
		if(condicion1 == 1 || condicion2 == 1 || condicion3 == 1){
			cont_atendidos_p1 = 0;
			cont_atendidos_p2 = 0;
			cont_atendidos_p3 = 0;
		}
				
		if (tope_p1 == 1 && tope_p2 == 1 && tope_p3 == 1){
			cont_atendidos_p1 = 0;
			cont_atendidos_p2 = 0;
			cont_atendidos_p3 = 0;
			tope_p1 = 0;
			tope_p2 = 0;
			tope_p3 = 0;
		}	
		
	
		while(colaAux != NULL){  //Paso todos los pacientes a la cola original
			if (cola == NULL){
				cola = colaAux;
				colaAux = colaAux->sig;
				ultimoCola = cola;
				ultimoCola->sig = NULL;
			}else{
				ultimoCola->sig = colaAux;
				ultimoCola = colaAux;
				colaAux = colaAux->sig;
				ultimoCola->sig = NULL;
			}
		}
	}else{
		printf("No hay pacientes\n\n");
	}
}


void encolar(struct paciente *nuevo){
	
	nuevo->sig = NULL;
	if (cola == NULL){
		cola = nuevo;
		ultimoCola = cola;
	}else{
		ultimoCola->sig = nuevo;
		ultimoCola = nuevo;
	}
}


void ingresar_paciente(){
	system("cls");
	struct paciente *nuevo = malloc(sizeof(struct paciente));
	
	printf("Ingrese la identificacion: "); gets(nuevo->id); fflush(stdin);
	printf("Ingrese el nombre: "); gets(nuevo->nombre);	fflush(stdin);
	printf("Ingrese el apellido: "); gets(nuevo->apellido); fflush(stdin);
	printf("Ingrese la prioridad del paciente: "); scanf("%d", &nuevo->prioridad); fflush(stdin);
	
	encolar(nuevo);
	if (nuevo->prioridad == 1){
		cant_p1++;
	}else if(nuevo->prioridad == 2){
		cant_p2++;
	}else{
		cant_p3++;
	}
}


void menu(){
	printf("\t\tGestor de consultas medicas\n");
	printf("1. Ingresar paciente.\n");
	printf("2. Consultar siguiente paciente.\n");
	printf("3. Consultar listado de pacientes en espera.\n");
	printf("4. Salir.\n");
	printf("Seleccion una opcion: ");
}

int main(){
	
	int opcion;
	do{
		menu();
		scanf("%d", &opcion); fflush(stdin);
		switch(opcion){
			case 1: ingresar_paciente(); break;
			case 2: consultar_sig_paciente(); break;
			case 3: consultar_lista_espera(); break;
			case 4: printf("Saliendo...\n"); break;
			default: printf("Ingrese una opcion valida...\n"); break;
		}
		system("pause");
		system("cls");
	}while(opcion != 4);
	return 0;
}
