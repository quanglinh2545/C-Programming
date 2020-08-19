#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Line
{
	int value;
	struct Line *next;
};
typedef struct Line *linenumber;

struct Index{
	char word[30];
	int number;
	linenumber line;
	struct Index *next;
};
typedef struct Index* Indexnode;

struct StopList
{
	char stopword[20];
	struct StopList *next;
};
typedef struct StopList *Stopwnode;
//----------------------------------------------------------------
Indexnode readFileIndex(Indexnode head,Stopwnode headstopw);
Stopwnode readFileStopW(Stopwnode head);

Indexnode createIndexNode(char word[],int line);
Stopwnode createStopwNode(char word[]);
linenumber createLineNode(int line);

Indexnode addIndexNode(Indexnode head,char word[],int line);
Stopwnode addStopwNode(Stopwnode head,char word[]);
linenumber addLine(linenumber head,int line);

Indexnode deleteIndexNode(Indexnode head,char word[]);

void printIndexList(Indexnode head);
void printStopwList(Stopwnode head);

int isLineExist(linenumber head,int line);  //0-Dong chua ton tai trong list  1-Ton tai 
int cmpStopw(Stopwnode head,char word[]);  //0-Khong ton tai trong stopwlist 1-ton tai trong stopwlist 
Stopwnode makeProperNounList(Stopwnode head);
int lastCheck(char word[], Stopwnode headstopw); //0-Khong ton tai trong propernoun 1- Ton tai trong propernoun
Indexnode finish(Indexnode head,Stopwnode headstopw);

//----------------------------------------------------------------
Indexnode finish(Indexnode head,Stopwnode headstopw){
	Indexnode temp = head;
	int i;
	while(temp!=NULL)
	{
		if (lastCheck(temp->word,headstopw)==1)
			{
				head = deleteIndexNode(head,temp->word);
			}	
		temp=temp->next;
	}
	return head;
}
//----------------------------------------------------------------
int lastCheck(char word[], Stopwnode headstopw){
	if (headstopw==NULL) return 0;
	if (strcmp(word,headstopw->stopword)==0) return 1;
	return lastCheck(word,headstopw->next);
}
//----------------------------------------------------------------
Stopwnode makeProperNounList(Stopwnode head){
	FILE *fptr;
	char c;
	int i=0;
	char buff[30],temp[1];
	if((fptr = fopen("vanban.txt","r")) == NULL) 
		{
			printf("Error! opening file\n");
			exit(1);
		}
	i=0;
	memset(buff,0,30);
	c = fgetc(fptr);
	while (c!=eof())
	{	
		if ( isalpha(c) ) 
		{	
			c=fgetc(fptr);
			if(c!=eof() && c==' ')     // Neu (alpha) (Chu in hoa) thi cho vao trong propernounlist 
			{
				c= fgetc(fptr);
				if(c>='A' && c<='Z')
				{
					while(isalpha(c))
					{
						c = tolower(c);
						buff[i] = c;
						i++;
						c=fgetc(fptr);
					}
					head = addStopwNode(head,buff);
					i=0;
					memset(buff,0,30);
				}
			}
		}
		c=fgetc(fptr);
	}

	fclose(fptr);
	return head;
}
//----------------------------------------------------------------
Stopwnode readFileStopW(Stopwnode head){
	FILE *fptr;
	char  buff[50];
	char c;
	int i;
	if((fptr = fopen("stopw.txt","r")) == NULL) 
		{
			printf("Error! opening file\n");
			exit(1);
		}
	while(!feof(fptr))
	{
		fscanf(fptr,"%s",buff);
		c= fgetc(fptr);
		for(i=0;i<strlen(buff);i++) buff[i]=tolower(buff[i]);
		head = addStopwNode(head,buff);
	}
	fclose(fptr);
	return head;
}
//----------------------------------------------------------------
int cmpStopw(Stopwnode head,char word[]){
	Stopwnode temp = head;
	while (temp!= NULL && strcmp(word, temp->stopword)!=0)
	{
		temp=temp->next;
	}
	if (temp==NULL) return 0;
	else return 1;
}
//----------------------------------------------------------------
Indexnode readFileIndex(Indexnode head,Stopwnode headstopw)
{
	FILE *fptr;
	char c;
	int line = 1,i=0;
	char buff[30],temp[1];
	if((fptr = fopen("vanban.txt","r")) == NULL) 
		{
			printf("Error! opening file\n");
			exit(1);
		}
	c = fgetc(fptr);
	c = tolower(c);
	memset(buff,0,30);
	while (c!=eof())
	{
		if (!isalpha(c)) 
		{	
			if(cmpStopw(headstopw,buff)==0) head = addIndexNode(head,buff,line);
			i=0;
			memset(buff,0,30);
			if(c =='\n') line++;
		}
		else
		{	
			buff[i] = c;
			i++;
			//strcat(buff,temp);
		}
		c = fgetc(fptr);
		c= tolower(c);
	}

	fclose(fptr);
	return head;
}
//----------------------------------------------------------------
Indexnode createIndexNode(char word[],int line){ // Tao node
    Indexnode temp; 
    temp = (Indexnode)malloc(sizeof(struct Index)); 
    temp-> line = (linenumber)malloc(sizeof(struct Line));     
    temp->next = NULL;
    strcpy(temp->word,word);       
    temp->number = 1;
    temp -> line -> value= line;
    temp -> line -> next = NULL;
    return temp;
}
//----------------------------------------------------------------
int isLineExist(linenumber head,int line){	
	linenumber temp=head;
	while(temp!=NULL)
	{
		if(temp->value == line) return 1;
		temp = temp -> next;
	}
	return 0;
}
//----------------------------------------------------------------
linenumber createLineNode(int line){
	linenumber temp;
	temp = (linenumber)malloc(sizeof(struct Line));
	temp -> value =line;
	temp -> next = NULL;
	return temp;
}
//----------------------------------------------------------------
linenumber addLine(linenumber head,int line){
	if (head == NULL) return createLineNode(line);
	else
	{
		linenumber temp = head;
		while (temp->next != NULL) temp =temp->next;
		temp ->next  = createLineNode(line);
		return head;
	}	
}
//----------------------------------------------------------------
Indexnode addIndexNode(Indexnode head, char word[],int line){	
	if (head == NULL)	return createIndexNode(word,line);
	if ( strcmp(word,head-> word) == 0)
	{
		head -> number++;
		if (isLineExist(head->line,line)==0)
		{
			addLine(head->line,line);
		}
		return head;
	}
	else if ( strcmp(word,head-> word) == -1)
	{
		Indexnode temp = createIndexNode(word,line);
		temp->next = head;
		return temp;
	}
	else head->next = addIndexNode(head->next,word,line);
}
//----------------------------------------------------------------
Indexnode deleteIndexNode(Indexnode head,char word[])
{
	Indexnode pre=head,pre2;
	if ( strcmp(word,head->word) ==0)
	{
		head = pre->next;
		free(pre);
		return head;
	}
	else
	{
		while(pre != NULL && strcmp(word,pre->word) !=0 )
		{
			pre2=pre;
			pre= pre->next;
		}
		if (pre==NULL) return head;
		pre2->next = pre ->next;
		free(pre);
		return head;		
	}
}
//----------------------------------------------------------------
void printIndexList(Indexnode head){
	if (head == NULL) return;
	else
	{
		printf("\t%-20s%d",head->word,head->number );
		while(head->line != NULL) 
		{
			printf(", %d", head->line->value);
			head->line = head->line->next;
		}
		printf("\n");
	}
	return printIndexList(head->next);
}
//----------------------------------------------------------------
Stopwnode createStopwNode(char word[]){
	Stopwnode temp;
	temp = (Stopwnode)malloc(sizeof(struct StopList));
	strcpy(temp-> stopword,word);
	temp->next =NULL;
	return temp;
}
//----------------------------------------------------------------
Stopwnode addStopwNode(Stopwnode head,char word[])
{
	if( head == NULL) return createStopwNode(word);
	if( strcmp(word,head->stopword) == -1)
	{
		Stopwnode temp = createStopwNode(word);
		temp->next = head;
		return temp;
	}
	else head->next = addStopwNode(head->next,word);
}
//----------------------------------------------------------------
void printStopwList(Stopwnode head){
	if (head == NULL) return;
	else{
		printf("\t%-15s\n",head->stopword );
		printStopwList(head->next);
	}
}