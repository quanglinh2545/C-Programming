#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_WORD 30
#define MAX_LINE 1000
#define MAX_SIZE 500
typedef struct DATA{
    char word[MAX_WORD];
    int number;
    int line[MAX_SIZE];
    int col[MAX_SIZE];
}DATA;
int size1=MAX_SIZE,size2=MAX_SIZE;
char *Tolower(char s[]){
    for (int i=0;i<strlen(s);i++){
        if(isupper(s[i])) s[i] = s[i]+32;
    }
    return s;
}
void Xu_ly(char s[]){
    int n = 0;
    char str[MAX_WORD];
  for (int i= 0;i<strlen(s);i++) if(isalpha(s[i])) str[n++] = s[i];
  str[n]='\0';
  strcpy(s,str);
}
int check_with_stopw(char s[],char stopw[][MAX_WORD],int num_stop){
    for (int i = 0; i<num_stop;i++)
        if (strcmp(Tolower(s),stopw[i]) == 0) return 0;    
    return 1;
}
void Scan_file_stopw(FILE *file, char  s[][MAX_WORD],int *num_stop){
    int i = 0;
    *num_stop = 0;
    while(!feof(file)){
        char a[MAX_WORD];
        fscanf(file,"%s%*c",a);
        if (feof(file)) break;
        strcpy(s[i++],Tolower(a));
        *num_stop +=1;
    }
}
int Find(char s[],DATA data[],int num){
    Tolower(s);
    for (int i=0;i<num;i++){
        if(strcmp(s,data[i].word) == 0) return i;
    }
    return -1;
}
void Add_word(char s[],DATA data[],int *num,int line,int col){
    int check_find = Find(s,data,*num);
    char k[MAX_WORD];
    if (check_find != -1){
        data[check_find].line[data[check_find].number] = line;
        data[check_find].col[data[check_find].number] = col;
        data[check_find].number++;
    }
    else {
        strcpy(data[*num].word,s);
        data[*num].number =1;
        data[*num].line[data[*num].number-1] = line;
        data[*num].col[data[*num].number-1] = col;
        *num +=1;
    }
}
void Scan_file_test(FILE *file, DATA s[],int *num, char stopw[][MAX_WORD],int num_stop){
    *num = 0;
    int line = 1;
    int check;
    int check1 = 1;
    int col = 0;
    while(!feof(file)){
        char get_line[MAX_LINE];
        fgets(get_line,MAX_LINE,file);
        char *token = strtok(get_line," ");
        while(token!=NULL){
            col++;
            char a[MAX_WORD];
            strcpy(a,token);
            if (a[strlen(a)-1]=='.') check = 0;
            else check = 1;
            Xu_ly(a);
            if(a[0]=='\0'){
                token = strtok(NULL," ");
                continue;
            }
            if(isupper(a[0]) && check1 == 1){
                token = strtok(NULL," ");
                continue;
            }
            Tolower(a);
            if(check_with_stopw(a,stopw,num_stop)) Add_word(a,s,&*num,line,col);
            check1 = check;
            token = strtok(NULL," ");
        }
        line ++;
        col = 0;
    }
}
void WriteFile(FILE *file , DATA s[],int num){
    for(int i =0;i<num;i++){
        fprintf(file,"%s %d,",s[i].word,s[i].number);
        for(int j = 0; j<s[i].number; j++){
            fprintf(file,"(%d,%d)",s[i].line[j],s[i].col[j]);
            if(j!= s[i].number-1) fprintf(file,",");
        }
        fprintf(file,"\n");
    }
}
void Sort(DATA s[],int num){
    for (int i = 0;i<num;i++)
        for(int j= i+1;j<num;j++)
            if (strcmp(s[i].word,s[j].word)>0){
                DATA tmp = s[i];
                s[i]=s[j];
                s[j]=tmp;
            }        
}
void Display(DATA s[],int num){
    for(int i =0;i<num;i++){
        printf("%s %d,",s[i].word,s[i].number);
        for(int j = 0; j<s[i].number; j++){
            printf("(%d,%d)",s[i].line[j],s[i].col[j]);
            if(j!= s[i].number-1) printf(",");
        }
        printf("\n");
    }
}
int main(){
    FILE *vanban = fopen("vanban.txt","r");
    FILE *stopw = fopen("stopw.txt","r");
    FILE *ketqua = fopen("ketqua.txt","w");
    if(!vanban){
        printf("File vanban.txt not found");
        return 0;
    }
    if(!stopw){
        printf("File stopw.txt not found");
        return 0;
    }
    char string_stopw[MAX_SIZE][MAX_WORD];
    int num_stop;
    Scan_file_stopw(stopw,string_stopw,&num_stop);

    DATA *string_test = (DATA *)malloc(sizeof(DATA)*MAX_SIZE);
    int num_test;
    Scan_file_test(vanban,string_test,&num_test,string_stopw,num_stop);
    Sort(string_test,num_test);
    WriteFile(ketqua,string_test,num_test);
    Display(string_test,num_test);

    fclose(vanban);
    fclose(ketqua);
    fclose(stopw);
    free(string_test);
    return 0;
}