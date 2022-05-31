/*
Sistema de Gestión de Estudiantes UTP usando escritura de archivos
Estudiante: Cristian Quesada Cossio
*/

#include<stdio.h>
#include<string.h>
#include<conio.h>

struct Estudiante_infoU // Estructura estudiante con Información de la Universidad
{
    int semestre, materias_cursadas;
    char periodo[7];
    float promedio_integral;

}; //Array en donde se podrán almacenar 12 periodos por estudiante

struct Estudiante{ //Estructura estudiante con información personal 

    char  codigo[12], nombre[30], telefono[11], direccion[30], estado[7];
    int cant_periodos,asignar_posiciones_periodo, cont_estudiantes; //asignar_posiciones_periodo sirve para agregar los periodos al array de forma ordenada(ascendente)
	float promedio_general;
	
	struct Estudiante_infoU info_u_estudiante[12];

};  //Array de 100 posiciones que almacenará datos de tipo Estudiante


//Punteros a archivos
FILE *archivo_datos = NULL;
FILE *archivo_contador_estudiantes = NULL;
const char* direccion_archivo = "datos_estudiantes";
const char* direccion_archivo_contador = "cont_estudiantes.txt";

//Prototipos
int leer_opcion();

void mostrar_menu_principal(void);

int ingresar_estudiante(struct Estudiante info_estudiante);

void agregar_periodo(struct Estudiante info_estudiante, char codigo_a_buscar[]);

void agregar_info_periodo_academico(struct Estudiante info_estudiante);

int estudiante_esta_registrado(struct Estudiante info_estudiante, char *codigo_a_buscar);

void definir_estado(struct Estudiante info_estudiante, int contador_estudiantes);

float sacar_promedio(struct Estudiante info_estudiante);

void asignar_estado(struct Estudiante info_estudiante, char const *estado);

void mostrar_info_estudiantes_estado_fuera(struct Estudiante info_estudiantes, int contador_estudiantes);

void mostrar_info_prom_integral(struct Estudiante info_estudiante, int cantidad_periodos_estudiante);

void mostrar_info_academica_estudiante(struct Estudiante info_estudiante, int cant_periodos_est);

void mostrar_estudiantes(int contador_estudiantes);


 int leer_opcion(){

    int seleccionada;

    scanf("%d",&seleccionada);

	while(getchar() != '\n');
    
    return seleccionada;

}

void mostrar_menu_principal(){
    printf("\n----------------------------------------------------------------------------\n");
    printf("\t\t\t\tMENU\n");
    printf("1.Ingresar un estudiante\n");
    printf("2.Agregar informacion de un periodo academico a un estudiante registrado\n");
    printf("3.Asignar estado a los estudiantes\n");
    printf("4.Mostrar toda la informacion de los estudiantes en estado FUERA registrados\n");
    printf("5.Mostrar informacion de todos los estudiantes.\n");
    printf("6.Salir\n");
    printf("Que deseas hacer?");
    printf("\n----------------------------------------------------------------------------\n");

}

void est_agregado(){
	printf("\n------------------------------------------\n");
    printf("El estudiante se ha agregado correctamente");
    printf("\n------------------------------------------\n");
}


void agregar_periodo( struct Estudiante info_estudiante, char codigo_a_buscar[] ){

    int i=1, semestre, materias_cursadas, posicion_cursor, limite_periodos, posicion_periodo;
    float promedio_integral;
    char resultado[2], periodo[7];
    
	archivo_datos = fopen(direccion_archivo, "r+b");
	
	if (archivo_datos == NULL){
		
		printf("\nError al leer el archivo!!1\n");
		
	}else{
		
		fseek(archivo_contador_estudiantes, 0, SEEK_SET);  //Posiciono el cursor al inicio del archivo
		fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos );
				
		while(!feof(archivo_datos)){
			
			if ( strcmp(info_estudiante.codigo, codigo_a_buscar) == 0 ){  //Si el codigo ingresado coincide con el codigo de los registros
				
				limite_periodos = 12 - info_estudiante.cant_periodos; // Establece la cantidad de periodos restantes para cada estudiante
								
				for (i = 1; i <= limite_periodos; i++){
					
					posicion_periodo = info_estudiante.asignar_posiciones_periodo;
					
	        		printf("\n\tSemestre: ");
	        		scanf("%d",&info_estudiante.info_u_estudiante[posicion_periodo].semestre);
	        		
			        printf("\tPeriodo: ");
			        scanf("%s",&info_estudiante.info_u_estudiante[posicion_periodo].periodo);
			
			        printf("\tPromedio integral: ");
			        scanf("%f",&info_estudiante.info_u_estudiante[posicion_periodo].promedio_integral);
			
			        printf("\t#Materias cursadas: ");
			        scanf("%d",&info_estudiante.info_u_estudiante[posicion_periodo].materias_cursadas);
			        
			        /*Se supone que debe aumentar la cantidad de periodos de cada estudiante pero al momento de evaluar 
					en la opcion 3 y 6 del menu, indica que no se ha aumentado la cantidad de periodos*/
			        
			        info_estudiante.cant_periodos++;   
			        info_estudiante.asignar_posiciones_periodo++; // Aumenta la posicion para el array

			        //Retrocedo el cursor
					posicion_cursor = ftell(archivo_datos) - sizeof(info_estudiante); 
					fseek(archivo_datos, posicion_cursor, SEEK_SET);
			        fwrite(&info_estudiante, sizeof(info_estudiante) , 1 , archivo_datos);  //Escribo en el archivo los datos del periodo academico

			        	
					printf("\n\tDeseas agregar otro periodo? Escribe si o no: ");
	        		scanf("%s",&resultado);
	        		
			        if ( strcmp(resultado,"no\0") == 0){
			        	
			        	printf("\n---------------------------------------------------\n");
			            printf("Informacion de periodo academico agregada correctamente");
			            
			            break;
			        }
				}
				break;
							
			}else{
				fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos );
			}
		}
		fclose(archivo_datos);  
	}
}

int ingresar_estudiante(struct Estudiante info_estudiante){
	
	char resultado[3],codigo_est[12], codigo[11], nombre[30], direccion[30], telefono[11];
	
    printf("\nIngrese el codigo del estudiante:");

	gets(codigo_est);
	
    if ( !estudiante_esta_registrado(info_estudiante, codigo_est) ){ // Si el estudiante no est� registrado
    
    	archivo_datos = fopen(direccion_archivo , "ab");
    	
    	if (archivo_datos == NULL){
    		printf("\nError al abrir el archivo!!\n");
		}else{
			
		   	printf("Ingrese el nombre del estudiante:");
	    	gets(info_estudiante.nombre);
	
	    	printf("Ingrese la direccion del estudiante:");
	    	gets(info_estudiante.direccion);
	    	
			printf("Ingrese el telefono del estudiante:");
	    	scanf("%s", info_estudiante.telefono);	
	    	
	    	strcpy(info_estudiante.codigo, codigo_est);
		    
		    fwrite( &info_estudiante, sizeof(info_estudiante), 1, archivo_datos ); //Escribo en el archivo los datos personales ingresados del estudiante
			fclose(archivo_datos); 
	
			est_agregado();
						    	
		    printf("Deseas agregar un periodo academico? Escribe si o no: ");
		    scanf("%s",&resultado);
		    	
	    	if ( (strcmp(resultado,"si") ) == 0 || (strcmp(resultado,"Si") == 0)){
	    		
	    		agregar_periodo(info_estudiante, codigo_est);
	    		
			}else if( (strcmp(resultado,"no") ) == 0 || (strcmp(resultado,"No") == 0) ){
				printf("\n---------------------------------------------------------\n");
				printf("No se ha agregado el periodo academico para el estudiante");
			}else{
				printf("\n---------------------------------------------------------\n");
				printf("Debes dar una respuesta valida.");
				
			}
			return 1;
		}
		
	}else{	
		printf("\n------------------------------------------------------------------------------\n");
		printf("\nEl estudiante con codigo %s ya se encuentra registrado en el sistema.",codigo_est);
		printf("\n------------------------------------------------------------------------------\n");
	
	}
	return 0;
}


int estudiante_esta_registrado(struct Estudiante info_estudiante, char  *codigo_a_buscar){

    int bandera = 0;
    
	archivo_datos = fopen(direccion_archivo, "a+b");
	fseek(archivo_datos, 0,SEEK_SET);
	
	if (archivo_datos == NULL){
		
		printf("\nError al leer el archivo!!\n");
		
	}else{
		
		fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos);
	
	    while ( !feof(archivo_datos) ){
		    	
	    	if ( strcmp(info_estudiante.codigo , codigo_a_buscar) == 0 ){
	    		fclose(archivo_datos);
	    		return 1;
	    			
			}
			
			fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos);
		}
		
		fclose(archivo_datos);
	    
	    if (bandera == 0){
	        return 0;
	    }		
	}
}

void agregar_info_periodo_academico(struct Estudiante info_estudiante){

	char codigo_a_buscar[12];
	
    printf("\nIngresa el codigo del estudiante registrado: ");

    scanf("%s",&codigo_a_buscar);

    if ( estudiante_esta_registrado(info_estudiante, codigo_a_buscar) == 1 ){

        agregar_periodo(info_estudiante, codigo_a_buscar);

    }else{

        printf("\nEl estudiante no esta registrado, debes registrarlo.");
    }
}

float sacar_promedio(struct Estudiante info_estudiante){

	int posicion_periodo;
    float sumatoria=0, promedio_estudiante;

	posicion_periodo = 0;
	while ( posicion_periodo < info_estudiante.cant_periodos ){
		sumatoria += info_estudiante.info_u_estudiante[posicion_periodo].promedio_integral;
		posicion_periodo++;
	}
	
    promedio_estudiante = sumatoria / posicion_periodo;
    return promedio_estudiante;		
}

void definir_estado(struct Estudiante info_estudiante, int contador_estudiantes){
	
    int i, j, estudiantes_mostrados = 0, posicion = 0,cantidad_registros;
    
    char fuera[]="FUERA";
    char prueba[]="PRUEBA";
    char normal[]="NORMAL";

    printf("\n\t\tINFORMACION Y ESTADO DE LOS ESTUDIANTES");
    															
    archivo_datos = fopen(direccion_archivo,"r+b");
    
    if (archivo_datos == NULL){

		printf("\nError al leer el archivo\n");
    	
	}else{
		
		fseek(archivo_datos,0,SEEK_END);
		
		cantidad_registros = ftell(archivo_datos) / sizeof(info_estudiante); //Obtengo la cantidad exacta de registros
			    
	    while( posicion < cantidad_registros ){
	    	
			fseek(archivo_datos, posicion * sizeof(info_estudiante), SEEK_SET);  //Me ubico en la posicion correspondiente
		    fread(&info_estudiante, sizeof(info_estudiante), 1 , archivo_datos); //Leo en esa posicion
		     
	    	printf("\n--------------------------------------\n");
	    	printf("\nEstudiante: %s", info_estudiante.nombre);
	    	
		    if (info_estudiante.cant_periodos > 0){ 
		    	
		    	info_estudiante.promedio_general = sacar_promedio(info_estudiante);
		    	
		    	if ( info_estudiante.promedio_general < 2.5 ){
		    		
		    		strcpy(info_estudiante.estado, fuera);

		
		        }else if ( info_estudiante.promedio_general >= 2.5 && info_estudiante.promedio_general <= 2.9 ){

		    		strcpy(info_estudiante.estado, prueba);
		
		        }else if (info_estudiante.promedio_general >= 3.0){
		        	
		    		strcpy(info_estudiante.estado, normal);
		
		        }				
				
				//Retrocedo el puntero
				fseek(archivo_datos, posicion * sizeof(info_estudiante), SEEK_SET); //Como el fread aumenta una posicion, me regreso a la posicion en la que necesito escribir el estado
				fwrite(&info_estudiante, sizeof(info_estudiante) , 1 , archivo_datos);
				
				mostrar_info_prom_integral(info_estudiante, info_estudiante.cant_periodos);
		        
			}else{
				printf("\n\tEl estudiante no tiene periodos academicos registrados");
			}
	
	    	posicion++;  //Aumento la posicion
	    	printf("\n--------------------------------------\n");
		}
		fclose(archivo_datos);
			
	}
}

void mostrar_info_prom_integral(struct Estudiante info_estudiante, int cantidad_periodos_estudiante){
	
	int j = 0;
	
	printf("\n\tNotas:\n");
	
    for(j ; j < cantidad_periodos_estudiante; j++){
    	printf("\t\tPromedio integral %d: %2f \n", j+1 , info_estudiante.info_u_estudiante[j].promedio_integral );
	}
	
	printf("\tPromedio general: %2f\n",info_estudiante.promedio_general);
    
    printf("\tEstado: %s",info_estudiante.estado);
	
}


void mostrar_info_academica_estudiante(struct Estudiante info_estudiante, int cant_periodos_est){
	
	int j = 0;
	
	for(j = 0; j < cant_periodos_est; j++){
		
		printf("\n\t\tPeriodo: %s\n", info_estudiante.info_u_estudiante[j].periodo);
		printf("\t\t\tSemestre: %d\n",info_estudiante.info_u_estudiante[j].semestre);
		printf("\t\t\tPromedio integral: %2f\n",info_estudiante.info_u_estudiante[j].promedio_integral);
		printf("\t\t\tCantidad de materias cursadas: %d",info_estudiante.info_u_estudiante[j].materias_cursadas);	
	}
	
	printf("\n\tEstado %s",info_estudiante.estado);
    printf("\n----------------------------------------------------------------------------\n");
	
}

void mostrar_info_estudiantes_estado_fuera(struct Estudiante info_estudiante, int contador_estudiantes){
	
	int bandera = 0;
	
    printf("----------------------------------------------------------------------------\n");
	printf("\t\tINFORMACION DE ESTUDIANTES EN ESTADO FUERA");
    printf("\n----------------------------------------------------------------------------\n");

	archivo_datos = fopen(direccion_archivo, "rb");
	
	if (archivo_datos == NULL){
		
		printf("\nError al leer el archivo.\n");
		
	}else{
		
		fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos );	
		
		while(!feof(archivo_datos)){
			
			if ( strcmp( info_estudiante.estado, "FUERA" ) == 0){
				
				bandera = 1; //Hay por lo menos un estudiante en estado fuera
				printf("\n\tNombre: %s", info_estudiante.nombre);
				printf("\n\tCodigo: %s", info_estudiante.codigo);
				printf("\n\tDireccion: %s", info_estudiante.direccion);
				printf("\n\tTelefono: %s", info_estudiante.telefono);
				
				mostrar_info_academica_estudiante(info_estudiante, info_estudiante.cant_periodos);
			}
			
			fread(&info_estudiante, sizeof(info_estudiante), 1, archivo_datos );	

			
		}
		
		fclose(archivo_datos);
		
		if (bandera == 0){
			printf("\n-----------------------------------\n");
			printf("No hay estudiantes en estado FUERA");
			printf("\n-----------------------------------");
	
		}	
	}	
}

void mostrar_estudiantes(int contador_estudiantes){
	
	int estudiantes_mostrados = 0;
	archivo_datos = fopen(direccion_archivo, "rb");
	
	if (archivo_datos == NULL){
		
		printf("\nError al leer archivo\n");
		
	}else{
		
		struct Estudiante estudiante;
		
		fseek(archivo_datos, 0, SEEK_SET);
		
		fread(&estudiante, sizeof(estudiante), 1, archivo_datos);
		
		printf("\n-------------------------------------------------\n");
		printf("INFORMACION DE TODOS LOS ESTUDIANTES REGISTRADOS\n");
		printf("-------------------------------------------------\n\n");
				
		while(!feof(archivo_datos)){
			
			printf("Informacion personal: ");
			printf("\n\t\tNombre: %s", estudiante.nombre);
			printf("\n\t\tCodigo: %s", estudiante.codigo);
			printf("\n\t\tDireccion: %s", estudiante.direccion);
			printf("\n\t\tTelefono: %s", estudiante.telefono);
			printf("\n\nInformacion academica: ");

			//Informacion de los periodos
			
			if ( estudiante.cant_periodos > 0 ){  
				
				printf("\n\t\tCantidad de periodos registrados: %d", estudiante.cant_periodos);	
				printf("\n\t\tPromedio general: %f", estudiante.promedio_general);	
				printf("\n\t\tEstado: %s", estudiante.estado);
				
				int contador_periodos = 0;
				while( contador_periodos < estudiante.cant_periodos ){
					printf("\n\t\t----------");
					printf("\n\t\tSemestre: %d", estudiante.info_u_estudiante[contador_periodos].semestre);
					printf("\n\t\t\tPeriodo: %s", estudiante.info_u_estudiante[contador_periodos].periodo);
					printf("\n\t\t\tPromedio integral: %f", estudiante.info_u_estudiante[contador_periodos].promedio_integral);
					printf("\n\t\t\tMaterias cursadas: %d", estudiante.info_u_estudiante[contador_periodos].materias_cursadas);
					contador_periodos++;
				}
				
				printf("\n\t\t----------\n");
				
			}else{
				printf("\n\t\tEl estudiante no tiene periodos academicos registrados\n");
				printf("\t\t----------\n");
			}
			
			estudiantes_mostrados++;
	    	if (  estudiantes_mostrados == contador_estudiantes){  //Si ya se han mostrado todos los estudiantes registrados
	    		break;
			}
			
			fread(&estudiante, sizeof(estudiante), 1, archivo_datos);

		}
		
		fclose(archivo_datos);	
	}
}

int main(){
		
	struct Estudiante info_estudiante;
    int opcion_selec, contador_estudiantes = 0, archivo_esta_vacio=1;
    
    info_estudiante.asignar_posiciones_periodo = 0;
    info_estudiante.cant_periodos = 0;
    
    archivo_contador_estudiantes = fopen( direccion_archivo_contador, "a+" );   //Abrir el archivo contador de estudiantes para tomar la cantidad de estudiantes antiguos
        
    if (archivo_contador_estudiantes == NULL){
    	
    	printf("\nError al leer el archivo que contiene la cantidad de estudiantes antiguos\n");
    	
	}else{

		fseek(archivo_contador_estudiantes, 0, SEEK_SET);
		fscanf(archivo_contador_estudiantes, "%d", &contador_estudiantes);
   
	    if ( contador_estudiantes == NULL  ){ //Si el fichero est� vacio(El cursor est� en la posici�n 0)
	    	//El archivo esta vacio
	    	fprintf(archivo_contador_estudiantes, "%d", 0);	
		}else{
			//El archivo no esta vacio
			fseek(archivo_contador_estudiantes, 0, SEEK_SET); // Posiciono el cursor en la primera posicion  
			fscanf(archivo_contador_estudiantes, "%d", &contador_estudiantes);  //Tomo la cantidad de estudiantes totales en contador_estudiantes
		}
		
		fclose(archivo_contador_estudiantes);
	    do{
	    	mostrar_menu_principal();
			opcion_selec = leer_opcion();
			
	        switch (opcion_selec){
	        case 1:
	        	system("cls");
		        if ( ingresar_estudiante(info_estudiante) == 1 ){ //Si se ingres� el estudiante
	            		            	
	            	archivo_contador_estudiantes = fopen( direccion_archivo_contador, "w+" );   //Abrir el archivo contador de estudiantes para tomar la cantidad de estudiantes antiguos
					
					fseek(archivo_contador_estudiantes, 0, SEEK_SET);  //Posiciono el cursor al inicio del archivo
	            	fscanf( archivo_contador_estudiantes, "%d" , &contador_estudiantes ); //Leo la cantidad de estudiantes antiguos
	            			
	            	fprintf(archivo_contador_estudiantes, "%d", contador_estudiantes + 1);	//Aumento la cantidad de estudiantes totales	            		

					fseek(archivo_contador_estudiantes, 0, SEEK_SET);
					fscanf(archivo_contador_estudiantes, "%d" , &contador_estudiantes);
									
					fclose(archivo_contador_estudiantes);
				} 
				break;
	        case 2:
	        	system("cls");
	        	archivo_contador_estudiantes = fopen( direccion_archivo_contador, "r" ); 
	        	if (archivo_contador_estudiantes == NULL){
	        		printf("\nError al leer el archivo!!!\n");
				}else{	
		        	if (contador_estudiantes > 0){
		        		agregar_info_periodo_academico(info_estudiante);  //Agrega informacion de periodo academdico a un estudiante registrado
					}else{
						printf("\n------------------------------------------\n");
						printf("\nDebes ingresar por lo menos un estudiante.\n");
					}			
				}
				fclose(archivo_contador_estudiantes);
	            break; 
	        case 3:
	        	system("cls");
	        	if( contador_estudiantes > 0 ){
	        		definir_estado(info_estudiante, contador_estudiantes);
				}else{
					printf("\n------------------------------------------\n");
					printf("\nDebes ingresar por lo menos un estudiante.\n");
				}
				break;
			case 4:
				system("cls");
				if (contador_estudiantes > 0){
					mostrar_info_estudiantes_estado_fuera(info_estudiante,contador_estudiantes);
				}else{
					printf("\n------------------------------------------\n");
					printf("\nDebes ingresar por lo menos un estudiante.\n");
				}
				break;
			case 5:
				system("cls");
				if (contador_estudiantes > 0){
					mostrar_estudiantes(contador_estudiantes);
				}else{
					printf("\n------------------------------------------\n");
					printf("\nDebes ingresar por lo menos un estudiante.\n");
				}
				break;
			case 6: //Opcion para ir mirando toda la informacion agregada de los estudiantes
				system("cls");
				printf("\n-------------------------------------------------\n");
				printf("SALIENDO DEL SISTEMA....");
				printf("\n-------------------------------------------------\n");
				break;
	        default:
				printf("\n-------------------------------------------------\n");
				printf("Debes ingresar una opcion valida");
				printf("\n-------------------------------------------------\n");
	            break;
	        }
		}while(opcion_selec != 6);
	}
    return 0;
}
