#ifndef STRING_EX_H_INCLUDED
#define STRING_EX_H_INCLUDED

typedef char* String;
typedef char** StringRef;
typedef int bool;
typedef unsigned int uint;

typedef struct StringEx{
    uint length;
    uint free;
    char buffer[];
}StringEx, *StringExRef;


//typedef struct StringArray {
//    uint length;
//    uint free;
//    String ss[];
//}StringArray, *StringArrayRef;

#define TRUE 1
#define FALSE 0

static inline uint length(const String s) {
    StringExRef str = (StringExRef)(s-(sizeof(StringEx)));
    return str->length;
}

static inline uint available(const String s) {
    StringExRef str = (StringExRef)(s-(sizeof(StringEx)));
    return str->free;
}

String new_string(const String s, unsigned int length);
String to_lower_case(const String s);
String to_upper_case(const String s);
String trim(const String s);
String ltrim(const String s);
String rtrim(const String s);
StringRef split(const String s, const String delim);
String join(String sa[], uint len, char ch);
String concat(const String s1, const String s2);
bool equals(const String s1, const String s2);
bool equals_ignore_case(const String s1, const String s2);
// Use destroy_string instead
void free_string(String s);
String clone(const String s);

#define destroy_string(s) free_string(s); \
    s = NULL

#endif // STRING_EX_H_INCLUDED
