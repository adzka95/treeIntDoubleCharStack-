#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int global_find;
struct node{
	void* value;
	char name;
	struct node *next, *prev, *father;
	int proba;

};

struct stack
{
	int number;
	int value;
	struct stack *next;
};

void print_stack(void* top){
	struct stack*temp=(struct stack*)top;
	printf("stos %d ",temp->number);
	if(temp->value!=NULL)
		printf("%d ", temp->value);
	while(temp->next!=NULL){
		printf(":%d ", temp->next->value);
		temp=temp->next;
	}

}
void print_node(struct node obj){
	if(&obj!=NULL){
		if(obj.name=='I')
			printf("%d ", obj.value );
		if(obj.name=='D'){
			double temp;
			temp=*(double*)(obj.value);
			printf("%f ",temp);
		}
		if(obj.name=='C')
			printf("%s ", obj.value);
		if(obj.name=='S')
			print_stack(obj.value);
	}
}

void print_all(struct node obj){
	if(&obj!=NULL){
		if(obj.name=='S'||obj.name=='I'||obj.name=='D'||obj.name=='C'){
			if(obj.prev!=NULL)
				print_all(*obj.prev);
			if(obj.value!=NULL) {
				print_node(obj);
			}
			if(obj.next!=NULL)
				print_all(*obj.next);	
		}
	}
}

int compare_c(void* root_c, void* neew_c){
	char *root_s=(char*)root_c;
	char *neew_s=(char*)neew_c;
	int i=0;
	while(root_s[i]!=0&&neew_s[i]!=0){
		if(root_s[i]==neew_s[i])
			i++;
		else{
			if(root_s[i]>neew_s[i])
				return 0;
			else 
				return 1;
		}
	}

//jesli nowy dalej w alfabecie to 1
return 1;
}

struct node* find(struct node*root, char what, void* val, int stack_n){
	if(root->name=='I'){
		if(what=='I')
			if(root->value==val)
				return root;
			
		if(what=='D'||what=='S'||what=='C'||((root->value)>val))
			if(root->prev==NULL)
				return NULL;
			else
				return find(root->prev, what, val, stack_n);
		else
			if(root->value<val)
			if(root->next==NULL)
				return NULL;
			else 
				return find(root->next, what, val, stack_n);	
	}
	if(root->name=='D'){
		if(what=='S'||what=='C'){
			if(root->prev==NULL)
				return NULL;
			else
				return find(root->prev, what, val, stack_n);		
		}
		else 
			if(what=='I'){
					if(root->next!=NULL)
							return find(root->next, what, val, stack_n);
						else
							return NULL;				
				}
			else
			if(what=='D'){
				double *root_wsk=(double*)malloc(sizeof(double));
				double *neew_wsk=(double*)malloc(sizeof(double));
				double root_v, neew_v;
				*root_wsk=(*(double*)root->value);
				root_v=*root_wsk;
				*neew_wsk=(*(double*)val);
				neew_v=*neew_wsk;
				free(root_wsk);
				free(neew_wsk);
				if(neew_v==root_v)
					return root;
				if(root_v>neew_v){
					if(root->prev!=NULL)
						return find(root->prev, what, val, stack_n);
					else
						return NULL;
				}
				else 
					if (root_v<neew_v){
					if(root->next!=NULL)
						return find(root->next, what, val, stack_n);
					else
						return NULL;
				}
			}	
	}
	if(root->name=='C'){
		if(what=='D'||what=='I'){
			if(root->next!=NULL)
						return find(root->next, what, val, stack_n);
					else
						return NULL;	
		}
		if(what=='S'){
			if(root->prev!=NULL)
						return find(root->prev, what, val, stack_n);
					else
						return NULL;	
		}
		if(what=='C'){
			if(compare_c(root->value, val)&&compare_c(val,root->value))
				return root;
			if(compare_c(root->value, val)==1)
				if(root->next!=NULL)
						return find(root->next, what, val, stack_n);
					else
						return NULL;	
			if(compare_c(root->value, val)==0)
				if(root->prev!=NULL)
						return find(root->prev, what, val, stack_n);
					else
						return NULL;
		}
	}
	if(root->name=='S'){
		if(what=='D'||what=='I'||what=='C')
				if(root->next!=NULL)
						return find(root->next, what, val, stack_n);
					else
						return NULL;
		if(what=='S'){
		struct stack *root_stack=(struct stack*)root->value;
				if(root_stack->number==stack_n)
					return root;
				if(root_stack->number>stack_n)
					if(root->prev!=NULL)
						return find(root->prev, what, val, stack_n);
					else
						return NULL;
				if(root_stack->number<stack_n)
					if(root->next!=NULL)
						return find(root->next, what, val, stack_n);
					else
						return NULL;
		}	
	}
}

void stack_push(struct node *root, int val, int stack_n){
	struct node *temp;
	struct stack *begin;
	temp=find(root, 'S', "", stack_n);
	if(temp!=NULL){
		begin=(struct stack*)(temp->value);
		if(begin->value!=NULL){
			struct stack *top=(struct stack*)malloc(sizeof(struct stack));
			while(begin->next!=NULL)
				begin=begin->next;
			begin->next=top;
			top->number=begin->number;
			top->next=NULL;
			top->value=val;
		}
		else
			begin->value=val;
	}
	else
		printf("Nie znaleziono stosu. ");
}

void stack_pop(struct node*root, int stack_n){
	struct node *temp;
	struct stack *begin;
	temp=find(root, 'S', "", stack_n);
	if(temp!=NULL){
		begin=(struct stack*)(temp->value);
		if(begin->value!=NULL){			
			if(begin->next!=NULL){
				while(begin->next->next!=NULL)
					begin=begin->next;				
				free(begin->next->next);
				begin->next=NULL;
				
			}
			else{				
				begin->value=NULL;
			}
		}
		else
			printf("Stos pusty");
	}
	else
		printf("Nie znaleziono stosu. ");
}

void add_node(struct node* root, char what, void* val, int stack_n){
	if(root->name==NULL){
		if(what=='I'||what=='C'){
			root->name=what;
			root->value=val;			
		}
		else 
			if(what=='D'){
				double *div=(double*)malloc(sizeof(double));
				*div=(*(double*)val);
				root->name=what;
				root->value=div;				
			}
			else if(what=='S'){
				struct stack* div=(struct stack*)malloc(sizeof(struct stack));
				div->next=NULL;
				div->number=stack_n;
				div->value=NULL;		
				root->name=what;
				root->value=div;			
			}
	}
	else{//gdy korzen nie pusty
		if(root->name=='I'){
			if(what=='S'||what=='C'||what=='D'||(what=='I'&&root->value>val)){
				if(root->prev!=NULL)
					add_node(root->prev, what, val, stack_n);
				else{				
					struct node *neew = (struct node*)malloc(sizeof(struct node));
					root->prev=neew;
					neew->father=root;					
					neew->name=what;
					neew->next=NULL;
					neew->prev=NULL;
					if(what!='D'){
						neew->value=val;
					}
					else{
						double *div=(double*)malloc(sizeof(double));
						double zmienna;
						*div=(*(double*)val);
						zmienna=*div;
						neew->value=div;					
					}
				}
			}
			else{
				if(root->next!=NULL)
					add_node(root->next, what, val, stack_n);
				else{
					struct node *neew = (struct node*)malloc(sizeof(struct node));
					root->next=neew;
					neew->father=root;
					neew->name=what;
					neew->next=NULL;
					neew->prev=NULL;
					if(what!='D'){
					neew->value=val;
					}
					else{
						double *div=(double*)malloc(sizeof(double));
						double zmienna;
						*div=(*(double*)val);
						zmienna=*div;
						neew->value=div;					
					}
				}
			}
		}
		else
			if(root->name=='D'){
				if(what=='I')
					if(root->next!=NULL)
						add_node(root->next, what, val, stack_n);
					else{
						struct node *neew = (struct node*)malloc(sizeof(struct node));
						root->next=neew;
						neew->father=root;
						neew->value=val;
						neew->name=what;
						neew->next=NULL;
						neew->prev=NULL;						
					}
				else{
					if(what=='D'){
						double root_val, new_val;
						root_val=(*(double*)root->value);
						new_val=(*(double*)val);
						if(root_val>new_val){
							if(root->prev!=NULL)
								add_node(root->prev, what, val, stack_n);
							else{
								struct node *neew = (struct node*)malloc(sizeof(struct node));
								double *div=(double*)malloc(sizeof(double));
								double zmienna;
								*div=(*(double*)val);
								zmienna=*div;
								root->prev=neew;
								neew->father=root;
								neew->value=val;
								neew->name=what;
								neew->value=div;
								neew->value=val;
								neew->next=NULL;
								neew->prev=NULL;								
							}				
						}
						else{
							if(root->next!=NULL)
								add_node(root->next, what, val, stack_n);
							else{
								struct node *neew = (struct node*)malloc(sizeof(struct node));
								double *div=(double*)malloc(sizeof(double));
								double zmienna;
								*div=(*(double*)val);
								zmienna=*div;
								root->next=neew;
								neew->father=root;
								neew->value=val;
								neew->name=what;
								neew->value=div;								
								neew->next=NULL;
								neew->prev=NULL;
							}						
						}
					}					
					else{
						if(root->prev!=NULL)
							add_node(root->prev, what, val, stack_n);
						else{
							struct node *neew = (struct node*)malloc(sizeof(struct node));
							root->prev=neew;
							neew->father=root;
							neew->value=val;
							neew->name=what;
							neew->value=val;
							neew->next=NULL;
							neew->prev=NULL;
						}
					}					
				}
			}
			if(root->name=='C'){
				if(what=='I'||what=='D'||what=='C'&&compare_c(root->value,val)==1){
					if(root->next!=NULL)
						add_node(root->next, what, val, stack_n);
					else{
						struct node *neew = (struct node*)malloc(sizeof(struct node));
						root->next=neew;
						neew->father=root;
						neew->value=val;
						neew->name=what;
						neew->value=val;
						neew->next=NULL;
						neew->prev=NULL;						
					}
				}
				else{
					if(root->prev!=NULL)
							add_node(root->prev, what, val, stack_n);
						else{
							
							struct node *neew = (struct node*)malloc(sizeof(struct node));
							if(what=='S'){
								struct stack *div=(struct stack*)malloc(sizeof(struct stack));
								div->next=NULL;
								div->number=stack_n;
								div->value=NULL;
								neew->value=div;
							}
							else{
								neew->value=val;
							}
							root->prev=neew;
							neew->father=root;							
							neew->name=what;							
							neew->next=NULL;
							neew->prev=NULL;
						}
				}
			}
			if(root->name=='S'){
				struct stack *root_stack=(struct stack*)root->value;
				if(what=='S'&&root_stack->number>=stack_n){//prev
					if(root->prev!=NULL)
						add_node(root->prev, what, val, stack_n);
					else{
						struct node *neew = (struct node*)malloc(sizeof(struct node));
						struct stack *div=(struct stack*)malloc(sizeof(struct stack));
						div->next=NULL;
						div->number=stack_n;
						div->value=NULL;
						neew->value=div;
						root->prev=neew;
						neew->father=root;					
						neew->name=what;						
						neew->next=NULL;
						neew->prev=NULL;						
					}
				}
				else{//next
					if(root->next!=NULL)
							add_node(root->next, what, val, stack_n);
					else{
						struct node *neew = (struct node*)malloc(sizeof(struct node));
						if(what=='S'){
							struct stack *div=(struct stack*)malloc(sizeof(struct stack));
							div->next=NULL;
							div->number=stack_n;
							div->value=NULL;
							neew->value=div;	
						}
						else
							neew->value=val;
						root->next=neew;
						neew->father=root;
						neew->name=what;						
						neew->next=NULL;
						neew->prev=NULL;
						if(what=='I'&&what=='C'){
							neew->value=val;
						}
						else
						{
							double *div=(double*)malloc(sizeof(double));
							double zmienna;
							*div=(*(double*)val);
							zmienna=*div;
							neew->value=div;
						}
					}
				}
			}
	}
}

void add(struct node* root, char what, void* val, int number, int stack_n){	
	for (; number > 0; number--)	
		add_node(root, what, val, stack_n);
	
};

struct node * min(struct node* root){
	while(root->prev!=NULL)
		root=root->prev;
	return root;
}

struct node * max(struct node* root){
	while(root->next!=NULL)
		root=root->next;
	return root;
}

struct node *next(struct node *root, char what, void *val, int stack_n){
	
	struct node *temp;
	struct node *div;
	div=find(root, what,val, stack_n);	
	if(div!=NULL){
		temp=div->father;
		if(div->next!=NULL)
			return min(div->next);	
		while(temp!=NULL && temp->prev!=div){
			div=temp;
			temp=temp->father;	
		}
		return temp;
	}
	else{
		printf("Nie znalezionow wartosci");
		return NULL;	
	}
}

struct node *prev(struct node *root, char what, void *val, int stack_n){
	
	struct node *temp;
	struct node *div;
	div=find(root, what,val, stack_n);	
	if(div!=NULL){
		temp=div->father;
	if(div->prev!=NULL)
		return max(div->prev);	
		while(temp!=NULL && temp->next!=div){
			div=temp;
			temp=temp->father;	
		}
		return temp;
	}
	else{
		printf("Nie znalezionow wartosci");
		return NULL;	
	}
}
void delete_stack(struct node *root,struct node*del, int stack_n){
	struct stack *temp= (struct stack *)del->value;
	while(temp->next!=NULL)
		stack_pop(root, stack_n);

}

void print_help(){
		printf("\nPomoc\n");
		printf("A - dodaj element\t A <co> <jakie/ktory stos> <ile>\n");
		printf("A - dodaj stos\t\t A S <numer stosu>\n");
		printf("D - usun element\t D <co> <jakie/ktory stos> <ile>\n");
		printf("P - poprzednik\t\t P <co> <jakie>\n");
		printf("N - nastepnik\t\t N <co> <jakie>\n");
		printf("B - push\t\t B <jakie> <ile> <gdzie>\n");
		printf("C - pop\t\t\t C <ile> <gdzie>\n");
		printf("S - stan drzewa\n");
		printf("H - pomoc\n");
		printf("Q - zakoncz\n");

}

void re_move( struct node * root,struct node *del){
	
	if(del==NULL) return;
	if(del->next==NULL && del->prev==NULL){
		if(del->father==NULL){
			del->name=NULL;	
			del->value=NULL;
		}
		else if(del==del->father->prev){
			del->father->prev=NULL;	
			free(del);
		}
		else{
			del->father->next=NULL;
			free(del);
		}
	}
	else 
		if(del->next==NULL||del->prev==NULL){
			if(del->next==NULL){
				if(del->father==NULL){
					del->next=NULL;
						root=del->next;
				}
				else
					if(del->father->next==del){
						del->father->next= del->prev;
						del->prev->father=del->father;
						free(del);
					}
					else 
						if(del->father->prev==del){
							del->father->prev= del->prev;
							del->prev->father=del->father;
							free(del);
						}			
			}
			else
				if(del->prev==NULL){
					if(del->father==NULL){
						del->prev=NULL;
						root=del->prev;

						
					}
					else 
						if(del->father->prev==del){
							del->father->prev=del->next;
							del->next->father=del->father;
							free(del);
						}
						else if (del->father->next==del){
							del->father->next=del->next;
							del->next->father=del->father;	
							free(del);
						}
				}		
			
		}
		else{
			struct node *temp;
			temp=min(del->next);
			del->value=temp->value;
			del->name=temp->name;
			re_move( root, temp);		
		}
}
void delete_all(struct node* root, char what, void* val, int number, int stack_n){
	struct node *temp=find(root, what, val,stack_n);
	for (; number > 0; number--){
		temp=find(root, what, val,stack_n);
		if(temp->name=='D')
			free(temp->value);
		if(temp->name=='S')
			delete_stack(root, temp,stack_n);
		re_move(root, temp);
	}
}
int main(){
int nr=3, em=0, stack_nr=0, i;
	struct node root, *temp;
	char let, what,no; 
	double number;
	void *v;
	double p;
	struct stack m_stack; 
	
	m_stack.next=NULL;
	m_stack.value=NULL; 
	root.next=NULL;
	root.father=NULL;
	root.name=NULL;
	root.prev=NULL;
print_help();
	
	while(1){
		scanf("%c", &let);
		if(let=='A'){
			em=0;
			scanf("%c%c", &no, &what);
			if(what=='I'){
				scanf("%d %d",&nr, &em);
				add(&root, what, nr, em, 0);
			}
			if(what=='D'){
				scanf("%lf %d",&number, &em);
				add(&root, what, &number, em, 0);			
			}
			if(what=='S'){
				scanf("%d", &stack_nr);
				add(&root, what, &m_stack, 1, stack_nr);
			}
			if(what=='C'){
					char *mes=(char*)malloc(sizeof(char)*20);
					scanf("%s", mes);
					scanf("%d", &em);
					add(&root, what, mes, em, 0);
			}
		} else if(let=='D'){
			em=0;
			scanf("%c%c", &no, &what);
			if(what=='I'){
				scanf("%d %d",&nr, &em);
				delete_all(&root, what, nr, em, 0);
			}
			if(what=='D'){
				scanf("%lf %d",&number, &em);
				delete_all(&root, what, &number, em, 0);			
			}
			if(what=='S'){
				scanf("%d", &stack_nr);
				delete_all(&root, what, &m_stack, 1, stack_nr);
			}
			if(what=='C'){
					char *mes=(char*)malloc(sizeof(char)*20);
					scanf("%s", mes);
					scanf("%d", &em);
					delete_all(&root, what, mes, em, 0);
					free(mes);
			}
			
		} else if(let=='P'){
			scanf("%c%c",&no, &what);
			if(what=='I'){
				scanf("%d",&nr);
				temp=prev(&root, what, nr,0);
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='D'){
				scanf("%lf",&number);
				temp=prev(&root, what, &number,0);	
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='S'){
				scanf("%d", &stack_nr);
				temp=prev(&root, what, 1,stack_nr);
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='C'){
					char *mes=(char*)malloc(sizeof(char)*20);
					scanf("%s", mes);
					temp=prev(&root,what, mes,0);
					if(temp!=NULL)
					print_node(*temp);
					free(mes);
			}
		} else if(let=='N'){
			scanf("%c%c",&no, &what);
			if(what=='I'){
				scanf("%d",&nr);
				temp=next(&root, what, nr,0);
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='D'){
				scanf("%lf",&number);
				temp=next(&root, what, &number,0);
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='S'){
				scanf("%d", &stack_nr);
				temp=next(&root, what, 1,stack_nr);
				if(temp!=NULL)
				print_node(*temp);
			}
			if(what=='C'){
					char *mes=(char*)malloc(sizeof(char)*20);
					scanf("%s", mes);
					temp=next(&root,what, mes,0);
					if(temp!=NULL)
					print_node(*temp);
					free(mes);
			}
			printf("next");
		} else if(let=='B'){
			scanf_s("%d%d%d",&nr, &em, &stack_nr);
			for(i=0; i<em; i++)
				stack_push(&root, nr, stack_nr);
		} else if(let=='C'){
			scanf_s("%d%d", &em, &stack_nr);
			for(i=0; i<em; i++)
				stack_pop(&root, stack_nr);
		} else if(let=='S'){
			print_all(root);
			printf("\n");
		} else if(let=='H'){
			print_help();
		} else if(let=='Q'){
			break;
		}	
	}
	return 0;
}
