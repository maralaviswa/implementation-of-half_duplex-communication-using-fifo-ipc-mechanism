#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
void convert(char *str)
{
        while(*str)
        {
                *str^=32;
                str++;
        }
}
int main()
{
        int fd,fd1,i=0;
        char arr[20],str[20],ch;
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
          fd=open("file1",O_RDONLY);
          fd1=open("file2",O_WRONLY);
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
                    i=0;
                    while(read(fd,&ch,1)==1)
                    {
                            arr[i++]=ch;
                            if(ch=='\0')
                                    break;
                    }
                    printf("%s\n",arr);
                    strcpy(str,arr);
                    convert(str);
                    write(fd1,str,strlen(str)+1);
            }while(strcmp(arr,"quit")!=0  && strcmp(str,"QUIT")!=0);
}