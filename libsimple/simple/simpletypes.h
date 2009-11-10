#ifndef __defined_simple_types_h
#define __defined_simple_types_h

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*sfree_mem_t) (void *obj);
typedef void * (*siter_t) (void *udata, void *data);
typedef int (sfilter_t) (void *udata, void *data);

#ifdef __cplusplus
}
#endif

#endif // __defined_simple_types_h
