#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main()
{
        int fd,fd1,i=0;
        char arr[20],ch,str[20];
        if(mkfifo("file1",0666)==-1 && errno!=EEXIST)
        {
                perror("mkfifo");
                exit(0);
        }
        if(mkfifo("file2",0666)==-1 && errno!=EEXIST)
        {
                perror("mkfifo1");
                exit(0);
        }
        printf("file created successfully\n");
            fd=open("file1",O_WRONLY);
            printf("file opened successfully\n");
          fd1=open("file2",O_RDONLY);
            if(fd1==-1)
            {
                perror("open1");
                exit(0);
            }
            if(fd==-1)
            {
                    perror("open");
                    exit(0);
            }
            do
            {
                    printf("enter the string\n");
                    fgets(arr,20,stdin);
                    arr[strlen(arr)-1]=0;
                    write(fd,arr,strlen(arr)+1);
                    i=0;
                    while(read(fd1,&ch,1)==1)
                    {
                            str[i++]=ch;
                            if(ch=='\0')
                                    break;
                    }
                    printf("%s\n",str);
            }while(strcmp(arr,"quit")!=0  && strcmp(str,"QUIT")!=0);
}