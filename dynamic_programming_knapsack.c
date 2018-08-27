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

/*return max int*/
int max(int a, int b) { return (a > b)? a : b; }

/*KnapSack logic*/
int knapSack()
{
  int i;
  int j;
  int l = 0;
  int temp;
  int knapSackContainer[numberOfElements+1][capacity+1];
  int totalWeight = 0;
  int weightSet[1000];

  for (i = 0; i <= numberOfElements; i++)
  {
    for (j = 0; j <= capacity; j++)
    {
      if (i==0 || j==0){
        knapSackContainer[i][j] = 0;
      }
      else if (sets[i-1].weight <= j){
        temp = j-sets[i-1].weight;
        knapSackContainer[i][j] = max(sets[i-1].profit + knapSackContainer[i-1][temp],  knapSackContainer[i-1][j]);
      }
      else{
        knapSackContainer[i][j] = knapSackContainer[i-1][j];
      }
    }
  }
  printf("\n---------(a)--------\n");
  printf("Total Profit: %d\n", knapSackContainer[numberOfElements][capacity]);
  j = capacity; 
  for(i = numberOfElements; i > 0; i--){
    if(knapSackContainer[i][j] != knapSackContainer[i-1][j]){
      weightSet[l++] = sets[i-1].weight;
      totalWeight = totalWeight + sets[i-1].weight;
      j = j - sets[i-1].weight;
    }
  }
  printf("Total Weight: %d\n", totalWeight);
  printf("\n---------(b)--------\n");
  printf("Weight Sets: ");
  for(i = l-1; i >= 0; i--){
    printf("%d", weightSet[i]);
    if(i != 0){
      printf(", ");
    }
    else{
      printf(".\n");
    }
  }
  printf("\n\n");
  return knapSackContainer[numberOfElements][capacity];
}

int main(int argc, char *argv[])
{
  if(argc == 2){
    readFile(argv);   /*Raeds text file*/
    displayInitialValues();
    knapSack();
  }
  else{
    printf("Only one file name is required.\n");
  }
  free(sets);
  return 0;
}
