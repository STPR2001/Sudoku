#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define muy_facil 70
#define facil 60
#define normal 50
#define dificil 35
#define muy_dificil 30
#define extremo 25

using namespace std;

//PROTOTIPO FUNCIONES

// 1era parte
bool sesion = false;
void inicializar_sudoku (int s[9][9]);
void imprimir_sudoku (int s [9][9]);
void generar_sudoku_valido ( int s [9][9], int cant_elem);
void generar_sudoku_jugable ( int s [9][9], int cant_elem, int copyS[9][9], int copyCopyS[9][9]);
bool sudoku_valido (int s[9][9]);
bool sudoku_resuelto (int s[9][9]);
void crear_candidatos (int s[9][9], int fila, int columna, bool candidatos[9]);
bool es_candidato (int s [9][9], int num, int fila, int columna);
void exclusivo(int s[9][9],int f,int c,int num);

// 2da parte
void iniciarApp();
void menu();
void registro_usuarios();
void listar_usuarios ();
void iniciar_sesion(bool sesion);
void subMenu1();
void crear_tablero(int s[9][9],int dificultad);
void iniciar_juego(int s[9][9]);
void jugando (int fila,int columna, int numero,int s[9][9],int contElementosPlayer);
void subMenuRendicion(int error);
void ver_informacion();
void ranking();
void creditos();
void candidato_unico (int s [9][9], int num, int fila, int columna);

//ESTRUCTRAS
struct usuarios{ 
	char nick[20], nombre[20]={'n','o','n','e','n','o','n',
		'e','n','o','n','e','n','o','n','e','n','o','n','\0'};
	int puntos;
	bool sesion = false;
}pag[100];

int main(int argc, char *argv[]) {
	
	iniciarApp();
	
	return 0;
}	
// NO SE USAN 
void candidato_unico (int s [9][9], int num, int fila, int columna){
	
	int i, j, candidatos[9];
	int numeros[9]={0};
	srand(time(NULL));
	int numeroRandom,c,f,y,l,a=0,randoms=0,region,f2=0,c2=0;
	int arr[9]={0},llenando=1,cont=-1;
	bool romper = false;
	
	//NUM ES CANDIDATO
	if(es_candidato(s, 5,5,5)==true){
		
		//UNICO
		
		f=fila-1;
		c=columna-1;
		
		j = 0;
		i = 0;
		f = 0;
		c = 0;
		for(y=0; y<9; y++){
			f=fila-1;
			c=columna-1;
			//	WHILE QUE LLENA UN ARRAY CON NUMEROS DEL 1 al 10, 
			//		pero en orden aleatorio.
			llenando = 1;
			/*SETEA EN CERO EL ARRAY*/
			for(a=0;a<9;a++){
				arr[a] = 0;
			}
			/*GENERA UN ARRAY CON LOS 9 POSIBLES RANDOMS*/
			while(llenando == 1){
				numeroRandom = rand()%9+1;
				for(a=0;a<9;a++){
					if(arr[a] == numeroRandom){
						a = 11;
					}
					if(a==8){
						cont++;
						arr[cont] = numeroRandom;
					}
				}
				if(cont==8){
					cont = -1;
					llenando = 0;
				}
			}
			
			/*ESTABLECE LA REGION DE LA CASILLA*/
			if(c<3 && f<3){
				region = 1;
			}
			if(c>2 && c<6 && f<3){
				region = 2;
			}
			if(c>5 && f<3){
				region = 3;
			}
			if(c<3 && f>2 && f<6){
				region = 4;
			}
			if(c<6 && c>2 && f<6 && f>2){
				region = 5;
			}
			if(c>5 && f<6 && f>2){
				region = 6;
			}
			if(c<3 && f>5){
				region = 7;
			}
			if(c>2 && c<6 && f>5){
				region = 8;
			}
			if(c>5 && f>5){
				region = 9;
			}
			/* PROBAMOS CADA NUMERO RANDOM EN LA CASILLA*/
			for(randoms=0;randoms<9;randoms++){
				j = 0;
				i = f;
				romper = false;
				/*RECORRE CADA CASILLA EN LA FILA*/
				while(s[j][i] != arr[randoms] && romper == false){
					if(j == 9-1){
						j = c;
						i = 0;
						/* RECORRE CADA CASILLA EN LA COLUMNA*/
						while(s[j][i] != arr[randoms]){
							if(i == 9-1){
								switch(region){
								case 1:
								{
									f2 = 0;
									while(f2<3){
										c2 = 0;
										while(c2<3){
											if(s[c2][f2]==arr[randoms]){
												c2 = 3;
												f2 = 3;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==3){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 2:
								{
									f2 = 0;
									while(f2<3){
										c2 = 3;
										while(c2<6){
											if(s[c2][f2]==arr[randoms]){
												c2 = 6;
												f2 = 3;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==3){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 3:
								{
									f2 = 0;
									while(f2<3){
										c2 = 6;
										while(c2<9){
											if(s[c2][f2]==arr[randoms]){
												c2 = 9;
												f2 = 3;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==3){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 4:
								{
									f2 = 3;
									while(f2<6){
										c2 = 0;
										while(c2<3){
											if(s[c2][f2]==arr[randoms]){
												c2 = 3;
												f2 = 6;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==6){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 5:
								{
									f2 = 3;
									while(f2<6){
										c2 = 3;
										while(c2<6){
											if(s[c2][f2]==arr[randoms]){
												c2 = 6;
												f2 = 6;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==6){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 6:
								{
									f2 = 3;
									while(f2<6){
										c2 = 6;
										while(c2<9){
											if(s[c2][f2]==arr[randoms]){
												c2 = 9;
												f2 = 6;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==6){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 7:
								{
									f2 = 6;
									while(f2<9){
										c2 = 0;
										while(c2<3){
											if(s[c2][f2]==arr[randoms]){
												c2 = 3;
												f2 = 9;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==9){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 8:
								{
									f2 = 6;
									while(f2<9){
										c2 = 3;
										while(c2<6){
											if(s[c2][f2]==arr[randoms]){
												c2 = 6;
												f2 = 9;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==9){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								case 9:
								{
									f2 = 6;
									while(f2<9){
										c2 = 6;
										while(c2<9){
											if(s[c2][f2]==arr[randoms]){
												c2 = 9;
												f2 = 9;
												romper = true;
												break;
											}
											c2++;
										}
										f2++;
										if(f2==9){
											i = f;
											numeros[y]=arr[randoms];
											y++;
										}
									}
									break;
								}
								}
								
								break;
							}
							i++;
						}
						break;
					}
					j++;
				}
			}
		}
	}
	int arrayTemporal[9]={0}, contt=0;
	for(l=0;l<9;l++){
		if(numeros[l]!=0){
			for(l=0;l<9;l++)
			{
				int var = numeros[l];
				if(arrayTemporal[var-1]==0){
					arrayTemporal[var-1]=1;
					contt++;
				}
			}
			l = 10;
		}
	}
	int conttt=0;
	for(i=0;i<9;i++){
		if(numeros[i] == num && contt == 1){
			cout<<num<<" es candidato unico para la celda ingresada";
			conttt++;
			i=10;
		}
	}
	if(conttt == 0)
		cout<<"El numero ingresado NO es candidato unico";
	
	cout<<endl;
	cout<<endl;
	
}
	void exclusivo(int s[9][9],int f,int c,int num){
		int i, k, copia[9][9],region;
		bool candidatos[9]={0},exclusivoBool[3];
		
		if(es_candidato(s,num,f,c) == true){
			
			// FILA
			for(i=0;i<9;i++){
				if(es_candidato(s,num,f,i) && i != c){
					cout<<"No es exclusivo"<<endl;
					break;
				}
			}
			if(i==9){
				exclusivoBool[0] = true;
			}
			// COLUMNA
			for(i=0;i<9;i++){
				if(es_candidato(s,num,i,c) && i != f){
					cout<<"No es exclusivo"<<endl;
					break;
				}
			}
			if(i==9){
				exclusivoBool[1] = true;
			}
			// REGION
			{
				if(c<3 && f<3){
					region = 1;
				}
				if(c>2 && c<6 && f<3){
					region = 2;
				}
				if(c>5 && f<3){
					region = 3;
				}
				if(c<3 && f>2 && f<6){
					region = 4;
				}
				if(c<6 && c>2 && f<6 && f>2){
					region = 5;
				}
				if(c>5 && f<6 && f>2){
					region = 6;
				}
				if(c<3 && f>5){
					region = 7;
				}
				if(c>2 && c<6 && f>5){
					region = 8;
				}
				if(c>5 && f>5){
					region = 9;
				}	
			}
			
			int f2,c2;
			switch(region){
			case 1:
			{
				f2 = 0;
				while(f2<3){
					c2 = 0;
					while(c2<3){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==3){
						cout<<"Es exclusivo"<<endl;
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 2:
			{
				f2 = 0;
				while(f2<3){
					c2 = 3;
					while(c2<6){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==3){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 3:
			{
				f2 = 0;
				while(f2<3){
					c2 = 6;
					while(c2<9){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==3){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 4:
			{
				f2 = 3;
				while(f2<6){
					c2 = 0;
					while(c2<3){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==6){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 5:
			{
				f2 = 3;
				while(f2<6){
					c2 = 3;
					while(c2<6){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==6){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 6:
			{
				f2 = 3;
				while(f2<6){
					c2 = 6;
					while(c2<9){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==6){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 7:
			{
				f2 = 6;
				while(f2<9){
					c2 = 0;
					while(c2<3){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==9){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 8:
			{
				f2 = 6;
				while(f2<9){
					c2 = 3;
					while(c2<6){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==9){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			case 9:
			{
				f2 = 6;
				while(f2<9){
					c2 = 6;
					while(c2<9){
						if(es_candidato(s,num,f2,c2) && c2 != c && f2 != f){
							cout<<"No es exclusivo"<<endl;
						}
						c2++;
					}
					f2++;
					if(f2==9){
						exclusivoBool[2] = true;
					}
				}
				break;
			}
			}
			// SI ALGUNO DE LOS 3 SE CUMPLE, ES EXCLUSIVO
			for(i=0;i<3;i++){
				if(exclusivoBool[i]){
					cout<<"Es exclusivo"<<endl;
					i = 3;
				}
			}
			
		}else{
			cout<<"No es candidato para esa casilla"<<endl;
		}
	}
		// =============
		void generar_sudoku_jugable ( int s [9][9], int cant_elem, int copyS[9][9], int copyCopyS[9][9]){
			srand(time(NULL));
			int numeroRandom,j,c,i,f,a=0,randoms=0,region,f2=0,c2=0,error=0;
			int arr[9]={0},llenando=1,cont=-1;
			bool romper = false, whileError = true;
			j = 0;
			i = 0;
			inicializar_sudoku(s);
			while(whileError){
				error = 0;
				inicializar_sudoku(s);
				// FOR QUE RECORRE FILAS
				f = 0;
				c = 0;
				for(f=0;f<9;f++){
					// FOR QUE RECORRE COLUMNAS
					for(c=0;c<9;c++){
						// WHILE QUE LLENA UN ARRAY CON NUMEROS DEL 1 al 10, 
						// pero en orden aleatorio.
						llenando = 1;
						// SETEA EN CERO EL ARRAY
						for(a=0;a<9;a++){
							arr[a] = 0;
						}
						// GENERA UN ARRAY CON LOS 9 POSIBLES RANDOMS
						while(llenando == 1){
							numeroRandom = rand()%9+1;
							for(a=0;a<9;a++){
								if(arr[a] == numeroRandom){
									a = 11;
								}
								if(a==8){
									cont++;
									arr[cont] = numeroRandom;
								}
							}
							if(cont==8){
								cont = -1;
								llenando = 0;
							}
						}
						// ESTABLECE LA REGION DE LA CASILLA
						if(c<3 && f<3){
							region = 1;
						}
						if(c>2 && c<6 && f<3){
							region = 2;
						}
						if(c>5 && f<3){
							region = 3;
						}
						if(c<3 && f>2 && f<6){
							region = 4;
						}
						if(c<6 && c>2 && f<6 && f>2){
							region = 5;
						}
						if(c>5 && f<6 && f>2){
							region = 6;
						}
						if(c<3 && f>5){
							region = 7;
						}
						if(c>2 && c<6 && f>5){
							region = 8;
						}
						if(c>5 && f>5){
							region = 9;
						}
						// PROBAMOS CADA NUMERO RANDOM EN LA CASILLA
						for(randoms=0;randoms<9;randoms++){
							j = 0;
							i = f;
							romper = false;
							// RECORRE CADA CASILLA EN LA FILA
							while(s[j][i] != arr[randoms] && romper == false){
								if(j == 9-1){
									j = c;
									i = 0;
									// RECORRE CADA CASILLA EN LA COLUMNA
									while(s[j][i] != arr[randoms]){
										if(i == 9-1){
											switch(region){
											case 1:
											{
												f2 = 0;
												while(f2<3){
													c2 = 0;
													while(c2<3){
														if(s[c2][f2]==arr[randoms]){
															c2 = 3;
															f2 = 3;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==3){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 2:
											{
												f2 = 0;
												while(f2<3){
													c2 = 3;
													while(c2<6){
														if(s[c2][f2]==arr[randoms]){
															c2 = 6;
															f2 = 3;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==3){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 3:
											{
												f2 = 0;
												while(f2<3){
													c2 = 6;
													while(c2<9){
														if(s[c2][f2]==arr[randoms]){
															c2 = 9;
															f2 = 3;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==3){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 4:
											{
												f2 = 3;
												while(f2<6){
													c2 = 0;
													while(c2<3){
														if(s[c2][f2]==arr[randoms]){
															c2 = 3;
															f2 = 6;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==6){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 5:
											{
												f2 = 3;
												while(f2<6){
													c2 = 3;
													while(c2<6){
														if(s[c2][f2]==arr[randoms]){
															c2 = 6;
															f2 = 6;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==6){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 6:
											{
												f2 = 3;
												while(f2<6){
													c2 = 6;
													while(c2<9){
														if(s[c2][f2]==arr[randoms]){
															c2 = 9;
															f2 = 6;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==6){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 7:
											{
												f2 = 6;
												while(f2<9){
													c2 = 0;
													while(c2<3){
														if(s[c2][f2]==arr[randoms]){
															c2 = 3;
															f2 = 9;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==9){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 8:
											{
												f2 = 6;
												while(f2<9){
													c2 = 3;
													while(c2<6){
														if(s[c2][f2]==arr[randoms]){
															c2 = 6;
															f2 = 9;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==9){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											case 9:
											{
												f2 = 6;
												while(f2<9){
													c2 = 6;
													while(c2<9){
														if(s[c2][f2]==arr[randoms]){
															c2 = 9;
															f2 = 9;
															romper = true;
															break;
														}
														c2++;
													}
													f2++;
													if(f2==9){
														i = f;
														s[j][i] = arr[randoms];
														randoms = 11;
													}
												}
												break;
											}
											}
											
											break;
										}
										i++;
									}
									break;
								}
								j++;
							}
						}
						if(randoms==9){
							error++;
						}
					}
				}
				if(error<1){
					
					int i,c,random1,random2,contCeros=0,matrizConCeros[9][9];
					for(i=0;i<9;i++){
						for(c=0;c<9;c++){
							copyS[c][i] = s[c][i];
						}
					}
					while(contCeros<81-cant_elem){
						random1 = rand()%9;
						random2 = rand()%9;
						if(matrizConCeros[random1][random2]!=0){
							copyS[random1][random2] = 0;
							contCeros++;
						}
					}
					for(i=0;i<9;i++){
						for(c=0;c<9;c++){
							copyCopyS[c][i] = copyS[c][i];
						}
					}
					whileError = false;
				}
			}
		}
			void iniciarApp(){
				int s[9][9], opcion, matrizConSolucion[9][9];
				do{
					menu();
					cin>>opcion;
					switch(opcion)
					{
					case 1:
					{
						registro_usuarios();
						break;	
					}
					case 2:
					{
						listar_usuarios();
						break;
					}
					case 3:
					{
						iniciar_sesion(sesion);
						break;
					}
					case 4:
					{
						iniciar_juego(s);
						break;
					}
					case 5:
					{
						ver_informacion();
						break;
					}
					case 6:
					{
						ranking();
						break;
					}
					}
				}while(opcion != 7);
			}
				void ver_informacion(){
					int i;
					for(i=0;i<99;i++){
						if(pag[i].sesion == /* Esto debe ir en true */ true){
							cout<<"=========================="<<endl;
							cout<<"Infomacion del usuario: "<<endl<<endl;
							cout<<"Nick: "<<pag[i].nick<<endl;
							cout<<"Nombre: "<<pag[i].nombre<<endl;
							cout<<"Puntos: "<<pag[i].puntos<<endl;
							cout<<"=========================="<<endl;
							i=100;
						}
					}
					if(i==99){
						cout<<"=========================="<<endl;
						cout<<"Debes iniciar sesion"<<endl;
						cout<<"=========================="<<endl;
					}
				}
					void ranking(){
						// RANKING BUBBLE SORT
						int i,c,cant;
						usuarios aux;
						for(i=0;i<10;i++){
							for(c=0;c<10;c++){
								if(pag[c].puntos < pag[c+1].puntos){
									aux = pag[c];
									pag[c] = pag[c+1];
									pag[c+1] = aux;
								}
							}
						}
						for(i=0;i<99;i++){
							if(strcmp(pag[i].nombre,pag[99].nombre)==0){
								cant = i;
								i = 100;
							}
						}
						cout<<"==========================="<<endl;
						cout<<"	RANKING"<<endl;
						cout<<"==========================="<<endl;
						creditos();
						for(i=0;i<cant;i++){
							cout<<"--------------------"<<endl;
							cout<<"  "<<pag[i].nick<<endl;
							cout<<"  "<<pag[i].nombre<<endl;
							cout<<"  "<<pag[i].puntos<<endl;
							cout<<"--------------------"<<endl;
						}
						cout<<"==========================="<<endl;
					}
						void iniciar_juego(int s[9][9]){
							inicializar_sudoku(s);
							int i;
							for(i=0;i<99;i++){
								if(pag[i].sesion == /* Esto debe ir en true */ true){
									i=100;
									subMenu1();
								}
							}
							if(i==99){
								cout<<"=========================="<<endl;
								cout<<"Debes iniciar sesion"<<endl;
								cout<<"=========================="<<endl;
							}
						}
							void creditos(){
								cout<<"--------------------"<<endl;
								cout<<"  LuquitasPro"<<endl;
								cout<<"  Lucas"<<endl;
								cout<<"  7000"<<endl;
								cout<<"--------------------"<<endl;
								cout<<"  ElSanti"<<endl;
								cout<<"  Santi"<<endl;
								cout<<"  7000"<<endl;
								cout<<"--------------------"<<endl;
							}
								void crear_tablero(int s[9][9],int dificultad){
									
									int nivelDificultad,fila
										,columna,score,numero,contElementosPlayer = 0,copyS[9][9],copyCopyS[9][9]
											,i,c,error = 1;
										generar_sudoku_jugable(s,dificultad,copyS,copyCopyS);
										bool jugandoWhile = true;
										
										imprimir_sudoku(copyS);
										
										while(jugandoWhile == true){
											char res;
											bool sinRendicion = true;
											int contadorCasillasRestantes = 0;
											
											cout<<"Fila? (Ingresa 11 para salir):"<<endl;
											cin>>fila;
											// SUBMENU DE RENDICION
											if(fila == 11){
												int opcion;
												subMenuRendicion(error);
												cin>>opcion;
												switch(opcion){
												case 1:{
													cout<<"Te rendiste"<<endl;
													cout<<"Deseas ver la solución? (s/n)"<<endl;
													cin>>res;
													if(res == 's' || res == 'S'){
														imprimir_sudoku(s);
													}
													jugandoWhile = false;
													sinRendicion = false;
													break;
												}
												case 2:{
														cout<<"Reseteaste"<<endl;
														imprimir_sudoku(copyCopyS);
														cout<<"Fila? (Ingresa 11 para salir):"<<endl;
														cin>>fila;
														
														break;
													};
												case 3:{
													cout<<"Fila? (Ingresa 11 para salir):"<<endl;
													cin>>fila;
													break;
												};
												}
											}
											
											
											if(sinRendicion == true){
												
												cout<<"Columna?: "<<endl;
												cin>>columna;
												cout<<"Numero?: "<<endl;
												cin>>numero;
												
												jugando(fila,columna,numero,copyS,contadorCasillasRestantes);
												
												for(i=0;i<9;i++){
													for(c=0;c<9;c++){
														if(copyS[c][i] == 0){
															contadorCasillasRestantes++;
														}
														if(c == 8 && i == 8 && contadorCasillasRestantes == 0){
															if(sudoku_resuelto(copyS) == true){
																if(sudoku_valido(copyS) == true){
																	switch(dificultad){
																	case muy_facil:
																		score = 1;
																		break;
																	case facil:
																		score = 2;
																		break;
																	case normal:
																		score = 3;
																		break;
																	case dificil:
																		score = 4;
																		break;
																	case muy_dificil:
																		score = 5;
																		break;
																	case extremo:
																		score = 6;
																		break;
																	}
																	cout<<"==================="<<endl;
																	cout<<"Felicidades crack"<<endl;
																	cout<<"Ganaste "<<score<<" puntos"<<endl;
																	cout<<"==================="<<endl;
																	for(i=0;i<99;i++){
																		if(pag[i].sesion == true){
																			pag[i].puntos += score;
																		}
																	}
																	jugandoWhile = false;
																}else{
																	int opcion;
																	cout<<"==================="<<endl;
																	cout<<"Lo siento, no esta correctamente resuelto"<<endl;
																	cout<<"==================="<<endl;
																	error = 0;
																	subMenuRendicion(error);
																	cin>>opcion;
																	switch(opcion){
																	case 1:{
																		cout<<"==================="<<endl;
																		cout<<"Te rendiste"<<endl;
																		cout<<"Deseas ver la solución? (s/n)"<<endl;
																		cout<<"==================="<<endl;
																		cin>>res;
																		if(res == 's' || res == 'S'){
																			/* IMPRIME CON CEROS AUN */  imprimir_sudoku(s);
																		}
																		jugandoWhile = false;
																		sinRendicion = false;
																		break;
																	}
																	case 2:{
																			// EMPEZAR DE CERO
																			int i,c;
																			imprimir_sudoku(copyCopyS);
																			cout<<"Fila? (Ingresa 11 para salir):"<<endl;
																			cin>>fila;
																			break;
																		};
																	case 3:{
																		cout<<"Fila? (Ingresa 11 para salir):"<<endl;
																		cin>>fila;
																		break;
																	};
																	}
																}
															}else{
																cout<<"Che no terminaste el sudoku"<<endl;
															};
														}
													}
												}
											}
										}
								}
									void registro_usuarios(){
										
										int cant = 0;
										int i;
										
										for(i=0;i<100;i++){
											if(strcmp(pag[i].nick, pag[99].nick) == 0){
												cant = i;
												break;
											}
										}
										int existe=0;
										char nickEnVerificacion[20]={'0'};
										
										fflush(stdin);
										cout<<'\t'<<"Registro de usuarios"<<endl;
										cout<<"-----------------------------"<<endl<<endl;
										cout<<"Ingrese nick "<<endl<<endl;
										gets(nickEnVerificacion);
										fflush(stdin);		
										cout<<endl<<"Ingrese nombre "<<endl<<endl;
										gets(pag[cant].nombre);
										fflush(stdin);
										fflush(stdin);
										{
											for(i=0; i<100; i++)
											{
												if(strcmp(pag[i].nick, nickEnVerificacion)==0){
													cout<<"====================================="<<endl;
													cout<<"El nick ingresado ya existe"<<endl;
													cout<<"====================================="<<endl;
													existe = 1;
													break;
												}
											}
											if(existe == 0){
												strcpy(pag[cant].nick,nickEnVerificacion);
												cout<<"====================================="<<endl;
												cout<<"Usuario registrado correctamente"<<endl;
												cout<<"====================================="<<endl;
											}
											cout<<endl;
										}
									}
										void listar_usuarios (){
											
											int i, j, cant=0;
											usuarios aux;  
											
											for(i=0;i<100;i++){
												if(strcmp(pag[i].nick, pag[99].nick) == 0){
													cant = i;
													break;
												}
											}
											if(cant == 0){
												cout<<'\t'<<"Lista de usuarios"<<endl;
												cout<<"=========================="<<endl;
												cout<<"No hay usuarios listados"<<endl;
												cout<<"=========================="<<endl;
											}else{
												for(i=0; i<cant; i++){
													for(j=0;j<cant-1; j++){
														if(strcmp(pag[j].nick, pag[j+1].nick)>0)
														{
															aux=pag[j];		
															pag[j]=pag[j+1];
															pag[j+1]=aux;
														}
													}
												}
												cout<<'\t'<<"Lista de usuarios"<<endl;
												cout<<"===================="<<endl;
												for(i=0; i<cant; i++){
													cout<<"--------------------"<<endl;
													cout<<"  "<<pag[i].nick<<endl;
													cout<<"  "<<pag[i].nombre<<endl;
													cout<<"  "<<pag[i].puntos<<endl;
													cout<<"--------------------"<<endl;
												}
												cout<<"===================="<<endl;
											}
										}
											void iniciar_sesion(bool sesion){
												
												int i, j, cant=0, existe=0;
												char usuario_ingresado[20];
												
												cout<<"============================="<<endl;
												cout<<'\t'<<"Inicio de sesion"<<endl;
												cout<<"============================="<<endl;
												cout<<"Ingrese su nick "<<endl;
												cin>>usuario_ingresado;
												
												for(i=0;i<100;i++){
													if(strcmp(pag[i].nick, pag[99].nick) == 0){
														cant = i;
														break;
													}
												}
												for(j=0;j<cant;j++)
												{
													if(strcmp(pag[j].nick, usuario_ingresado) ==0){
														// SI HAY USUARIO CON SESION ACTIVA LO BAJA
														for(i=0;i<cant;i++){
															if(pag[i].sesion == true){
																pag[i].sesion = false;
															}
														}
														// ===========================
														pag[j].sesion = true;
														cout<<"=========================="<<endl;
														cout<<"Bienvenido al juego "<<pag[j].nick<<endl;
														cout<<"=========================="<<endl;
														cout<<endl;
														existe = 1;
														break;
													}
												}
												if(existe==0)
													cout<<"El nick ingresado no existe"<<endl;
												cout<<endl;
											}	
												
												void jugando (int fila,int columna, int numero,int copyS[9][9],int contElementosPlayer){
													if(copyS[columna-1][fila-1] != 0){
														cout<<endl;
														cout<<"========================================"<<endl;
														cout<<"No puedes poner un numero en esa casilla"<<endl;
														cout<<"========================================"<<endl;
													}else{
														copyS[columna-1][fila-1] = numero;
														imprimir_sudoku(copyS);
														contElementosPlayer++;
														cout<<contElementosPlayer<<endl;
													}
												}
													void subMenu1(){
														int error = 1;
														int s[9][9];
														int nivelDificultad,fila,columna
															,numero;
														cout<<"Que nivel queres?: "<<endl;
														cout<<"--------------------"<<endl;
														cout<<"1. Muy Fácil"<<endl;
														cout<<"2. Fácil"<<endl;
														cout<<"3. Normal"<<endl;
														cout<<"4. Difícil"<<endl;
														cout<<"5. Muy difícil"<<endl;
														cout<<"6. Extremo"<<endl;
														cin>>nivelDificultad;
														switch(nivelDificultad){
														case 1:{
															crear_tablero(s,muy_facil);
															break;
														}
														case 2:{
																crear_tablero(s,facil);
																break;
															}
														case 3:{
																	crear_tablero(s,normal);
																	break;
																}
														case 4:{
																		crear_tablero(s,dificil);
																		break;
																	}
														case 5:{
																			crear_tablero(s,muy_dificil);
																			break;
																		}
														case 6:{
																				crear_tablero(s,extremo);
																				break;
																			}
														}
													}
														void subMenuRendicion(int error){
															cout<<"Que quieres hacer?"<<endl;
															cout<<"1. Rendirse"<<endl;
															cout<<"2. Empezar de nuevo"<<endl;
															if(error != 0){
																cout<<"3. Continuar"<<endl;
															}
														}
															void menu(){
																cout<<'\t'<<"MENU"<<endl;
																cout<<" 1) Registrar Usuario"<<endl;
																cout<<" 2) Listar Usuarios"<<endl;
																cout<<" 3) Iniciar Sesión"<<endl;
																cout<<" 4) Jugar"<<endl;
																cout<<" 5) Ver información de Usuario"<<endl;
																cout<<" 6) Ver Ranking"<<endl;
																cout<<" 7) Salir"<<endl;
															}
																
																void inicializar_sudoku(int  s[9][9]){
																	int i,j;
																	
																	for(i=0;i<9;i++){
																		for(j=0;j<9;j++){
																			s[j][i] = 0;
																		}
																	}
																}
																	
																	
																	bool sudoku_resuelto (int s[9][9]){
																		int i,c;
																		for(i=0;i<9;i++){
																			for(c=0;c<9;c++){
																				if(s[c][i]==0){
																					return false;
																				}
																			}
																		}
																		if(i==9){
																			return true;
																		}
																		return true;
																	}
																		void imprimir_sudoku (int s[9][9]){
																			int cont=2,cont2=2, i, j,d = 0;
																			cout<<endl<<endl;
																			cout<<'\t'<<"SUDOKU LISTO"<<endl;
																			for(i=0;i<9;i++){
																				cont2++; 
																				if(cont2==9/3){
																					cont2 = 0;
																					for(d=0;d<9-1;d++){
																						cout<<"---";
																					}
																					cout<<endl;
																				}
																				
																				for(j=0;j<9;j++){
																					cont++; 
																					if(cont==9/3){
																						cont = 0;
																						cout<<"| ";
																					}
																					if(s[j][i]==0){
																						cout<<"-"<<" ";
																					}else{
																						cout<<s[j][i]<<" ";
																					}
																					
																				}
																				if(j==9){
																					cout<<"| ";
																				}
																				cout<<endl;
																			}
																			for(d=0;d<9-1;d++){
																				cout<<"---";
																			}
																			cout<<endl;
																		}
																			
																			
																			// ESTA FUNCION NO SE USA (SOLO POR PEDIDO)
																			void generar_sudoku_valido (int s[9][9], int cant_elem){
																				srand(time(NULL));
																				int numeroRandom,j,c,i,f,a=0,randoms=0,region,f2=0,c2=0,error=0;
																				int arr[9]={0},llenando=1,cont=-1;
																				bool romper = false, whileError = true;
																				j = 0;
																				i = 0;
																				inicializar_sudoku(s);
																				while(whileError){
																					error = 0;
																					inicializar_sudoku(s);
																					// FOR QUE RECORRE FILAS
																					f = 0;
																					c = 0;
																					for(f=0;f<9;f++){
																						// FOR QUE RECORRE COLUMNAS
																						for(c=0;c<9;c++){
																							// WHILE QUE LLENA UN ARRAY CON NUMEROS DEL 1 al 10, 
																							// pero en orden aleatorio.
																							llenando = 1;
																							// SETEA EN CERO EL ARRAY
																							for(a=0;a<9;a++){
																								arr[a] = 0;
																							}
																							// GENERA UN ARRAY CON LOS 9 POSIBLES RANDOMS
																							while(llenando == 1){
																								numeroRandom = rand()%9+1;
																								for(a=0;a<9;a++){
																									if(arr[a] == numeroRandom){
																										a = 11;
																									}
																									if(a==8){
																										cont++;
																										arr[cont] = numeroRandom;
																									}
																								}
																								if(cont==8){
																									cont = -1;
																									llenando = 0;
																								}
																							}
																							// ESTABLECE LA REGION DE LA CASILLA
																							if(c<3 && f<3){
																								region = 1;
																							}
																							if(c>2 && c<6 && f<3){
																								region = 2;
																							}
																							if(c>5 && f<3){
																								region = 3;
																							}
																							if(c<3 && f>2 && f<6){
																								region = 4;
																							}
																							if(c<6 && c>2 && f<6 && f>2){
																								region = 5;
																							}
																							if(c>5 && f<6 && f>2){
																								region = 6;
																							}
																							if(c<3 && f>5){
																								region = 7;
																							}
																							if(c>2 && c<6 && f>5){
																								region = 8;
																							}
																							if(c>5 && f>5){
																								region = 9;
																							}
																							// PROBAMOS CADA NUMERO RANDOM EN LA CASILLA
																							for(randoms=0;randoms<9;randoms++){
																								j = 0;
																								i = f;
																								romper = false;
																								// RECORRE CADA CASILLA EN LA FILA
																								while(s[j][i] != arr[randoms] && romper == false){
																									if(j == 9-1){
																										j = c;
																										i = 0;
																										// RECORRE CADA CASILLA EN LA COLUMNA
																										while(s[j][i] != arr[randoms]){
																											if(i == 9-1){
																												switch(region){
																												case 1:
																												{
																													f2 = 0;
																													while(f2<3){
																														c2 = 0;
																														while(c2<3){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 3;
																																f2 = 3;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 2:
																												{
																													f2 = 0;
																													while(f2<3){
																														c2 = 3;
																														while(c2<6){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 6;
																																f2 = 3;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 3:
																												{
																													f2 = 0;
																													while(f2<3){
																														c2 = 6;
																														while(c2<9){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 9;
																																f2 = 3;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 4:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 0;
																														while(c2<3){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 3;
																																f2 = 6;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 5:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 3;
																														while(c2<6){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 6;
																																f2 = 6;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 6:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 6;
																														while(c2<9){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 9;
																																f2 = 6;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 7:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 0;
																														while(c2<3){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 3;
																																f2 = 9;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 8:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 3;
																														while(c2<6){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 6;
																																f2 = 9;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												case 9:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 6;
																														while(c2<9){
																															if(s[c2][f2]==arr[randoms]){
																																c2 = 9;
																																f2 = 9;
																																romper = true;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															s[j][i] = arr[randoms];
																															randoms = 11;
																														}
																													}
																													break;
																												}
																												}
																												
																												break;
																											}
																											i++;
																										}
																										break;
																									}
																									j++;
																								}
																							}
																							if(randoms==9){
																								error++;
																							}
																						}
																					}
																					if(error<1){
																						
																						int i,c,random1,random2,contCeros=0,matrizConCeros[9][9];
																						for(i=0;i<9;i++){
																							for(c=0;c<9;c++){
																								matrizConCeros[c][i] = s[c][i];
																							}
																						}
																						while(contCeros<81-cant_elem){
																							random1 = rand()%9;
																							random2 = rand()%9;
																							if(matrizConCeros[random1][random2]!=0){
																								matrizConCeros[random1][random2] = 0;
																								contCeros++;
																							}
																						}
																						for(i=0;i<9;i++){
																							for(c=0;c<9;c++){
																								s[c][i] = matrizConCeros[c][i];
																							}
																						}
																						whileError = false;
																					}
																				}
																			}
																				bool sudoku_valido (int s[9][9]){
																					int numeroRandom,j,c,i,f,a=0,randoms=0,region,f2=0,c2=0,error=0;
																					int arr[9]={0},llenando=1,aux;
																					bool romper = false, whileError = true, noSeEncontroCero;
																					j = 0;
																					i = 0;
																					// FOR QUE RECORRE FILAS
																					f = 0;
																					c = 0;
																					for(f=0;f<9;f++){
																						// FOR QUE RECORRE COLUMNAS
																						for(c=0;c<9;c++){
																							// ESTABLECE LA REGION DE LA CASILLA
																							if(c<3 && f<3){
																								region = 1;
																							}
																							if(c>2 && c<6 && f<3){
																								region = 2;
																							}
																							if(c>5 && f<3){
																								region = 3;
																							}
																							if(c<3 && f>2 && f<6){
																								region = 4;
																							}
																							if(c<6 && c>2 && f<6 && f>2){
																								region = 5;
																							}
																							if(c>5 && f<6 && f>2){
																								region = 6;
																							}
																							if(c<3 && f>5){
																								region = 7;
																							}
																							if(c>2 && c<6 && f>5){
																								region = 8;
																							}
																							if(c>5 && f>5){
																								region = 9;
																							}
																							aux = s[c][f];
																							j = 1;
																							i = f;
																							if(aux == 0)
																							{
																								c++;
																								noSeEncontroCero = false;
																							}else{
																								noSeEncontroCero = true;
																							}
																							if(noSeEncontroCero == true){
																								// ESTO LE FALTABA A LA SOLUCION 22/06/22
																								if(aux == s[c+1][f]){
																									cout<<"aux "<<aux<<" casilla "<<c+1<<"    "<<f<<endl;
																									return false;
																								}
																								// RECORRE CADA CASILLA EN LA FILA
																								while(s[j][i] != aux){
																									if(j == 9-1){
																										j = c;
																										i = 1;
																										// RECORRE CADA CASILLA EN LA COLUMNA
																										while(s[j][i] != aux ){
																											if(i == 9-1){
																												
																												switch(region){
																													cout<<"Switch"<<endl;
																												case 1:
																												{	
																													f2 = 0;
																													while(f2<3){
																														c2 = 1;
																														while(c2<3){
																															if(s[c2][f2] == aux){
																																c2 = 3;
																																f2 = 3;
																																cout<<"Case"<<endl;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															
																															break;
																														}
																													}
																													break;
																												}
																												case 2:
																												{
																													f2 = 0;
																													while(f2<3){
																														c2 = 4;
																														while(c2<6){
																															if(s[c2][f2]==aux){
																																c2 = 6;
																																f2 = 3;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 3:
																												{
																													f2 = 0;
																													while(f2<3){
																														c2 = 7;
																														while(c2<9){
																															if(s[c2][f2]==aux){
																																c2 = 9;
																																f2 = 3;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==3){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 4:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 1;
																														while(c2<3){
																															if(s[c2][f2]==aux){
																																c2 = 3;
																																f2 = 6;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 5:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 4;
																														while(c2<6){
																															if(s[c2][f2]==aux){
																																c2 = 6;
																																f2 = 6;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 6:
																												{
																													f2 = 3;
																													while(f2<6){
																														c2 = 7;
																														while(c2<9){
																															if(s[c2][f2]==aux){
																																c2 = 9;
																																f2 = 6;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==6){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 7:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 1;
																														while(c2<3){
																															if(s[c2][f2]==aux){
																																c2 = 3;
																																f2 = 9;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 8:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 4;
																														while(c2<6){
																															if(s[c2][f2]==aux){
																																c2 = 6;
																																f2 = 9;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												case 9:
																												{
																													f2 = 6;
																													while(f2<9){
																														c2 = 7;
																														while(c2<9){
																															if(s[c2][f2]==aux){
																																c2 = 9;
																																f2 = 9;
																																return false;
																																break;
																															}
																															c2++;
																														}
																														f2++;
																														if(f2==9){
																															i = f;
																															break;
																														}
																													}
																													break;
																												}
																												}
																												
																												break;
																											}
																											i++;
																										}
																										/*return false;*/
																										break;
																									}
																									j++;
																								}
																							}
																							/*return false;*/
																						}
																					}
																					cout<<endl;
																					return true;
																				}
																					bool es_candidato (int s[9][9], int num, int fila, int columna){
																						int j,c,i,f,region,f2=0,c2=0;
																						bool verificador;
																						
																						j = 0;
																						i = 0;
																						
																						
																						f=fila-1;
																						c=columna-1;
																						
																						if(s[c][f] == num)
																							return false;
																						else{
																							/*ESTABLECE LA REGION DE LA CASILLA*/
																							if(c<3 && f<3){
																								region = 1;
																							}
																							if(c>2 && c<6 && f<3){
																								region = 2;
																							}
																							if(c>5 && f<3){
																								region = 3;
																							}
																							if(c<3 && f>2 && f<6){
																								region = 4;
																							}
																							if(c<6 && c>2 && f<6 && f>2){
																								region = 5;
																							}
																							if(c>5 && f<6 && f>2){
																								region = 6;
																							}
																							if(c<3 && f>5){
																								region = 7;
																							}
																							if(c>2 && c<6 && f>5){
																								region = 8;
																							}
																							if(c>5 && f>5){
																								region = 9;
																							}
																							
																							j = 0;
																							i = f;
																							/*RECORRE CADA CASILLA EN LA FILA*/
																							while(s[j][i] != num){
																								if(j == 9-1){
																									j = c;
																									i = 0;
																									/* RECORRE CADA CASILLA EN LA COLUMNA*/
																									while(s[j][i] != num){
																										if(i == 9-1){
																											switch(region){
																											case 1:
																											{
																												f2 = 0;
																												while(f2<3){
																													c2 = 0;
																													while(c2<3){
																														if(s[c2][f2]== num){
																															c2 = 3;
																															f2 = 3;
																															return false;
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==3){
																														i = f;
																														verificador = true;
																														return true;
																													}
																												}
																												break;
																											}
																											case 2:
																											{
																												f2 = 0;
																												while(f2<3){
																													c2 = 3;
																													while(c2<6){
																														if(s[c2][f2]==num){
																															c2 = 6;
																															f2 = 3;
																															return false;
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==3){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 3:
																											{
																												f2 = 0;
																												while(f2<3){
																													c2 = 6;
																													while(c2<9){
																														if(s[c2][f2]==num){
																															c2 = 9;
																															f2 = 3;
																															return false;
																															
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==3){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 4:
																											{
																												f2 = 3;
																												while(f2<6){
																													c2 = 0;
																													while(c2<3){
																														if(s[c2][f2]==num){
																															c2 = 3;
																															f2 = 6;
																															return false;
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==6){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 5:
																											{
																												f2 = 3;
																												while(f2<6){
																													c2 = 3;
																													while(c2<6){
																														if(s[c2][f2]==num){
																															c2 = 6;
																															f2 = 6;
																															return false;
																															
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==6){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 6:
																											{
																												f2 = 3;
																												while(f2<6){
																													c2 = 6;
																													while(c2<9){
																														if(s[c2][f2]==num){
																															c2 = 9;
																															f2 = 6;
																															return false;
																															
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==6){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 7:
																											{
																												f2 = 6;
																												while(f2<9){
																													c2 = 0;
																													while(c2<3){
																														if(s[c2][f2]==num){
																															c2 = 3;
																															f2 = 9;
																															return false;
																															
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==9){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 8:
																											{
																												f2 = 6;
																												while(f2<9){
																													c2 = 3;
																													while(c2<6){
																														if(s[c2][f2]==num){
																															c2 = 6;
																															f2 = 9;
																															return false;
																															
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==9){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											case 9:
																											{
																												f2 = 6;
																												while(f2<9){
																													c2 = 6;
																													while(c2<9){
																														if(s[c2][f2]==num){
																															c2 = 9;
																															f2 = 9;
																															return false;
																															break;
																														}
																														c2++;
																													}
																													f2++;
																													if(f2==9){
																														i = f;
																														return true;
																													}
																												}
																												break;
																											}
																											}
																											break;
																										}
																										i++;
																									}
																									break;
																								}
																								j++;
																							}
																							if(verificador == true){
																								return true;
																							}else{
																								return false;
																							}
																						}
																					}
																						void crear_candidatos (int s [9][9], int fila, int columna, bool candidatos[9])
																						{
																							int numeros[9]={0};
																							srand(time(NULL));
																							int numeroRandom,j,c,i,f,y,l,a=0,randoms=0,region,f2=0,c2=0;
																							int arr[9]={0},llenando=1,cont=-1;
																							bool romper = false;
																							j = 0;
																							i = 0;
																							f = 0;
																							c = 0;
																							for(y=0; y<9; y++){
																								f=fila-1;
																								c=columna-1;
																								//	WHILE QUE LLENA UN ARRAY CON NUMEROS DEL 1 al 10, 
																								//		pero en orden aleatorio.
																								llenando = 1;
																								/*SETEA EN CERO EL ARRAY*/
																								for(a=0;a<9;a++){
																									arr[a] = 0;
																								}
																								/*GENERA UN ARRAY CON LOS 9 POSIBLES RANDOMS*/
																								while(llenando == 1){
																									numeroRandom = rand()%9+1;
																									for(a=0;a<9;a++){
																										if(arr[a] == numeroRandom){
																											a = 11;
																										}
																										if(a==8){
																											cont++;
																											arr[cont] = numeroRandom;
																										}
																									}
																									if(cont==8){
																										cont = -1;
																										llenando = 0;
																									}
																								}
																								/*ESTABLECE LA REGION DE LA CASILLA*/
																								if(c<3 && f<3){
																									region = 1;
																								}
																								if(c>2 && c<6 && f<3){
																									region = 2;
																								}
																								if(c>5 && f<3){
																									region = 3;
																								}
																								if(c<3 && f>2 && f<6){
																									region = 4;
																								}
																								if(c<6 && c>2 && f<6 && f>2){
																									region = 5;
																								}
																								if(c>5 && f<6 && f>2){
																									region = 6;
																								}
																								if(c<3 && f>5){
																									region = 7;
																								}
																								if(c>2 && c<6 && f>5){
																									region = 8;
																								}
																								if(c>5 && f>5){
																									region = 9;
																								}
																								/* PROBAMOS CADA NUMERO RANDOM EN LA CASILLA*/
																								for(randoms=0;randoms<9;randoms++){
																									j = 0;
																									i = f;
																									romper = false;
																									/*RECORRE CADA CASILLA EN LA FILA*/
																									while(s[j][i] != arr[randoms] && romper == false){
																										if(j == 9-1){
																											j = c;
																											i = 0;
																											/* RECORRE CADA CASILLA EN LA COLUMNA*/
																											while(s[j][i] != arr[randoms]){
																												if(i == 9-1){
																													switch(region){
																													case 1:
																													{
																														f2 = 0;
																														while(f2<3){
																															c2 = 0;
																															while(c2<3){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 3;
																																	f2 = 3;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==3){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 2:
																													{
																														f2 = 0;
																														while(f2<3){
																															c2 = 3;
																															while(c2<6){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 6;
																																	f2 = 3;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==3){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 3:
																													{
																														f2 = 0;
																														while(f2<3){
																															c2 = 6;
																															while(c2<9){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 9;
																																	f2 = 3;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==3){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 4:
																													{
																														f2 = 3;
																														while(f2<6){
																															c2 = 0;
																															while(c2<3){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 3;
																																	f2 = 6;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==6){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 5:
																													{
																														f2 = 3;
																														while(f2<6){
																															c2 = 3;
																															while(c2<6){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 6;
																																	f2 = 6;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==6){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 6:
																													{
																														f2 = 3;
																														while(f2<6){
																															c2 = 6;
																															while(c2<9){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 9;
																																	f2 = 6;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==6){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 7:
																													{
																														f2 = 6;
																														while(f2<9){
																															c2 = 0;
																															while(c2<3){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 3;
																																	f2 = 9;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==9){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 8:
																													{
																														f2 = 6;
																														while(f2<9){
																															c2 = 3;
																															while(c2<6){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 6;
																																	f2 = 9;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==9){
																																i = f;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													case 9:
																													{
																														f2 = 6;
																														while(f2<9){
																															c2 = 6;
																															while(c2<9){
																																if(s[c2][f2]==arr[randoms]){
																																	c2 = 9;
																																	f2 = 9;
																																	romper = true;
																																	break;
																																}
																																c2++;
																															}
																															f2++;
																															if(f2==9){
																																i = f;
																																cout<<arr[randoms]<<"es candidato"<<endl;
																																numeros[y]=arr[randoms];
																																y++;
																															}
																														}
																														break;
																													}
																													}
																													
																													break;
																												}
																												i++;
																											}
																											break;
																										}
																										j++;
																									}
																								}
																							}
																							cout<<endl<<"Los candiadatos para fila "<<fila<<" columna "<<columna<< " son: "<<endl;
																							///////////////////////////////////////
																							for(i=0;i<9;i++)
																								cout<<numeros[i];
																							////////////////////////////
																							int arrayTemporal[9]={0};
																							for(l=0;l<9;l++){
																								if(numeros[l]!=0){
																									for(l=0;l<9;l++)
																									{
																										int var = numeros[l];
																										if(arrayTemporal[var-1]==0){
																											arrayTemporal[var-1]=1;
																											cout<<numeros[l]<<","<<endl;
																										}
																									}
																									l = 10;
																								}
																							}
																							if(l==9){
																								cout<<endl<<"No hay candidatos para esta casilla"<<endl;
																							}
																							
																							//SOLUCIONAR ESTO!!!
																							
																							
																							
																							for(i=0;i<9;i++){
																								for(c=0;c<9;c++){
																									if(numeros[c] == i+1){
																										candidatos[i] = true;
																									}
																								}
																							}
																							cout<<endl<<"Array booleano: "<<endl;
																							for(i=0;i<9;i++){
																								cout<<candidatos[i]<<",";
																							}
																						}
