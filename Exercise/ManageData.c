#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEN 256
// set some generous maximum lengths for filename size and each line in a file
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

void ReplaceData(int replace_line, char *replace);

int main(void)
{
    FILE* fp;
    fp = fopen("file.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];
    int i=1;
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        printf("%d %s\n",i, buffer);
        i++;
    }

    ReplaceData(2, "");

    fclose(fp);
    return 0;
}

void ReplaceData(int replace_line, char *replace)
{
  FILE *file, *temp;
  // buffer will store each line from the original file
  char buffer[MAX_LINE];
  
  // open the original file for reading, and the temp file for writing
  file = fopen("file.txt", "r");
  temp = fopen("temp_file.txt", "w");
  
  // check if either file failed to open, if either did exit with error status
  if (file == NULL || temp == NULL)
  {
    printf("Error opening files(s).\n");
  }
  
  // we'll keep reading the file so long as keep_reading is true
  bool keep_reading = true;

  // will keep track of the current line number we are reading from the file
  int current_line = 1;
   
  int i=1;


//   printf("\nChu trinh:");
//   printf("%s",stt);
//   printf("%s",a);
//   printf("%s",b);
//   printf("%s",c);
 char data[4]="abcd";
 data[2]=data[3];
 printf("123: %s",data);


  

  do 
  {
    int j=0;
    int count = 0;
    char stt[2];
    char a[2];
    char b[2];
    char c[2];
    // read the next line of the file into the buffer
    fgets(buffer, MAX_LINE, file);
    for (int i=0;i<10;i++)
    {
        if ((buffer[i]!=' ')&&count==0) 
        {
            stt[j]=buffer[i];
            j++;
        }
        else if ((buffer[i]!=' ')&&count==1) 
        {
            a[j]=buffer[i];
            j++;
        }
        else if ((buffer[i]!=' ')&&count==2) 
        {
            b[j]=buffer[i];
            j++;
        }
        else if ((buffer[i]!=' ')&&count==3) 
        {
            c[j]=buffer[i];
            j++;
        }
        else if ((buffer[i]==' ')) 
        {
            j=0;
            count++;
        }
    }
    printf("\nChu trinh:");
    printf("%s ",stt);
    printf("%s ",a);
    printf("%s ",b);
    printf("%s",c);
    // if we've reached the end of the file, stop reading
    if (feof(file)) keep_reading = false;
    // if the line we've reached is the one we wish to replace, write the 
    // replacement text to this line of the temp file
    else if (current_line == replace_line)
      fputs(replace, temp);
    // otherwise write this line to the temp file
    else 
    {
        // char str[2];
        // sprintf(str, "%d", i);
        // buffer[0]=i+48;
        fputs(buffer, temp);
        i++;
    }
    
    // increment the current line as we will now be reading the next line
    current_line++;

  } while (keep_reading);
  
  // close our access to both files as we are done with them
  fclose(file);
  fclose(temp);
  
  // delete the original file, rename temp file to the original file's name
//   remove("file.txt");
//   rename("temp_file.txt", "file.txt");
  printf("Done !!");

}

// void Calculate()
// {
//     int num = 0, sum = 0;
//     double avg = 0;

//     FILE* fp;
//     char * line = NULL;
//     size_t len = 0;
//     size_t read;

//     fp = fopen("scores.txt", "r");
//     if(fp == NULL) {
//         printf("Fail to the file\n");
//         exit(EXIT_FAILURE);
//     }

//         while(read = getline(&line, &len, fp) != -1) {
//         sum += atoi(line);
//         num++;
//     }
    
//     avg = (double)sum / num;
//     printf("%d scores read\nscores avg: %lf\n", num, avg);
//     fclose(fp);
// }