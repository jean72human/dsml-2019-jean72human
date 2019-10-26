/*
 * 
 * You will need to write your B+Tree almost entirely from scratch. 
 * 
 * B+Trees are dynamically balanced tree structures that provides efficient support for insertion, deletion, equality, and range searches. 
 * The internal nodes of the tree direct the search and the leaf nodes hold the base data..
 * 
 * For a basic rundown on B+Trees, we will refer to parts of Chapter 10 of the textbook Ramikrishnan-Gehrke 
 * (all chapters and page numbers in this assignment prompt refer to the 3rd edition of the textbook).
 *
 * Read Chapter 10 which is on Tree Indexing in general. In particular, focus on Chapter 10.3 on B+Tree.
 */

#ifndef BTREE_H
#define BTREE_H

#include "data_types.h"
#include "query.h"
#include <stdbool.h> 
#include <stdlib.h>



/* 
Designing your C Structs for B+Tree nodes (Chapter 10.3.1)
How will you represent a B+Tree as a C Struct (or series of C structs that work together)? There are many valid ways to do this part of your design, and we leave it open to you to try and tune this as you progress through the project.
How will you account for a B+Tree node being an internal node or a leaf node? Will you have a single node type that can conditionally be either of the two types, or will you have two distinct struct types?
How many children does each internal node have? This is called the fanout of the B+Tree.
What is the maximum size for a leaf node? How about for an internal node?
What is the minimum threshold of content for a node, before it has to be part of a rebalancing?
*/

// TODO: here you will need to define a B+Tree node(s) struct(s)


#define INTSIZE sizeof(int)
#define FANOUT 10000
#define CUT 0.95

typedef struct node {
	int * keys;
    int * values;
    int nvals;
	struct node * parent;
	struct node * next; 
    bool isleaf;
} node;

struct node create_leaf(){
    struct node leaf;
    leaf.isleaf = true;
    leaf.nvals = 0;
    leaf.parent = NULL;
    leaf.values = (int*)malloc(INTSIZE * FANOUT);
    leaf.keys = (int*)malloc(INTSIZE * FANOUT);
    leaf.next = NULL;
    
    return leaf;
}

struct node create_root(){
    struct node root;
    root.isleaf = false;
    root.nvals = 0;
    root.parent = NULL;
    root.values = NULL;
    root.keys = (int*)malloc(INTSIZE * FANOUT);
    root.next = (struct node *)malloc(sizeof(node) * FANOUT);

    for(int q=0; q<FANOUT; q++){
        struct node any = create_leaf();
        any.parent = &root;
        struct node * temp = root.next;
        temp+=q;
        temp = &any;
    }
    
    return root;
}




void _print_empty(){
    for(int i=0;i<FANOUT;i++){
        printf(" | | ");
    }
}


void _print(struct node * node){
    if (node) {
        if (node->nvals > 0){
            for(int i=0;i<node->nvals;i++){
                printf(" %d ",node->keys[i]);
            }
            for(int i=node->nvals;i<FANOUT;i++){
                printf(" | | ");
            }
        } else {
            printf("EMPTY");
        }
    }
}




void print_tree(struct node * root){
    if (root == NULL)
    {
        printf("NULL");
    }
    else
    {
        _print(root);
    }

    printf("\n");
}





/* The following are methods that can be invoked on B+Tree node(s).
 * Hint: You may want to review different design patterns for passing structs into C functions.
 */

/* FIND (Chapter 10.4)
This is an equality search for an entry whose key matches the target key exactly.
How many nodes need to be accessed during an equality search for a key, within the B+Tree? 
*/

// TODO: here you will need to define FIND/SEARCH related method(s) of finding key-values in your B+Tree.



struct node * _find_leaf(int key, struct node * rootnode){
    int the_key = 0;
    int i = 0;

    if (rootnode->isleaf){
        return rootnode;
    }

    if (rootnode == NULL){
        return NULL;
    }
    
    if (rootnode->nvals == 0){
        return NULL;
    }


    while ( i < rootnode->nvals - 1){
        the_key = rootnode->keys[i+1];
        if (key>=the_key){
            i++;
        } else {
            break;
        }
    }
    if (i>=rootnode->nvals)
    return NULL;
    
    return _find_leaf(key, rootnode->next + i);
}

int _print_value_from_leaf(int key, struct node * leaf){
    int i = 0;
    int the_key = 0;

    if(leaf == NULL)
    return 0;

    if (!leaf->isleaf){
        return 0;
    }
    while ( i < leaf->nvals){
        the_key = leaf->keys[i];
        if (key>the_key){
            i++;
        } else {
            if (key == the_key){
                return leaf->values[i];
            } else {
            return 0;
            }
        }
    }
    return 0;
}

int find(int key, struct node * rootnode){
    return _print_value_from_leaf(key, _find_leaf(key, rootnode));
}




/* INSERT (Chapter 10.5)
How does inserting an entry into the tree differ from finding an entry in the tree?
When you insert a key-value pair into the tree, what happens if there is no space in the leaf node? What is the overflow handling algorithm?
For Splitting B+Tree Nodes (Chapter 10.8.3)
*/

// TODO: here you will need to define INSERT related method(s) of adding key-values in your B+Tree.


void insert_in_leaf(struct node * leaf, int key, int value) {
	int i;
	int the_key = 0;

	while (the_key < leaf->nvals && leaf->keys[the_key] < key){
		the_key++;
    }

	for (i = leaf->nvals; i > the_key; i--) {
		leaf->keys[i] = leaf->keys[i - 1];
		leaf->values[i] = leaf->values[i - 1];
	}

	leaf->keys[the_key] = key;
	leaf->values[the_key] = value;

	leaf->nvals++;
}

void insert_node_in_node(struct node * parent, struct node * node, int key) {
	int i = 0;
	int the_key = 0;
    bool replace = false;

    node->parent = parent;

    
	while (the_key < parent->nvals ){
        if (parent->keys[the_key] <= key){
            if (parent->keys[the_key] == key){
                replace = true;
                break;
            } else {
                the_key++;
            }
        } else {
            break;
        }
    }

    if (!replace){
        //shift
        for (i = parent->nvals; i > the_key; i--) {
            parent->keys[i] = parent->keys[i - 1];
            struct node * temp = parent->next + i;
            *temp = *(parent->next + i - 1);
        }
        parent->nvals++;
    } 

	parent->keys[the_key] = key;
    struct node * temp = parent->next;
    temp += the_key;
	*temp = *node;
}

void insert_in_parent(struct node * p, struct node * node1, struct node * node2){

    if (p->parent == NULL){
        if (p->nvals < (CUT * FANOUT - 1)){
            insert_node_in_node(p, node1, node1->keys[0]);
            insert_node_in_node(p, node2, node2->keys[0]);
            
            return ;
        } else {
            struct node r = create_root();
            struct node temp;
            
            temp = *p;

            insert_node_in_node(&r, &temp, temp.keys[0]);

            insert_node_in_node(&r, node1, node1->keys[0]);

            insert_node_in_node(&r, node2, node2->keys[0]);

            *p = r;

            for (int i=0; i<FANOUT; i++){
                struct node * temp = p->next;
                temp+=i;
            }
            return ;

        }
    }
    if (p->nvals < (CUT * FANOUT - 1)){
        insert_node_in_node(p, node1, node1->keys[0]);
        insert_node_in_node(p, node2, node2->keys[0]);
    } else {
        
        struct node p1 = create_root();
        struct node p2 = create_root();
        
        int half = 0.5*p->nvals;
        struct node * temp;
        temp = p->next;
        for (int i=0; i<half; i++){
            temp ++;
            insert_node_in_node(&p1, temp, temp->keys[0]);
        }
        
        for (int i=half; i<p->nvals; i++){
            temp ++;
            insert_node_in_node(&p2, temp, temp->keys[0]);
        }

        p1.parent = p->parent;
        p2.parent = p->parent;

        insert_node_in_node(&p2, node1, node1->keys[0]);
        insert_node_in_node(&p2, node2, node2->keys[0]);

        insert_in_parent(p->parent, &p1, &p2);
    }
}


void insert(struct node * rootnode, int key, int value){
    struct node * leaf;
    leaf = _find_leaf(key, rootnode);
    if (leaf == NULL){
        struct node newleaf = create_leaf();
        newleaf.parent = rootnode;
        insert_in_leaf(&newleaf, key, value);
        insert_node_in_node(rootnode, &newleaf, key);
        return ;
    } 
    if (leaf->nvals < CUT * FANOUT){
        insert_in_leaf(leaf, key, value);
    } else {
        // split leaf node
        struct node n1 = create_leaf();
        struct node n2 = create_leaf();

        int half = 0.5*leaf->nvals;
        for (int i=0; i<half; i++){
            insert_in_leaf(&n1, leaf->keys[i], leaf->values[i]);
        }
        for (int i=half; i<leaf->nvals; i++){
            insert_in_leaf(&n2, leaf->keys[i], leaf->values[i]);
        }
        insert_in_leaf(&n2, key, value);
        n1.parent = leaf->parent;
        n2.parent = leaf->parent;
        insert_in_parent(leaf->parent,&n1, &n2);
    }
}







/* BULK LOAD (Chapter 10.8.2)
Bulk Load is a special operation to build a B+Tree from scratch, from the bottom up, when beginning with an already known dataset.
Why might you use Bulk Load instead of a series of inserts for populating a B+Tree? Compare the cost of a Bulk Load of N data entries versus that of an insertion of N data entries? What are the tradeoffs?
*/

// TODO: here you will need to define BULK LOAD related method(s) of initially adding all at once some key-values to your B+Tree.
// BULK LOAD only can happen at the start of a workload


/*RANGE (GRADUATE CREDIT)
Scans are range searches for entries whose keys fall between a low key and high key.
Consider how many nodes need to be accessed during a range search for keys, within the B+Tree?
Can you describe two different methods to return the qualifying keys for a range search? 
(Hint: how does the algorithm of a range search compare to an equality search? What are their similarities, what is different?)
Can you describe a generic cost expression for Scan, measured in number of random accesses, with respect to the depth of the tree?
*/

// TODO GRADUATE: here you will need to define RANGE for finding qualifying keys and values that fall in a key range.



#endif
