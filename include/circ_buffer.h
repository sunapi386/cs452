/* circ_buffer.h */
#ifndef __CIRC_BUFFER_H
#define __CIRC_BUFFER_H
#define CIRC_BUF_SIZE      1024
#define CIRC_NAME_SIZE      32
#include <bool.h>

typedef struct CircularBuffer {
    int front;
    int back;
    int count;
    int last_access_time;
    char name[CIRC_NAME_SIZE + 2];
    char elements[CIRC_BUF_SIZE + 2]; /* slightly larger buffer */
} circ_buffer_t;

static inline void CB_Clean( circ_buffer_t *b ) {
    b->front = b->back = b->count = b->last_access_time = 0;
    int i;
    for( i = 0; i < CIRC_NAME_SIZE + 2; i++ ) { b->name[i] = '\0'; }
    for( i = 0; i < CIRC_BUF_SIZE + 2; i++ ) { b->name[i] = '\0'; }
}

static inline char CB_Pop( circ_buffer_t *b ) { /* Unsafe poping */
    if( b-> count <= 0 ) { return '!'; }
    char ch = b->elements[b->front];
    b->front = (b->front + 1) % CIRC_BUF_SIZE;
    b->count -= 1;
    b->last_access_time = 0;
    return ch;
}

static inline int CB_Insert( circ_buffer_t *b, char c ) {
    b->elements[b->back] = c;
    b->back = (b->back + 1) % CIRC_BUF_SIZE;
    b->count += 1;
    return b->count;
}

static inline bool CB_IsFull( const circ_buffer_t *b ) {
    return (bool)(b->count == CIRC_BUF_SIZE);
}

static inline bool CB_IsEmpty( const circ_buffer_t *b ) {
    return (bool)(b->count == 0);
}


// /* TODO: memcpy should be put somewhere appropriate */
// static inline void memcpy( char *destaddr, char *srcaddr, int len ) {
//     while ( len-- ) *destaddr++ = *srcaddr++;
// }


// static inline int CircBufferInsert( circ_buffer_t *b, char c ) {
//     if( b->count == BUFFERSIZE ) {
//         PRINT( "[WARN] Input buffer full!" );
//         return -1;
//     }
//     b->elements[b->count] = c;
//     b->count++;
//     return 0;
// }

// static inline void CircBufferEmpty( circ_buffer_t *b ) {
//     int i;
//     for(i = 0; i < b->count; i++ ) {
//         b->elements[i] = '\0';
//     }
//     b->count = 0;
// }

// static inline void CircBufferBackspace( circ_buffer_t *b ) {
//     b->count--;
//     b->elements[b->count] = '\0'; /* Nulify the last entry */
// }

// static inline void CircBufferCopy( circ_buffer_t *src, circ_buffer_t *dst ) {
//     dst->count = src->count;
//     memcpy( dst->elements, src->elements, BUFFERSIZE );
// }
#endif
