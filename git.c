#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // if (argc != 3) {
    //     fprintf(stderr, "Usage: %s <username> <email>\n", argv[0]);
    //     return 1;
    // }

    char *username = "rohitwtbs";
    char *email = "12rohit4@gmail.com";

    // Build the git config commands
    char usernameCommand[256];
    snprintf(usernameCommand, sizeof(usernameCommand), "git config --global user.name \"%s\"", username);

    char emailCommand[256];
    snprintf(emailCommand, sizeof(emailCommand), "git config --global user.email \"%s\"", email);

    // Execute the git config commands using system()
    int usernameResult = system(usernameCommand);
    int emailResult = system(emailCommand);

    // Check if the commands were executed successfully
    if (usernameResult == 0 && emailResult == 0) {
        printf("Git username and email updated successfully.\n");
    } else {
        fprintf(stderr, "Failed to update Git username or email.\n");
        if(usernameResult != 0){
            fprintf(stderr, "Username command failed. error code: %d\n", usernameResult);
        }
        if(emailResult != 0){
            fprintf(stderr, "Email command failed. error code: %d\n", emailResult);
        }
        return 1;
    }

    return 0;
}