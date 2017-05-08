#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct OWN{
	float data;
	struct OWN *next;
}OWN;

typedef struct{
	OWN *beg;
	OWN *cur;
}LOWL;

LOWL *lowl_create_empty (void){
	LOWL *list;
	list = malloc(sizeof(LOWL));
	if(list == NULL)
	return NULL;
	list->cur = NULL;
	return list;
	list->beg = NULL;
	return list;
}

LOWL *lowl_create_random(unsigned int size){
	srand(time(0));
	int i;
	LOWL *list;
	list = malloc(sizeof(LOWL));
	if(list == NULL)
	return NULL;
	for(i=1;i<=size;i++){
		list->cur=malloc(sizeof(OWN));
		list->cur->data =rand()%10;
		if(i<size) 	list->cur->next =list->cur; else list->cur->next=NULL;
	}
}

void lowl_destroy(LOWL *list){
	free(list);
}

void lowl_print(LOWL *list);
char lowl_cur_step_left(LOWL *list);
char lowl_cur_step_right(LOWL *list);
OWN *lowl_insert_left(LOWL* list, float val);
OWN *lowl_insert_right(LOWL* list, float val);
char lowl_delete(LOWL* list);


main(){
	LOWL *line;
}
