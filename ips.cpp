#include<stdio.h>
#include<conio.h>
#include<cstdlib>
#include<synchapi.h>
#include<iostream>
#include<fstream>
using namespace std;
struct jugador{
	string IP;
	string nombre;
	jugador *siguiente;
};
int len(char *cadena){
	return sizeof(cadena);
}
int menu(){
	printf("Seleccione una opcion:\n1.Buscar por nombre\n2.Buscar por IP\n3.Agregar\n4.Salir\n");
	int opcion=0;
	bool error=true;
	while(error){
		error=false;
		try{
			scanf("%d",&opcion);
		}	
		catch(int numero){
			error=true;
		}
		if (opcion<=0 or opcion>=5){
			error=true;
		}
	}
	return opcion;
}
bool Comp(string a, string b){
	if(a.size()<b.size()){
		return false;
	}
	for(int x=0;x<b.size();x++){
		if (a[x]!=b[x]){
			return false;
		}
	}
	return true;
}
	
jugador *Lista(){
	string texto;
	bool lectura=true;
	jugador *primero=NULL;
	jugador *nuevo=NULL;
	jugador *anterior=NULL;
	ifstream f("pl.txt");
	nuevo=new jugador;
	while(getline(f,texto)){
		if (primero==NULL){
			primero=nuevo;
		}
		if (lectura){
			nuevo->nombre=texto;
			lectura=false;
		}else{
			nuevo->IP=texto;
			lectura=true;
			anterior=nuevo;
			nuevo=new jugador;
			anterior->siguiente=nuevo;
		}
	}
	if(anterior!=NULL){
		anterior->siguiente=NULL;
	}
	return primero;
}
jugador *buscar(jugador *primero,int tipo, string valor){
	jugador *aux=primero;
	jugador *primero2=NULL;
	jugador *anterior=NULL;
	while(aux!=NULL){
		if(tipo==1){
			if(Comp(aux->nombre,valor)){
				if (primero2==NULL){
					primero2=new jugador;
					primero2->nombre=aux->nombre;
					primero2->IP=aux->IP;
					primero2->siguiente=NULL;
					anterior=primero2;
				}else{
					anterior->siguiente=new jugador;
					anterior->siguiente->nombre=aux->nombre;
					anterior->siguiente->IP=aux->IP;
					anterior->siguiente->siguiente=NULL;
					anterior=anterior->siguiente;
				}
			}
		}else{
			if(Comp(aux->IP,valor)){
				if (primero2==NULL){
						primero2=new jugador;
						primero2->nombre=aux->nombre;
						primero2->IP=aux->IP;
						primero2->siguiente=NULL;
						anterior=primero2;
				}else{
						anterior->siguiente=new jugador;
						anterior->siguiente->nombre=aux->nombre;
						anterior->siguiente->IP=aux->IP;
						anterior->siguiente->siguiente=NULL;
						anterior=anterior->siguiente;
				}
			}
		}
		aux=aux->siguiente;
		} 
	return primero2;
	}
void borrarLista(jugador *primero){
	jugador *aux=primero;
	while(aux!=NULL){
		jugador *aux2=aux;
		aux=aux->siguiente;
		delete aux2;
	}
}
void agregar(jugador *&primero, string nombre, string IP){
	jugador *aux=primero;
	if (aux!=NULL){
		while(aux->siguiente!=NULL){
		aux=aux->siguiente;
		}
		aux->siguiente=new jugador;
		aux->siguiente->nombre=nombre;
		aux->siguiente->IP=IP;
		aux->siguiente->siguiente=NULL;
		ofstream f("pl.txt",ios::app);
		f<<"\n"<<nombre<<"\n"<<IP;
		f.close();
	}else{
		aux=new jugador;
		aux->nombre=nombre;
		aux->IP=IP;
		aux->siguiente=NULL;
		ofstream f("pl.txt",ios::app);
		f<<nombre<<"\n"<<IP;
		f.close();
}
	}
	
void imprimirInfo(jugador *primero){
	jugador *aux=primero;
	while(aux!=NULL){
		cout<<"\nNombre: "<<aux->nombre<<"\n"<<"IP: "<<aux->IP<<"\n\n";
		aux=aux->siguiente;
	}
}
main(){
	system("cls");
	jugador *lista=Lista();
	int eleccion=0;
	while(eleccion!=4){
		eleccion=menu();
		if (eleccion==1){
			system("cls");
			char busqueda[11];
			printf("Digite el nombre del jugador a buscar (sin espacios):\n");
			scanf("%s^[\n]",busqueda);
			printf("Coincidencias:\n");
			jugador *nLista=buscar(lista,1,busqueda);
			imprimirInfo(nLista);
			system("Pause");
			borrarLista(nLista);
			return main();
		}else if(eleccion==2){
			system("cls");
			char busqueda[20];
			printf("Digite el IP del jugador a buscar (sin espacios):\n");
			scanf("%s^[\n]",busqueda);
			printf("Coincidencias:\n");
			jugador *nLista=buscar(lista,2,busqueda);
			imprimirInfo(nLista);
			system("Pause");
			borrarLista(nLista);
			return main();
		}else if(eleccion==3){
			system("cls");
			char nombre[11];
			char IP[20];
			printf("Nombre (sin espacios):  ");
			scanf("%s^[\n]",nombre);
			printf("IP (sin espacios):  ");
			scanf("%s^[\n]",IP);
			agregar(lista,nombre,IP);
			return main();
		}
	}
	return 0;
}
