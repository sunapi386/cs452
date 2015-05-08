#define BUFFERSIZE 1024
typedef struct Buffer {
    int count;
    char elements[BUFFERSIZE]; /* slightly larger buffer */
} buffer_t;


/* TODO: memcpy should be put somewhere more appropriate than in kernel */
static inline void memcpy( char *destaddr, char *srcaddr, int len ) {
    while ( len-- ) *destaddr++ = *srcaddr++;
}


static inline int BufferInsert( buffer_t *b, char c ) {
    if( b->count == BUFFERSIZE ) {
        PRINT( "[WARN] Input buffer full!" );
        return -1;
    }
    b->elements[b->count] = c;
    b->count++;
    return 0;
}

static inline void BufferEmpty( buffer_t *b ) {
    int i;
    for(i = 0; i < b->count; i++ ) {
        b->elements[i] = '\0';
    }
    b->count = 0;
}

static inline void BufferBackspace( buffer_t *b ) {
    b->count--;
    b->elements[b->count] = '\0'; /* Nulify the last entry */
}

static inline void BufferCopy( buffer_t *src, buffer_t *dst ) {
    dst->count = src->count;
    memcpy( dst->elements, src->elements, BUFFERSIZE );
}
