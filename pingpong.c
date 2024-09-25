#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define BUFSIZE 512

void ping_pong(int fd) 
{
   // ------------------------- Write your code here -------------------------
   int i, n;
  int l, w, c, inword;
  l = w = c = 0;
  inword = 0;
  char word[4] = "****";
  char buf[BUFSIZE];
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = buf[i];
    if(word[0] == 'p' && word[1] == 'i' && word[2] == 'n' && word[3] == 'g'){
          printf(1, "pong\n");
    }

  }
  }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
