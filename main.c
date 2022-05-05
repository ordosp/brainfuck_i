#include <stdio.h>
#include <stdlib.h>

#define MEMORY_MIN 0
#define MEMORY_MAX 30000
#define FILE_MAX_SIZE 4096


void run(char *program) {
    FILE *f;
    char buf;
    int i = 0;
    char fileContent[FILE_MAX_SIZE];
    int currentCommand = 0;
    char memory[MEMORY_MAX];
    memset(memory, 0, MEMORY_MAX);
    int currentCell = MEMORY_MIN;

    f = fopen(program, "r");
    while(!feof(f)) {
        fscanf(f, "%c", &buf);
        fileContent[i] = buf;
        i++;
    }
    fclose(f);
    fileContent[i] = '\0';

    while (1) {
        switch (fileContent[currentCommand]) {
            case '>':
                currentCell++;
                if (currentCell > MEMORY_MAX) {
                    printf("Memory access error!");
                    exit(1);
                }
                break;
            case '<':
                currentCell--;
                if (currentCell < MEMORY_MIN) {
                    printf("Memory access error!");
                    exit(1);
                }
                break;
            case '+':
                memory[currentCell]++;
                break;
            case '-':
                memory[currentCell]--;
                break;
            case '.':
                printf("%c", memory[currentCell]);
                break;
            case ',':
                scanf("%c", memory[currentCell]);
                break;
            case '[':
                if (memory[currentCell] == 0) {
                    int level = 1;
                    while (1) {
                        currentCommand++;
                        if (fileContent[currentCommand] == '[') { level++;}
                        if (fileContent[currentCommand] == ']') {
                            level--;
                            if (level == 0) { break; }
                        }
                    }
                }
                break;
            case ']':
                if (memory[currentCell] != 0) {
                    int level = 1;
                    while (1) {
                        currentCommand--;
                        if (level == 0) { break; }
                        if (fileContent[currentCommand] == ']') { level++;}
                        if (fileContent[currentCommand] == '[') { level--;}
                    }
                }
                break;
        }

        currentCommand++;
        if (fileContent[currentCommand] == '\0') {
            break;
        }
    }
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("program <source-file>\n");
        exit(1);
    }

    run(argv[1]);
    return 0;
}
