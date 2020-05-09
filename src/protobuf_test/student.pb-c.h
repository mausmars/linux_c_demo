/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: student.proto */

#ifndef PROTOBUF_C_student_2eproto__INCLUDED
#define PROTOBUF_C_student_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Student Student;


/* --- enums --- */


/* --- messages --- */

struct  _Student
{
  ProtobufCMessage base;
  char *id;
  char *name;
  char *gender;
  int32_t age;
  char *object;
  char *home_address;
  char *phone;
};
#define STUDENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&student__descriptor) \
    , NULL, NULL, NULL, 0, NULL, NULL, NULL }


/* Student methods */
void   student__init
                     (Student         *message);
size_t student__get_packed_size
                     (const Student   *message);
size_t student__pack
                     (const Student   *message,
                      uint8_t             *out);
size_t student__pack_to_buffer
                     (const Student   *message,
                      ProtobufCBuffer     *buffer);
Student *
       student__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   student__free_unpacked
                     (Student *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Student_Closure)
                 (const Student *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor student__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_student_2eproto__INCLUDED */
