1 #include "types.h"
2 #include "stat.h"
3 #include "user.h"
4
5  int main(int argc, char *argv[])
6  {
7     int i;
8     for(i = 1; i < argc; i++)
9        printf(1, "%s%s", argv[i], i+1 < argc ? " " : "\n");
10   exit();
11 }
