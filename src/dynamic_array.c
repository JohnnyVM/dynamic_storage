#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "dynamic_array.h"

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
