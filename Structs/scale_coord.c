#include "scale_coord.h"

struct Coordinate scale_coord(struct Coordinate c, int factor) {
    return (struct Coordinate){.x = c.x * factor, .y = c.y * factor, .z = c.z * factor};
}
