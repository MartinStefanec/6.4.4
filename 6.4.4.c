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
	list = lowl_create_empty();
	if(list == NULL)
	return NULL;
	list->beg=malloc(sizeof(OWN));
	list->cur=list->beg;
	for(i=1;i<=size;i++){
		list->cur->data =rand()%10;
//		printf("%f, ",list->cur->data);
		if(i<size){
			list->cur->next=malloc(sizeof(OWN));
			list->cur =list->cur->next; 
		} 	
			else 
				list->cur->next=NULL;
	}
	return list;
}


void lowl_destroy(LOWL *list){
	list->cur=list->beg;
	OWN *adress;
	do {
		adress=list->cur->next;
		free(list->cur);
		list->cur=adress;
	}	
	while(list->cur->next!=NULL);
	free(list);
}

void lowl_print(LOWL *list){
	OWN *pomocne;
	pomocne=list->beg;
	while(pomocne!=NULL) {
		printf("%f ",pomocne->data);
		pomocne=(OWN*) pomocne->next;	
		}
}

char lowl_cur_step_left(LOWL *list);
char lowl_cur_step_right(LOWL *list);
OWN *lowl_insert_left(LOWL* list, float val);
OWN *lowl_insert_right(LOWL* list, float val);
char lowl_delete(LOWL* list);


main(){
	LOWL *line;
	line=lowl_create_random(5);
	lowl_print(line);
}
