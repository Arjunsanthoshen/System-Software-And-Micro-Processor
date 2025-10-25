#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 65536 // Simulated 64KB memory

int main() {
    FILE *fp;
    unsigned char memory[MEM_SIZE] = {0}; // Simulated memory
    char line[100], recordType;
    int startAddr = 0, addr = 0, i;
    int initialStartAddr = -1; // To store the first T record start address

    // Open object program file
    fp = fopen("objectcode.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    // Read line by line
    while (fgets(line, sizeof(line), fp)) {
        recordType = line[0];

        if (recordType == 'H') {
            printf("\nHeader Record: %s", line);
        }

        else if (recordType == 'T') {
            // Example: T^001000^1E^141033^281030^300015
            char *token;
            token = strtok(line, "^"); // skip 'T'
            token = strtok(NULL, "^"); // starting address
            sscanf(token, "%x", &startAddr);
            if (initialStartAddr == -1) {
                initialStartAddr = startAddr;  // Save first T record start address
            }
            addr = startAddr;

            token = strtok(NULL, "^"); // skip length
            token = strtok(NULL, "^"); // first object code

            while (token != NULL) {
                // Strip trailing newline and whitespace characters from token
                int len = strlen(token);
                while (len > 0 && (token[len - 1] == '\n' || token[len - 1] == '\r' || token[len - 1] == ' ')) {
                    token[len - 1] = '\0';
                    len--;
                }

                if (token[0] == 'E' || token[0] == 'H' || token[0] == 'T')
                    break;

                printf("Loading %s at address %X\n", token, addr);

                // Convert object code (e.g. "141033") into bytes
                for (i = 0; i < strlen(token); i += 2) {
                    char hexByte[3];
                    hexByte[0] = token[i];
                    hexByte[1] = token[i + 1];
                    hexByte[2] = '\0';
                    memory[addr++] = (unsigned char)strtol(hexByte, NULL, 16);
                }

                token = strtok(NULL, "^"); // next object code
            }
        }

        else if (recordType == 'E') {
            printf("\nEnd Record: %s", line);
            break;
        }
    }

    fclose(fp);

    if (initialStartAddr == -1) {
        printf("No Text records found in the object file.\n");
        return 1;
    }

    // Display a memory dump (first 20 bytes from the first text record start address)
    printf("\nMemory Dump (first 20 bytes from start address %04X):\n", initialStartAddr);
    for (i = initialStartAddr; i < initialStartAddr + 20; i++) {
        printf("%04X : %02X\n", i, memory[i]);
    }

    return 0;
}