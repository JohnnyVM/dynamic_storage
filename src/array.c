#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "array.h"

/* \brief Define the fields for a struct array
 * I am going to keep the flat struct without pointer for do morre robust interface
 * */
struct array _init_array(size_t element_size, void(*free_ptr)(void*)) {
	struct array output = {
		.storage = NULL,
		.length = 0,
		.capacity = 0,
		.element_size=element_size,
		.free = free_ptr
	};

	return output;
}

struct array* _create_array(size_t element_size, void(*free_ptr)(void*)) {

	struct array* arr = malloc(sizeof *arr);
	*arr = _init_array(element_size, free_ptr);
	return arr;
}

/**
 * \brief append element to struct array_array
 *
 * the expected size of new_element MUST be equal to data_size,
 * \param arr handled array
 * \param new_element new element to append to arr
 * \return null if error else pointer to arr
 */
struct array *array_append(struct array *arr, const void *new_element) {
	void *tmp;
	if(!arr || !new_element) { return NULL; }
	if (arr->capacity <= arr->length) {
		if(!arr->capacity) { arr->storage = NULL; }
		arr->capacity += 2 * arr->capacity + 1;
		tmp = realloc(arr->storage, arr->capacity * arr->element_size);
		if(!tmp) { return tmp; }
		arr->storage = tmp;
	}
	memcpy((char *)arr->storage + (arr->length * arr->element_size), new_element, arr->element_size);
	arr->length += 1;
	assert(arr->capacity >= arr->length);
	return arr;
}

/**
 * \brief change the capacity of array
 *
 * if capacity = 0 its equivalent to free storage
 * if something go wrong storage its untouched
 * arr->storage its unitialized, arr.storage must be freed
 * \param size of elements
 * \param capacity of array
 * \return null if error else pointer to arr
 */
struct array* array_make(struct array* arr, const unsigned int capacity) {
	void *tmp;
	if(!arr) { return NULL; }
	if(arr->capacity == capacity) { return arr; }
	tmp = realloc(arr->capacity ? arr->storage : NULL, capacity * arr->element_size);
	if(!tmp) { return tmp; }
	arr->storage = tmp;
	arr->length = capacity < arr->length ? capacity : arr->length;
	arr->capacity = capacity;
	return arr;
}

/**
 * \brief return copy of last element
 *
 * \param arr stack of elements
 * \param memory for copy the elem
 * \return copy of the last element, if no element return null
 */
void* array_pop(struct array* arr, void* elem) {

	if(!arr) { return NULL; }
	if(arr->length <= 0) { return NULL; }

	--arr->length;
	if(!elem) { return NULL; }
	memcpy(elem, (char *)arr->storage + (arr->length * arr->element_size), arr->element_size);
	return elem;
}

/* clean the content of the array, but not free the array */
void free_array(struct array* arr) {
	if(!arr) { return; }

	// todo add overflow check
	for(intmax_t i = arr->length-1; arr->free && i >= 0; i--) {
		arr->free((char *)arr->storage + ((uintmax_t)i * arr->element_size));
	}

	free(arr);
}
