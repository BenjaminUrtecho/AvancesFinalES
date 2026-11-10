/* Nombre de programa: Mascota Virtual
Proposito: Entretener al usuario con un pequeño juego de tener una mascota virtual
Autor: Benjamin Urtecho Flota
V1.0
28/10/2026
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100
#define min 0
FILE *fd;
//estructura de la mascota
struct stats{
	char nombre[20];
	int energia;
	int hambre;
	int salud;
	int diversion;
};
//prototipos de funciones
void crear(struct stats *m);
void cargar(struct stats *m);
void menu(struct stats *m);
void guardar(struct stats *m);
void menuinicial();
void limites(struct stats *m);

int main(){ //funcion principal donde ocurren lo que pasa al inicio y al final solo sale el bucle del menu
	int opc;
	struct stats mascota;
	menuinicial();
	scanf("%d", &opc);
	switch(opc){
		case 1:
			crear(&mascota);
			break;
		case 2:
			cargar(&mascota);
			break;
		default:
			printf("Opcion no valida, cerrando...");
			return 0;
	}
	menu(&mascota);
	return 0;
}

void menuinicial(){ //el menu de inicio
	printf("====================================================\n");
    printf("    |  |  (\"La Mascotita\")   \n");
    printf("====================================================\n");
    printf("    |\n");
    printf("   /\\_/\\\n");
    printf("  ( owo )  < \"Hola, me adoptaras?\"\n\n");
    printf("====================================================\n");
    printf("  [1] Crear Nueva Partida (Adoptar Mascota)\n");
    printf("  [2] Cargar Partida Existente (Decir \"Lo siento ya tengo mascota\")\n");
    printf("====================================================\n");
    printf("Selecciona una opcion: ");
}

void crear(struct stats *m){
	printf("\n--- ADOPTAR MASCOTA ---\n");
    printf("Ingresa el nombre de tu mascota: ");
    scanf("%s", m->nombre);
    m->diversion=50;
    m->energia=50;
    m->hambre=50;
    m->salud=50;
    //guardar datos nuevos
    fd=fopen("mascota.txt", "w");
    if(fd==NULL){
    	printf("Error al crear el archivo");
    	return;
	}
	fprintf(fd, "%s %d %d %d %d\n", m->nombre, m->diversion, m->energia, m->hambre, m->salud);
	fclose(fd);
	printf("Ahora %s es tu nueva mascota!, Guardando...\n", m->nombre);
}
void cargar(struct stats *m){
	fd=fopen("mascota.txt", "r");
	if (fd==NULL){
		printf("No hay archivo aun, creando uno nuevo...\n");
		crear(m);
		return;
	}
	fscanf(fd, "%s %d %d %d %d", m->nombre, &m->diversion, &m->energia, &m->hambre, &m->salud);
	fclose(fd);
	limites(m);
	printf("Partida cargada, ahora %s esta contigo de nuevo\n\n", m->nombre);
}

void menu(struct stats *m) {
    int opc;
    int cerrar;
    
    do {
        limites(m);
        printf("==================================================\n");
        printf("    |  |  Tu mascota                              \n");
        printf("==================================================\n");
        printf("Nombre: %s\n\n", m->nombre);
        
        printf(" /\\_/\\\n");
        
        // Dialogos que cambian dependiendo las stats
        if(m->hambre<30) {
            printf("( owo )  < \"Tengo hambre!!!!!\"\n\n");
        }else if(m->energia<30) {
            printf("( owo )  < \"Tengo mucho sueño...\"\n\n");
        }else if(m->diversion<30) {
            printf("( owo )  < \"Quiero jugar! Me aburroo...\"\n\n");
        }else {
            printf("( owo )  < \"Me siento muy bien!\"\n\n");
        }
        
        printf("[Hambre]    : %d\n", m->hambre); //aun me falta ponerle las barras de progreso
        printf("[Sueno]     : %d\n", m->energia);
        printf("[Diversion] : %d\n", m->diversion);
        printf("[Salud]     : %d\n", m->salud);
        printf("==================================================\n");
        
        printf("1. Alimentar\n");
        printf("2. Jugar\n");
        printf("3. Dormir\n");
        printf("4. Ir a la veterinaria\n");
        printf("5. Guardar\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opc);;
        
        switch(opc) {
            case 1:
            	if(m->hambre>=100) {
                    printf("\n>>> %s ya está lleno y rechaza la comida.\n", m->nombre);
                    break; // Cancelar si esta lleno
                }
                m->hambre=m->hambre+20;
                m->energia=m->energia-5;
                m->diversion=m->diversion-5;
                printf("\n>>> Has alimentado a %s. Ñam Ñam\n", m->nombre);
                break;
                
            case 2: // La mascota descansa y bajan otras
                if(m->energia>=100) {
                    printf("\n>>> %s ya esta con energias y listo para todo.\n", m->nombre);
                    break;
				} // Cancelar si ya esta al full de descanso
                m->energia=m->energia+25;
                m->hambre=m->hambre-10;
                m->diversion=m->diversion-5;
                printf("\n>>> %s tomo una siesta y recupero energias.\n", m->nombre);
                break;
                
            case 3: // Juegar con la mawscota y otras bajan
                if(m->diversion>=100) {
                    printf("\n>>> %s ya esta entretenido y no quiere jugar (se va a aburrir de repetir lo mismo :c).\n", m->nombre);
                    break;
				} // Cancelar si ya esta al full de diversion
                m->diversion=m->diversion+25;
                m->energia=m->energia-10;
                m->hambre=m->hambre-10;
                printf("\n>>> Jugaste con %s\n", m->nombre);
                break;
                
            case 4: // Curar a la mascota y otras bajan
                if(m->salud>=100) {
                    printf("\n>>> %s ya esta muy bien no necesita ir al veterinario.\n", m->nombre);
                    break;
				} // Cancelar si ya esta al full de salud
                m->salud=m->salud+25;
                m->diversion=m->diversion-15;
                printf("\n>>> %s fue revisado por el veterinario. Ahora esta mejor\n", m->nombre);
                break;
                
            case 5: // Guardar partida y preguntar si guardar al salir
                guardar(m);
                printf("¿Deses cerrar la aplicacion\n?");
                printf("[1] SI\n");
                printf("[2] NO\n");
                scanf(" %d",&cerrar);
                if(cerrar==1){
                    printf("Saliendo del juego... Adios!\n");
                    return;
                }else if(cerrar==2){
                	printf("Continuando con el juego...\n");
				}else{
					printf("Opcion invalida, continuando...");
					cerrar=1;
				}
		}
		limites(m);
    }while(cerrar!=1);
}

void guardar(struct stats *m) { //funcion de guardado
    limites(m);
    
    fd = fopen("mascota.txt", "w");
    if(fd == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fprintf(fd, "%s %d %d %d %d\n", m->nombre, m->diversion, m->energia, m->hambre, m->salud);
    fclose(fd);
    printf("\n[Partida guardada con exito]\n");
}

void limites(struct stats *m){ //funcion para limitar las estadisticas a donde deben estar
    if(m->hambre>max){
    	m->hambre=max;
	}
    if(m->hambre<min){
    	m->hambre=min;
	}
    if(m->energia>max){
    	m->energia=max;
	}
    if(m->energia<min){
    	m->energia=min;
	}
    if(m->diversion>max){
    	m->diversion=max;
	}
    if(m->diversion<min){
    	m->diversion=min;
	}
    if(m->salud>max){
    	m->salud=max;
	}
    if(m->salud<min){
    	m->salud=min;
	}
}
/*por hacer:
-las mascota PERECE si sus stats son bajas
-barras de progreso en el menu basado en las estadisticas
-mejorar la impresion de la mascota y textos
-corregir errores de impresion
-encontrar bugs y solucionarlos
-frase si la mascota tiene stats muy altas (perfeccion)
-balancear juego
*/
                






