#ifndef SCALA_NATIVE_BINARYTREE_H
#define SCALA_NATIVE_BINARYTREE_H

#include <stddef.h>
#include <sys/types.h>

typedef struct treenode btree_node_t;

typedef struct {
    btree_node_t *root;
    size_t size;
} btree_t;

void btree_init(btree_t *btree);
void btree_insert(btree_t *btree, pid_t pid, size_t pos);
size_t btree_height(const btree_t *btree);
int btree_search(const btree_t *btree, pid_t key, size_t *value);

#endif // SCALA_NATIVE_BINARYTREE_H
