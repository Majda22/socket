
Description:

This repository contains a socket programming project comprising client, server, router 1, and router 2 implementations. Follow these steps to execute the project on Linux/Ubuntu:

<strong>Execution:</strong>

You can directly execute the project using the following commands in three separate terminals:

- Run the server:

./server.exe

- Run the router:

./router.exe

- Run the client:

./client.exe

*Compilation:*

If you wish to compile the project from source, follow these steps:

Compile the client:


gcc -c client.c
gcc client.o majda.o -o client.exe

Compile the router:

gcc -c router.c
gcc router.o majda.o -o router.exe
Compile the server:

gcc -c server.c
gcc server.o majda.o -o server.exe

*Additional Information:*

majda.c is the file containing all the functions of the project.
Make sure to run each component (server, router, client) in separate terminals for proper execution.
Feel free to explore the source code to understand the project's functionality and structure.
if you need help, please contact me : contactmajdaelhasnaoui@gmail.com

