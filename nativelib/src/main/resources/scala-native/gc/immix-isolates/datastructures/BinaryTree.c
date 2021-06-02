#include <stdlib.h>
#include "BinaryTree.h"

typedef struct {
    pid_t pid;
    size_t pos;
} data_t;

struct treenode {
    btree_node_t *left;
    btree_node_t *right;
    data_t data;
};

static int btree_is_empty(const btree_t *btree) { return btree->size == 0u; }

void btree_init(btree_t *btree) {
    btree->root = NULL;
    btree->size = 0u;
}

void btree_insert(btree_t *btree, pid_t pid, size_t pos) {
    btree_node_t **it = &btree->root;

    while (*it) {
        it = (pid < (*it)->data.pid) ? &(*it)->left : &(*it)->right;
    }

    *it = malloc(sizeof(btree_node_t));
    (*it)->left = NULL;
    (*it)->right = NULL;
    (*it)->data = (data_t){.pid = pid, .pos = pos};

    ++btree->size;
}

static size_t max(size_t a, size_t b) { return a > b ? a : b; }

static size_t btree_height_rec(const btree_node_t *node) {
    size_t depth_left = node->left ? btree_height_rec(node->left) : 0;
    size_t depth_right = node->right ? btree_height_rec(node->right) : 0;
    return 1 + max(depth_left, depth_right);
}

size_t btree_height(const btree_t *btree) {
    return btree_height_rec(btree->root) - 1;
}

int btree_search(const btree_t *btree, pid_t key, size_t *value) {
    btree_node_t *p = btree->root;

    while (p) {
        if (key == p->data.pid) {
            *value = p->data.pos;
            return 0;
        }
        p = (key < p->data.pid) ? p->left : p->right;
    }

    return 1;
}
