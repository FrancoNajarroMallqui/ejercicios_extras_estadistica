
//ping-pong entre dos procesadores usando comunicacion sin interrupcion !!!!
#include <stdio.h> 
#include <mpi.h> 
#include<stdlib.h>
#include<time.h>
#define VUELTAS 400 //aqui se define el numero de vueltas o iteraciones
double calculo() //devuelve un entero aleatorio entre 0 y 100
{ 
  double aux;  
  aux = rand() % 100; 
  return(aux); 
} 
int main(int argc, char** argv)  
{ 
  double      t0, t1, dat = 0.0, dat1, dat_rec; 
  int         pid, i;    
  MPI_Status  status; 
  MPI_Request request; //request requerido para Isend y wait
  MPI_Init(&argc, &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
  if (pid == 0) t0 = MPI_Wtime(); 
  for(i=0; i<VUELTAS; i++)  
  { 
    if (pid == 0)  
    { 
      MPI_Isend(&dat, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD,&request); //envio sin interrupcion !!!
      dat1 = calculo(); 
      MPI_Wait(&request, &status); 
      MPI_Recv(&dat_rec, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status); 
      dat = dat1 + dat_rec; 
    }  
    else  
    {    
      dat1 = calculo(); 
      if (i!=0) MPI_Wait(&request, &status); 
      MPI_Recv(&dat_rec, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status); 
      dat = dat1 + dat_rec;    // se esta ping-poneando un entero que crecera al sumarle otro aleatorio.
      MPI_Isend(&dat, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,&request); // envio sin interrupcion!!! 
    } 
  } 
  if (pid == 0)  
  { 
    t1 = MPI_Wtime(); 
    printf("\n   Tiempo de ejecucion = %f s \n", t1-t0); 
    printf("\n   el dato final es : Dat = %1.3f  para %d iteraciones\n\n", dat,VUELTAS); 
  } 
  MPI_Finalize(); 
  return 0; 
}
