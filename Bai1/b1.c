
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tudien{
    char tu[20];
    int times;
    int lineApper[100];
}tudien;

typedef struct node{
    tudien data;
    struct node *left;
    struct node *right;
} node;

node *createNode(tudien x){
    node*tmp = (node*)malloc(sizeof(node));
    strcpy((tmp->data).tu,x.tu);
    (tmp->data).times = 0;
    //(tmp->data).lineApper = NULL;
    return tmp;
}

void insertNode(node ** tree, tudien val)
{
    char tu1[20];
    char tu2[20];
    int check ;

    node *temp = NULL;
    if((*tree) == NULL)
    {
        node *temp = createNode(val);
        *tree = temp;
        return;
    }
    else{
        strcpy(tu1,((*tree)->data).tu);
        strcpy(tu2,val.tu);
        check = strcmp(tu2,tu1);
        //printf("\ntu1 : %s",tu1);
        //printf("\ntu2 : %s",tu2);
        //printf("\ncheck%d",check);
        if(check < 0)
        {
            insertNode(&(*tree)->left, val);
        }
        else if(check > 0)
        {
            insertNode(&(*tree)->right, val);
        }
    }

}

node *readFile(node *root, char filename[] ){
    tudien sv;
    FILE *f;
    char tu[20];
    //char nghia[255];
    int diem;
    f = fopen(filename,"r");
    do{
        fscanf(f,"%s",sv.tu);
        insertNode(&(root),sv);
    }while(fgetc(f) != EOF);
        fclose(f);
    return root;
}


void inOrder(node *root){
    if(root != NULL){
        printf("%s",(root->data).tu);
        //printf(" - %s",(root->data).nghia);
        printf("\n");
        inOrder(root->left);
        inOrder(root->right);
        return;
    }
    return;
}



node *searchNode(node *root,char tu2[]){
    char tu1[20];
    strcpy(tu1,(root->data).tu);
    int check =0;
    check = strcmp(tu2,tu1);
    if(root == NULL || check == 0) return root;
    if(check > 0){
        return searchNode(root->right,tu2);
    }
    if(check < 0){
        return searchNode(root->left,tu2);
    }

    return NULL;
}



int main(int argc,char *argv[]) {
    int luachon;
    tudien new_tudien;
    char tutimiem[20];
    node *tudaco = NULL;
    node *head = NULL;
    node *timkiem = NULL;
    char file_name[20]  ;
    //argv[1]
    //strcpy(file_name,file_name[1]);
    // file information
    printf("\nfilename : %s",file_name);
    head = readFile(head,argv[1]);
    if(head == NULL){
        printf("\nKhong doc duoc file ! Nhap lai");
    }


    do {
        printf("Hello - Chao mung cac ban ");
        printf("\n 1 :Duyet cay va in ra cay ");
        printf("\n 2 :Them tu ");
        printf("\n 3 :Dich ");
        printf("\n 0 :Exit");
        printf("\n lua chon : ");
        scanf("%d",&luachon);
        switch(luachon){
            case 1:{
                inOrder(head);
                break;
            }
            case 2:{
                printf("\nNhap tu : ");
                fflush(stdin);
                gets(new_tudien.tu);

                //tudaco = searchNode(head,new_tudien.tu);

                if(tudaco == NULL){
                    insertNode(&head,new_tudien);
                    printf("Done!\n");
                }

                if(tudaco != NULL){
                    printf("\nDa ton tai tu nay !\n");
                    break;
                }

                break;
            }
            case 3:{
                printf("\nNhap vao tu can tim kiem : ");
                fflush(stdin);
                gets(tutimiem);

                timkiem = searchNode(head,tutimiem);

                if(timkiem == NULL){
                    printf("\nKhong co tu can tim kiem");
                }

                if( timkiem != NULL ){
                    printf("%s \n",(timkiem->data).tu);
                   //printf(" - %s\n",(timkiem->data).nghia);
                }

                // if(timkiem == NULL){
                //  printf("\nKhong co tu can tim kiem");
                // }
                break;
            }
            case 0:{
                printf("Goodbye -- See you again! \n");
                break;
            }
        }
    }while(luachon!=0);
    return 0;
}
