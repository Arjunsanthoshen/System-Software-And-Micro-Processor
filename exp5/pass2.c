#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *str) {
    int i = 0, j = 0;
    while (isspace((unsigned char)str[i])) i++;  
    while (str[i]) str[j++] = str[i++];
    str[j] = '\0';
    while (j > 0 && isspace((unsigned char)str[j - 1])) str[--j] = '\0';
}

int main() {
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20];
    char symbol[20], address[20];
    char line[100], objcode[50];
    int loc, startAddr = 0, progLen = 0;
    char progName[20] = "";

    FILE *intermediate = fopen("output.txt", "r");
    FILE *optab = fopen("optab.txt", "r");
    FILE *symtab = fopen("symtab.txt", "r");
    FILE *codeFile = fopen("code.txt", "w");
    FILE *programFile = fopen("program.txt", "w");

    if (!intermediate || !optab || !symtab || !codeFile || !programFile) {
        printf("Error opening files.\n");
        return 1;
    }

    if (!fgets(line, sizeof(line), intermediate)) {
        printf("Error: empty intermediate file.\n");
        return 1;
    }

    sscanf(line, "%s %s %X", label, opcode, &startAddr);
    if (strcmp(opcode, "START") == 0) {
        strcpy(progName, label);
        trim(progName);
        fprintf(codeFile, "%06X  %-10s %-10s %-10X %-10s\n",
                startAddr, label, opcode, startAddr, "**");
    }

    int lastAddr = startAddr;
    while (fgets(line, sizeof(line), intermediate)) {
        int tmpAddr;
        char tmpLabel[20], tmpOpcode[20], tmpOperand[20];
        sscanf(line, "%X %s %s %s", &tmpAddr, tmpLabel, tmpOpcode, tmpOperand);
        lastAddr = tmpAddr;
    }
    progLen = lastAddr - startAddr;

    fseek(intermediate, 0, SEEK_SET);
    fgets(line, sizeof(line), intermediate);

    fprintf(programFile, "H^%s^%06X^%06X\n", progName, startAddr, progLen);

    char textRecord[2000] = "";
    int textLen = 0;

    while (fgets(line, sizeof(line), intermediate)) {
        sscanf(line, "%X %s %s %s", &loc, label, opcode, operand);

        if (strcmp(opcode, "END") == 0) {
            fprintf(codeFile, "%06X  %-10s %-10s %-10s %-10s\n",
                    loc, label, opcode, "**", "**");
            break;
        }

        int found = 0;
        rewind(optab);
        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                rewind(symtab);
                int symFound = 0;
                while (fscanf(symtab, "%s %s", symbol, address) != EOF) {
                    if (strcmp(operand, symbol) == 0) {
                        snprintf(objcode, sizeof(objcode), "%s%s", mnemonic, address);
                        symFound = 1;
                        break;
                    }
                }
                if (!symFound) snprintf(objcode, sizeof(objcode), "%s0000", mnemonic);
                found = 1;
                break;
            }
        }

        if (found) {
            snprintf(textRecord + strlen(textRecord),
                     sizeof(textRecord) - strlen(textRecord),
                     "^%s", objcode);
            textLen += 3;
            fprintf(codeFile, "%06X  %-10s %-10s %-10s %-10s\n",
                    loc, label, opcode, operand, objcode);
        }
        else if (strcmp(opcode, "WORD") == 0) {
            snprintf(objcode, sizeof(objcode), "%06X", atoi(operand));
            snprintf(textRecord + strlen(textRecord),
                     sizeof(textRecord) - strlen(textRecord),
                     "^%s", objcode);
            textLen += 3;
            fprintf(codeFile, "%06X  %-10s %-10s %-10s %-10s\n",
                    loc, label, opcode, operand, objcode);
        }
        else if (strcmp(opcode, "BYTE") == 0) {
            char hex[50] = "";
            if (operand[0] == 'C') {
                for (int i = 2; operand[i] != '\''; i++) {
                    char temp[5];
                    snprintf(temp, sizeof(temp), "%02X", operand[i]);
                    strcat(hex, temp);
                }
            }
            else if (operand[0] == 'X') {
                for (int i = 2; operand[i] != '\''; i++) {
                    char temp[2] = {operand[i], '\0'};
                    strcat(hex, temp);
                }
            }
            strncpy(objcode, hex, sizeof(objcode));
            objcode[sizeof(objcode) - 1] = '\0';

            snprintf(textRecord + strlen(textRecord),
                     sizeof(textRecord) - strlen(textRecord),
                     "^%s", objcode);
            textLen += strlen(hex) / 2;

            fprintf(codeFile, "%06X  %-10s %-10s %-10s %-10s\n",
                    loc, label, opcode, operand, objcode);
        }
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
            fprintf(codeFile, "%06X  %-10s %-10s %-10s %-10s\n",
                    loc, label, opcode, operand, "**");
        }
    }

    fprintf(programFile, "T^%06X^%02X%s\n", startAddr, textLen, textRecord);
    fprintf(programFile, "E^%06X\n", startAddr);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(codeFile);
    fclose(programFile);

    printf("Pass Two completed successfully.\n");
    return 0;
}