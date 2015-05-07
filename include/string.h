// string.h string functions

/* Needs to be null terminated */
static inline int strcmp( const char* str1, const char* str2 ) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) { i++; }
    /* if str1[i] == str2[i], means they all equal to '\0' */
    return (str1[i] == str2[i] ? 0 : (str1[i] > str2[i] ? 1 : -1));
}

static inline int char2int( const char c ) {
    return (int) (c - '0');
}

