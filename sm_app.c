// Redesigned Social Media App Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "sm_structs.h"
#include "sm_utils.h"

// Create a new user and insert in alphabetical order
user_t *register_user(user_t *head, const char *uname, const char *pwd) {
    assert(uname && pwd);
    user_t *node = malloc(sizeof(user_t));
    assert(node);
    strcpy(node->username, uname);
    strcpy(node->password, pwd);
    node->friends = NULL;
    node->timeline = NULL;
    node->next = NULL;

    if (!head || strcmp(uname, head->username) < 0) {
        node->next = head;
        return node;
    }

    user_t *ptr = head;
    while (ptr->next && strcmp(uname, ptr->next->username) > 0)
        ptr = ptr->next;

    node->next = ptr->next;
    ptr->next = node;
    return head;
}

user_t *lookup_user(user_t *head, const char *uname) {
    assert(uname);
    while (head) {
        if (strcmp(head->username, uname) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

friend_t *create_friend_node(const char *uname) {
    friend_t *f = malloc(sizeof(friend_t));
    assert(f);
    strcpy(f->username, uname);
    f->next = NULL;
    return f;
}

void add_new_friend(user_t *user, const char *fname) {
    assert(user && fname);
    friend_t *f = create_friend_node(fname);
    if (!user->friends || strcmp(fname, user->friends->username) < 0) {
        f->next = user->friends;
        user->friends = f;
        return;
    }
    friend_t *cur = user->friends;
    while (cur->next && strcmp(fname, cur->next->username) > 0)
        cur = cur->next;
    f->next = cur->next;
    cur->next = f;
}

bool remove_friend(user_t *user, int index) {
    assert(user);
    if (index < 0) return false;

    friend_t *cur = user->friends;
    friend_t *prev = NULL;

    int i = 0;
    while (cur && i < index) {
        prev = cur;
        cur = cur->next;
        i++;
    }

    if (!cur) return false; 

    if (!prev)
        user->friends = cur->next; 
    else
        prev->next = cur->next;

    free(cur);
    return true;
}

post_t *new_post(const char *title, const char *desc) {
    post_t *p = malloc(sizeof(post_t));
    assert(p);
    strncpy(p->title, title, sizeof(p->title) - 1);
    p->title[sizeof(p->title) - 1] = '\0';
    strncpy(p->description, desc, sizeof(p->description) - 1);
    p->description[sizeof(p->description) - 1] = '\0';
    p->next = NULL;
    return p;
}


void push_post(user_t *user, const char *title, const char *desc) {
    post_t *p = new_post(title, desc);
    p->next = user->timeline;
    user->timeline = p;
}

bool pop_post(user_t *user) {
    if (!user->timeline) {
        printf("No posts to delete.\n\n");
        return false;
    }

    printf("\n=== Your Posts ===\n");
    show_posts(user);
    printf("\nEnter the number of the post to delete (0 to cancel): ");

    int choice;
    scanf("%d", &choice);
    if (choice <= 0) return false;

    post_t *cur = user->timeline, *prev = NULL;
    int idx = 1;
    while (cur && idx < choice) {
        prev = cur;
        cur = cur->next;
        idx++;
    }

    if (!cur) {
        printf("Invalid post number.\n\n");
        return false;
    }

    if (!prev) user->timeline = cur->next;
    else prev->next = cur->next;

    printf("Deleted post: %s\n\n", cur->title);
    free(cur);
    return true;
}


void show_posts(user_t *user) {
    post_t *p = user->timeline;
    int idx = 1;
    while (p) {
        printf("%d. %s: %s\n", idx++, p->title, p->description); 
        p = p->next;
    }
}

void show_friends(user_t *user) {
    friend_t *f = user->friends;
    int idx = 1;
    while (f) {
        printf("%d. %s\n", idx++, f->username);
        f = f->next;
    }
}

void browse_posts(user_t *user, int chunk) {
    post_t *p = user->timeline;
    char ans;
    if (p == NULL)
    {
        printf("No posts\n"); 
        return;
    }

    while (p) {
        for (int i = 0; i < chunk && p; i++, p = p->next)
            printf("%s: %s\n", p->title, p->description);

        if (!p) break;
        printf("\nWould you like to see more posts? (y/n): ");
        scanf(" %c", &ans);
        if (ans != 'y' && ans != 'Y') break;
    }
}


void cleanup(user_t *head) {
    while (head) {
        user_t *next_user = head->next;

        friend_t *f = head->friends;
        while (f) {
            friend_t *nf = f->next;
            free(f);
            f = nf;
        }

        post_t *p = head->timeline;
        while (p) {
            post_t *np = p->next;
            free(p);
            p = np;
        }

        free(head);
        head = next_user;
    }
}

void print_ui_menu() {
    printf("\n");
    for (int i = 0; i < 40; i++) printf("=");
    printf("\n      Welcome to CmdConnect\n");
    for (int i = 0; i < 40; i++) printf("=");
    printf("\n\n");
    printf("1.  Create Account\n");
    printf("2.  Change Password\n");
    printf("3.  Manage Posts\n");
    printf("4.  Manage Friends\n");
    printf("5.  View Posts\n");
    printf("6.  Quit\n");
    printf("\nChoose an option: ");
}


