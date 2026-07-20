# Task 4: Network Programming and IPC

Simple examples showing client-server communication using sockets.
Scenario used: a print server that accepts print job requests from client computers over the network.

## Files

- 1_server.c - basic server, accepts one client and receives a print job
- 2_client.c - basic client, connects and sends a print job
- 3_server_multi.c - server handles 3 clients one after another
- 4_auth_check.c - server requires a valid login before accepting a job
- 5_auth_client.c - client that sends login credentials before sending a job

## How to compile and run

Each pair (server + client) needs two terminal windows - run the server first, then the client.

```bash
gcc 1_server.c -o 1_server
gcc 2_client.c -o 2_client
```

In terminal 1:
```bash
./1_server
```

In terminal 2 (while server is running):
```bash
./2_client
```

Same pattern for 3_server_multi.c (run alone, handles 3 client connections using 2_client.c),
and 4_auth_check.c with 5_auth_client.c (login: username pooja, password 1234).

## Notes

See notes.md for what each file does and the results.
Screenshots of the output are in the screenshots folder.
