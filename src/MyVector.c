#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// REFER: https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc

#define MyVectorTemplate(DataType, Suffix)                                      \
                                                                                \
    struct MyVector ## Suffix {                                                 \
        int32_t n, nMax;                                                        \
        DataType* arr;                                                          \
    };                                                                          \
                                                                                \
    /* RETURNS: true if resize was successful */                                \
    bool mv_resize ## Suffix (struct MyVector ## Suffix *mv, int32_t newSize) { \
        DataType *arrNew = realloc(mv->arr, sizeof(DataType) * newSize);        \
        if(arrNew != NULL) {                                                    \
            mv->arr = arrNew;                                                   \
            mv->nMax = newSize;                                                 \
        }                                                                       \
        return arrNew != NULL;                                                  \
    }                                                                           \
                                                                                \
    /* RETURNS: true if push_back was successful */                             \
    bool mv_push_back ## Suffix (struct MyVector ## Suffix *mv, DataType val) { \
        if(mv->n == mv->nMax) {                                                 \
            if(! (mv_resize ## Suffix (mv, mv->nMax * 2))) {                    \
                /* if resize fails */                                           \
                return false;                                                   \
            }                                                                   \
        }                                                                       \
        mv->arr[mv->n] = val;                                                   \
        mv->n += 1;                                                             \
        return true;                                                            \
    }                                                                           \
                                                                                \
    /* RETURNS: true if push_back was successful */                             \
    bool mv_push_back_default ## Suffix (struct MyVector ## Suffix *mv) {       \
        if(mv->n == mv->nMax) {                                                 \
            if(! (mv_resize ## Suffix (mv, mv->nMax * 2))) {                    \
                /* if resize fails */                                           \
                return false;                                                   \
            }                                                                   \
        }                                                                       \
        mv->n += 1;                                                             \
        return true;                                                            \
    }                                                                           \
                                                                                \
    /* RETURNS: the last element popped */                                      \
    DataType mv_pop_back ## Suffix (struct MyVector ## Suffix *mv) {            \
        if(mv->n <= 1) mv->n = 0;                                               \
        else mv->n -= 1;                                                        \
        return mv->arr[mv->n];                                                  \
    }                                                                           \
                                                                                \
    /* RETURNS: the last element popped */                                      \
    DataType mv_pop_back_n ## Suffix (struct MyVector ## Suffix *mv, int32_t popCount) {  \
        if(popCount <= 0) return mv->arr[0];                                    \
        if(mv->n <= popCount) mv->n = 0;                                        \
        else mv->n -= popCount;                                                 \
        return mv->arr[mv->n];                                                  \
    }                                                                           \
                                                                                \
    /* Removes all elements from the vector */                                  \
    void mv_clear ## Suffix (struct MyVector ## Suffix *mv) {                   \
        mv->n = 0;                                                              \
    }                                                                           \
                                                                                \
    /* Destructor */                                                            \
    void mv_free ## Suffix (struct MyVector ## Suffix *mv) {                    \
        free(mv->arr);                                                          \
    }                                                                           \
                                                                                \
    /* Constructor */                                                           \
    void mv_init ## Suffix (struct MyVector ## Suffix *mv, int32_t defSize) {   \
        mv->n = 0;                                                              \
        mv->nMax = defSize;                                                     \
        mv->arr = malloc(sizeof(DataType) * mv->nMax);                          \
    }


/*

Usage:
    MyVectorTemplate(char, _CHAR);


Data Members:
    // char_vector.arr   --->  same as "std::vector::data()" of C++     , i.e. Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
    // char_vector.nMax  --->  same as "std::vector::capacity()" of C++ , i.e. Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
    // char_vector.n     --->  same as "std::vector::size()" of C++     , i.e. Returns the number of elements in the vector.


Function Available:

    // Create an object instance
    struct MyVector_CHAR char_vector;

    // CONSTRUCTOR - the capacity will be 1024, but the vector will be empty
    mv_init_CHAR(&char_vector, 1024);

    // RETURNS: true if push_back was successful
    // same as std::vector::push_back(val) of C++, i.e. Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
    mv_push_back_CHAR(&char_vector, 'A');
    mv_push_back_default_CHAR(&char_vector);  // garbage value is pushed to the end of the vector

    // RETURNS: the last element popped
    // same as std::vector::pop_back() of C++, i.e. Removes the last element in the vector, effectively reducing the container size by one.
    mv_pop_back_CHAR(&char_vector);
    mv_pop_back_n_CHAR(&char_vector, 1);

    // RETURNS: true if resize was successful
    // same as std::vector::resize(n) of C++, i.e. Resizes the container so that it contains n elements.
    mv_resize_CHAR(&char_vector, 2048);

    // same as std::vector::clear() of C++, i.e. Removes all elements from the vector, leaving the container with a size of 0.
    mv_clear_CHAR(&char_vector);

    // DESTRUCTOR
    mv_free_CHAR(&char_vector);

 * */
