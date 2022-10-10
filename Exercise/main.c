#include <stdio.h>
#include <stdlib.h>

void Create(char *pFileName);
void AddNewStudent(char *pFileName, double x, double y, double z);
double GetDataFromFile(char *pFileName, int position);

int main(int argc, char *argv[])
{
    char data[4]="9.8";
    double num = strtod("123.0", NULL);
    printf("%0.2f :\n", num);

    // Create("file1.txt");
    // AddNewStudent("file1.txt", 4.5, 10, 7.8);
    printf("Get Data: %0.2f\n",GetDataFromFile("file1.txt",5));
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

        printf("Record is successfully!\n");

        fclose(LpFile);
    }
}

double GetDataFromFile(char *pFileName, int position)
{
    FILE *LpFile;

    LpFile = fopen(pFileName, "r");
    double a,b,c,d,e;

    char x[6], y[6], z[6], avr[6];
    int Id;

    fscanf(LpFile,"%d %s %s %s %s", &Id, x, y, z, avr);
    
    switch (position)
    {
    case 2:
        return strtod(x, NULL);
        break;
    case 3:
        return strtod(y, NULL);
        break;
    case 4:
        return strtod(y, NULL);
        break;
    case 5:
        return strtod(avr, NULL);
        break;
    default:
        return Id;
        break;
    }

    // printf("Begin\n");
    // printf("1: %d\n", Id);
    // printf("2: %s\n",x);
    // printf("3: %s\n",y);
    // printf("4: %s\n",z);
    // printf("5: %s\n",avr);
    // printf("Done\n");

    fclose(LpFile);
}