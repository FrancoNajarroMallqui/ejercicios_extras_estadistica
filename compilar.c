#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* extraer_nombre_programa(char* name_programa,int size){
int i;
char* salida=(char*)malloc(sizeof(char)*100);
memset(salida,'\0',100);
int k=0;
int centinela=1;
for(i=size-1;centinela;i--){
if(name_programa[i]=='c' && name_programa[i-1]=='.')
centinela=0;
}
i--;
while(name_programa[i]!='/'){
salida[k++]=name_programa[i];
i--;
}
char aux;
int f=k-1;
for(i=0;i<k/2;i++){
aux=salida[i];
salida[i]=salida[f];
salida[f--]=aux;
}
return salida;
}

int main(){
int np;
char* name_programa=(char*)malloc(sizeof(char)*300);
memset(name_programa,'\0',300);
printf("ingrese el nombre del archivo fuente *.c para proceder a compilar y hacer pruebas:\n");
gets(name_programa);
int size_name=strlen(name_programa);
printf("ingrese la cantidad de pruebas a realizar en el programa:\n");
scanf("%d",&np);
int* array_np=(int*)malloc(sizeof(int)*np);
int i;
for(i=0;i<np;i++){
printf("ingrese la cantidad de procesadores para la prueba %d:\n",i);
scanf("%d",array_np+i);
}
char * compilar=(char*)malloc(sizeof(char)*(size_name+40));
memset(compilar,'\0',size_name+40);
sprintf(compilar,"mpicc ");
strcat(compilar,name_programa);
strcat(compilar," -o ");
char* name_ejecutable=extraer_nombre_programa(name_programa,size_name);
strcat(compilar,name_ejecutable);
strcat(compilar," -lm\n");
system(compilar);
char* ejecutar=(char*)malloc(sizeof(char)*(strlen(name_ejecutable)+30));

for(i=0;i<np;i++){
memset(ejecutar,'\0',strlen(name_ejecutable)+30);
sprintf(ejecutar,"mpirun -np %d ./%s\n",array_np[i],name_ejecutable);
system(ejecutar);
}
return 0;
}
