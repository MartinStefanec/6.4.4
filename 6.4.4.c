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
	if(list == NULL){
		return NULL;
	}
	
	list->cur = NULL;
	list->beg = NULL;
	return list;
}
OWN *lowl_insert_right(LOWL* list, float val){
	OWN *pomocne;
	
	pomocne=malloc(sizeof(OWN));
	if(list->beg==NULL || list->cur==NULL){
		pomocne->data=val;
		pomocne->next=NULL;
		list->beg=pomocne;
		list->cur=pomocne;
	}else{
		pomocne=list->cur->next;
		list->cur->next=malloc(sizeof(OWN));
		list->cur=list->cur->next;
		list->cur->data=val;
		list->cur->next=pomocne;
	}
	
	return list->cur;
}
LOWL *lowl_create_random(unsigned int size){
	srand(time(0));
	int i;
	LOWL *list;
	list = lowl_create_empty();
	if(list == NULL){
		printf("Unable to create list.");
		return NULL;
	}

	list->beg=malloc(sizeof(OWN));
	list->cur=malloc(sizeof(OWN));
	list->cur=list->beg;
	for(i=1;i<=size;i++){
		list->cur->data =rand()%10;
		if(i<size){
			lowl_insert_right(list,rand()%10);
		}else{
			list->cur->next=NULL;
		} 
	}
	
	return list;
}
void lowl_destroy(LOWL *list){
	OWN *pomocne;
	
	list->cur=list->beg;
	pomocne=malloc(sizeof(OWN));
	do {
		pomocne=list->cur->next;
		free(list->cur);
		list->cur=pomocne;
	}	
	while(list->cur->next!=NULL);
	
	free(pomocne);
	free(list);
}
void lowl_print(LOWL *list){
	OWN *pomocne;
	
	pomocne=malloc(sizeof(OWN));
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
		
	free(pomocne);
}
char lowl_cur_step_left(LOWL *list){
	OWN *pomocne;
	
	pomocne=malloc(sizeof(OWN));
	if(list->cur==NULL || list->cur==list->beg){
		printf("\nBOUNDARY_REACHED");
		return -1;
	}
	else{
		pomocne=list->cur;
		list->cur=list->beg;
		while(list->cur->next!=pomocne){
			list->cur=list->cur->next;
		};
		
		printf("\nLOWL_SUCCESS");
		return 1;
	}
	
	free(pomocne);
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
OWN *lowl_insert_left(LOWL* list, float val){
	OWN *pomocne,*pomocne2;
	
	pomocne=malloc(sizeof(OWN));
	pomocne2=malloc(sizeof(OWN));
	if(list->beg==NULL || list->cur==NULL){
		pomocne->data=val;
		pomocne->next=NULL;
		list->beg=pomocne;
		list->cur=pomocne;
	}else{
		if(list->beg==list->cur){
			pomocne=list->cur;
			pomocne2->data=val;
			pomocne2->next=pomocne;
			list->beg=pomocne2;
			list->cur=pomocne2;
		}else{
			pomocne=list->cur;
			list->cur=list->beg;
			while(list->cur->next!=pomocne){
				list->cur=list->cur->next;
			};
			
			list->cur->next=malloc(sizeof(OWN));
			list->cur=list->cur->next;
			list->cur->data=val;
			list->cur->next=pomocne;
		}
	}
	
	free(pomocne2);
	return list->cur;
}
char lowl_delete(LOWL* list){	
	OWN *next,*prev,*pomocne;
	
	if(list->beg==NULL || list->cur==NULL){
		printf("\nLOWL_OK");
		return 0;
	}else{
		if(list->beg==list->cur){
			if(list->cur->next==NULL){
				list->beg=NULL;
				list->cur=NULL;
				list=lowl_create_empty();
				printf("\nLOWL_OK");
				return 0;
			}else{
				pomocne=malloc(sizeof(OWN));
				pomocne=list->cur->next;
				free(list->cur);
				list->beg=pomocne;
				list->cur=list->beg;
				return 0;
			}	
		}else{
			if(list->cur->next==NULL){
				prev=malloc(sizeof(OWN));
				pomocne=malloc(sizeof(OWN));
				pomocne=list->cur;
				while(list->cur->next!=pomocne){
					list->cur=list->cur->next;
				};
				
				prev=list->cur;
				prev->next=NULL;
				free(pomocne);
				list->cur=prev;
				return 0;
			}else{
				next=malloc(sizeof(OWN));
				prev=malloc(sizeof(OWN));
				pomocne=malloc(sizeof(OWN));
				next=list->cur->next;
				pomocne=list->cur;
				list->cur=list->beg;
				while(list->cur->next!=pomocne){
					list->cur=list->cur->next;
				};
				
				prev=list->cur;
				free(pomocne);
				prev->next=next;
				list->cur=next;
				return 0;
			}
		}			
	}	
}
LOWL *lowl_divide(LOWL *list){
	OWN *pomocne;
	LOWL *list2;
	
	if(list->cur->next==NULL || list->beg==NULL || list->cur==NULL){
		printf("\nUnable to divide");
		return NULL;
	} else {
		pomocne=malloc(sizeof(OWN));
		pomocne=list->cur->next;	
		list->cur->next=NULL;
		list2=lowl_create_empty();
		list2->beg=pomocne;
		list2->cur=pomocne;
		return list2;
	}
	
}

main(){
	int kolko,hodnota;
	LOWL *line,*line2;
	int choice;
	
	printf("Zadajte aky dlhy zoznam chcete (ak prazdny, tak 0): ");
	scanf("%d",&kolko);
	while(kolko<0){
		printf("Zadajte aky dlhy zoznam chcete (ak prazdny, tak 0): ");
		scanf("%d",&kolko);
	}
	
	if(kolko==0){
		line=lowl_create_empty();
	}else{
		line=lowl_create_random(kolko);
	}
	
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
			case 3:	printf("Zadajte hotnotu: ");
					scanf("%d",&hodnota);
					lowl_insert_right(line,hodnota);
					lowl_print(line);
					break;
			case 4:	printf("Zadajte hotnotu: ");
					scanf("%d",&hodnota);
					lowl_insert_left(line,hodnota);
					lowl_print(line);
					break;
			case 5:	lowl_delete(line);
					lowl_print(line);
					break;
			case 6:	line2=lowl_divide(line);
					lowl_print(line);
					lowl_print(line2);
					break;
			case 7:	printf("Goodbye\n");
					lowl_destroy(line);
					if(line2->beg!=NULL){
						lowl_destroy(line2);
					}
					
					break; 
       
			default: printf("Wrong Choice. Enter again\n");
                    break;
		} 
  
	} while (choice != 7);
	
	
}
