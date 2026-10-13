#include "structs_intro.h"

struct Coordinate new_coord(int x, int y, int z) {
    return (struct Coordinate){.x = x, .y = y, .z = z};
}
