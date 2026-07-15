# Task 3 notes

## 1_login.c
Simple username and password check using strcmp.
Username: pooja, Password: 1234
If both match, login successful. If not, login failed.
This is a basic form of user authentication before allowing file access.

## 2_file_ops.c
Basic file operations: create, write, read, delete.
Used fopen with "w" to create and write a note, fopen with "r" to read it back, then remove() to delete it.
Tested by typing a note, it saved correctly, read back correctly, then deleted successfully.

