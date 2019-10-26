
#include <stdio.h>

#include "btree.h"


int main(){
    printf("Hello! Let's test \n");
    struct node root = create_root();
    print_tree(&root);
    insert(&root, 1, 42);
    printf("First insertion worked\n");
    insert(&root, 3, 4);
    printf("Second insertion worked\n");
    insert(&root, 355, 452);
    printf("Third insertion worked\n");
    insert(&root, 2, 55);
    printf("Fourth insertion worked\n");
    insert(&root, 8, 2);
    printf("Fifth insertion worked\n");
    insert(&root, 38, 1);
    printf("Sixth insertion worked\n");
    insert(&root, 45, 4562);
    printf("Seventh insertion worked\n");
    insert(&root, 4, 2564655);
    printf("Eigth insertion worked\n");
    insert(&root, 39, 488);
    printf("Ninth insertion worked\n");
    insert(&root, 47, 123);
    printf("Tenth insertion worked\n");
    insert(&root, 3, 488);
    printf("Eleventh insertion worked\n");
    insert(&root, 45, 228);
    printf("Twelth insertion worked\n");
    insert(&root, 46785, 228);
    printf("Thirteenth insertion worked\n");
    insert(&root, 565, 5645648);
    printf("Fourteenth insertion worked\n");
    insert(&root, 48848585, 98);
    printf("Fifteenth insertion worked\n");


    

    
    printf("Root has %d children\n\n", root.nvals );
    printf("Here is at index 8: %d\n", find(8, &root));
    printf("Here is at index 3: %d\n", find(3, &root));
    printf("Here is at index 2: %d\n", find(2, &root));
    printf("Here is at index 38: %d\n", find(38, &root));
    printf("Here is at index 355: %d\n", find(355, &root));
    printf("Here is at index 45: %d\n", find(45, &root));
    printf("Here is at index 4: %d\n", find(4, &root));
    printf("Here is at index 39: %d\n", find(39, &root));
    printf("Here is at index 48848585: %d\n", find(48848585, &root));
    printf("Here is at index 565: %d\n", find(565, &root));
    printf("Here is at index 46785: %d\n", find(46785, &root));


    return 0;
}