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
bool ERR_CheckInteger(char *number);
bool ERR_CheckFormatFile(char *pFileName);
int CalculateInput(char **pFileName, double *x, double *y, double *z, int *Id);
void Instruction();



int main(int argc, char *argv[])
{
    // char data[4]="9.8";
    // double num = strtod("123.0", NULL);
    // printf("%0.2f :\n", num);

    // Create("\file1.txt");
    // printf("ID: %d\n",ERR_CheckInteger("10.5"));
    // AddNewStudent("file1.txt", 8.6, 5.3, 4.5);
    // AddNewStudent("file1.txt", 5.6, 4.6, 5.8);
    // AddNewStudent("file1.txt", 8.5, 2.1, 9.6);
    // AddNewStudent("file1.txt", 4.3, 9.8, 7.2);
    // AddNewStudent("file1.txt", 6.7, 6.2, 8.6);
    // printf("Total: %d\n", Total("file1.txt"));
    // Max("file1.txt");
    // Min("file1.txt");
    // RemoveID("file1.txt", 3);
    // printf("Get Data: %0.2f\n",GetDataFromFile("file1.txt",3, 0));

    char *pFileName;
    double x, y, z;
    int Id;

    bool lbStatus = true;
    while (lbStatus)
    {
        int mode = CalculateInput(&pFileName, &x, &y, &z, &Id);
//        if(mode==1) Instruction();
//        else if (mode==2) Create(pFileName);
//        else if (mode ==3) AddNewStudent(pFileName,x , y, z);
//        else if (mode==4) RemoveID(pFileName,Id);
//        else if (mode==5) Max(pFileName);
//        else if (mode==6) Min(pFileName);
//        else if (mode==7) Total(pFileName);
//        else if (mode==8) lbStatus=false;

         switch (mode)
         {
         case 1:
             Instruction();
             break;
         case 2:
             Create(pFileName);
             break;
         case 3:
             AddNewStudent(pFileName,x , y, z);
             break;
         case 4:
             RemoveID(pFileName,Id);
             break;
         case 5:
             Max(pFileName);
             break;
         case 6:
             Min(pFileName);
             break;
         case 7:
             Total(pFileName);
             break;
         case 8:
             lbStatus=false;
             break;
         default:
             break;
         }
    }

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
            printf("ERR: Name file is uncorrect. Unable to create file \n");
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

void Instruction()
{
    printf("Usage:\n");
    printf("1. program -create filename     : Create a new text file with a predefined format\n");
    printf("2. program -add filename x y z  : Add a new student with x - Math score, y - Physics score, z - English score\n");
    printf("3. program -remove filename N   : Remove the student with ID N from the filename.\n");
    printf("4. program -max filename        : Get the ID of the students who has the highest average score and also display score.\n");
    printf("5. program -min filename        : Get the ID of the students who has the lowest average score and also display score.\n ");
    printf("6. program -total filename      : Display the total number of the students existing in the database file.\n");
    printf("7. program -h                   : Display the instruction.\n");
    printf("8. program -end                 : End program.\n");
}

int CalculateInput(char **pFileName, double *x, double *y, double *z, int *Id)
{
    // char strCmd[50];
    char *strCmd;

    printf("Typing your command:\t");
    fgets(strCmd, 50, stdin);
    // strCmd = "program -create abc.txt";

    char splitInput[6][10];
    char *ptempFile;
    int number=0;
    int j=0;

    for(int i=0; i<=strlen(strCmd);i++)
    {
        if (number>5) return 0;
        if ((strCmd[i] == ' ') || (strCmd[i] == '\n') || (strCmd[i] == '\0'))
        {
            splitInput[number][j]='\0';
            if (strCmd[i] != '\n')
            {
                number++;
                j=0;
            }
        }
        else
        {
            splitInput[number][j]=strCmd[i];
            j++;
        }
    }

    if ((!strcmp(splitInput[0],"program")))
    {
        if ((!strcmp(splitInput[1],"-h"))&&number==2)
        {
            return 1;
        }
        else if ((!strcmp(splitInput[1],"-create"))&&number==3)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];
                return 2;
            }
            return 0;
        }
        else if ((!strcmp(splitInput[1],"-add"))&&number==6)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];

                if (ERR_CheckInteger(splitInput[3]) && ERR_CheckInteger(splitInput[4])&& ERR_CheckInteger(splitInput[5]))
                {
                    *x=strtod(splitInput[3], NULL);
                    *y=strtod(splitInput[4], NULL);
                    *z=strtod(splitInput[5], NULL);

                    if((*x<0||*x>10)||(*y<0||*y>10)||(*z<0||*z<10))
                    {
                        printf("ERR: Wrong score\n");
                        return 0;
                    }
                }
                else
                {
                    printf("ERR: Wrong format score\n");
                    return 0;
                }
                return 3;
            }           
            return 0;
        }
        else if ((!strcmp(splitInput[1],"-remove"))&&number==4)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];

                if (ERR_CheckInteger(splitInput[3]))
                {
                    *Id=strtod(splitInput[3], NULL);
                }
                else
                {
                    printf("ERR: ID is not an integer\n");
                    return 0;
                }
                return 4;
            }
            return 4;
        }
        else if ((!strcmp(splitInput[1],"-max"))&&number==3)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];
                return 5;
            }
            return 0;
        }
        else if ((!strcmp(splitInput[1],"-min"))&&number==3)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];
                return 6;
            }
            return 0;
        }
        else if ((!strcmp(splitInput[1],"-total"))&&number==3)
        {
            if (ERR_CheckFormatFile(splitInput[2])) 
            {
                *pFileName=splitInput[2];
                return 7;
            }
            return 0;
        }
        else if ((!strcmp(splitInput[1],"-end"))&&number==2)
        {
            return 8;
        } 
    }
    else return 0;
}

bool ERR_CheckFormatFile(char *pFileName)
{
    char *strFormat;

    strFormat=&pFileName[strlen(pFileName)-4];

    if (strcmp(strFormat,".txt"))
    {
        printf("ERR: Wrong format file\n");
        return false;
    }
    return true;
}

bool ERR_CheckInteger(char *number)
{
    printf("Number %d\n",strlen(number));
    if ( number[0]<47 || number[0]>58 || number[strlen(number)-1]<47 || number[strlen(number)-1]>58 )
    {
        return false;
    }
    return true;
}



