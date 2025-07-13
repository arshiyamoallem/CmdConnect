#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sm_structs.h"
#include "sm_utils.h"

int main() {
    user_t *users = NULL;
    int choice, index;
    char uname[30], pwd[30];
    char post_title[50], post_desc[250], friend_name[30];
    user_t *user = NULL;

    while (true) {
        print_ui_menu();
        if (scanf("%d", &choice) != true) {
            printf("Invalid input. Please enter a number.\n\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }  
        printf("\n");

        switch (choice) {
            case 1:
                printf("Enter new username: ");
                scanf("%s", uname);
                printf("Enter password: ");
                scanf("%s", pwd);
                users = register_user(users, uname, pwd);
                printf("User '%s' registered successfully!\n\n", uname);
                break;

            case 2:
                printf("Enter your username: ");
                scanf("%s", uname);
                user = lookup_user(users, uname);
                if (user) {
                    char attempt[15];
                    int tries = 3;
                    while (tries--) {
                        printf("Enter your password: ");
                        scanf("%s", attempt);
                        if (strcmp(attempt, user->password) == 0) {
                            printf("Enter new password: ");
                            scanf("%s", pwd);
                            strncpy(user->password, pwd, 14);
                            user->password[14] = '\0';
                            printf("Password updated!\n\n");
                            break;
                        } else {
                            printf("Incorrect password. Try again.\n");
                        }
                    }
                    if (tries < 0)
                        printf("Too many failed attempts. Returning to menu.\n\n");
                } else {
                    printf("User not found.\n\n");
                }
                break;


            case 3:
                printf("Username: ");
                scanf("%s", uname);
                user = lookup_user(users, uname);
                if (!user) {
                    printf("User not found.\n\n");
                    break;
                }

                while (1) {
                    printf("1. Add Post\n2. Delete Post\n3. Back\n> ");
                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a number.\n\n");
                        while (getchar() != '\n'); // clear buffer
                        continue;
                    }

                    if (choice == 1) {
                        printf("Enter post title: ");
                        scanf(" %[^\n]s", post_title);
                        printf("Enter post description: ");
                        scanf(" %[^\n]s", post_desc);
                        push_post(user, post_title, post_desc);
                        printf("Post added.\n\n");

                    } else if (choice == 2) {
                        if (!pop_post(user)) {
                            printf("No post deleted.\n\n");
                        }

                    } else if (choice == 3) {
                        break;  // exit the Manage Posts submenu

                    } else {
                        printf("Invalid option. Please select 1, 2, or 3.\n\n");
                    }
                }
                break;

            case 4:
                printf("Username: ");
                scanf("%s", uname);
                user = lookup_user(users, uname);
                if (!user) {
                    printf("User not found.\n\n");
                    break;
                }

                while (1) {
                    printf("1. Add Friend\n2. Remove Friend\n3. Back\n> ");
                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a number.\n\n");
                        while (getchar() != '\n'); // clear buffer
                        continue;
                    }

                    if (choice == 1) {
                        printf("Friend's username: ");
                        scanf("%s", friend_name);
                        add_new_friend(user, friend_name);
                        printf("Friend added.\n\n");

                    } else if (choice == 2) {
                        if (!user->friends) {
                            printf("No friends to remove.\n\n");
                            continue;
                        }
                        printf("\n=== Your Friends ===\n");
                        show_friends(user);
                        printf("\nEnter the number of the friend to remove (0 to cancel): ");

                        int index;
                        if (scanf("%d", &index) != 1) {
                            printf("Invalid input. Please enter a number.\n\n");
                            while (getchar() != '\n'); // clear buffer
                            continue;
                        }

                        if (index == 0) {
                            printf("Cancelled removal.\n\n");
                            continue;
                        }

                        if (remove_friend(user, index - 1)) { // zero-based index internally
                            printf("Friend removed.\n\n");
                        } else {
                            printf("Invalid friend number.\n\n");
                        }

                    } else if (choice == 3) {
                        break;  // exit Manage Friends submenu

                    } else {
                        printf("Invalid option. Please select 1, 2, or 3.\n\n");
                    }
                }
                break;

            case 5:
                printf("Enter username to view posts: ");
                scanf("%s", uname);
                user = lookup_user(users, uname);
                if (!user) {
                    printf("User not found.\n\n");
                    break;
                }
                browse_posts(user, 3);
                break;

            case 6:
                cleanup(users);
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Try again.\n\n");
        }
    }
}
