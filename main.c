#include <stdio.h>
#include <dirent.h>
#include <string.h>

int listdir(const char *path){
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);

  if(dp == NULL)
    return -1;

  while ((entry = readdir(dp))) {
    if(entry->d_type != DT_DIR)
      if(!strcmp((entry->d_name)+strlen(entry->d_name)-4, ".mp4"))
      {
        FILE *f = fopen(entry->d_name, "r");
        fseek(f, 0, SEEK_END);
        double size = ftell(f);
        fclose(f);

        printf("%s\t%.2lf\t MB\n", entry->d_name, size/1024/1024);
      }
  }
  closedir(dp);

  return 0;
}

int main(int argc, char **argv){
  char* path = ".";

  listdir(path);
  return 0;
}
