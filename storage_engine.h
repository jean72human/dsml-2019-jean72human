/*
 * The storage engine functions prefixed with `wrapper`, map the corresponding k-v operations 
 * of the k-v DSL to actual B+Tree functions invoked on your B+Tree.
 */
#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include "data_types.h"
#include "query.h"
#include "btree.h"

/*
 * A struct to store the context of your storage engine.
 * You may wish to extend this struct, to not only store your B+Tree, but also store additional state.
 * 
 * 1. You will need to decide how to hold a B+Tree in your storage context. 
 *      Hint, you will need to modify the storage context struct, 
 *      while thinking about memory management and pointers for accessing your B+Tree.
 */
typedef struct storageContext {
    // TODO: you hold a pointer here to find your B+Tree
    struct node * tree;
} STORAGECXT_t;



/*
 * The following are wrapper functions which are entry points into your storage engine.
 * 
 * You will need to make sure these call your B+Tree to do actual data acccess operations.
 * Your B+Tree will need multiple supporting methods in order to be complete.
 * It is up to you to design: define and declare the additional functions in B+Tree,
 *      and how they interact with the methods in these files.
 */

/*
 *  Get looks for a `targetKey`, and will give back the corresponding key in foundVal, if it exists.
 * 
 *  @Params: 
 *      storageEngine   - the storage engine to operate on
 *      targetKey       - the target key to search for
 *      foundVal        - declared outside the function invocation. should hold any found value.
 * 
 *  Returns:
 *       0 for no result, 
 *       1 if a value exists for `targetKey` in which case `foundVal` is populated
 * 
 */
int wrapperGet(STORAGECXT_t **storageEngine, KEY_t targetKey, VAL_t *foundVal){
    // TODO: finish this by running the find operation on your B+Tree.
    //      You will need to define and declare a method(s) to run find on your B+Tree.

    (void) storageEngine;
    (void) targetKey;
    (void) foundVal;

    STORAGECXT_t * engine = *storageEngine;

    int value = find(targetKey, engine->tree);
    if  (value){
        *foundVal = value;
        return 1;
    }

    return 0;
}

/*
 *  Put sets a key value pair. 
 *  If a key does not exist previously in the storage engine, it should be inserted.
 *  If the key exists previously, the old value should be overwritten with the newly specified value.
 * 
 *  @Params: 
 *      storageEngine   - the storage engine to operate on
 *      key             - key to add
 *      val             - val to add
 * 
 *  Returns:
 *       0 for failed, 
 *       1 if the k,v pair addition succeeded
 * 
 */
int wrapperPut(STORAGECXT_t **storageEngine, KEY_t key, VAL_t val){
    // TODO: finish this by running the `insert` or `update` operation on your B+Tree.
    //      You will need to define and declare a method(s) to run `insertions` and `updates` on your B+Tree.
    //      Consider: will you treat `insertions` and `updates` as the same algorithm?
    //      Consider: how does the design of these B+Tree algorithms compare to `find`?
    (void) storageEngine;
    (void) key;
    (void) val;

    STORAGECXT_t * engine = *storageEngine;

    return insert(engine->tree, key, val);
}

/*
 *  Range finds a set of key value pairs that qualify between a low and high range. 
 *  Low key should be inclusive and High key should be exclusive.
 *  
 * 
 *  @Params: 
 *      storageEngine      - the storage engine to operate on
 *      lowKey             - inclusive low point of the range to find
 *      highKey            - exclusive high point of the range to find
 *      rangeResult        - results, which if found, will be populated 
 *                              (see the query.h definition for more details)
 *  Returns:
 *       0 for no result, 
 *       non-zero indicating the number of the qualifying entries, held inside `rangeResult`'s keys and values
 * 
 */
// returns 0 for no result
// returns non-zero for the length of the qualifying entries
int wrapperRange(STORAGECXT_t **storageEngine, KEY_t lowKey, KEY_t highKey, RANGE_RESULT_t **rangeResult){
    // TODO GRADUATE: 
    //      You will need to define and declare a method(s) to run 
    (void) storageEngine;
    (void) lowKey;
    (void) highKey;
    (void) rangeResult;
    return 0;
}

#endif
