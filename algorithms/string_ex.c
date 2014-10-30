#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_ex.h"

int main(int argc, char **argv) {
    String s = new_string("This Is a string.", 17);
    printf("%s\n", s);
    printf("%d\n", length(s));
    printf("%d\n", available(s));
    printf("%s\n", to_lower_case(s));
    printf("%s\n", to_upper_case(s));
    destroy_string(s);
    String s1 = new_string("This Is a string.", 17);
    String s2 = new_string("This Is a bTring.", 17);
    if(equals_ignore_case(s1, s2)) {
        printf("True\n");
    }else {
        printf("False\n");
    }
    destroy_string(s1);
    destroy_string(s2);

    String s3 = new_string("    This is a string  .", strlen("    This is a string  ."));
    printf("%d\n", strlen("    This is a string  ."));
    printf("s3=%s\n", ltrim(s3));
    printf("len=%d\n", length(s3));
    String s4 = clone(s3);
    printf("s3=%d, s4=%d\n", s3, s4);
    printf("s4=%s\n", s4);
    destroy_string(s3);
    destroy_string(s4);

    String s5 = new_string("This is a string demo.", strlen("This is a string demo."));
    String s6 = new_string("And it's very simple to use.", strlen("And it's very simple to use."));

    String s7 = concat(s5, s6);
    printf("len5=%d, len6=%d, len7=%d\n", length(s5), length(s6), length(s7));
    printf("s7=%s\n", s7);
    destroy_string(s5);
    destroy_string(s6);
    destroy_string(s7);

    return 0;
}


String new_string(const String s, uint length) {
    StringExRef str = (StringExRef)malloc(sizeof(StringEx) + length + 1);
    if(str == NULL) return NULL;
    str->length = length;
    str->free = 0;
    if(length && s) {
        memcpy(str->buffer, s, length);
    }
    str->buffer[length] = '\0';
    return (String)str->buffer;
}

String to_lower_case(String s) {
    String p = s;
    while(*p != '\0') {
        if(*p >= 'A' && *p <= 'Z') {
			*p += 32;
		}
		p++;
    }
    return s;
}

String to_upper_case(String s) {
    String p = s;
    while(*p != '\0') {
        if(*p >= 'a' && *p <= 'z') {
			*p -= 32;
		}
		p++;
    }
    return s;
}

bool equals(const String s1, const String s2) {
    uint l1 = length(s1);
    uint l2 = length(s2);
    if(l1 != l2) return FALSE;
    uint i;
    for(i = 0; i < l1; i++) {
        if(s1[i] != s2[i])
            return FALSE;
    }
    return TRUE;
}

bool equals_ignore_case(const String s1, const String s2) {
    return equals(to_lower_case(s1), to_lower_case(s2));
}

String ltrim(const String s) {
    StringExRef str = (StringExRef)(s-(sizeof(StringEx)));
    uint len = str->length, i;
    for(i = 0; i < len; i++) {
        if(!isspace(s[i])) break;
    }
    if(i == 0) return s;
    str->length -= i;
    str->free = i;
    uint j = 0;
    while(i <= len) {
        s[j++] = s[i++];
    }
    return s;
}

String rtrim(const String s) {
    StringExRef str = (StringExRef)(s-(sizeof(StringEx)));
    uint len = str->length, i;
    for(i = len; i > 0; i--) {
        if(!isspace(s[i - 1])) break;
        s[i - 1] = '\0';
        s[i] = 0;
    }
    if(i == len) return s;

    str->length = i;
    str->free = len - i;
    uint j = 0;
    while(i <= len) {
        s[j++] = s[i++];
    }
    return s;
}

String trim(const String s) {
    return(ltrim(rtrim(s)));
}

String concat(const String s1, const String s2) {
    if(s1 == NULL || s2 == NULL) return NULL;
    uint len1 = length(s1);
    uint len2 = length(s2);
    uint len = len1 + len2;

    String s = new_string("", len);
    if(s == NULL) return NULL;
    StringExRef str = (StringExRef)(s - (sizeof(StringEx)));
    str->length = len;
    str->free = 0;

    if(len1 && len2 && s1 && s2) {
        memcpy(s, s1, len1);
        memcpy(s + len1, s2, len2);
    }
    str->buffer[len] = '\0';
    return (String)str->buffer;

}

String join(String sa[], uint len, char ch) {
    int i;
    for(i = 0; i < len - 1; i++) {

    }
}

String clone(const String s) {
    StringExRef str = (StringExRef)(s - (sizeof(StringEx)));
    return new_string(s, str->length);
}

void free_string(String s) {
    if(s == NULL) return;
    StringExRef str = (StringExRef)(s-(sizeof(StringEx)));
    free(str);
}
