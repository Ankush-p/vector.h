#
/*_
Copyright (c) <2017>, <Ankush Patel> <ankushjp4@gmail.com>
The Source Code is released under a (3-Clause)BSD-Style Licence.
All rights reserved. 

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the author nor the names of its contributors may 
	  be used to endorse or promote products derived from this software 
	  without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL The COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef VECTOR_H
#define VECTOR_H

#include "stdlib.h"
#include "string.h"
/* for new*() functions or destroy() functions */
/* this struct allows an object to keep a reference to it's self so that the
 * program does not leak memory, and so that the program is able to manipulate
 * it's own objects to point to something else. 
 */
struct __OBEJCT_SELF_ {
	void *object_ref;
};

#define NEW_VECTOR_TYPE(name, elemType) \
typedef struct VECTOR_##name##_v { \
	struct __OBEJCT_SELF_ _self_ptr; \
\
	elemType *Elements; \
	/* The number of elements currently in the vector */ \
	size_t Occupied; \
	/* The maximum number of elements that the vector can hold */ \
	size_t Capacity; \
\
	/* some function pointers */ \
\
	/** @brief - return the first element in the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return A <elemType>.
 	 */ \
	elemType (*front)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - return the last element in the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return A <elemType>.
 	 */ \
	elemType (*back)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - return the element at index in the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @param [in] n - The index of the element in the vector..
 	 * @return A <elemType>.
 	 */ \
	elemType (*get)(struct VECTOR_##name##_v *vec, size_t n);\
\
	/** @brief - return the number of elements in the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return A <size_t>.
 	 */ \
	size_t (*size)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - return the capacity of the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return a <size_t>.
 	 */ \
	size_t (*capacity)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - resize the vector(->Elements) to hold n elements.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @param [in] n - Number of elements the vector should be able to hold.
 	 * @return <int> - , -1 indicates malloc() failed.
 	 */ \
	int (*resize)(struct VECTOR_##name##_v *vec, size_t n); \
\
	/** @brief - resize the vector to exactly enough bytes for 
	 * 	vec->Occupied elements (so that vec->Occupied = vec->Capacity)
	 * @param [in] vec - A Pointer To The Vector
	 * @ return <int> - , -1 indictes malloc() failed.
	 */ \
	int (*clamp)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - add one element to the end of the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @param [in] data - The data to push (add) onto the vector.
 	 * @return <int> - , -1 indicates malloc() failed.
 	 */ \
	int (*push)(struct VECTOR_##name##_v *vec, elemType data); \
\
	/** @brief - remove one element from the end of the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return <int> - , -1 indicates malloc() failed.
 	 */ \
	int (*pop)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - return the size (in bytes) of the elements array
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return <size_t> - The size (in bytes) of the elements array
 	 */ \
\
	/** @brief - return a pointer to <vec->Elements>
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return <elemType> - A pointer to <vec->Elements>
 	 */ \
	elemType *(*data)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - return the size of the vec->Elements in bytes.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @return <elemType> - the size of the vec->Elements in bytes.
 	 */ \
	size_t (*bytesize)(struct VECTOR_##name##_v *vec); \
\
	/** @brief - insert an element into position <index> in the vector.
 	 * @param [in] vec - A Pointer To The Vector.
 	 * @param [in] index - The index in the vector at which to insert <data>
 	 * @param [in] data - The data to insert.
 	 * @return <int> - , -1 indicates malloc() failed.
 	 */ \
	int (*insert)(struct VECTOR_##name##_v*vec,size_t index,elemType data);\
\
	/** @brief - remove an element from position <index> in the vector.
	 * @param [in] vec - A Pointer To The Vector.
 	 * @param [in] index - The index in the vector at which to remove data.
 	 * @return <int> - , -1 indicates malloc() failed.
 	 */ \
	int (*remove)(struct VECTOR_##name##_v *vec, size_t index); \
\
} VECTOR_##name##_v; \
/* return the first element in the vector */ \
static elemType VECTOR_##name##_v_FRONT(struct VECTOR_##name##_v *vec) \
{ \
	return (vec->Elements[0]); \
} \
/* return the last element in the vector */ \
static elemType VECTOR_##name##_v_BACK(struct VECTOR_##name##_v *vec) \
{ \
	return (vec->Elements[vec->Occupied-1]); \
} \
/* return the <n>th element in the vector
 * This function should more-often-then-not be overridden (as in the get()
 * function pointer should point to some other custom function that is specific
 * to the vector type) because this function requires the user to pass in a
 * success flag - this flag is set to 0 on success and -1 on an out-of-bounds
 * access. This function is also capable of handling negative indexes: An <n>
 * of minus one will retrieve the last element in the vector.
 */ \
static elemType VECTOR_##name##_v_AT(struct VECTOR_##name##_v *vec, size_t n) \
{ \
	if (n < 0) n += vec->Occupied; \
	return (vec->Elements[n]); \
} \
/* return the number of elements in the vector */ \
static size_t VECTOR_##name##_v_SIZE(struct VECTOR_##name##_v *vec) \
{ \
	return (vec->Occupied); \
} \
/* return the capacity of the vector */ \
static size_t VECTOR_##name##_v_CAPACITY(struct VECTOR_##name##_v *vec) \
{ \
	return (vec->Capacity); \
} \
/* resize the vector(->Elements) to hold n elements */ \
static int VECTOR_##name##_v_RESIZE(struct VECTOR_##name##_v *vec, size_t n) \
{ \
	elemType *new; \
	new = realloc(vec->Elements, n * sizeof(elemType)); \
	if (new == NULL) \
		return (-1); \
	vec->Elements = new; \
	vec->Capacity = n; \
	if (n < vec->Occupied) \
		vec->Occupied = n; \
	return (0); \
} \
/* resize vector(->Elements) to hold vec->Ocucpied elements */ \
static int VECTOR_##name##_v_CLAMP(struct VECTOR_##name##_v *vec) \
{ return (VECTOR_##name##_v_RESIZE(vec, vec->Occupied)); } \
/* add one element to the end of the vector */ \
static int VECTOR_##name##_v_PUSH(struct VECTOR_##name##_v *vec, elemType data)\
{ \
	if (vec->Occupied + 1 >= vec->Capacity) \
		VECTOR_##name##_v_RESIZE(vec, 2 * vec->Capacity); \
	vec->Elements[vec->Occupied] = data; \
	++vec->Occupied; \
	return (0); \
} \
/* remove one element from the end of the vector */ \
static int VECTOR_##name##_v_POP(struct VECTOR_##name##_v *vec) \
{ \
	--vec->Occupied; \
	if (vec->Occupied < (vec->Capacity / 2) + 1) \
		VECTOR_##name##_v_RESIZE(vec, (vec->Capacity / 2) + 1); \
	return (0); \
} \
/* insert an element into position index in the vector */ \
static int VECTOR_##name##_v_INSERT(struct VECTOR_##name##_v *vec, size_t index\
	, elemType data) \
{ \
	if (vec->Occupied + 1 >= vec->Capacity) \
		VECTOR_##name##_v_RESIZE(vec, 2 * vec->Capacity); \
	memmove(vec->Elements + index + 1, vec->Elements + index, \
		sizeof(elemType) * vec->Occupied - index); \
	vec->Elements[index] = data; \
	++vec->Occupied; \
	return (0); \
} \
/* remove an element from position index in the vector */ \
static int VECTOR_##name##_v_REMOVE(struct VECTOR_##name##_v *vec,size_t index)\
{ \
	if (vec->Occupied - 1 <= (vec->Capacity / 2) + 1) \
		VECTOR_##name##_v_RESIZE(vec, (vec->Capacity / 2) + 1); \
	memmove(vec->Elements + index, vec->Elements + index + 1 \
		, sizeof(elemType) * (vec->Occupied - index)); \
	--vec->Occupied; \
	return (0); \
} \
/* return the size of the vec->Elements in bytes */ \
static size_t VECTOR_##name##_v_BYTE_SIZE(struct VECTOR_##name##_v *vec) \
{ \
	return(sizeof(*vec->Elements) * vec->Occupied); \
} \
/* return a pointer to vec->Elements */ \
static elemType *VECTOR_##name##_v_DATA(struct VECTOR_##name##_v *vec) \
{ \
	return(vec->Elements); \
} \
static struct VECTOR_##name##_v *NEW_VECTOR_##name##_v(size_t size) \
{ \
	struct VECTOR_##name##_v *vec=malloc(sizeof(struct VECTOR_##name##_v));\
	vec->_self_ptr.object_ref = vec; \
	vec->Elements = malloc(sizeof(elemType) * size); \
	if (vec->Elements == NULL) \
		return (NULL); \
	vec->Capacity = size; \
	vec->Occupied = 0; \
\
	/* Function Pointers (can be overridden by implementation) */ \
	vec->front = &VECTOR_##name##_v_FRONT; \
	vec->back = &VECTOR_##name##_v_BACK; \
	vec->get = &VECTOR_##name##_v_AT; \
	vec->size = &VECTOR_##name##_v_SIZE; \
	vec->capacity = &VECTOR_##name##_v_CAPACITY; \
	vec->resize = &VECTOR_##name##_v_RESIZE; \
	vec->clamp = &VECTOR_##name##_v_CLAMP; \
	vec->push = &VECTOR_##name##_v_PUSH; \
	vec->pop = &VECTOR_##name##_v_POP; \
	vec->insert = &VECTOR_##name##_v_INSERT; \
	vec->remove = &VECTOR_##name##_v_REMOVE; \
	vec->data = &VECTOR_##name##_v_DATA; \
	vec->bytesize = &VECTOR_##name##_v_BYTE_SIZE; \
\
	return (vec); \
} \
static void DELETE_VECTOR_##name##_v(struct VECTOR_##name##_v *vec) \
{ \
	free(vec->Elements); \
	free(vec->_self_ptr.object_ref); \
}

#endif /* VECTOR_H */
