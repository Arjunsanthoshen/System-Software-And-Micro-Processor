 #include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char label[10], opcode[10], operand[10], code[10], mnemonic[10];
    int locctr, start = 0, length;

    FILE *input, *optab, *symtab, *output;
    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    output = fopen("output.txt", "w");

    if (input == NULL || optab == NULL || symtab == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
        locctr = start;
        fprintf(output, "\t\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(output, "%04X\t", locctr);

        if ((strcmp(label, "**") != 0) && (strcmp(opcode, "RESW") != 0) && (strcmp(opcode, "RESB") != 0)) {
            fprintf(symtab, "%s\t%04X\n", label, locctr);
        }

        int found = 0;
        rewind(optab);

        while (fscanf(optab, "%s\t%s", code, mnemonic) != EOF) {
            if (strcmp(code, opcode) == 0) {
                found = 1;
                locctr += 3;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += strlen(operand) - 3;
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2;
                }
            }
        }

        fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(output, "%04X\t%s\t%s\n", locctr, label, opcode);

    length = locctr - start;
    printf("Length of the code: %X \n", length) ;

    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(output);

    return 0;
}