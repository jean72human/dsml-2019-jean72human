
#include <stdio.h>

#include "btree.h"


int main(){
    printf("Hello! Let's test \n");
    struct node root = create_root();
    print_tree(&root);
    insert(&root, 1, 42);
    printf("First insertion worked\n");
    print_tree(&root);
    insert(&root, 3, 4);
    printf("Second insertion worked\n");
    print_tree(&root);
    insert(&root, 355, 452);
    printf("Third insertion worked\n");
    print_tree(&root);
    insert(&root, 2, 55);
    printf("Fourth insertion worked\n");
    print_tree(&root);
    insert(&root, 8, 2);
    printf("Fifth insertion worked\n");
    print_tree(&root);
    insert(&root, 38, 1);
    printf("Sixth insertion worked\n");
    print_tree(&root);
    insert(&root, 45, 4562);
    printf("Seventh insertion worked\n");
    print_tree(&root);
    insert(&root, 4, 2564655);
    printf("Eigth insertion worked\n");
    print_tree(&root);
    insert(&root, 39, 488);
    printf("Ninth insertion worked\n");
    //print_tree(&root);
    //print_tree(&root);
    insert(&root, 47, 123);
    insert(&root, 3, 488);
    //printf("Tenth insertion worked\n\n\n");
    
    //struct node * temp = root.next;
    //temp+=0;
    
    printf("Root has %d children\n\n\n\n", root.nvals );
    print_tree(_find_leaf(8,&  root));
    printf("Here is at index 8: %d\n", find(8, &root));
    //print_tree(_find_leaf(8,&root));
    printf("Here is at index 3: %d\n", find(3, &root));
    //print_tree(_find_leaf(3,&root));
    printf("Here is at index 2: %d\n", find(2, &root));
    //print_tree(_find_leaf(2,&root));
    printf("Here is at index 38: %d\n", find(38, &root));
    //print_tree(_find_leaf(38,&root));
    printf("Here is at index 355: %d\n", find(355, &root));
    //print_tree(_find_leaf(355,&root));
    printf("Here is at index 45: %d\n", find(45, &root));
    //print_tree(_find_leaf(45,&root));
    printf("Here is at index 4: %d\n", find(4, &root));
    //print_tree(_find_leaf(4,&root));
    printf("Here is at index 39: %d\n", find(39, &root));
    //print_tree(_find_leaf(39,&root));
    //printf("Here is at index 47: %d\n", find(47, &root));


    return 0;
}