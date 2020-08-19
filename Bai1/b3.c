#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct qa{
   char word[100];
   int time ;
   char line[100];
}wor;
int sotu(FILE *f){
 int n = 0;
 char test[100];
 while (!feof(f)){
	 fscanf(f,"%s",test);
	 n++;
 }
 return n;
}
int find_Dtu(FILE *f, wor *a)
{   int i = 0;
    char test[100];
  while (!feof(f)){
	  fscanf(f,"%s",a[i].word);
	  if(i > 0)
	  {   int k = strlen(test);
	      if(isalpha(test[k-1]) && 64 < a[i].word[0] && a[i].word[0]<91) { 
	      	 }
		  else 
		   {  strcpy(test,a[i].word);
		     continue;		   	
			 }	   
	  }
	  strcpy(test,a[i].word);
      i++;
	  }   
	  strcpy(a[0].word,a[i-1].word);
	  i--;
     return i;
}

int fix_word(wor *a,wor *b, int m)
{   
	int n = strlen((*a).word);
	int i;
	int j = 0;
	for(  i = 0 ; i < n ; i++ ) 
	{
	   if(isalpha((*a).word[i]))	j++;
	}
	if( j == 0 ) return 0;
	for( j = 0 ; j < m ; j++)
	  {
	  	if ( strcmp((*a).word,b[j].word) == 0) return 0;
	  }
	char test[100];
	 j = 0 ;
	 int k = n;
	for( i = 0 ; i < n ; i++)
	{    
		if(isalpha((*a).word[i]))
		{  
           char b  = (*a).word[i];
		   test[j] = b;
		   	j++;
		}
		else k--;
	}
	memset((*a).word, '\0', sizeof((*a).word));
		strncpy((*a).word,test,k);
   return 1;
}
void sapxep(wor* a, int i){
	int n;
	for(n = 0 ; n < i ; n++)
	{
		int j;
		for( j = 0; j < n ; j ++)
		{
			if(strcmp(a[j].word,a[n].word) > 0)
			{
				wor b;
				b = a[n];
				a[n] = a[j];
				a[j] = b;
			}
		}
	}
}
int docfile(FILE *f, wor* a,wor *b, int n,wor *c, int num_dtu)
{  
      int i = 0;
      while (!feof(f)){
	  fscanf(f,"%s", a[i].word);
	  int test = fix_word(&a[i],c,num_dtu);
	  if(test == 0 )continue;
	   strlwr(a[i].word);
	   test = fix_word(&a[i],b,n);
	  if(test == 0 )continue;
	  int j = 0;
	  for ( j = 0 ; j < i ; j++)
	  { 
		 if ( strcmp(a[i].word,a[j].word) == 0) { a[j].time++, i--;
	
		 } 
	  }
	  i++;
	  }
	  return i;
}
void getline(wor *a,int n, FILE *f,wor *dt, int num_Dtu)
{  char test[1000];
   int k  = 1;
   char line[1000];
   char test1[101];
  while(!feof(f))
   {  sprintf(line,"%d",k);
     fgets(test,1000,f);
     char *word = strtok(test," ");
     int cot = 1;
     while( word != NULL)
     { 
         int i;
		for(i = 0 ; i < n ; i++)
		{    int j, dem = 0;
		for (j = 0 ; j < num_Dtu; j++)
		{
		  if(strcmp(dt[j].word,word) == 0) dem = 1;
		}
		  if( dem == 1){}
		  else strlwr(word);
		    int m = strlen(a[i].word);
		     if(strncmp(a[i].word,word,m) == 0 && !isalpha(word[m]))
		      {
			   char ct[100];
			    strcat(a[i].line,",(");
			    strcat(a[i].line,line);
			    strcat(a[i].line,",");
			    sprintf(ct,"%d",cot);
			    strcat(a[i].line,ct);
			    strcat(a[i].line,")");
			  }
		}  
		word = strtok(NULL," ");
		cot++;
	 }
     k++;
   }
}
int main(){
FILE *f, *f1;
	if ((f = fopen("vanban.txt", "r")) == NULL)
	{
	 printf("khong mo duoc  vanban.txt file.\n ");
     	exit(1);
	}
	if ((f1 = fopen("stopw.txt", "r")) == NULL)
	{
	  printf("khong mo duoc  stopw.txt file.\n ");
     	exit(1);
	}
	
    int n = sotu(f);
    rewind(f);
	wor *a;
	a = (wor*)malloc(n * sizeof(wor));
	wor *dtu;
	dtu = (wor*)malloc(n* sizeof(wor));
	n = sotu(f1); 
	rewind(f1);  
	wor *stopw;
	stopw = (wor*)malloc(n* sizeof(wor));
	n = 0;
      while (!feof(f1)){
	  fscanf(f1,"%s", stopw[n].word);
	  n++;
       }
       rewind(f);
   int num_dtu = find_Dtu(f,dtu);   
    rewind(f);
       int j;
       int i = docfile(f,a,stopw,n,dtu,num_dtu);  
      sapxep(a,i);
      rewind(f);
      getline(a,i,f,dtu,num_dtu);
      
      for ( j = 0 ; j < i; j++)
     {
        printf("%s %d%s\n",a[j].word, a[j].time+1,a[j].line);
    }
  fclose(f);
  free(a);
}


