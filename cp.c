#include “types.h”
#include “stat.h”
#include “fcntl.h”
#include “user.h”
int main(int argc,char *argv[])
{
  //Declaration of Variables
  int SourceFD,TargetFD,RdFlag,WrFlag;
  char Data[100];
 //Step1 Opening the Source File
  SourceFD=open(argv[1],O_RDONLY);
 //If unable to open source file error is displayed
  if(SourceFD<0)  {
        printf(1, "Error in Opening the File");
        exit();
  }
//Step2 Reading the Data from the Source File
RdFlag=read(SourceFD,Data,sizeof(Data)); 
//If unable to Read the Data from source file error //is displayed
If(RdFlag<0) {
     printf(1, "Error in Reading the File");
     exit();
}
//Step3 Opening the Target File
TargetFD=open(argv[2],O_CREATE|O_WRONLY);
//If unable to open Target file error is displayed
If(RdFlag<0) {
     printf(1, "Error in Reading the File");
     exit();
}
//Step4 Writing the Data into the Target File
  WrFlag=write(TargetFD,Data,sizeof(Data));
//If unable to Write the Data into Target file error is displayed
  if(WrFlag<0)  {
        printf(1, "Error in Writing the Data into Target File");
        exit();
  }
 //Step5 Closing the Source and Target Files
  close(SourceFD);
  close(TargetFD);
  return 0;
}
