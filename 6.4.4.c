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
			if(list->cur->next == NULL)
			return NULL;
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
	
	printf("\n");
	if(list->beg==NULL || list->cur==NULL){
		printf("Empty list");
	} else{
		pomocne=list->beg;
		while(pomocne!=NULL) {
			if(pomocne==list->cur){
				printf("Cursor: ");
			}
		
			printf("%f ",pomocne->data);
			pomocne=(OWN*) pomocne->next;	
			}
		}
}

char lowl_cur_step_left(LOWL *list){
	OWN *pomocne;
	
	if(list->cur==NULL || list->cur==list->beg){
		printf("\nBOUNDARY_REACHED");
		return -1;
	}
	else{
		pomocne=list->cur;
		list->cur=list->beg;
		do{
			list->cur=list->cur->next;	
		} while(
			list->cur->next!=pomocne
		);
		
		printf("\nLOWL_SUCCESS");
		return 1;
	}
}
char lowl_cur_step_right(LOWL *list){
	if(list->cur==NULL || list->cur->next==NULL){
		printf("\nBOUNDARY_REACHED");
		return -1;
	}
	else{
		list->cur=list->cur->next;
		printf("\nLOWL_SUCCESS");
		return 1;
	}
}
OWN *lowl_insert_left(LOWL* list, float val);
OWN *lowl_insert_right(LOWL* list, float val){
	OWN *pomocne;
	
	pomocne=list->cur->next;
	list->cur->next=malloc(sizeof(OWN));
	list->cur=list->cur->next;
	list->cur->data=val;
	list->cur->next=pomocne;
}
char lowl_delete(LOWL* list);


main(){
	int kolko;
	
	printf("Zadajte aky dlhy zoznam chcete (ak prazdny, tak 0): ");
	scanf("%d",&kolko);
	while(kolko<0){
		printf("Zadajte aky dlhy zoznam chcete (ak prazdny, tak 0): ");
		scanf("%d",&kolko);
	}
	
	LOWL *line;
	if(kolko==0){
		line=lowl_create_empty();
	}else{
		line=lowl_create_random(kolko);
	}
	
	lowl_print(line);
	lowl_cur_step_left(line);
	lowl_print(line);
	lowl_insert_right(line,100);
	lowl_print(line);
}
