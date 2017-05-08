#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct OWN{
	float data;
	struct OWN *next;
}OWN;

typedef struct{
	OWN *beg;
	OWN *cur;
}LOWL;

LOWL *lowl_create_empty (void){
	LOWL	*list;
	list = malloc(sizeof(LOWL));
	if(list == NULL)
	return NULL;
	list->cur = NULL;
	return list;
	list->beg = NULL;
	return list;
}


main(){
	LOWL *line;
	line=lowl_create_empty();
}
