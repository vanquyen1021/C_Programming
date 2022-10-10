#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void Create(char *pFileName);
void AddNewStudent(char *pFileName, double x, double y, double z);
double GetDataFromFile(char *pFileName, int position, int line);
void RemoveID(char *pFileName, int Id);
int Total(char *pFileName);
void Max(char *pFileName);
void Min(char *pFileName);

int main(int argc, char *argv[])
{
    char data[4]="9.8";
    double num = strtod("123.0", NULL);
    printf("%0.2f :\n", num);

    // Create("file1.txt");
    // AddNewStudent("file1.txt", 8.6, 5.3, 4.5);
    // AddNewStudent("file1.txt", 5.6, 4.6, 5.8);
    // AddNewStudent("file1.txt", 8.5, 2.1, 9.6);
    // AddNewStudent("file1.txt", 4.3, 9.8, 7.2);
    // AddNewStudent("file1.txt", 6.7, 6.2, 8.6);
    printf("Total: %d\n", Total("file1.txt"));
    Max("file1.txt");
    Min("file1.txt");
    RemoveID("file1.txt", 3);
    // printf("Get Data: %0.2f\n",GetDataFromFile("file1.txt",3, 0));
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
        int max_line = (int) Total(pFileName);
        int max = 0;
        if (max_line > 0)
        {
            max = (int) GetDataFromFile(pFileName, 1, max_line+1);
        }
        Avr = (x + y + z)/3;

        fprintf(LpFile,"%d \t\t %0.2f \t\t %0.2f \t\t\t %0.2f \t\t\t %0.2f\n", max+1, x, y, z, Avr);

        printf("Record is successfully!\n");

        fclose(LpFile);
    }
}

double GetDataFromFile(char *pFileName, int position, int line)
{
    FILE *LpFile;

    LpFile = fopen(pFileName, "r");

    char x[6], y[6], z[6], avr[6];
    int Id;

    int current_line=1;
    char buffer[50];
    do
    {
        if (current_line == line)
        {
            fscanf(LpFile,"%d %s %s %s %s", &Id, x, y, z, avr);
    
            switch (position)
            {
            case 2:
                fclose(LpFile);
                return strtod(x, NULL);
                break;
            case 3:
                fclose(LpFile);
                return strtod(y, NULL);
                break;
            case 4:
                fclose(LpFile);
                return strtod(y, NULL);
                break;
            case 5:
                fclose(LpFile);
                return strtod(avr, NULL);
                break;
            default:
                fclose(LpFile);
                return Id;
                break;
            }
        } 
        current_line++;
    } while(fgets(buffer, 50, LpFile));
}

void RemoveID(char *pFileName, int Id)
{
    FILE *LpFile, *ptempFile;

    LpFile = fopen(pFileName,"r");
    char tempFileName[20];
    strcpy(tempFileName,"temp_");
    strcat(tempFileName,pFileName);
    ptempFile= fopen(tempFileName, "w");

    char buffer[50];

    int current_line=1;
    int position = 1;
    bool CheckID=false;

    while (fgets(buffer, 50, LpFile))
    {
        if ((int)GetDataFromFile(pFileName, position, current_line)==Id)
        {
            fputs("", ptempFile);
            CheckID=true;
        }
        else
        {
            fputs(buffer, ptempFile);
        }
        current_line++;
    } 

    fclose(LpFile);
    fclose(ptempFile);

    remove(pFileName);
    rename(tempFileName,pFileName);

    if (CheckID==true)
    {
        printf("Student with ID: %d is removed", Id);
    }
    else
    {
        printf("There is no student with ID: %d", Id);
    }
}

int Total(char *pFileName)
{
    FILE *LpFile;

    LpFile = fopen(pFileName, "r");

    int current_line=0;
    char buffer[50];
    while(fgets(buffer, 50, LpFile))
    {
        current_line++;
    } 
    return (current_line-1);
}

void Max(char *pFileName)
{
    double max=0;
    FILE *LpFile;
    
    LpFile=fopen(pFileName, "r");

    int max_student = Total(pFileName);
    if (max_student<1)
    {
        printf("There is no student in file");
    }
    else
    {
        for(int i = 2; i <= max_student+1; i++)
        {
            double current_avr = GetDataFromFile(pFileName, 5, i);
            if(current_avr>max)
            {
                max=current_avr;
            }
        }
        for (int i = 2; i <= max_student+1; i++)
        {
            if(GetDataFromFile(pFileName, 5, i)==max)
            {
                printf("Student with ID: %d has the highest avearge score: %0.2f\n",(int)GetDataFromFile(pFileName, 1, i),max);
            }
        }
    }
    fclose(LpFile);
}

void Min(char *pFileName)
{
    double min=10;
    FILE *LpFile;
    
    LpFile=fopen(pFileName, "r");

    int max_student = Total(pFileName);
    if (max_student<1)
    {
        printf("There is no student in file");
    }
    else
    {
        for(int i = 2; i <= max_student+1; i++)
        {
            double current_avr = GetDataFromFile(pFileName, 5, i);
            if(current_avr<min)
            {
                min=current_avr;
            }
        }
        for (int i = 2; i <= max_student+1; i++)
        {
            if(GetDataFromFile(pFileName, 5, i)==min)
            {
                printf("Student with ID: %d has the lowest avearge score: %0.2f\n",(int)GetDataFromFile(pFileName, 1, i),min);
            }
        }
    }
    fclose(LpFile);
}