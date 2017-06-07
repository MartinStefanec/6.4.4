#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define BOUNDARY_REACHED	1
#define LOWL_SUCCESS	2
#define LOWL_OK	3
#define LOWL_FAIL 4

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
	if(list == NULL){
		return NULL;
	}
	
	list->cur = NULL;
	list->beg = NULL;
	return list;
}
OWN *lowl_insert_right(LOWL* list, float val){
	OWN *pomocne;
	
	if(list->beg==NULL || list->cur==NULL){
		list->beg=malloc(sizeof(OWN));
		if(list->beg == NULL){
			return NULL;
		}
		
		list->beg->data=val;
		list->beg->next=NULL;
		list->cur=list->beg;
	}else{
		if(list->cur->next!=NULL){
			pomocne=list->cur->next;
			list->cur->next=malloc(sizeof(OWN));
			if(list->cur->next == NULL){
				return NULL;
			}
		
			list->cur=list->cur->next;
			list->cur->data=val;
			list->cur->next=pomocne;
		}else{
			list->cur->next=malloc(sizeof(OWN));
			if(list->cur->next == NULL){
				return NULL;
			}
		
			list->cur=list->cur->next;
			list->cur->data=val;
			list->cur->next=NULL;	
		}
	}
	
	return list->cur;
}
LOWL *lowl_create_random(unsigned int size){
	int i;
	LOWL *list;
	
	list = lowl_create_empty();
	if(list == NULL){
		return NULL;
	}

	for(i=1;i<=size;i++){
		lowl_insert_right(list,rand()%10);
	}
	
	return list;
}
void lowl_destroy(LOWL *list){
	OWN *pomocne;
	
	if(list->cur!=NULL && list->beg!=NULL){
		list->cur=list->beg;
		if(list->cur->next==NULL){
			free(list->cur);
		}else{
			while(list->cur->next!=NULL){
				pomocne=list->cur->next;
				free(list->cur);
				list->cur=pomocne;
			}		
		
			free(pomocne);
		}
	}
	
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
			pomocne=pomocne->next;	
			}
		}	
}
char lowl_cur_step_left(LOWL *list){
	OWN *pomocne;
	
	if(list->cur==NULL || list->cur==list->beg){
		return BOUNDARY_REACHED;
	}else{
		pomocne=list->cur;
		list->cur=list->beg;
		while(list->cur->next!=pomocne){
			list->cur=list->cur->next;
		};
		
		return LOWL_SUCCESS;
	}
}
char lowl_cur_step_right(LOWL *list){
	if(list->cur==NULL || list->cur->next==NULL){
		return BOUNDARY_REACHED;
	}
	else{
		list->cur=list->cur->next;
		return LOWL_SUCCESS;
	}
}
OWN *lowl_insert_left(LOWL* list, float val){
	OWN *pomocne;
	
	if(list->beg==NULL || list->cur==NULL){
		lowl_insert_right(list,val);
		return list->cur;
	}else{
		if(list->beg==list->cur){
			list->beg=malloc(sizeof(OWN));
			if(list->beg == NULL){
				return NULL;
			}
			
			list->beg->data=val;
			list->beg->next=list->cur;
			list->cur=list->beg;
			return list->cur;
		}else{
			pomocne=list->cur;
			list->cur=list->beg;
			while(list->cur->next!=pomocne){
				list->cur=list->cur->next;
			};
			
			list->cur->next=malloc(sizeof(OWN));
			if(list->cur->next == NULL){
				return NULL;
			}
			
			list->cur=list->cur->next;
			list->cur->data=val;
			list->cur->next=pomocne;
			return list->cur;
		}
	}
}
char lowl_delete(LOWL* list){	
	OWN *pomocne;
	
	if(list->beg==NULL || list->cur==NULL){
		return LOWL_OK;
	}else{
		if(list->beg==list->cur){
			if(list->cur->next==NULL){
				list->beg=NULL;
				list->cur=NULL;
				return LOWL_OK;
			}else{
				pomocne=list->cur->next;
				free(list->cur);
				list->beg=pomocne;
				list->cur=list->beg;
				return LOWL_OK;
			}	
		}else{
			if(list->cur->next==NULL){
				pomocne=list->cur;
				lowl_cur_step_left(list);
				list->cur->next=NULL;
				free(pomocne);
				return LOWL_OK;								
			}else{
				pomocne=list->cur->next;
				lowl_cur_step_left(list);
				free(list->cur->next);
				list->cur->next=pomocne;
				list->cur=pomocne;
				return LOWL_OK;
			}
		}			
	}	
}
LOWL *lowl_divide(LOWL *list){
	LOWL *list2;
	
	if(list->beg!=NULL || list->cur!=NULL){
		list2=lowl_create_empty();
		list2->beg=list->cur->next;
		list2->cur=list2->beg;
		list->cur->next=NULL;
		lowl_print(list);
		lowl_print(list2);
		return list2;
	} else {
		printf("\nUnable to divide");
		return NULL;
	}
}
main(){
	unsigned int kolko;
	float hodnota;
	LOWL *line=NULL,*line2=NULL;
	int choice;
	
	srand(time(0));
	printf("Zadajte aky dlhy zoznam chcete (ak prazdny, tak 0): ");
	scanf("%d",&kolko);
	line=lowl_create_random(kolko);	
	lowl_print(line);
	
	do{
 		printf("\nMenu:  1. cursor right  2. cursor left  3. insert right  4. insert left  5. delete  6. Divide  7. Exit and destroy : ");
 		scanf("%d",&choice);
   
 		switch (choice){
			case 1:	lowl_cur_step_right(line);
					lowl_print(line);
					break;
			case 2:	lowl_cur_step_left(line);
					lowl_print(line);
					break;
			case 3:	printf("Enter value: ");
					scanf("%f",&hodnota);
					lowl_insert_right(line,hodnota);
					lowl_print(line);
					break;
			case 4:	printf("Enter value: ");
					scanf("%f",&hodnota);
					lowl_insert_left(line,hodnota);
					lowl_print(line);
					break;
			case 5:	lowl_delete(line);
					lowl_print(line);
					break;
			case 6:	line2=lowl_divide(line);
					break;
			case 7:	printf("Goodbye\n");
					lowl_destroy(line);
					if(line2!=NULL){
						lowl_destroy(line2);
					}
					
					break; 
       
			default: printf("Wrong Choice. Enter again\n");
                    break;
		}  
	} while (choice != 7);
}
