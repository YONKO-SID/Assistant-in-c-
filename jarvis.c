#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the maximum number of commands and the maximum input length
#define MAX_COMMANDS 6
#define MAX_INPUT 100

int main() {
    // Array of valid commands
    const char *commands[MAX_COMMANDS] = {
        "open notepad",
        "say hello",
        "exit",
        "open firefox",
        "help",
        "cmd"
    };

    // Array of responses for each command (same order as commands[])
    const char *responses[MAX_COMMANDS] = {
        "Opening Notepad...",
        "Hello, human!",
        "Goodbye!",
        "Opening Firefox...",
        "Available commands: open notepad, say hello, open firefox, exit, help, cmd",
        "Opening Command Prompt..."
    };

    char input[MAX_INPUT];
    int running = 1;

    printf("Hello! I am hackoid, your assistant.\n");
    printf("Type any command (type 'help' to see available commands):\n");

    while (running) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        int found = 0; // Flag to check if command is found
        for (int i = 0; i < MAX_COMMANDS; i++) {
            if (strcmp(input, commands[i]) == 0) {
                printf("%s\n", responses[i]);
                found = 1;
                // Perform actions for specific commands
                if (strcmp(input, "open notepad") == 0) {
                    system("notepad");
                } else if (strcmp(input, "open firefox") == 0) {
                    // Try to open Firefox using start (Windows)
                    system("start firefox");
                } else if (strcmp(input, "exit") == 0) {
                    running = 0;
                } else if (strcmp(input, "cmd") == 0) {
                    system("cmd");
                }   
                break; // Command found, exit loop
            }
        }
        if (!found) {
            printf("Sorry, I don't understand that command. Type 'help' for a list of commands.\n");
        }
    }

    return 0;
}
