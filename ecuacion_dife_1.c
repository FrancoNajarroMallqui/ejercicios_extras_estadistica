#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void resolver_ecuacion(int inf , int sup, int num_puntos ){
int i,j;
float * intervalo=(float*)malloc(sizeof(float)*num_puntos);
FILE* arch=fopen("archivo_datos.txt","a+t");
float dx=(float)(sup-inf)/(float)n;
intervalo[0]=sin(inf);
intervalo[1]=
float f_actual=sin(inf-dx);
fprintf(arch,"%f %f\n",inf,sin(inf));
for(i=1;i<n;i++){
f_actual=cos(inicial+(i)*dx)*2*dx+f_actual;
fprintf(arch,"%f %f\n",inf+(i+1)*dx,f_actual);
}

	

