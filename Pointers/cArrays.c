#include "cArrays.h"

void update_file(int filedata[200], int new_filetype, int new_num_lines) {
    filedata[1] = new_num_lines;
    filedata[2] = new_filetype;
    filedata[199] = 0;
}
