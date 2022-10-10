#include <stdio.h>
#include <stdlib.h>

void Create(char *pFileName);
void AddNewStudent(char *pFileName, double x, double y, double z);

int main(int argc, char *argv[])
{
    char data[4]="9.8";
    double num = strtod("123.0", NULL);
    printf("%0.2f :\n", num);

    Create("file1.txt");
    AddNewStudent("file1.txt", 4.5, 10, 7.8);
}

void Create(char *pFileName)
{
    FILE *LpFile;

    if(LpFile=fopen(pFileName,"r"))
    {
        fclose(LpFile);
        printf("File name existed. Please check again !");
    }
    else
    {
        LpFile=fopen(pFileName,"w");

        if (LpFile == NULL)
        {
            printf("Unable to create file \n");
        }
        else
        {
            fprintf(LpFile, "ID \t\t Math \t\t Physics \t\t English \t\t Average\n");
            fclose(LpFile);
            printf("File was created successfully\n");
        }
    }
}

void AddNewStudent(char *pFileName, double x, double y, double z)
{
    FILE *LpFile;
    double Avr=0;
    int Id=0;

    LpFile = fopen(pFileName,"a");

    if (LpFile==NULL)
    {
        printf("File name is incorrect or File is not existed.");
    }
    else
    {
        Avr = (x + y + z)/3;

        fprintf(LpFile,"%d \t\t %0.2f \t\t %0.2f \t\t\t %0.2f \t\t\t %0.2f\n", Id, x, y, z, Avr);

        printf("Recorded successfully!\n");

        fclose(LpFile);
    }
}