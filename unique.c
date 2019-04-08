//Slightly incomplete unique code with mergesort implemented


#include<stdio.h>
#include<stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

char **breaks;

char **linesCHAR;
int INC=0;
char **allLines;
char **temp;
char **tempNUM;
int totalLines=1;
char *a=NULL;
int i,x;
size_t sizeAlloc=32;
size_t line;
int numLines=0;


void mergesort(char **sortMe,char **lines, int lower, int higher,char **breakPoint);
void merge(char **sortMe,char **lines,int l, int m, int h,char **breakPoint);

int main(long long int argc, char **argv) {
 
  allLines=malloc(totalLines*sizeof(char*));
  line = getline(&a,&sizeAlloc,stdin);    
  
  //Creating the list within Memory (READING IN INPUT)
  while (line!=-1){
    //Checking if the memory has grown too small for the number of lines
	if (numLines>=totalLines){
	  //Doubling the total amount of memory
	     totalLines*=2;
	     //Allocating memory to a temporary 2D array to store the current values obtained (All Lines)
	     temp=malloc(totalLines*sizeof(char*));
	     //copying the memory of each line and saving it inside the temporary variable
          for (i=0;i<totalLines/2;i++){
	    //Finding the width of each individual line (the exact amount of space required)
	     int width=strlen(allLines[i])+1;
	     //Allocating the required amount of space within the temporary variable
	     temp[i]=malloc(width);
	     //Actually copying the memory
	     memcpy(temp[i],allLines[i],width);
	  }
	  //Freeing the main storage spot
	   free(allLines);
	   //Allocating the required amount of space
	   allLines=malloc(totalLines*sizeof(char*));
	   //Copying data from temp variable to main variable
           for (i=0;i<totalLines/2;i++){
             int width=strlen(temp[i])+1;
	     //Allocating width
	     allLines[i]=malloc(width);
	     //Copying memory over
	     memcpy(allLines[i],temp[i],width);
	   }
	   //Freeing the temporary variable
	   free (temp);
	   temp=NULL;
	}       
	//What To do normally (when array isn't full)
	//Allocate appropriate amount of space
	  allLines[numLines] = malloc(strlen(a) + 1);
	  //Copy string over into AllLines
	  strcpy(allLines[numLines], a);
	  //Increment the total number of lines
          numLines++;
	   //Free the lines
	 free (a);
	 a=NULL;
	 //Get The Next Line
	 line = getline(&a,&sizeAlloc,stdin);    
   }  


  //NO ARGUMENTS PRESENTED
  if (argc==1){
    //Creating A representation of the LINE numbers
    linesCHAR=malloc(numLines*(sizeof(int*)));
    breaks=malloc(numLines*(sizeof(int*)));
    //Creating a string to track the original position of the line read throughout the many searches
    for (INC=0;INC<numLines;INC++){
      linesCHAR[INC]=malloc(sizeof(int));
      breaks[INC]=malloc(sizeof(int));
      sprintf(linesCHAR[INC],"%d",INC);
    }

   
    //merge Sorting the lines as well as the integer array converted to CHARS
    mergesort(allLines,linesCHAR,0,numLines-1,breaks);        

    //Creating temp variables for output
    temp=malloc(numLines*sizeof(char*));
    tempNUM=malloc(numLines*sizeof(int*));
    
    x=0;

    //Removing Duplicates
    for (i=0;i<numLines;i++){
      if (i==0){
        int width=strlen(allLines[i])+1;
        temp[x]=malloc(width);
        tempNUM[x]=malloc(sizeof(int));
        memcpy(temp[x],allLines[i],width);
        memcpy(tempNUM[x],linesCHAR[i],sizeof(int));
        x++;

      }
      if (i!=0&&strcmp(allLines[i],allLines[i-1])!=0){
        int width=strlen(allLines[i])+1;
        temp[x]=malloc(width);
        tempNUM[x]=malloc(sizeof(int));
	memcpy(temp[x],allLines[i],width);
        memcpy(tempNUM[x],linesCHAR[i],sizeof(int));
        x++;
      }
    }

    //Merging based on original input order
    mergesort(tempNUM,temp,0,x-1,breaks);

    //Printing out Final Output resorted and without duplicates
    printf("\n");
    for (i=0;i<x;i++){
      printf("%s",temp[i]);
    }

    //Free any memory which has not yet been released. 
    free(allLines);
    free(temp);
    free(tempNUM);
    free(a);
  }


  if (argc==2){

    breaks=malloc(numLines*(sizeof(int*)));
    for (INC=0;INC<numLines;INC++){
      breaks[INC]=malloc(sizeof(int));
    }

    
    if (strcmp((argv[1]),"-m")!=0){
	printf("ERROR: You must use the format\nunique [-m]\n");
     }
  if (argc>2){
    	printf("ERROR: You must use the format\nunique [-m]\n");
	return 0;
  }
  return 0;
}

void mergesort(char **sortMe,char **lines, int lower, int higher,char **breakPoint){
  if (lower<higher) {
    int middle =(lower+higher)/2;
    mergesort(sortMe,lines, lower, middle,breakPoint);
    mergesort(sortMe,lines, middle+1, higher,breakPoint);
    merge(sortMe,lines, lower, middle, higher,breakPoint);
  }
}

void merge(char **sort,char **lines,int l, int m, int h,char**breakPoint){
  int left = m - l + 1;
  int right = h - m;
  char **rightNUM;
  char **leftNUM;
  char **leftA;
  char **rightA;
  char **BR;
  char **BL;
  int i, j, k;

  rightNUM=malloc(right*sizeof(int*));
  leftNUM=malloc(left*sizeof(int*));
  BR=malloc(right*sizeof(int*));
  BL=malloc(left*sizeof(int*));;
  rightA=malloc(right*sizeof(int*)); 
  leftA=malloc(left*sizeof(int*));
    
  for (i = 0, j=l; i < left; i++, j++){
    int width=strlen(sort[j])+1; 
    int width2=strlen(lines[j])+1;
    leftA[i] = malloc(width);
    leftNUM[i]=malloc(width2);
    BL[i]=malloc(width2);
    memcpy(leftA[i],sort[j],width);
    memcpy(leftNUM[i],lines[j],width2);
    memcpy(BL[i],breakPoint[j],width2);
  }
    
  for (i = 0, j = m+1; i < right; i++, j++){
      int width1= strlen(sort[j])+1;
      int width2=strlen(lines[j])+1;
      rightA[i]= malloc(width1);
      rightNUM[i]=malloc(width2);
      BR[i]=malloc(width2);
      memcpy(rightNUM[i],lines[j],width2);
      memcpy(BR[i],breakPoint[j],width2);
      memcpy(rightA[i],sort[j],width1);
  }
  
  i = j = 0; k = l;
  
  while (i < left && j < right) {
    if (strcmp(leftA[i], rightA[j]) <= 0){
          allLines[k++] = leftA[i++];
	  lines[k-1]=leftNUM[i-1];
	  breakPoint[k-1]=BL[i-1];
    }else{
        allLines[k++] = rightA[j++];
	lines[k-1]=rightNUM[j-1];
	breakPoint[k-1]=BR[j-1];
    }
  }
    
  while (i <left){
    sort[k++] = leftA [i++];
    lines[k-1]=leftNUM[i-1];
    breakPoint[k-1]=BL[i-1];
  }
  while (j < right){
    sort[k++] = rightA[j++];
    lines[k-1]=rightNUM[j-1];
    breakPoint[k-1]=BR[j-1];
  }
  free(BR);
  free(BL);
  free(rightNUM);
  free(leftNUM);
  free (rightA);
  free (leftA);  
}
