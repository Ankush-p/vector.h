# vector.h
A small header file that adds basic support for vectors in plain/pure ANSI-C (c89).

## Licence
This header file is released under a (3-clause) BSD-Style Licence. Check either the _vector.h_ or _COPYING_ files for the complete licence.

## How do I use this? 

The header is very simple to use - all you have to do is include it, and then use one macro to define the new vector type:
##### Example:
###### The example below is very basic and shows off 2 (not including the `NEW_*` and `DELETE_*` functions) functions/operations you can perform on the vector types.
``` c
#include "vector.h"

NEW_VECTOR_TYPE(IntVector, int) /* name the created vector type IntVector and make it's elements (the data it holds) of type int */

main()
{
	/* create a new IntVector with space for 5 elements (i.e. 5 int's in this case) */
	VECTOR_IntVector_v *vec1 = NEW_VECTOR_IntVector_v(5);
	
	vec1.push(vec1, 10); /* 'Push' an element (the integer value 10) into the vector */
	/* now vec1->Elements[0] == 10 */
	/* do this a couple more times */	
	vec1->push(vec1, 20); /* now vec1->Elements[1] == 20 */
	vec1->push(vec1, 30); /* now vec1->Elements[2] == 30 */
	vec1->push(vec1, 40); /* now vec1->Elements[3] == 40 */
	vec1->push(vec1, 50); /* now vec1->Elements[4] == 50 */
	
	/* the vector will automatically resize itself so that it can hold the next element */
	vec1->push(vec1, 60); /* now vec1->Elements[5] == 60 */
	
	/* the vector will automatically resize itself so that it does not take up to much unnecessary memory */
	vec1->pop(vec1); /* now vec1->Elements[5] is __Undefined Behaviour__ */
	
	/* we are now done with the vector, delete to free up its resources */
	DELETE_VECTOR_IntVector_v(vec1);
	
	return (0);
}
```

#### How do I create a new vector type? (i.e. a vector of int's)
To create a vector of any type, use the macro `NEW_VECTOR_TYPE(name, elemType)`, where `name` is the name you want to give to the vector type (so that the full name will be `VECTOR_name_v`) and `elemType` is the type of data the vector is supposed to hold (i.e. int's): `NEW_VECTOR_TYPE(IntVector, int)`

#### Why are my vectors pre-and-post-fixed with huge names like `VECTOR_name_v`? 
Because I was overcautious of namespace clashing! I highly doubt any sane person will ever give such pedantic names to `typedef`'s in their code - and that's why the names are so long.
I don't expect anyone to use the vectors this way (I certainly don't!) - instead I use a simple `typedef` to alias the vector's name to something I know there will be no clashes with in my current project:
(continuing on from the previous example) `typedef VECTOR_IntVector_v IntVec;`If you really want, you could even use the preprocessor to define the `NEW_*` and `DELETE_*` functions: `#define NEW_IntVec NEW_VECTOR_IntVector_v` _or_ `#define NEW_IntVec(n) NEW_VECTOR_IntVector_v(n)` (The second `define` looks more function like, but it has the same net effect on the code).

#### Hey, what gives! I thought c gave complete control to the programmer! I wish to shoot myself in the foot - how are the vectors implemented and can I mess with them in my code?
You're right! C does give complete control to the programmer, and so I thought it was best to give the user (read _programmer_) full access to the structure,
instead of making it an opaque type. As such, you don't really have to use any of the function pointers provided by the vectors.
The variables in the structure look like this:
``` c
struct __OBEJCT_SELF_ _self_ptr; /* DON'T EVER MODIFY/ACCESS THIS - YOU WILL NEVER NEED IT, BUT THE DELETE FUNCTIONS DO */
elemType *Elements; /* The elements in the vector */
size_t Occupied; /* The number of elements currently in the vector */
size_t Capacity; /* The maximum number of elements that the vector can hold */

/* function pointers */
...
```
I think the comments in the code explain all of that quite well :)

#### I don't really want to use a pointer for my vector ... can I not? 
Sure! Just do this: `VECTOR_IntVector_v vec1 = *NEW_VECTOR_IntVector_v(5);` (Dereferencing the pointer returned by `NEW_VECTOR_name_v()` - It's completely safe I promise (the `_self_ptr` member of the vector helps ensure that this is safe, and no memory is leaked when this sort of dereferencing is performed!).

#### So what functions are there? 
I'm Glad you asked! The functions (_Function Pointers / Methods_) and their operations are listed below:
###### NOTE: ALL of the function pointers listed below expect a pointer to the vector to operate on as the first parameter!
_`elemType` refers to the second parameter passed to the `NEW_VECTOR_TYPE()` macro, `name` refers to the first parameter passed to the `NEW_VECTOR_TYPE()` macro._ 

###### Return the first element in the vector - (`return` type is `elemType`):
``` c
.front(VECTOR_name_v *vec)
```

###### Return the last element in the vector - (`return` type is `elemType`):
``` c
.back(VECTOR_name_v *vec)
```

###### Return the element at the index `n` in the vector - (`return` type is `elemType`):
``` c
.get(VECTOR_name_v *vec, size_t n)
```

###### Return the number of elements in the vector - (`return` type is `size_t`):
``` c
.size(VECTOR_name_v *vec)
```

###### Return the capacity of the vector (the amount of elements memory has been allocated for, explained below) - (`return` type is `size_t`):
``` c
.capacity(VECTOR_name_v *vec)
```

###### Resize the vector `(vec->Elements)` to hold `n` elements (you should never need this - but just incase) - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure):
``` c
.resize(VECTOR_name_v *vec, size_t n) 
```

###### Resize the vector to exactly enough bytes for `vec->Occupied` elements (so that `vec->Occupied` == `vec->Capacity`) - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure):
``` c
.clamp(VECTOR_name_v *vec)
```

###### Add one element (`data`) to the end of the vector - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure):
``` c
.push(VECTOR_name_v *vec, elemType data)
```

###### Remove one element from the end of the vector - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure):
``` c
.pop(VECTOR_name_v *vec)
```

###### Return a pointer to `vec->Elements`. (`return` type is `elemType`):
``` c
.data(VECTOR_name_v *vec)
```

###### Return the size of the `vec->Elements` in bytes - (`return` type `size_t`):
``` c
.bytesize(VECTOR_name_v *vec)
```

###### Insert an element into position `index` in the vector - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure)):
``` c
.insert(VECTOR_name_v *vec, size_t index, elemType data)
```

###### Remove the element in position `index` in the vector - (`return` type is `int`, __0__ on success and __-1__ to indicate (`realloc()`) failure)):
``` c
.remove(VECTOR_name_v *vec, size_t index)
```

#### Why does `vec->Occupied` differ from `vec->Capacity`? 
Good Question! There is quite a bit of overhead involved in calling `malloc()` (and it's family, i.e. `realloc()`) in succession, so like many vector implementations
this header chooses to double the amount of `alloc`'d memory each time the vector's full capacity is reached - However, most vector implementations also "forget" to reduce the amount
of allocated memory when the size of the vector halfs, rest assured that `vector.h` does not forget to reduce the memory when the vector's `occupied` is half of it's `capacity`.

#### Does this leak memory? Have you tested it with [Valgrind](http://valgrind.org/)!?
No, and Yes! No this header does not leak memory (providing that __YOU__ call `DELETE_VECTOR_name_v()`) and yes, it has been tested with [Valgrind](http://valgrind.org/) - It comes back squeaky clean!

#### I found a bug/have an idea/want to contribute - can I? 
YES! You can... I don't byte :) Open an issue on GitHub, send me an email or create a pull request!

