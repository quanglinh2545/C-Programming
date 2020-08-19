#include<stdio.h>
void main(){
    int a,b,c,x;
    printf("Nhap vao a: ");
    scanf("%d",&a);
    printf("Nhap vao b: ");
    scanf("%d",&b);
    printf(" a= %d ; b = %d \nSau khi chuyen \n",a,b);
void change(int *c,int *d){
x = *c;
*c = *d;
*d = x;
}
change (a,b);
printf( " a= %d ; b = %d \n",a,b);
}