#include <stdio.h>
#include <stdlib.h>

void Create(char *pFileName);
void AddNewStudent(char *pFileName, double x, double y, double z);
double GetDataFromFile(char *pFileName, int position, int line);

int main(int argc, char *argv[])
{
    char data[4]="9.8";
    double num = strtod("123.0", NULL);
    printf("%0.2f :\n", num);

    // Create("file1.txt");
    AddNewStudent("file1.txt", 7.4, 5.4, 9.5);
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
        int max_line = (int) GetDataFromFile(pFileName, 1, 0);
        int max = 0;
        if (max_line>1)
        {
            max = (int) GetDataFromFile(pFileName, 1, max_line);
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
    double a,b,c,d,e;

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
    return (current_line-2);
}
