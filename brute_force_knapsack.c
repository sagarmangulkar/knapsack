#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

int numberOfElements;;
int weights[1000];
int profits[1000];
int capacity;
int totalProfit[1000];
int totalWeight[1000];
int weightSets[1000][1000];
int possibleTotalProfit[1000];

/*create the number of combinations equal to the 2 to the power of
  number Of Elements*/
void createCombinations()
{
  int numberOfCombinations = pow(2, numberOfElements);
  int i, j;
  int totalProfitTemp = 0;
  int totalWeightTemp = 0;

  for(i = 0; i < numberOfCombinations; i++)
  {
    for(j = 0; j < numberOfElements; j++)
    {
      if(i & (1<<j)){
        totalProfitTemp = totalProfitTemp + profits[j];
        totalWeightTemp = totalWeightTemp + weights[j];
        weightSets[i][j] = weights[j];
      }
    }
    totalProfit[i] = totalProfitTemp;
    totalWeight[i] = totalWeightTemp;
    totalProfitTemp = 0;
    totalWeightTemp = 0;
  }
}

/*decide the item to be selected on the basis of capacity and max profit*/
int decideSelectedItem(){
  int i = 0;
  int j = 0;
  int k = 0;
  bool isGreater = true;
  int selectedItem;
  int temp;
  int itemIndex;
  int size = pow(2, numberOfElements);

  /*eleminate the items that crosses the capacity*/
  for(i = 0; i < size; i++){
    if(totalWeight[i] <= capacity){
      possibleTotalProfit[j] =  totalProfit[i];
      j++;
    }    
  }

  temp = possibleTotalProfit[0];
  for (i = 1; i < j; i++) {
      if (possibleTotalProfit[i] > temp) {
             itemIndex = i;
             temp = possibleTotalProfit[i];
          }
    }
  return itemIndex;
}

/*display the info*/
void display(int item){
  int i;
  int j;
  printf("\n-----------------(a)----------------\n");
  printf("\nTotal Profit: %d\n", possibleTotalProfit[item]);
  printf("Total Weight: %d\n", totalWeight[item]);

  printf("\n-----------------(b)----------------\n");
  printf("\nWeight Sets: ");
  for(j = 0; j < numberOfElements; j++){
    if(weightSets[item][j] != 0){
      printf("%d", weightSets[item][j]);
      if(j != numberOfElements-1){
        printf(", ");
      }
      else{
        printf(".");
      } 
    }
  }
  printf("\n");

}


/*displays initial values fetched from text file*/
void displayInitialValues(){
  int i;
  printf("\n-----------------Knapsack Details---------------\n");
  printf("Number of Elements: %d\n", numberOfElements);
  for(i = 0; i < numberOfElements; i++){
    printf("Weight[%d]: %d  ", i, weights[i]);
  }
  printf("\n");
  for(i = 0; i < numberOfElements; i++){
    printf("Profit[%d]: %d  ", i, profits[i]);
  }
  printf("\n");
  printf("Capacity: %d\n", capacity);
  printf("-----------------------------------------------\n");
}

//fetching data from txt file
int readFile(char *fileName[]){
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

    if((read = getline(&line, &len, file)) != -1) {
      token = strtok (line, ",");
      while (token != NULL)
      {
        sscanf (token, "%d", &var);
        weights[i++] = var;
        token = strtok (NULL, ",");
      }
    }

    if((read = getline(&line, &len, file)) != -1) {
      token = strtok (line, ",");
      i = 0;
      while (token != NULL)
      {
        sscanf (token, "%d", &var);
        profits[i++] = var;
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


int main(int argc, char *argv[])
{
  if(argc == 2){
    int maxIndex = 0;
    int i;
    int selectedItem; 
    readFile(argv);   /*reads from text file*/
    displayInitialValues();
    createCombinations();
    selectedItem = decideSelectedItem();
    display(selectedItem);
    printf("\n");
  }
  else{
    printf("Only one file name is required.\n");
  }
  return 0;
}
