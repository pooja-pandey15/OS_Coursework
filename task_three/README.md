# Task 3: File System Operations and Security

Simple examples showing file operations, permissions, encryption, and audit logging.
Scenario used: a personal notes app where a user logs in and manages private notes.

## Files

- 1_login.c - simple username and password check
- 2_file_ops.c - create, write, read, and delete a note file
- 3_permissions.c - sets file permissions so only the owner can read/write
- 4_encryption.c - simple XOR encryption and decryption of a note
- 5_audit_log.c - logs file actions with timestamps to audit.log

## How to compile and run

```bash
gcc 1_login.c -o 1_login
./1_login
```

Same pattern for files 2 to 5, no extra libraries needed except standard C libraries (string.h, time.h, sys/stat.h where used).

## Notes

See notes.md for what each file does and the results.
Screenshots of the output are in the screenshots folder.
