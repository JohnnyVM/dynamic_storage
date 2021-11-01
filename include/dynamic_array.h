#include <stdlib.h>

struct array {
	void *storage;
	unsigned int length;
	unsigned int capacity;
	size_t element_size;
};

struct array_array *array_append(struct array *, const void *);
#define array_push array_append
struct array* array_make(struct array*, const unsigned int);
void* array_pop(struct array*, void*);
