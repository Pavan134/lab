#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void help()
{
    printf(1,"Usage:\n");
    printf(1,"pwd [OPTION]\n");
    printf(1,"Options:\n");
    printf(1,"-L : Displays the Address even if there are symlinks\n");
printf(1,"-P : Displays the address without containing symlinks\n\n");
    printf(1,"--help : Show last help exit\n");
    printf(1,"--version : Shows information about the past version exit\n");
    exit();
}

void prog()
{
    printf(1,"pwd version 1.00\n");
    exit();
}

int main(int argc,char *argv[])
{
    char cwd[100];
    int logical=0,physical=1;
    int err=open("/temp.pwd",O_RDONLY);
    if(argv[1][0]=='-')
    {
        if(strcmp(argv[1],"-L")==0) {logical=1;physical=0;}
        if(strcmp(argv[1],"-P")==0) physical=1;
        if(strcmp(argv[1],"--help")==0) help();
        if(strcmp(argv[1],"--version")==0) prog();
        else
        {
                printf(1,"pwd: invalid option %s\ntry 'pwd --help' for 	more information\n",argv[1]);
                exit();
        }
    }
 if(err<0)
    {
        printf(1,"/ \n");
        exit(); 
    }
    int red=read(err,cwd,sizeof(cwd));
    if(red<0)
    {
        printf(2,"ERROR\n");
        exit();
    }
    close(err);
    if(logical==1 || physical==1 || logical==0)
        printf(1,"%s\n", cwd);
    exit();
}

