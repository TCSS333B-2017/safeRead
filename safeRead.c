#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFERSIZE 4 

int main(){
	//example of safe fgets - which just outputs text from the file making no assumptions about the maximum line length

 char buffer[BUFFERSIZE];  //buffer will buffer the the output of fgets
 char *line=malloc(BUFFERSIZE);  //line will store hold the actual line
 
 //always check if memory was successfully allocated 
 if(!line){
		fprintf(stderr,"unable to allocate BUFFERSIZE bytes to line\n");
		return 1;
	}	
 int lineSize=BUFFERSIZE;  //must keep track of size ourselves
 int lineno=0;
 
 //instead of using strcat we will use strcpy because strcat searches for the '\0' end which makes it very slow for long strings
 //same with strlen - instead of searching for '\0' each time we will just search for it once and store the value 
 int lineStrLen=0, bufferStrLen=0;
 
 FILE *fp=fopen("test.txt","r"); //open a stream to read the contents of file test.txt
 //always check to see that it was successfully opened
 if(!fp){
		fprintf(stderr,"unable to open file text.txt\n");
	 return 1;
	}
	
 while(fgets(buffer,sizeof(buffer),fp)){
		bufferStrLen=strlen(buffer); //store the length to avoid multiple searches for \0
  while(lineSize < lineStrLen+bufferStrLen+1){ //+1 for the extra space for \0
			fprintf(stderr,"reallocating %d bytes\n",lineSize*2);
   line=realloc(line,lineSize*2);
   //check to make sure the realloc worked
   if(!line){
				fprintf(stderr,"unable to reallocate %d bytes to line\n",lineSize*2);
				return 1;
			}	
   lineSize*=2;
  }
  strcpy(line+lineStrLen,buffer); //copies string to end of line - faster than strcat 
  lineStrLen+=bufferStrLen; //update the length of the new String
  
  //now check if we have reached the end of the line - either a \n will be the last character or we will have read a line shorter than the maximum length
  if(buffer[bufferStrLen-1]=='\n'){ 
  //note that sizeof is just a lookup and is very fast   
  //note that the maximum length of the string is sizeof(buffer)-1 because of the \0
  //note that the final character is going to be buffer[bufferStrLen-1] because arrays start at index 0
   
   printf("%d %s",lineno,line);
   //reset the lineStrLen to zero because we are ready for the next line 
   lineStrLen=0;
   lineno++;
  }
	}
	//check for one edge case - it could be that the buffer will be exactly the right size for the rest of the line
 //if so then the loop will end while lineStrLen is not zero
 if(lineStrLen){
		printf("%d %s",lineno,line);
		lineno++;
	}
 fclose(fp);
 return 0;
}
