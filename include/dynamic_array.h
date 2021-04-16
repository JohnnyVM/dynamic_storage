#include <stdlib.h>

struct go_array {
	void *storage;
	unsigned int length;
	unsigned int capacity;
	size_t element_size;
};

struct go_array *go_append(struct go_array *, const void *);
#define go_push go_append
struct go_array* go_make(struct go_array*, const unsigned int);
void* go_pop(struct go_array*, void*);
