#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

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
      if(!strcmp((entry->d_name)+strlen(entry->d_name)-4, ".mp4"))
      {
          FILE *f = fopen(entry->d_name, "r");
          fseek(f, 0, SEEK_END);
          double size = ftell(f);
          fclose(f);

          printf("%s\t%.2lf\t MB\n", entry->d_name, size/1024/1024);

          if(fout != NULL){
            fprintf(fout, "%s\t%.2lf\t MB\n", entry->d_name, size/1024/1024);
          }
      }
    }
  }

  fclose(fout);
  closedir(dp);
  free(entry);

  return 0;
}

int sort_in_file(const char* path_to_file){
  // Prepare for sorting
  FILE* fp = fopen(path_to_file, "r");
  if(fp == NULL)  return -1;

  char* line = NULL;
  size_t line_length = 0;
  ssize_t read_chars = 0;
  int lines = 0;
  while((read_chars = getline(&line, &line_length, fp)) != -1){
    ++lines;
  }
  free(line);

  //  Make an array to sort.
  char* lines_array[lines];

  fseek(fp, 0, SEEK_SET);

  for(int i = 0; i < lines; ++i){
    lines_array[i] = NULL;
    getline(&lines_array[i], &line_length, fp);
  }
  fclose(fp);

  //  Lines written, do sorting.

  for(short i = 0; i < lines-1; ++i){
    if(strcmp(lines_array[i], lines_array[i+1]) > 0){
      char* temp = lines_array[i];
      lines_array[i] = lines_array[i+1];
      lines_array[i+1] = temp;

      i = -1;
    }
  }

  fp = fopen(path_to_file, "w");

  for(short i = 0; i < lines; ++i){
    fprintf(fp, "%s", lines_array[i]);
    free(lines_array[i]);
  }
  fclose(fp);

  return 0;
}

int main(){
  //  Run initial function.
  listdir(".", "list.txt");
  sort_in_file("list.txt");
    return 0;
}
