#include <stdio.h>
#include <dirent.h>
#include <string.h>

int listdir(const char *path_to_dir, const char* path_to_log){
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path_to_dir);

  if(dp == NULL)
    return -1;

  FILE *fout = fopen(path_to_log, "w");

  while ((entry = readdir(dp))) {
    if(entry->d_type != DT_DIR)
    {
      //if(!strcmp((entry->d_name)+strlen(entry->d_name)-4, ".mp4"))
      //{
          FILE *f = fopen(entry->d_name, "r");
          fseek(f, 0, SEEK_END);
          double size = ftell(f);
          fclose(f);

          printf("%s\t%.2lf\t MB\n", entry->d_name, size/1024/1024);

          if(fout != NULL){
            fprintf(fout, "%s\t%.2lf\t MB\n", entry->d_name, size/1024/1024);
          }
      //}
    }
  }

  fclose(fout);
  closedir(dp);

  return 0;
}

int main(int argc, char **argv){
  if(argc == 2)
    listdir(argv[1], "list.txt");
  else
    listdir(".", "list.txt");
  
  return 0;
}
