# CmdConnect - Social-Media-App (text-based)

CmdConnect is a simple, text-based social media application. 
Users can create accounts, change their passwords, manage posts and friends, and view their post timeline—all from a clean terminal interface.

## Features

Create new accounts
Change passwords
Publish and Delete posts with titles and descriptions
Add and Remove friends
Browse published posts

## Prerequisites

Requirements:

- A C compiler (e.g., gcc) (here is a link: https://code.visualstudio.com/docs/cpp/config-mingw)
- A terminal or shell (e.g., IDE terminal, Windows Command Prompt, Linux terminal, macOS Terminal)

## 🛠️ Compiling

Open your terminal in the project folder and run:

```bash
gcc main.c sm_app.c sm_utils.c -o cmdconnect
```

```bash
Run the program:
./cmdconnect    # or .\cmdconnect.exe on Windows
```
 
## File Structure
```
📁 CmdConnect/
├── main.c             # Entry point and UI logic
├── sm_utils.c         # Core functions for posts and friends
├── sm_structs.h       # Data structure definitions (user_t, post_t, etc.)
├── sm_utils.h         # Function declarations
├── README.md          # You're reading it!
```
## Sample:

```
========================================
         Welcome to CmdConnect
========================================

1.  Create Account
2.  Change Password
3.  Manage Posts
4.  Manage Friends
5.  View Posts
6.  Quit

Choose an option:
```
