#include "scale_coord.h"

coordinate_t scale_coord(coordinate_t c, int factor) {
    return (coordinate_t){.x = c.x * factor, .y = c.y * factor, .z = c.z * factor};
}
