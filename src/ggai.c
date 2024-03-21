/**
 * @filename: ggai.c
 * 
 * @brief: 用的command调用的curl命令,参数放到curl命令里面而已,格式化 output
 * 
 * @version: 0.1
 * 
 * @date: 2021-07-20
 * 
 * @note:
 * gai () 
 * {
	curl -H 'Content-Type: application/json' -d
    "{\"contents\":[{\"parts\":[{\"text\":\"$1\"}]}]}" -X POST
    "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent?key=%s"
   }

 * @usage:
 *    Usage: ggai <your Question>  
 *    or
 *    Usage: ggai  
 *    And Input Your Question And End Question while Typing EOF
 *  
 * 
*/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char Buff[BUFSIZ];
char command[BUFSIZ];
char PathBuff[BUFSIZ];
char RESPONSE[BUFSIZ * 10];
char *CurlFormat = "curl -H 'Content-Type: application/json' -d "
                   "'{\"contents\":[{\"parts\":[{\"text\":\"%s\"}]}]}' -X POST "
                   "\"https://generativelanguage.googleapis.com/v1beta/models/"
                   "gemini-pro:generateContent?key=%s\" 2>/dev/null";

void process_string(const char *input) {
  size_t len = strlen(input);
  for (size_t i = 0; i < len; i++) {
    if (input[i] == '*') {
      continue;
    }
    if (input[i] == '\\') {
      if (i + 1 < len && input[i + 1] == 'n') {
        printf("\n");
        i++; // Skip the 'n'
        continue;
      }
    }
    printf("%c", input[i]);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "-H"))) {
    printf("Usage: %s <your Question>\nor\n", argv[0]);
    printf("Usage: %s \nAnd Input Your Question And End Question while Typing EOF\n", argv[0]);
    // printf("Usage: %s\n", argv[0]);

    printf(
        "用的command调用的curl命令,参数放到curl命令里面而已,格式化 output\n");

    realpath(".", PathBuff);
    printf("source file : %s/%s\n", PathBuff, __FILE__);
    return 0;
  }

  if (argc == 1) {
    printf("Please input your Question (EOF for end):\n");
    char *BuffMove = Buff;

    while (fgets(BuffMove, BUFSIZ, stdin) && strncmp(BuffMove, "EOF", 3)) {
      BuffMove += strlen(BuffMove);
    }

  } else {
    char *move = Buff;
    for (int i = 1; argv[i]; i++) {
      sprintf(move, "%s ", argv[i]);
      move += strlen(move);
    }

    Buff[strlen(Buff) - 1] = '\0'; // remove last space
  }

  // 保存原始的标准输出文件描述符

  int stdout_save = dup(STDOUT_FILENO);

  // argvc >1 end

  char *envValue=getenv("GGOOGLEAPI");
  if(envValue==NULL){
      fprintf(stderr,"Please set GGOOGLEAPI On your environment \n");
      exit(EXIT_FAILURE);
  }

  sprintf(command, CurlFormat, Buff, envValue);

  int fd = open("/tmp/gaiXXXXXX", O_RDWR | O_CREAT | O_TRUNC, 0644);

  if (fd == -1) {
    fprintf(stderr, "%s\n", "mkstemp error");
    close(stdout_save);
    exit(EXIT_FAILURE);
  }

  if (dup2(fd, STDOUT_FILENO) == -1) {
    fprintf(stderr, "%s line:%d\n", "dup2 error", __LINE__);
    close(stdout_save);
    exit(EXIT_FAILURE);
  }

  system(command);

  // 错误输出
  // fprintf(stderr,"---Content Start
  // Line-----------------------------------------------------\n\n");

  lseek(fd, 0, SEEK_SET);

  read(fd, RESPONSE, BUFSIZ * 10 - 1); // 读取文件内容 TODO 判断大小

  const char *startFlag = "\"text\": \"";
  char endFlag = '"';

  char *start = strstr(RESPONSE, startFlag);
  // fprintf(stderr,"line:%d,start:%s\n\n\n\n",__LINE__,start);
  if (start == NULL) {
    fprintf(stderr, "Can't find %s line:%d\n", startFlag, __LINE__);
    close(fd);
    close(stdout_save);

    exit(EXIT_FAILURE);
  }

  start += strlen(startFlag);

#if 0
    char *end=strchr(start,endFlag);
    if(end==NULL){
        fprintf(stderr,"Can't find %s line:%d\n",startFlag,__LINE__);
        close(fd);
        close(stdout_save);
        exit(EXIT_FAILURE);
    }
    *end='\0';
#else
  char *end = start;
  int flag = 1;
  while (*end != '\0') {
    if (*end == '{') {
      flag++;
    } else if (*end == '}') {
      flag--;
      if (flag == 0) {
        while (*end != '"') {
          end--;
        }
        // end++;

        *end++ = '\n';
        *end = '\0';

        break;
      }
    }
    end++;
  }

#endif

  if (dup2(stdout_save, STDOUT_FILENO) == -1) {
    fprintf(stderr, "%s\n", "dup2 error");
    close(fd);
    close(stdout_save);
    exit(EXIT_FAILURE);
  }

  // printf("%s\n",start);
  process_string(start);
  fflush(stdout);

  // fprintf(stderr,"\n\n--------------------------------------------------------------------------\n");

  close(fd);
  close(stdout_save);

  return 0;
}