#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 typedef struct node{
     char tu[20];
     int tong;
     char dong[10];
     struct node* next;
 }node;
 node * root ;node *root1;
 node * cur; node *cur1;node *pre;
 node *createnode(){
     node *m = (node*)malloc(sizeof(node));
     //strcpy(m->tu,x);
     m->next = NULL;
     return m;
 }
 void delnode( node *del){
     if(del == root ){
         root = root-> next;
         free(del);
     }
 else{
     node *pre = root;
     while(pre->next != del && pre != NULL )
     pre = pre->next;
     del = pre->next;
     pre->next = pre->next->next;
     free(del);
 }

 }

 node *addnode(char x[10]){
     node*new = ( node*)malloc(sizeof(node));
     strcpy(new->tu,x);
     new-> next = NULL;
     if (root== NULL) {
         root = new;
        cur = root;
     }
     else {
         cur->next = new;
         cur = cur -> next;
     }
 }
node *add(node* p){
     node*new = ( node*)malloc(sizeof(node));
     new->next = NULL;
     if (root ==NULL ) {
         root = new;
         cur = root;
     }
     else {
         cur->next = new;
         cur = cur -> next;
     }
}
 //node * new;
int main() {
    int i,l,dem;
 FILE *f , *f1;
 char x1[50], x2[50];
 char *c;
 char buff[20];
 char s[20];
 node*nw ;
 f1 = fopen("vanban.txt","r");
while(!feof(f1)){
fscanf(f1,"%s",buff);
addnode(buff);
for(i=0;i<strlen(buff);i++)
if(isalpha(buff[i])) {
printf("%c",buff[i]);


}
printf(" ");
}

printf("\n\n");
cur = root;
dem = 0;
while(cur != NULL) {
    printf("%s %d\n",cur->tu,strlen(cur->tu));
    strcpy(s,cur->tu);
    l = strlen(s);
    for(i=0;i<l;i++)
    if(isalpha(s[i])) 
    {
   printf("%c",s[i]);
    dem = dem +1;
    }
printf(" %d ",dem);
    if (dem != l-1) {
        strcpy(cur->tu,"");
        strncpy(cur->tu,s,l-1);
    
    }
    if (dem == 0 ) delnode(cur);
    printf("\n");
    dem = 0;
    cur = cur->next;
}
cur1 = root;int z =1;
while(cur1 != NULL){
    printf("%d  %s \n",z,cur1->tu);
    cur1 = cur1 ->next;
    z++;
}


fclose(f1);

strcpy(x1,"1 2 3 4 5 6 7 8 9");
strcpy(x2,"a b c d e f g h i");

printf("\n xau x1: %s\n",x1);
printf("\n xau x2: %s\n",x2);
strncpy(x1,x2,15);
printf("\nxau moii la \n");

printf("%s\n",x1);
strcpy(x2,"");
printf("\n xau x2: %s\n",x2);
return 0;
}