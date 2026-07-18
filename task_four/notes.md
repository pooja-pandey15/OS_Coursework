# Task 4 notes

## 1_server.c and 2_client.c
Basic client-server using sockets. Server listens on port 8080, waits for one client.
Client connects, sends a print job message as text, server receives it and replies with a confirmation message.
Tested by running server in one terminal and client in another - server received the exact message sent, and client received the server's reply correctly.
This is a simple example of IPC (inter-process communication) over a network socket, even though both were run on the same machine (localhost / 127.0.0.1).
