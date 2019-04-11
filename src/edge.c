#include <edge.h>

// Allocate edge in memory
edge_edge *edge_init(void){
	edge_edge *temp;
	list_head(child);
	list_head(parent);
	init_list_head(&child);
	init_list_head(&parent);
	temp 		= calloc(0,sizeof(edge_edge));
	parent.edge = temp;
	child.edge  = temp;
	return temp;
}
// Unallocate edge in memory
uint8_t edge_free(edge_edge *edge){
	if(edge!=NULL){
		memset(edge,0,sizeof(edge_edge));
		free(edge);
		edge = NULL;
		return BOOL_TRUE;
	}return BOOL_FALSE;
}

static INLINE struct list_chain *find_edge(struct list_chain *head,edge_edge *edge){
	struct list_chain chain;
	struct list_chain *temp;
	chain.edge = head->edge;
	chain.head->next = head->head->next;
	for(;chain.edge!=edge or chain.head->next!=NULL;){
		temp = list_next_entry(&chain.head,struct list_chain,head);
		if(temp==NULL){break;}
		chain.edge = temp->edge;
		chain.head = temp->head;
	}if(chain.edge==edge){return temp;}
	return NULL;
}

static INLINE void __edge_set_child(edge_edge *edge,edge_edge *new){
	list_head(head);
	init_list_head(&head);
	struct list_chain chain = {
		.edge = new,
		.flag = (new->flag==EDGE_FLAG_UNALLOC)?BOOL_FALSE:BOOL_TRUE,
		.head = head
	};
	list_add_tail(&chain.head,&edge->child.head);
	edge->numLow++;
	new->numHigh++;
}
static INLINE void __edge_set_parent(edge_edge *edge,edge_edge *new){
	list_head(head);
	init_list_head(&head);
	struct list_chain chain = {
		.edge = new,
		.flag = (new->flag==EDGE_FLAG_UNALLOC)?BOOL_FALSE:BOOL_TRUE,
		.head = head
	};
	list_add_tail(&chain.head,&edge->parent.head);
	edge->numLow++;
	new->numHigh++;
}
static INLINE void __edge_dismiss(edge_edge *high,edge_edge *low){
	struct list_chain *hi;
	struct list_chain *lo;
	hi = find_edge(high->child,low);
	lo = find_edge(low->parent,high);
	if(hi!=NULL && lo!=NULL){
		list_del(&hi->head);
		list_del(&lo->head);
		high->numLow--;
		low->numHigh--;
	}
}
static INLINE void __edge_set_friend(edge_edge *edge,edge_edge *new){
	list_head(head);
	init_list_head(&head);
	struct list_chain chain = {
		.edge = new,
		.flag = (new->flag==EDGE_FLAG_UNALLOC)?BOOL_FALSE:BOOL_TRUE,
		.head = head
	};
	list_add_tail(&chain.head,&edge->friend.head);
	edge->numLow++;
	new->numHigh++;
}
static INLINE void __edge_farewell(edge_edge *left,edge_edge *right){
	struct list_chain *hi;
	struct list_chain *lo;
	hi = find_edge(high->child,low);
	lo = find_edge(low->parent,high);
	if(hi!=NULL && lo!=NULL){
		list_del(&hi->head);
		list_del(&lo->head);
		high->numLow--;
		low->numHigh--;
	}
}

// Vertical
void edge_tree_connect(edge_edge *high,edge_edge *low){
	__edge_set_child(high,low);
	__edge_set_parent(low,high);
}
// Vertical
void edge_tree_dismiss(edge_edge *high,edge_edge *low){
	__edge_dismiss(high,low);
}
// Horizental
void edge_friend_shake(edge_edge *left,edge_edge *right){
	__edge_set_friend(left,right);
	__edge_set_friend(right,left);
}
// Horizental
void edge_friend_farewell(edge_edge *left,edge_edge *right){
	__edge_farewell(left,right);
}

void edge_set_flag(edge_edge *edge,uint8_t flag){edge->flag = flag;}
void edge_copy(edge_edge *src,edge_edge *dst){
	memcpy(dst,src,sizeof(edge_edge));
}

 