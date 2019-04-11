#include <stddfd.h>

#define EDGE_FLAG_UNALLOC    0
#define EDGE_FLAG_ROOT       1
#define EDGE_FLAG_LEAF       2
#define EDGE_FLAG_NONLEAF    4
#define EDGE_FLAG_LEVEL_HEAD 8

// byte cursor
union bcursor_t{
	uint8_t  u8[8];
	uint16_t u16[4];
	uint32_t u32[2];
	uint64_t u64;
};

// function box
typedef struct __function{
	uint8_t *fname;         // function name
	void 	*ftype;	        // function type
	void    *param;	        // function parameter
	void 	*ret;	        // return address
	void 	*context;		// function context
}edge_function;

struct list_chain{
	uint8_t  flag;
	edge_edge *edge;
	struct list_head head;
};

// contain connection information
typedef struct __edge{
	uint64_t linkCount;      // Total direct link count concerning this edge
	uint64_t level;          // Current level
	uint8_t  flag;           // Edge type
	uint8_t  *name;			 // Edge name
	uint64_t numFriend;      // The number of connected edge (friend)
	uint64_t numHigh;        // The number of connected edge (Parent)
	uint64_t numLow;         // The number of connected edge (Child)
	struct list_chain friend;// The list of friend edge (neighbour)
	struct list_chain parent;// The list of parent edge
	struct list_chain child; // The list of child edge
	struct __function **func;// The information of functions which an edge contains
	uint8_t  *description;	 // Edge description
}edge_edge;

// Allocate edge in memory
edge_edge *edge_init(void);
// Unallocate edge in memory
uint8_t edge_free(edge_edge *edge);

void edge_tree_connect(edge_edge *high,edge_edge *low);
void edge_tree_dismiss(edge_edge *high,edge_edge *low);

void edge_friend_shake(edge_edge *left,edge_edge *right);
void edge_friend_farewell(edge_edge *left,edge_edge *right);

void edge_set_flag(edge_edge *edge,uint8_t flag);
void edge_copy(edge_edge *src,edge_edge *dst);