# include <stdio.h>
# include <stdlib.h>
# include <string.h>


typedef struct Word_t{
  char word[50];
}Word;

Word A[1000]; 

typedef struct node_t{
   char data[50];
   int count;
   char line[255];
  struct node_t *left,*right;
}node;

 node *head = NULL;

//hien thi danh sach
void printLinked( node *root){ 
    
    node * cur = root;
  //  while (cur->left != NULL) cur = cur -> left;
  //  cur = cur ->right;
    while( cur != NULL){
        if(strcmp(cur->data, "\0") != 0){
         printf("%s %d ", cur->data, cur->count);
            printf("%s",cur->line );
            printf("\n");
            }
            cur = cur -> left;
    }
}
// ham tao ra mot node cho danh sach lien ket
node *MakeNode(char *data,int count,char *line)
{
node *p = (node *)malloc(sizeof(node));
   p->left = p->right = NULL; 
    strcpy(p->data,data);
    p->count = count;
    strcpy(p->line,line);
  return p;
}

// ham them mot node vao danh sach 

node* insertNode(node *head,char *key, int count,char *line){ 
    
    if (head == NULL) return MakeNode(key,count,line); 
    if (strcmp(head->data, key) > 0) 
        head->left  = insertNode(head->left,key,count,line); 
    else if (strcmp(head->data, key) < 0) 
        head->right = insertNode(head->right, key, count,line);  
    else if (strcmp(head->data, key) == 0){
        head->count += 1;
        strcat(head->line,line);
    }
    return head; 
}

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

// ham kiem tra tu co trong stopw.txt 

int check_word(char *str,FILE *fo2)
{
  int count = read_File_Stopw(fo2);
  int a = 0;
  for (int i = 0; i < count ; i++)
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

void change(char str[]){
  for (int i = 0; i < strlen(str); i++)
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
      
      char *line = (char *)malloc(50);
      line[0] =' ';
      if(c == '\n'){
          number_line ++;
        }
        char *a = (char *)malloc(50);
        sprintf(a,"%d",number_line);
        
        strcat(line,a);

     	if( isalpha(c)){
     		strcat(buffer,str);
     		free(str);
     		char *str = (char *)malloc(1);
     	}

     	else {
     		
     		//fseek(fo,-1,SEEK_CUR);
       // c = fgetc(fo);
        
        if(c == '.' && (check_word(buffer,fo2) == 0)){
             change(buffer);
            
             head = insertNode(head,buffer,1,line);
           
        }
        if(c != '.' && (buffer[0] <= 'z' && buffer[0] >='a') && (check_word(buffer,fo2) == 0)){
         
          head = insertNode(head,buffer,1,line);
        }
        free(buffer);
          
     		char *buffer = (char *)malloc(50);
     		
     	}
      free(line);
     }
    
   fclose(fo);
}
void main()
{
	FILE * fo;
	FILE *fo2;
  readFile(fo,fo2);
  printLinked(head);
}