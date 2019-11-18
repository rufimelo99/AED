//
// Rui Melo, nº 88889
// ...
//
// AED, 2018/2019
//
// solution of the traveling salesman problem
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "cities.h"
#include "../P01/elapsed_time.h"
#include <time.h>

//
// record best solutions
//

static int min_length = 0,max_length = 0;
static int min_tour[max_n_cities + 1],max_tour[max_n_cities + 1];
static long n_tours;
clock_t start, end;
double cpu_time_used;
int numero_de_cidades = max_n_cities-1;
//
// first solution (brute force, distance computed at the end, compute best and worst tours)
//

void tsp_v1(int n,int m,int *a)
{
  int i,t, distancia_tempo;
  int tour_temp[max_n_cities + 1];

  if(m < n - 1)
    for(i = m;i < n;i++)
    {
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      tsp_v1(n,m + 1,a);
      t = a[m];
      a[m] = a[i];
      a[i] = t;
    }
  else
  { // visit permutation
    n_tours++;
    distancia_tempo = 0;
    //EDITING HERE!!!!!!!


    // modify the following code to do your stuff
    for(i = 0;i <= n;i++){
    //printf("O valor de a[i]: %d\n", a[i]);
    //printf(i);
      tour_temp[i]=a[i];
      if(i< n-1){
      printf("Distancia de %d a %d: %3d\n ",a[i],a[i+1], cities[a[i]].distance[a[i+1]]);
      distancia_tempo = distancia_tempo + cities[a[i]].distance[a[i+1]];
      

      }
      if(i == n-1){
        printf("Distancia do ciclo: %d\n", distancia_tempo);

        if(distancia_tempo < min_length){
          min_length = distancia_tempo;
          for(int j = 0; j < 6; j++){ //6 para o meu exemplo
            printf("%i", tour_temp[j]);
            
            min_tour[j] = tour_temp[j];
          }
        }
        
        if(distancia_tempo > max_length){
          max_length = distancia_tempo;
          for(int j = 0; j < n; j++){
            printf("%i", tour_temp[j]);
            
            max_tour[j] = tour_temp[j];
          }
        }  
      }

      printf("%d%s\n",a[i],(i == n - 1) ? "\n\n " : " ");
    }
  

  }
  
}

void tempos_execucao(double cpu_time_used, int numero_de_cidades){
  //printf("%i\n", numero_de_cidades);
  //printf("%i\n", numero_de_cidades);
  //printf("%f\n", cpu_time_used);

  while(numero_de_cidades > 2){
    cpu_time_used = cpu_time_used/numero_de_cidades;
    numero_de_cidades--;
  }

  printf("%25s: %25s (seg)\n", "Numero de Cidades", "Tempo de Execução");
  for(int j=3; j< 18; j++){
    printf("%25i: %25f\n", j, cpu_time_used);
    cpu_time_used= cpu_time_used*(j+1);
    

  }


}

//
// main program
//

int main(int argc,char **argv)
{
  int n_mec,special,n,i,a[max_n_cities];
  char file_name[32];
  double dt1;

  start = clock();

  n_mec = 88889; // CHANGE THIS!
  special = 0;
  init_cities_data(n_mec,special);
  printf("data for init_cities_data(%d,%d)\n",n_mec,special);
  fflush(stdout);

  print_distances();
  for(n = 3;n <= n_cities;n++)
  {
    //
    // try tsp_v1
    //
    dt1 = -1.0;
    if(n <= 16)
    {
      (void)elapsed_time();
      for(i = 0;i < n;i++)
        a[i] = i;
      min_length = 1000000000;
      max_length = 0;
      n_tours = 0l;
      tsp_v1(n,1,a); // no need to change the starting city, as we are making a tour
      dt1 = elapsed_time();
      printf("tsp_v1() finished in %8.3fs (%ld tours generated)\n",dt1,n_tours);
      printf("  min %5d [",min_length);
      for(i = 0;i < n;i++)
        printf("%2d%s",min_tour[i],(i == n - 1) ? "]\n" : ",");
      printf("  max %5d [",max_length);
      for(i = 0;i < n;i++)
        printf("%2d%s",max_tour[i],(i == n - 1) ? "]\n" : ",");
      fflush(stdout);
      if(argc == 2 && strcmp(argv[1],"-f") == 0)
      {
        min_tour[n] = -1;
        sprintf(file_name,"min_%02d.svg",n);
        make_map(file_name,min_tour);
        max_tour[n] = -1;
        sprintf(file_name,"max_%02d.svg",n);
        make_map(file_name,max_tour);
      }
    }
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  //printf("ola   %f\n", cpu_time_used);
  //printf("Numero de cidades %i\n", max_n_cities-1);
  tempos_execucao(cpu_time_used, numero_de_cidades);
  return 0;
}
