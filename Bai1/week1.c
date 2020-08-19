#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"function.h"

int main()
{	
	Indexnode test=NULL;
	Stopwnode stopword=NULL,propernoun=NULL; 
	
	stopword = readFileStopW(stopword);
	test = readFileIndex(test,stopword);
	test = deleteIndexNode(test,"");
	propernoun = makeProperNounList(propernoun);
	//printStopwList(propernoun);
	test = finish(test,propernoun);
	printIndexList(test);
	return 0;
}