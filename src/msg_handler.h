#ifndef CHIRC_HANDLER_H_
#define CHIRC_HANDLER_H_

#include <stdbool.h>
#include "server_info.h"

/* This struct holds data received from the client
 * until a complete command has been received;
 * then we renew it to hold the next command
 */
typedef struct msg
{
    /* msg buffer holds the data we receive about a command */
    char *msg;
    /* keep track of where in the array msg we have filled with data */
    int counter;
    /* keep track of whether a NICK command has been sent yet */
    bool nick_cmd;
    /* keep track of whether a USER command has been sent yet */
    bool user_cmd;
} msg_t;

/* This struct breaks down a complete command 
 * into command and parameters
 */
typedef struct cmd {
    /* This will be the first string in the command line */
    char* command;
    /* How many params a certain command requires */
    int num_params;
    /* each element in the array will represent a parameter in order */
    char *params[MAX_PARAMS];
} cmd_t;


/* IRC server's message handler helper functions */

/* This function takes in data received from the buffer
 * and assemble it into separate commands
 * and feed each complete command to exec_msg function.
 * It also takes in the client hashtable, client's server info
 * and host server info to pass these inputs to exec_msg
 */
msg_t recv_msg(char *buf, msg_t rmsg, client_info_t **clients,
                int client_socket, char *client_hostname, 
                char *server_hostname);

/* This function parses a complete command and 
 * breaks it down into command part and parameters part
 */
cmd_t parse_msg(char *buffer);

/* This function executes commands sent by client;
 * specifically, it checks conditions and returns
 * the reply welcome when user correctly registers in the server
 */
void exec_msg(int client_socket, client_info_t **clients, 
                char *client_hostname, char *server_hostname, cmd_t msg);

#endif