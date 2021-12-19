#include "include/string.h"

void* memcpy(void* dst, const void* src, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = ((char*) src)[count];
    return dst;
}

void* memset(void* dst, char value, size_t count) {
    while (count-- > 0)
        ((char*) dst)[count] = value;
    return dst;
}

void byte_swap(uint8_t *data, int len) {
    int i;
    uint8_t temp;
    for(i = 0; i < len; i += 2) {
        temp = data[i];
        data[i] = data[i+1];
        data[i+1] = temp;
    }
}

char* strcpy(char *dest, const char *src) {
    return memcpy(dest, src, strlen(src) + 1);
}

size_t strlen(const char* str){
    const char *char_ptr;
    const unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;

    for (char_ptr = str; ((unsigned long int) char_ptr
                          & (sizeof (longword) - 1)) != 0;
         ++char_ptr)
        if (*char_ptr == '\0')
            return char_ptr - str;

    longword_ptr = (unsigned long int *) char_ptr;

    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if(sizeof (longword) > 4){
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }

    if(sizeof (longword) > 8) abort();
    while(1) {
        longword = *longword_ptr++;
        if (((longword - lomagic) & ~longword & himagic) != 0){
            const char *cp = (const char *) (longword_ptr - 1);
            if (cp[0] == 0)
                return cp - str;
            if (cp[1] == 0)
                return cp - str + 1;
            if (cp[2] == 0)
                return cp - str + 2;
            if (cp[3] == 0)
                return cp - str + 3;
            if (sizeof (longword) > 4){
                if (cp[4] == 0)
                    return cp - str + 4;
                if (cp[5] == 0)
                    return cp - str + 5;
                if (cp[6] == 0)
                    return cp - str + 6;
                if (cp[7] == 0)
                    return cp - str + 7;
            }
        }
    }
}

int strcmp(const char *p1, const char *p2) {
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}

char* appendCharToCharArray(char* array, char a) {
    size_t len = strlen(array);

    char* ret = malloc((len+2)*sizeof(*ret));

    strcpy(ret, array);
    ret[len] = a;
    ret[len+1] = '\0';

    return ret;
}