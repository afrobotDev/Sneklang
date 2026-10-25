#include <stdlib.h>
#include <string.h>

void swap(void *vp1, void *vp2, size_t size) {
	void *temp = malloc(size);
	if (temp == NULL) { return; };

	// temp = vp1 
	memcpy(temp, vp1, size);

	// vp1 = vp2 
	memcpy(vp1, vp2, size);

	// vp2 = temp
	memcpy(vp2, temp, size);

	free(tmp);
}
