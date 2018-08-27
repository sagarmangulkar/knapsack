#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>


typedef struct sets{
  int index;
  int profit;
  int weight;
}Sets;

Sets * sets = NULL;
int numberOfElements;
int capacity;

int cmpfuncMaxBenifit (const void * a, const void * b)
{ 
  Sets *s1 = (Sets *)a;
  Sets *s2 = (Sets *)b;
  if ( s1->profit == s2->profit ) return 0;
  else if ( s1->profit < s2->profit ) return -1;
  else return 1;
}

int cmpfuncMinWeight (const void * a, const void * b)
{ 
  Sets *s1 = (Sets *)a;
  Sets *s2 = (Sets *)b;
  if ( s1->weight== s2->weight) return 0;
  else if ( s1->weight < s2->weight ) return 1;
  else return -1;
}

int cmpfuncMaxWeight (const void * a, const void * b)
{ 
  Sets *s1 = (Sets *)a;
  Sets *s2 = (Sets *)b;
  if ( s1->weight== s2->weight) return 0;
  else if ( s1->weight < s2->weight ) return -1;
  else return 1;
}


int cmpfuncMaxBenifitPerUnit (const void * a, const void * b)
{ 
  Sets *s1 = (Sets *)a;
  Sets *s2 = (Sets *)b;
  if ((s1->profit)/(s1->weight) == (s2->profit)/(s2->weight)) return 0;
  else if ((s1->profit)/(s1->weight) < (s2->profit)/(s2->weight)) return -1;
  else return 1;
}

/*displays initial values fetched from text file*/
void displayInitialValues(){
  int i;
  printf("\n-----------------Knapsack Details---------------\n");
  printf("Number of Elements: %d\n", numberOfElements);
  for(i = 0; i < numberOfElements; i++){
    printf("(%d)Weight: %d  ", i, sets[i].weight);
  }
  printf("\n");
  for(i = 0; i < numberOfElements; i++){
    printf("(%d)Profit: %d  ", i, sets[i].profit);
  }
  printf("\n");
  printf("Capacity: %d\n", capacity);
  printf("-----------------------------------------------\n");
}

/*fetching data from txt file*/
int readFile(char *fileName[]){
  sets =  malloc(100 * sizeof(sets));
  FILE * file;
  size_t len = 0;
  int read;
  char *line = NULL;
  char *token;
  int i = 0;
  int var;
  file = fopen(fileName[1], "r");
  if(file){
    if((read = getline(&line, &len, file)) != -1) {
      numberOfElements = atoi(line);
    }
    sets = realloc(sets, numberOfElements * sizeof(Sets));
    if((read = getline(&line, &len, file)) != -1) {
      token = strtok (line, ",");
      while (token != NULL)
      {
        sscanf (token, "%d", &var);
        sets[i++].weight = var;
        token = strtok (NULL, ",");
      }
    }

    if((read = getline(&line, &len, file)) != -1) {
      token = strtok (line, ",");
      i = 0;
      while (token != NULL)
      {
        sscanf (token, "%d", &var);
        sets[i++].profit = var;
        token = strtok (NULL, ",");
      }
    }

    if((read = getline(&line, &len, file)) != -1) {
      capacity = atoi(line);
    }
    fclose(file);
    return 1;
  }
  else{
    printf("please check the file name or no such file is present.\n");
  }
  return -1;
}

void maxBenifitFirst(){
  int i;
  int j = 0;
  int weight = 0;
  int capa = capacity;
  int totalProfit = 0;
  int totalWeight = 0;
  int counter[50];
  for(i = numberOfElements-1; i >= 0; i--){
    if(sets[i].weight <= capa){
      weight = sets[i].weight;
      capa = capa - weight;
      totalProfit = totalProfit + sets[i].profit;
      totalWeight = totalWeight + sets[i].weight;
      counter[j] = i;
      j++;
    }
  }
  printf("\n(a)\n");
  printf("Total Profit: %d\n", totalProfit);
  printf("Total Weight: %d\n", totalWeight);
  printf("\n(b)\n");
  for(i = 0; i < j; i++){
    printf("%d", sets[counter[i]].weight);
    if(i != j){
      printf(", ");
    }
    else{
      printf(".");
    }
  }
  printf("\n");
}

void minWeightFirst(){
  int i;
  int j = 0;
  int weight = 0;
  int capa = capacity;
  int totalProfit = 0;
  int totalWeight = 0;
  int counter[50];
  for(i = numberOfElements-1; i >= 0; i--){
    if(sets[i].weight <= capa){
      weight = sets[i].weight;
      capa = capa - weight;
      totalProfit = totalProfit + sets[i].profit;
      totalWeight = totalWeight + sets[i].weight;
      counter[j] = i;
      j++;
    }
  }
  printf("\n(a)\n");
  printf("Total Profit: %d\n", totalProfit);
  printf("Total Weight: %d\n", totalWeight);
  printf("\n(b)\n");
  printf("Weight Sets: ");
  for(i = 0; i < j; i++){
    printf("%d", sets[counter[i]].weight);
    if(i != j){
      printf(", ");
    }
    else{
      printf(".");
    }
  }
  printf("\n");
}

void maxWeightFirst(){
  int i;
  int j = 0;
  int weight = 0;
  int capa = capacity;
  int totalProfit = 0;
  int totalWeight = 0;
  int counter[50];
  for(i = numberOfElements-1; i >= 0; i--){
    if(sets[i].weight <= capa){
      weight = sets[i].weight;
      capa = capa - weight;
      totalProfit = totalProfit + sets[i].profit;
      totalWeight = totalWeight + sets[i].weight;
      counter[j] = i;
      j++;
    }
  }
  printf("\n(a)\n");
  printf("Total Profit: %d\n", totalProfit);
  printf("Total Weight: %d\n", totalWeight);
  printf("\n(b)\n");
  printf("Weight Sets: ");
  for(i = 0; i < j; i++){
    printf("%d", sets[counter[i]].weight);
    if(i != j){
      printf(", ");
    }
    else{
      printf(".");
    }
  }
  printf("\n");
}

void maxBenifitPerUnit(){
  int i;
  int j = 0;
  int weight = 0;
  int capa = capacity;
  int totalProfit = 0;
  int totalWeight = 0;
  int counter[50];
  for(i = numberOfElements-1; i >= 0; i--){
    if(sets[i].weight <= capa){
      weight = sets[i].weight;
      capa = capa - weight;
      totalProfit = totalProfit + sets[i].profit;
      totalWeight = totalWeight + sets[i].weight;
      counter[j] = i;
      j++;
    }
  }
  printf("\n(a)\n");
  printf("Total Profit: %d\n", totalProfit);
  printf("Total Weight: %d\n", totalWeight);
  printf("\n(b)\n");
  printf("Weight Sets: ");
  for(i = 0; i < j; i++){
    printf("%d", sets[counter[i]].weight);
    if(i != j){
      printf(", ");
    }
    else{
      printf(".");
    }
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if(argc == 2){
    int selectedItem; 
    readFile(argv);   /*reads text file*/
    displayInitialValues();
    qsort(sets, numberOfElements, sizeof(Sets), cmpfuncMaxBenifit);
    printf("\n-----------Max Benifit First---------\n");
    maxBenifitFirst();
    printf("\n-----------Min Weight First---------\n");
    qsort(sets, numberOfElements, sizeof(Sets), cmpfuncMinWeight);
    minWeightFirst();
    printf("\n-----------Max Weight First---------\n");
    qsort(sets, numberOfElements, sizeof(Sets), cmpfuncMaxWeight);
    maxWeightFirst();
    printf("\n-----------Max Benifit First---------\n");
    qsort(sets, numberOfElements, sizeof(Sets), cmpfuncMaxBenifitPerUnit);
    maxBenifitPerUnit();
    printf("\n");
  }
  else{
    printf("Only one file name is required.\n");
  }
  free(sets);
  return 0;
}
