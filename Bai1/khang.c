# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <ctype.h>
//#include <stdbool.h>

typedef struct
{
  char word[50];

}Word;
Word A[1000]; 

struct node  
{
   char data[50];
   int count;
   char list_line[255];
   struct node *left,*right;
};

struct node *head = NULL;

//hien thi danh sach
void printLinked(struct node *root){ 
    if (root != NULL){ 
        printLinked(root->left); 
        if(strcmp(root->data, "\0") != 0){
            printf("%s %d ", root->data, root->count);
            printf("%s",root->list_line );
            printf("\n");
            
        }
        printLinked(root->right); 
    } 
}
// ham tao ra mot node cho danh sach lien ket
struct node *MakeNode(char *data,int count,char *list_line)
{
  struct node *p = (struct node *)malloc(sizeof(struct node));
  if(p == NULL) return NULL;
  else{
   p->left = p->right = NULL; 
    strcpy(p->data,data);
    p->count = count;
    strcpy(p->list_line,list_line);
  }
  return p;
}

// ham them mot node vao danh sach 

struct node* insertNode(struct node *head,char *key, int count,char *list_line){ 
    
    if (head == NULL) return MakeNode(key,count,list_line); 
    if (strcmp(head->data, key) > 0) 
        head->left  = insertNode(head->left,key,count,list_line); 
    else if (strcmp(head->data, key) < 0) 
        head->right = insertNode(head->right, key, count,list_line);  
    else if (strcmp(head->data, key) == 0){
        head->count += 1;
        strcat(head->list_line,list_line);
    }
    return head; 
}

//kiem tra list co trong hay khong
//bool isEmpty()
//{
 //  return head == NULL;
//}


// ham doc file Stopw.txt va cho vao mang A
int  read_File_Stopw(FILE *fo2)
{
	
    int i = 0 ;

	fo2 = fopen("stopw.txt","r");
       char *buffer = (char *)malloc(50);
       
       while (fscanf(fo2, "%s", buffer) != EOF){
       	   strcpy(A[i].word,buffer);
           i++;
          
       }
      
	fclose(fo2 );
	return i;
}
// ham kiem tra tu 
int check_word(char *str,FILE *fo2)// tra ve 1 neu hai chuoi giong nhau 
{
  int count = read_File_Stopw(fo2);
  int a = 0;
  for (int i = 0; i < count ; ++i)
  {
     if(strcmp(str,A[i].word) == 0)
     {
         a = 1;
         break;
     }
  }
  return a;
}
// ham chuyen chuoi sang chuoi ky tu thuong 
void convert_nor(char str[]){
  for (int i = 0; i < strlen(str); ++i)
  {
      str[i] = tolower(str[i]);

  }
 
}
// ham doc file vanban.txt
void readFile(FILE * fo,FILE * fo2)
{
   fo = fopen("vanban.txt","r");
     
     char c;
     char *str = (char *)malloc(1);
     char *buffer = (char *)malloc(50);
     
     int number_line = 1;
    
     
     while((c= fgetc(fo)) != EOF){
     	str[0] = c;
      char *list_line = (char *)malloc(50);
      if(c == '\n'){
          number_line ++;
        }
        char *a = (char *)malloc(50);
        sprintf(a,"%d",number_line);
        list_line[0] =' ';
        strcat(list_line,a);


       
     	if( isalpha(c) != 0 ){
        
     		strcat(buffer,str);
       

     		free(str);
     		char *str = (char *)malloc(1);
     	}
     	else {
     		
     		fseek(fo,-1,SEEK_CUR);
        c = fgetc(fo);

        
        if(c == '.' && (check_word(buffer,fo2) == 0)){
             convert_nor(buffer);
            
             head = insertNode(head,buffer,1,list_line);
           
        }
        if(c != '.' && (buffer[0] <= 'z'&&buffer[0] >='a')&&(check_word(buffer,fo2) == 0)){
         
          head = insertNode(head,buffer,1,list_line);
        }
        free(buffer);
          
     		char *buffer = (char *)malloc(50);
     		
     	}
      free(list_line);
     }
    
   fclose(fo);
}
void main(int argc, char const *argv[])
{
	FILE * fo;
	FILE *fo2;
  readFile(fo,fo2);
  printLinked(head);
  
	return;
}



