/* Prototypes for __malloc_hook, __free_hook */
#include <malloc.h>

/* Prototypes for our hooks.  */
static void my_init_hook(void);

static void *my_malloc_hook(size_t, const void *);

static void *my_realloc_hook(void *, size_t, const void *);

static void *my_memalign_hook(size_t, size_t, const void *);

static void *my_free_hook(void *, const void *);

/* Variables to save original hooks */
static void *(*old_malloc_hook)(size_t, const void *);

static void *(*old_realloc_hook)(void *, size_t, const void *);

static void *(*old_memalign_hook)(size_t, size_t, const void *);

static void (*old_free_hook)(void *, const void *);

/* Override initializing hook from the C library. */
void (*__malloc_initialize_hook)(void) = my_init_hook;

static void my_init_hook(void) {
    printf("my_init_hook \n");
    old_malloc_hook = __malloc_hook;
    __malloc_hook = my_malloc_hook;
    //----------------------------------
    old_realloc_hook = __realloc_hook;
    __realloc_hook = my_realloc_hook;
    //----------------------------------
    old_memalign_hook = __memalign_hook;
    __memalign_hook = my_memalign_hook;
    //----------------------------------
    old_free_hook = __free_hook;
    __free_hook = my_free_hook;
}

static void *my_malloc_hook(size_t size, const void *caller) {
    void *result;
    /* Restore all old hooks */
    __malloc_hook = old_malloc_hook;
    /* Call recursively */
    result = malloc(size);
    /* Save underlying hooks */
    old_malloc_hook = __malloc_hook;
    /* printf() might call malloc(), so protect it too */
    printf("malloc(%zu) called from %p returns %p\n", size, caller, result);
    /* Restore our own hooks */
    __malloc_hook = my_malloc_hook;
    return result;
}

static void *my_realloc_hook(void *ptr, size_t size, const void *caller) {
    void *result;
    /* Restore all old hooks */
    __realloc_hook = old_realloc_hook;
    /* Call recursively */
    result = realloc(ptr, size);
    /* Save underlying hooks */
    old_realloc_hook = __realloc_hook;
    /* printf() might call realloc(), so protect it too */
    printf("realloc(%zu) called from %p returns %p\n", size, caller, result);
    /* Restore our own hooks */
    __realloc_hook = my_realloc_hook;
    return result;
}

static void *my_memalign_hook(size_t alignment, size_t size, const void *caller) {
    void *result;
    /* Restore all old hooks */
    __memalign_hook = old_memalign_hook;
    /* Call recursively */
    result = memalign(alignment, size);
    /* Save underlying hooks */
    old_memalign_hook = __memalign_hook;
    /* printf() might call realloc(), so protect it too */
    printf("memalign(%zu) called from %p returns %p\n", size, caller, result);
    /* Restore our own hooks */
    __memalign_hook = my_memalign_hook;
    return result;
}

static void *my_free_hook(void *ptr, const void *caller) {
    /* Restore all old hooks */
    __free_hook = old_free_hook;
    /* Call recursively */
    free(ptr);
    /* Save underlaying hooks */
    old_free_hook = __free_hook;
    /* printf might call free, so protect it too. */
   // printf("freed called from %p pointer %p\n", caller, ptr);
    /* Restore our own hooks */
    __free_hook = my_free_hook;
}
