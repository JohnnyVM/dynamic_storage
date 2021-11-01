#include <stdlib.h>

struct array {
	void *storage;
	unsigned int length;
	unsigned int capacity;
	const size_t element_size;
	
	/* pointer to free the objects */
	void (*free)(void*element);
};

struct array _create_array(size_t size_element, void (*free)(void));
#define create_array(TYPE, POINTER) _create_array(sizeof(TYPE), POINTER)

struct array_array *array_append(struct array *, const void *);
#define array_push array_append
struct array* array_make(struct array*, const unsigned int);
void* array_pop(struct array*, void*);
/* todo, this is pretty bad interface and bad name */
void free_array(struct array arr);
