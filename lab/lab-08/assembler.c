#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct customRegister
{
    int isOccupied;
    char data[20];
    char label_no[20];
    char name[5][5];
} customRegisterInformation;

customRegisterInformation registerDescription[4];

int label_no = 0;

char *getNewLabel()
{
    static char label[5];
    sprintf(label, "L%d", label_no);
    label_no++;
    return label;
}

int inRegDesc(char *var)
{
    int found = 0;
    int reg_no = -1;
    for (int i = 0; i < 4; i++)
    {
        if (found)
            break;

        if (registerDescription[i].isOccupied)
        {
            for (int j = 0; j < 5; j++)
            {
                if (strlen(registerDescription[i].name[j]) == 0)
                    break;

                if (strcmp(registerDescription[i].name[j], var) == 0)
                {
                    found = 1;
                    reg_no = i;
                    break;
                }
            }
        }
    }
    return reg_no;
}

int main(int argc, char **argv)
{
    FILE *intermediateFile = fopen(argv[1], "r");
    FILE *assemblyFile = fopen(argv[2], "w");

    const int BUFFER_SIZE = 50;
    char line_read[BUFFER_SIZE];
    size_t len = 0;
    srand(time(0));

    if (intermediateFile == NULL)
    {
        printf("Error in opening file");
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        registerDescription[i].isOccupied = 0;
        for (int j = 0; j < 5; j++)
            memset(registerDescription[i].name[j], 0, 5);
    }

    char *tokens[6];
    for (int i = 0; i < 6; i++)
    {
        tokens[i] = NULL;
    }

    while (fgets(line_read, BUFFER_SIZE, intermediateFile))
    {

        line_read[strlen(line_read) - 1] = '\0';

        char *token = strtok(line_read, " ");
        int i = 0;
        while (token != NULL)
        {

            tokens[i] = (char *)malloc(5 * sizeof(char));
            strcpy(tokens[i], token);

            token = strtok(NULL, " ");
            i++;
        }

        if (tokens[1][strlen(tokens[1]) - 1] == ':' || strcmp(tokens[1], "end") == 0 || strcmp(tokens[1], "return") == 0)
        {
            continue;
        }

        /* for(int j=0;j<i;j++) {
            printf("tokens[%d] = %s\n", j, tokens[j]);
        }*/

        if (strcmp(tokens[2], "=") == 0)
        {

            if (strcmp(tokens[3], "not") == 0)
            {
                char *l1 = getNewLabel();
                char *l2 = getNewLabel();
                fprintf(assemblyFile, "LHLD %s\n", tokens[4]);
                fprintf(assemblyFile, "MOV A,M\n");
                fprintf(assemblyFile, "ADI 0\n");
                fprintf(assemblyFile, "JZ %s\n", l1);
                fprintf(assemblyFile, "MVI A,0\n");
                fprintf(assemblyFile, "JMP %s\n", l2);
                fprintf(assemblyFile, "%s: MVI A,1\n", l1);
                fprintf(assemblyFile, "%s: NOP\n", l2);

                int done = 0;
                int reg_no = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (!registerDescription[i].isOccupied)
                    {
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                registerDescription[reg_no].isOccupied = 1;
                strcpy(registerDescription[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
            }

            else if (tokens[4] == NULL)
            {
                fprintf(assemblyFile, "LHLD %s\n", tokens[3]);

                int reg_no = inRegDesc(tokens[3]);
                if (reg_no != -1)
                {
                    for (int j = 0; j < 5; j++)
                        if (strlen(registerDescription[reg_no].name[j]) == 0)
                            strcpy(registerDescription[reg_no].name[j], tokens[1]);
                }

                else
                {
                    int done = 0;
                    int reg_no1 = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (!registerDescription[i].isOccupied)
                        {
                            reg_no1 = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no1 = rand() % 4;

                    registerDescription[reg_no1].isOccupied = 1;
                    strcpy(registerDescription[reg_no1].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,M\n", reg_no1);
                }
            }

            else if (tokens[3][0] >= '0' && tokens[3][0] <= '9')
            {

                if (tokens[5][0] >= '0' && tokens[5][0] <= '9')
                {
                    fprintf(assemblyFile, "MVI A,%s\n", tokens[3]);
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADI %s\n", tokens[5]);
                    else
                        fprintf(assemblyFile, "SUI %s\n", tokens[5]);

                    int done = 0;
                    int reg_no = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (!registerDescription[i].isOccupied)
                        {
                            reg_no = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no = rand() % 4;

                    registerDescription[reg_no].isOccupied = 1;
                    strcpy(registerDescription[reg_no].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
                }

                else
                {
                    int reg_no = inRegDesc(tokens[5]);
                    if (reg_no == -1)
                    {
                        fprintf(assemblyFile, "LHLD %s\n", tokens[5]);
                        fprintf(assemblyFile, "MOV A,M\n");
                    }
                    else
                        fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADI %s\n", tokens[3]);
                    else
                        fprintf(assemblyFile, "SUI %s\n", tokens[3]);

                    int done = 0;
                    reg_no = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (!registerDescription[i].isOccupied)
                        {
                            reg_no = i;
                            done = 1;
                            break;
                        }
                    }
                    if (!done)
                        reg_no = rand() % 4;

                    registerDescription[reg_no].isOccupied = 1;
                    strcpy(registerDescription[reg_no].name[0], tokens[1]);

                    fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
                }
            }

            else if (tokens[5][0] >= '0' && tokens[5][0] <= '9')
            {
                int reg_no = inRegDesc(tokens[3]);
                if (reg_no == -1)
                {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[3]);
                    fprintf(assemblyFile, "MOV A,M\n");
                }
                else
                    fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                if (strcmp(tokens[4], "+") == 0)
                    fprintf(assemblyFile, "ADI %s\n", tokens[5]);
                else
                    fprintf(assemblyFile, "SUI %s\n", tokens[5]);

                int done = 0;
                reg_no = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (!registerDescription[i].isOccupied)
                    {
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                registerDescription[reg_no].isOccupied = 1;
                strcpy(registerDescription[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
            }

            else
            {
                int reg_no = inRegDesc(tokens[3]);
                if (reg_no == -1)
                {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[3]);
                    fprintf(assemblyFile, "MOV A,M\n");
                }
                else
                    fprintf(assemblyFile, "MOV A,R%d\n", reg_no);

                reg_no = inRegDesc(tokens[5]);
                if (reg_no == -1)
                {
                    fprintf(assemblyFile, "LHLD %s\n", tokens[5]);
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADD M\n");
                    else
                        fprintf(assemblyFile, "SUB M\n");
                }
                else
                {
                    if (strcmp(tokens[4], "+") == 0)
                        fprintf(assemblyFile, "ADD R%d\n", reg_no);
                    else
                        fprintf(assemblyFile, "SUB R%d\n", reg_no);
                }

                int done = 0;
                reg_no = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (!registerDescription[i].isOccupied)
                    {
                        reg_no = i;
                        done = 1;
                        break;
                    }
                }
                if (!done)
                    reg_no = rand() % 4;

                registerDescription[reg_no].isOccupied = 1;
                strcpy(registerDescription[reg_no].name[0], tokens[1]);

                fprintf(assemblyFile, "MOV R%d,A\n", reg_no);
            }
        }

        else
        {

            if (strcmp(tokens[1], "goto") == 0)
                fprintf(assemblyFile, "JMP %s\n", tokens[2]);

            else
            {
                fprintf(assemblyFile, "LHLD %s\n", tokens[2]);
                fprintf(assemblyFile, "MOV A,M\n");
                fprintf(assemblyFile, "ADI 0\n");
                fprintf(assemblyFile, "JNZ %s\n", tokens[4]);
            }
        }

        for (int i = 0; i < 6; i++)
        {
            free(tokens[i]);
            tokens[i] = NULL;
        }
    }

    fclose(intermediateFile);
    fclose(assemblyFile);
}
