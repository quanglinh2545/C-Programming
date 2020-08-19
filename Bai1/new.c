#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 typedef struct node{
     char tu[20];
     int dem;
     char dong[10];
     struct node* next;
 }node;
 node *createnode(char x[20]){
     node *m = (node*)malloc(sizeof(node));
     m->next = NULL;
     strcpy(m->tu,x);
     return m;
 }
 void delnode(node *head, node *del){
     if(del == head ){
         head = head-> next;
         free(del);
     }
 else{
     node *pre = head;
     while(pre->next != del && pre != NULL )
     pre = pre->next;
     del = pre->next;
     pre->next = pre->next->next;
     free(del);
 }

 }
node * addnode(node *head,char x[20]){
node * temp,*p;
temp = createnode(x);
     
     if (head == NULL) {
         head = temp;
      
    
     }
     else {
         p = head;
         while(p->next != NULL) p = p -> next;
         p -> next = temp;
     }
 return head;
}
  int search(node * head, char x[20]){
int pos = 0;
for(node * p = head; p != NULL; p = p -> next){
    if( strcmp(p -> tu,x) == 0) return pos;
pos = pos + 1;
}
return -1;
 }
 node * searchnode(node * head,node * temp){
     node * p = head;
     while (p != temp ) p = p->next;
     return p;
 }

 node * root, *cur,*root1,*root2,*root3, *dau;
 void main(){
      

FILE *f1,*f2,*f,*f3;
char buff[20],c;
int i;
int vitri = 0;
f1 = fopen("stopw.txt","r");// doc file stopw
while(!feof(f1)){
    fscanf(f1,"%s",buff);
    root1 = addnode(root1,buff);
}
fclose(f1);
cur = root1;
while( cur != NULL){
    printf("%s\n",cur->tu);
    cur = cur -> next;
}

f = fopen("ghi.txt","w"); // ghi vao file
f2 = fopen("vb.txt","r"); // doc file vanban
while (!feof(f2)){
    fscanf(f2,"%s",buff);
for(i=0;i<strlen(buff);i++)
if(isalpha(buff[i])) {
  fputc(tolower(buff[i]),f);
}
fputs(" ",f);
}
fclose(f2);
fclose(f);
f3 = fopen("ghi.txt","r"); // doc file ghi
while (!feof(f3)){
    fscanf(f3,"%s",buff);
   // strcpy(buff,strlwr(buff));
root3 = addnode(root3,buff);
}
fclose(f3);

cur = root3;
while( cur ->next->next != NULL){ // in ra file ghi
  if (search(root1,cur -> tu ) == -1)
  {
      root = addnode(root,cur->tu);
    printf("%s",cur -> tu);
     printf(" ");
  }
    cur = cur -> next;
  
}
printf("\n\n");

cur = root;          // dem so lian xuat hien
int d = 0;
while(cur != NULL){
    if (search(root,cur->tu) != -1){
if(search(root,cur -> tu) == d) cur -> dem ++;
else{ 
node * find = searchnode(root ,cur);
    find -> dem ++;
}
    }
    
    
    cur = cur -> next;
    d++;
}
printf("\n\n");
cur = root;
while(cur != NULL){
    printf("%s  %d\n",cur->tu,cur->dem);
    cur = cur->next;
}
printf(" d= %d\n",d);

 }






 