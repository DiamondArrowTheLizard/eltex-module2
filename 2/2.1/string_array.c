#include "string_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_ARRAY_INIT_CAPACITY 10

string_array* string_array_init()
{
    string_array* array = (string_array*)malloc(sizeof(*array));
    array->strings = NULL;
    array->count = 0;
    array->capacity = STRING_ARRAY_INIT_CAPACITY;

    return array;
}

void string_array_destroy(string_array* array)
{
    if(array == NULL) return;

    for(size_t i = 0; i < array->count; i++)
    {
        free(array->strings[i]);
        array->strings[i] = NULL;
    }
    free(array->strings);
    array->strings = NULL;

    array->count = 0;
    array->capacity = 0;

    free(array);
    array = NULL;
}

int string_array_append(string_array* array, char* string)
{
    if(array == NULL) return 0;

    if(array->count >= array->capacity)
    {
        if(array->capacity == 0) array->capacity = STRING_ARRAY_INIT_CAPACITY;
        else array->capacity *= 2;

        array->strings = realloc(array->strings, array->capacity * sizeof(*array->strings));
        strncpy(array->strings[array->count++], string, strlen(string));
    }
    return 1;
}

int string_array_remove(string_array* array, size_t index)
{
    if(array == NULL) return 0;

    string_array* new_array = string_array_init();
    for (size_t i = 0; i < array->count; i++)
    {
        if(i == index) continue;
        else string_array_append(new_array, array->strings[i]);
    }

    string_array_destroy(array);
    array = new_array;

    return 1;
}

void string_array_print_all(string_array* array)
{
    for(size_t i = 0; i < array->count; i++)
    {
        printf("%s\n", array->strings[i]);
    }
}

int string_array_print_at_index(string_array* array, size_t index)
{
    if(index >= array->count) return 0;
    printf("%s\n", array->strings[index]);

    return 1;
}
