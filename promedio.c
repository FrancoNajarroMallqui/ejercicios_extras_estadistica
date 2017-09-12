#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#include<string.h>
#include<math.h>

double t0,t1;
int *array,*gather_array;
int num_elem;
int nproc,rank;
int size_partido;

void print_array(int *a,int size , int rank){
int i;
printf("soy el nodo: %d y este es el array que almaceno:\n",rank);
for(i=0;i<size;i++)
printf("%d ",a[i]);
printf("\n");
}

int main(){
srand(time(NULL));
int*buffer;
MPI_Init(NULL,NULL);
	MPI_Comm_size( MPI_COMM_WORLD, &nproc );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
MPI_Barrier(MPI_COMM_WORLD);
	t0=MPI_Wtime();
if(rank==0){
	
	int i=0;
	printf("ingrese el tamaño del array aleatorio a generar:\n");
	scanf("%d",&num_elem);
	array=(int*)malloc(sizeof(int)*num_elem);
	for(i=0;i<num_elem;i++)
		array[i]=rand()%100;
	gather_array=(int*)malloc(sizeof(int)*nproc);
	print_array(array,num_elem,rank);
size_partido=num_elem/nproc;

}
MPI_Bcast(&size_partido,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);


buffer=(int*)malloc(sizeof(int)*size_partido);

	printf("hola soy el procesador %d y este es el numero de elementos : %d\n",rank,size_partido);
	
	//MPI_Bcast(&size_partido,1,MPI_INT,0,MPI_COMM_WORLD);

MPI_Scatter(array,size_partido,MPI_INT,buffer,size_partido,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
print_array(buffer,size_partido,rank);

int i,sum=0;
for(i=0;i<size_partido;i++)
	sum+=buffer[i];
MPI_Barrier(MPI_COMM_WORLD);
MPI_Gather(&sum,1,MPI_INT,gather_array,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
if(rank==0){
	int i;
int sum=0;
for(i=0;i<nproc;i++)
	sum+=gather_array[i];
t1=MPI_Wtime();
printf("este es el proceso %d y este es el promedio de los numeros:%lf en un tiempo de %lf\n",rank,(double)sum/(double)num_elem,t1-t0);
}
MPI_Finalize();
return 0;
}







	
