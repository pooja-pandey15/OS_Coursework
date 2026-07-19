# Task 4 notes

## 1_server.c and 2_client.c
Basic client-server using sockets. Server listens on port 8080, waits for one client.
Client connects, sends a print job message as text, server receives it and replies with a confirmation message.
Tested by running server in one terminal and client in another - server received the exact message sent, and client received the server's reply correctly.
This is a simple example of IPC (inter-process communication) over a network socket, even though both were run on the same machine (localhost / 127.0.0.1).


## 3_server_multi.c
Same idea as before but server now handles 3 clients one after another using a for loop, instead of just 1 and quitting.
Each client gets a reply with its own job number (Job 1, Job 2, Job 3).
Tested by running the client program 3 separate times while the server was running - all 3 were handled correctly and the server closed itself after the 3rd one.
This shows a server can serve more than one client, just handled one at a time here to keep it simple.

