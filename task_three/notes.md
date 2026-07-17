# Task 3 notes

## 1_login.c
Simple username and password check using strcmp.
Username: pooja, Password: 1234
If both match, login successful. If not, login failed.
This is a basic form of user authentication before allowing file access.

## 2_file_ops.c
Basic file operations: create, write, read, delete.
Used fopen with "w" to create and write a note, fopen with "r" to read it back,
 then remove() to delete it.
Tested by typing a note, it saved correctly, read back correctly,
 then deleted successfully.

## 3_permissions.c
Created a file and used chmod to set permission: only owner can read/write, no access for group or others.
Used stat to check the permission bits and print them out.
Confirmed with ls -l that Linux shows the same permission (-rw-------).

## 4_encryption.c
Simple XOR cipher to encrypt/decrypt a note.
Each character is XORed with a fixed key ('K'). XORing again with the same key undoes it, which is why encrypt and decrypt use the same function.
Tested with "bank password is 5566" - encrypted text was unreadable,
 decrypted text matched the original exactly.
This is a simple demonstration, not real-world secure encryption,
 but shows the basic idea of protecting sensitive file content.
