#ifndef SM_STRUCTS_H
#define SM_STRUCTS_H

typedef struct friend {
    char username[30];
    struct friend *next;
} friend_t;

typedef struct post {
    char title[50];
    char description[250];
    struct post *next;
} post_t;

typedef struct user {
    char username[30];
    char password[30];
    friend_t *friends;
    post_t *timeline;
    struct user *next;
} user_t;

#endif // SM_STRUCTS_H
