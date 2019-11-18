//
// Rui Melo  
// Andre Catarino
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
#include "elapsed_time.h" 
#define DEBUG (0)

//
// record best solutions
//

static int min_length=100000000,max_length=0;
static int min_tour[max_n_cities + 1],max_tour[max_n_cities + 1];
static long n_tours;


clock_t start, end;
double cpu_time_used;
//
// first solution (brute force, distance computed at the end, compute best and worst tours)
//

void tsp_v1(int n,int m,int *a)
{
  int i,t, distancia_tempo=0;

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
  {  // visit permutation
    n_tours++;
    for(i = 0;i < n - 1;i++){
		  distancia_tempo+=cities[a[i]].distance[a[i+1]];
    }
      distancia_tempo+=cities[a[n-1]].distance[a[0]];     //adicionar cidade 0


	if(distancia_tempo<min_length){
		min_length=distancia_tempo;
		for(i = 0;i < n;i++){
      min_tour[i]=a[i];
		}
	}
	if(distancia_tempo>max_length){
		max_length=distancia_tempo;
		for(i = 0;i < n;i++){
      max_tour[i]=a[i];
		}
	}
  }
}


int matriz[18][18];
int mask_plus_city[300000][18]; //2^¹8 < 300000
int mask_cheia_int;
//mask-plus_city[mask][cidade]=custo


void make_matrix(){

  int i,j;

  for(i = 0;i < n_cities;i++)
  {
    for(j = 0;j < n_cities;j++)
      if(i == j){

        //printf("%i\n", cities[i].distance[j]);
        matriz[i][j]=0;
      }

      else{

        //printf("%i\n", cities[i].distance[j]);
        //printf("se ta zero é pq deu erro\n");
        matriz[i][j]=cities[i].distance[j]; 
      }

  }

  
  if DEBUG {
    printf("\n\n\nMatrix\n\n\n");
    for(i = 0;i < n_cities;i++)
    {
      for(j = 0;j < n_cities;j++){
        printf("%3i ",matriz[i][j]);
        if(j==n_cities-1){
          printf("\n");
        }
      }
    }
  
  printf("making matrix...over...\n");
  }
}

void imprime_exemplo_matriz(){
  printf("Matriz Exemplo\n\n");
  for(int i=0; i<18; i++){
    for(int j=0; j<18; j++){
      if(j==17){
        printf("%4i\n",matriz[i][j] );
      }
      else{

        printf("%4i",matriz[i][j] );
      }
    }
  }
}

 
int pot(int x, int n){
  int i, p=1;
  for(i=0; i<n;i++)
  { 
    p=p*x;
  }
  return p;
}

int conv_array_bin(int amount_of_cities, int mask[amount_of_cities]){
  int decimal=0;
  for(int i=0; i<amount_of_cities; i++){
      if DEBUG {
        printf("mask[i]: %i\n", mask[i]);
        printf("i: %i\n\n", i);
        printf("2^i: %i\n\n", pot(2,i));
      }
      if(mask[i]==1)
        decimal+=pot(2,amount_of_cities-1-i);
  }
  if DEBUG {
    printf("decimal: %i\n", decimal);
  }
  return decimal;
}
     
int tsp_v2(int initial_node, int amount_of_cities, int mask[amount_of_cities]){
  int n_opcoes=0;
  int min_temp=999999; //numero demasiado grande


  //ocupar na mascara o node usado
  mask[initial_node]=1;
  
  //imprimir mascara
    if DEBUG {
      printf("mask-->");
    }
    for(int i=0; i<amount_of_cities; i++){  
      if DEBUG {
        printf("%3i ", mask[i]);  
      } 
        if(mask[i]==0){
          n_opcoes++;
          
        }
    }
  //
  //determinar a quantidade de cidades que falta comparar e verificar
    int cidades_em_falta[n_opcoes];
    int counter=0;
    for(int i=0; i<amount_of_cities; i++){
      if(mask[i]==0){
        cidades_em_falta[counter]=i;
        counter++;
      }
    }
    if DEBUG {
      printf("\nn_opcoes:  %i\n", n_opcoes);
      printf("\ncidades em falta:  ");
  
      for(int i=0; i<n_opcoes; i++){
        printf("%i ", cidades_em_falta[i]);
      }
      printf("\n");
    }
  //
  
  //EXEMPLO TEORICO (comentario)
    /*
    T (0, {1,2,3})= minimum of

    = { (0,1)  + T (1,  {2,3} )     -->matriz[0][1] + tsp_v3(1, {1,1,0,0})
            = { (1,2)  + T (2,  {3} )     
                  = { (2,3)  + T (3,  {} )     
            = { (1,3)  + T (3,  {2} )     
                  = { (3,2)  + T (2,  {} )

    = { (0,2)  + T (2,  {1,3} )     -->matriz[0][2] + tsp_v3(2, {1,0,1,0})

    = { (0,3)  + T (3,  {1,2} )     -->matriz[0][3] + tsp_v3(3, {1,0,0,1});
    */
  //
  if(n_opcoes==0){
    min_temp=matriz[initial_node][0];//supostamente 0 pq comecamos nesta cidade
    
    //trying dp
    //mask-plus_city[mask][cidade]=custo
    //(caso base em que nao ha mais cidades para percorrer-->direto da matriz, basicamente)
    
    
    if DEBUG {
      printf("initial node %i\n", initial_node);
      printf("valor q/ opcao 0 %i\n", min_temp);
    
    }
  }
  else{
    for(int i=0; i<n_opcoes; i++){  
      //criar mascara nova
      int mask_temp[amount_of_cities];
      for(int j=0; j<amount_of_cities; j++){
        mask_temp[j]=mask[j];
      }
      mask_temp[cidades_em_falta[i]]=1;
      

      

      int valor=matriz[cidades_em_falta[i]][initial_node]+tsp_v2(cidades_em_falta[i], amount_of_cities, mask_temp);
      
      



  
      
      if DEBUG{
        printf("cidade em falta: %i\n", cidades_em_falta[i]);
        printf("distancia a cidade original: %i\n", valor);
      
        printf("valor: %i\n", valor);
      }
      if(valor<min_temp){
        min_temp=valor;
        //printf("trocou\n");
      }
    }
  }
  
  return min_temp;

}
int tsp_v3(int initial_node, int amount_of_cities, int mask[amount_of_cities]){
  int minimo=999999; //numero excesivamente grande
  int maximo=-1;

  //TODO 
  //ocupar na mascara o node usado
    mask[initial_node]=1;
  //
  if DEBUG {
    printf("\nNumero de cidades: %i\n", amount_of_cities);
  }
  //imprimir mascara
    if DEBUG {
      printf("mask original-->");
      for(int i=0; i<amount_of_cities; i++){  
        printf("%3i ", mask[i]);  
      } 
      printf("\n");
    }
  //
  int mask_int=conv_array_bin(amount_of_cities, mask);

  //arranjar quantidade de cidades que faltam
    int n_opcoes=0;
    for(int i=0; i<amount_of_cities; i++){  
      if DEBUG {
        printf("%3i ", mask[i]);  
      }

      if(mask[i]==0){
        n_opcoes++;
        
      }
    }
  //
  //determinar quais as cidades que faltam comparar
    int cidades_em_falta[n_opcoes];
    int counter=0;
    for(int i=0; i<amount_of_cities; i++){
      if(mask[i]==0){
        cidades_em_falta[counter]=i;
        counter++;
      }
    }
  //

  //verificar qual a menor parcela que tem o minimo
     //numero excesivamente grande
    if(n_opcoes==0){
      
      minimo=matriz[initial_node][0];
      
    }
    else{
      int parcela=99999999;
      int max_temp=-1;
      for(int i=0; i<n_opcoes;i++){
        
        //criar mascara temporaria
          int mask_temp[amount_of_cities];
          for(int i=0; i<amount_of_cities; i++){  
            mask_temp[i]=mask[i];
          }

          if DEBUG {
            printf("\ncidade em falta: %i\n", cidades_em_falta[i]);
          }
          mask_temp[cidades_em_falta[i]]=1;
        
        //
        //imprimir mascara
          if DEBUG {
            printf("mask temp    -->");
            for(int i=0; i<amount_of_cities; i++){  
              printf("%3i ", mask_temp[i]);  
            } 
            printf("\n");
          }
        //
        int mask_temp_int=conv_array_bin(amount_of_cities, mask_temp);
        if(mask_plus_city[mask_temp_int][cidades_em_falta[i]]==0){
          if DEBUG {
            printf("Nao tenho o valor\n"); 
            printf("mask_plus_city[%i][%i]: ???\n\n",mask_temp_int, cidades_em_falta[i]);
          }
          tsp_v3(cidades_em_falta[i], amount_of_cities, mask_temp);
        }
        else{ 
          if DEBUG {
            printf("Pelos vistos, tenho o valor\n");
            printf("mask_plus_city[%i][%i]: %i\n",mask_temp_int, cidades_em_falta[i] ,mask_plus_city[mask_temp_int][cidades_em_falta[i]]);
            
          }
        }
        parcela=matriz[initial_node][cidades_em_falta[i]]+mask_plus_city[mask_temp_int][cidades_em_falta[i]];
        if DEBUG {
          printf("parcela=matriz[%i][%i]+mask_plus_city[%i][%i]\n", initial_node, cidades_em_falta[i], mask_temp_int, cidades_em_falta[i]);
          printf("%i = %i + %i\n", parcela, matriz[initial_node][cidades_em_falta[i]], mask_plus_city[mask_temp_int][cidades_em_falta[i]]);
        }
        if(parcela<minimo){
          minimo=parcela;
        }
        if(max_temp>maximo){
          maximo=max_temp;
        }
      }
    }
    //
  
  if DEBUG {
    printf("mascara: %i\n", mask_int);
    printf("initial node %i\n", initial_node);
    printf("valor agora guardado %i\n", minimo);
  }
  mask_plus_city[mask_int][initial_node]=minimo;
  return minimo;
}


int main(int argc,char **argv)
{
  //Forca Bruta
    int n_mec,special,n,i,a[max_n_cities];
    char file_name[32];
    double dt1;

    n_mec = 88889; // CHANGE THIS!
    special = 1;
    init_cities_data(n_mec,special);
    printf("data for init_cities_data(%d,%d)\n",n_mec,special);
    fflush(stdout);


    print_distances();

    printf("\n\n\nBrute Force...\n");
    for(n = 3;n <= n_cities;n++)
    {
      
      dt1 = -1.0;

      min_length=100000000,max_length=0;

      if(n <= 12 )
      {
        (void)elapsed_time();
        for(i = 0;i < n;i++)
          a[i] = i;
        n_tours = 0l;
        tsp_v1(n,1,a); // no need to change the starting city, as we are making a tour
        dt1 = elapsed_time();
        printf("\ntsp_v1() finished in %8.3fs       (%8ld tours generated)\n",dt1,n_tours);
        
        
        
        
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
  //
  //NEW BRUTE FORCE
    printf("\n\n\nNew Brute Force...\n\n");
    make_matrix();
    if DEBUG {
      imprime_exemplo_matriz(); 
    }
    int amount_of_cities;
    dt1 = -1.0;
    for(int i=3; i<=12; i++){

      (void)elapsed_time();
     
      amount_of_cities=i;
      //int tour[amount_of_cities+1]; ----> TODO

      int mask[amount_of_cities];
      for(int i=0; i<amount_of_cities;i++){
        mask[i]=0;
      }

      //int mask_plus_city[mask[amount_of_cities]][int city];  


      int minimo= tsp_v2(0,amount_of_cities, mask);
      printf("minimo para %2i cidades: %i\n", amount_of_cities, minimo);
      dt1 = elapsed_time();
      printf("tsp_v2() finished in %8.3fs       \n\n",dt1);

    }
  //
  //Dynamic Programming
    printf("\nDynamic Programming...\n\n");
    dt1 = -1.0;
    for(int i=3; i<=18  ; i++){ 

      (void)elapsed_time();
        
        


      int amount_of_cities=i;
      int mascara_exemplo[amount_of_cities];
      for(int i=0; i<amount_of_cities; i++){
        mascara_exemplo[i]=0;
      }
      int minimo=tsp_v3(0, amount_of_cities , mascara_exemplo);
      printf("minimo para %2i cidades: %i\n", amount_of_cities, minimo);

      dt1 = elapsed_time();
      printf("tsp_v3() finished in %8.3fs       \n\n",dt1);

    }
  //

  return 0;
}
