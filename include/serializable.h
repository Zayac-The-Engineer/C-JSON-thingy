#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#include "field.h"
#include <stdio.h>

Value get_value(Serializable *self, char *key);
char *Serializeable_to_JSON(Serializable *self);
void Serializeable_destroy(Serializable *self);
Serializable *Serializeable_from_JSON(char *json_string);

#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define DEFINE_STRUCT(struct_name, ...)\
struct struct_name {\
    size_t size;\
    Field fields[NUM_ARGS(__VA_ARGS__)];\
};\
const size_t struct_name##_size = NUM_ARGS(__VA_ARGS__);\
struct_name struct_name##_create(__VA_ARGS__) {\
    struct_name self = {.size = struct_name##_size};\
    size_t i = 0;

// To be used to initialize fields in serializeable struct constructor
#define FIELD_INT(value) {\
    self.fields[i] = (Field){#value, ValueType_Integer, {.integer = value}};\
    i++;\
}

#define FIELD_STR(value) {\
    char *buffer_##__LINE__ = malloc(128);\
    self.fields[i] = (Field){#value, ValueType_String, {.string = strncpy(buffer_##__LINE__, value, 128)}};\
    i++;\
}

#define FIELD_SERIALIZEABLE(value) {\
    self.fields[i] = (Field){#value, ValueType_Serializable, {.object = value}};\
    i++;\
}

#define STRUCT_END return self;}

#endif // SERIALIZABLE_H_