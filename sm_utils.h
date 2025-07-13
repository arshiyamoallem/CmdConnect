#ifndef SM_UTILS_H
#define SM_UTILS_H

#include "sm_structs.h"
#include <stdbool.h>

user_t *register_user(user_t *head, const char *uname, const char *pwd);
user_t *lookup_user(user_t *head, const char *uname);

friend_t *create_friend_node(const char *uname);
void add_new_friend(user_t *user, const char *fname);
bool remove_friend(user_t *user, int index);

post_t *new_post(const char *title, const char *desc);
void push_post(user_t *user, const char *title, const char *desc);
bool pop_post(user_t *user);

void show_posts(user_t *user);
void show_friends(user_t *user);
void browse_posts(user_t *user, int chunk);
void cleanup(user_t *head);

void print_ui_menu();

#endif // SM_UTILS_H
