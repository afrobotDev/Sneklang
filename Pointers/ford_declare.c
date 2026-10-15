#include "ford_declare.h"
#include <stdlib.h>

snekobject_t new_node(char *name) {
    struct SnekObject node;
    node.name = name;
    node.child = NULL;
    return node;
}