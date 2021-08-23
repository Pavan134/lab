#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char *argv[])
{
   //Declaration of Variables
    int CharCount=0,WordCount=0,LineCount=0,FD,RdFlag,i;
    char Data[500];
   //Step1 Opening the File in Read Only Mode
    FD=open(argv[1],O_RDONLY);
   //If unable to open source file error is displayed
    if(FD<0)
    {
        printf(1,"Error in Opening the File");
        exit();
     }
//Step2 Reading the Data from the File
  RdFlag=read(FD,Data,sizeof(Data));
//If unable to Read the Data from the file Error is displayed
  if(RdFlag<0)  {
       printf(1, "Error in Reading the Data");
       exit();
   }
 //Loop to Read the Data Character by Character
for(i=0;i<RdFlag;i++)  {
    CharCount++;
    if(Data[i]==' ' || Data[i]=='\n’) //Checks for Space or New Line
        WordCount++; 
 //Checks for the New Line Character
    if(Data[i]=='\n')
        LineCount++;
  }
 //Closing the File
  close(FD);
  printf(1, "%d\t%d\t%d\n",CharCount,WordCount,LineCount);
  return 0;
}
