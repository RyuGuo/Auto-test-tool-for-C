#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <time.h>

#define SAMPLE_FILE_MAXNUM 256
#define COMMAND_MAXNUM 1024

char command[COMMAND_MAXNUM];
char sample_in_files[FILENAME_MAX][SAMPLE_FILE_MAXNUM];
char sample_out_files[FILENAME_MAX][SAMPLE_FILE_MAXNUM];
char sample_testout_files[FILENAME_MAX][SAMPLE_FILE_MAXNUM];

int sample_in_num = 0;
int sample_out_num = 0;

int begintime = 0;
int endtime = 0;

int parsingCommand(int argc, char const *argv[]);
int getSampleFile();
int checkSampleFile();
int createTextOutFile();
int executePrograme(const char *);
int diffTestOut();
int showError(char type);

int main(int argc, char const *argv[])
{

  begintime = clock();
  parsingCommand(argc, argv);
  getSampleFile();
  if(checkSampleFile() == 0) {
    showError(1);
    return 0;
  }

  createTextOutFile();
  executePrograme(argv[1]);
  endtime = clock();
  diffTestOut();
  return 0;
}

int parsingCommand(int argc, char const *argv[])
{
  if(argc == 1) {
    showError(0);
  } else if(argc == 2) {
    if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0) {
      printf("auto_test is an automatic testing tool, which can directly test C program with one key and output test results.\nCommand:\n");
      printf("\t--help\t\t\tfor help\n");
      printf("\t[program]\t\tstart auto test a program\n");
      printf("\t-s [n]\t\t\tcreate n tests in and out files\n");
      printf("If you have any questions or suggestions, you can consult through the following ways:\nEmail:843840655@qq.com");
      exit(0);
    } else {
      return 1;
    }
  } else if(argc == 3) {
    if(strcmp(argv[1], "-s")==0) {
      int i;
      int len = strlen(argv[2]);
      for(i=0;i<len;i++){
        if(argv[2][i] < '0' || argv[2][i] > '9') {
          showError(2);
        }
      }
      int num = atoi(argv[2]);
      if(access("./sample", 0)) {
        system("mkdir sample");
      }

      FILE *fp;
      for(i=1;i<=num;i++){
        sprintf(command, "./sample/sample%d_in.txt", i);
        fp = fopen(command, "a");
        fclose(fp);
        sprintf(command, "./sample/sample%d_out.txt", i);
        fp = fopen(command, "a");
        fclose(fp);
      }
      exit(0);
    }
  }
}

int getSampleFile() 
{
  long FileHandle;
  struct _finddata_t FileInfo;
  sample_in_num = sample_out_num = 0;

  if((FileHandle = _findfirst(".\\sample\\*_in.txt", &FileInfo)) == -1L) {
    printf("没有找到测试输入用例文件");
    return 0;
  } else {
    strcpy(sample_in_files[sample_in_num], FileInfo.name);
    sample_in_num++;
    while(_findnext(FileHandle, &FileInfo) == 0) {
      strcpy(sample_in_files[sample_in_num], FileInfo.name);
      sample_in_num++;
    }
    _findclose(FileHandle);
  }

  if((FileHandle = _findfirst(".\\sample\\*_out.txt", &FileInfo)) == -1L) {
    printf("没有找到测试输出用例文件");
    return 0;
  } else {
    strcpy(sample_out_files[sample_out_num], FileInfo.name);
    sample_out_num++;
    while(_findnext(FileHandle, &FileInfo) == 0) {
      strcpy(sample_out_files[sample_out_num], FileInfo.name);
      sample_out_num++;
    }
    _findclose(FileHandle);
  }
  return 1;
}

int checkSampleFile()
{
  if(sample_in_num != sample_out_num) {
    return 0;
  }
  int i;
  char str1[FILENAME_MAX], str2[FILENAME_MAX];
  for(i=0;i<sample_in_num;i++){
    strcpy(str1, sample_in_files[i]);
    strcpy(str2, sample_out_files[i]);
    str1[strlen(str1) - 7] = '\0';
    str2[strlen(str2) - 8] = '\0';
    if(strcmp(str1, str2) != 0) {
      return 0;
    }
  }
  return 1;
}

int createTextOutFile()
{
  int i;
  for(i=0;i<sample_in_num;i++){
    strcpy(sample_testout_files[i], sample_in_files[i]);
    sample_testout_files[i][strlen(sample_testout_files[i]) - 6] = '\0';
    strcat(sample_testout_files[i], "testout.txt");
  }
  return 1;
}

int executePrograme(const char *program)
{
  int i;
  if(access("./sample_testout", 0)) {
    system("mkdir sample_testout");
  }
  for(i = 0; i < sample_in_num; i++) {
    sprintf(
      command,
      "%s < ./sample/%s > ./sample_testout/%s",
      program,
      sample_in_files[i],
      sample_testout_files[i]
    );
    printf("%s\n", command);
    system(command);
  }
  return 1;
}

int diffTestOut()
{
  FILE *fp = fopen("sample_test_diff.txt", "w");
  FILE *fp_sample_out;
  FILE *fp_sample_testout;
  char ch_out=0, ch_testout=0;

  int i,j;
  int str_p;
  char str[32768];

  fprintf(fp, "Sample File: ");
  for(i=0;i<sample_in_num;i++) {
    fprintf(fp, "%s ", sample_in_files[i]);
  }
  
  fprintf(fp, "\nSample File Num: %d\nTest Time: %ld ms\n", sample_in_num, endtime - begintime);

  for(i=0;i<sample_in_num;i++){
    
    strcpy(str, "./sample/");
    strcat(str, sample_out_files[i]);
    fp_sample_out = fopen(str, "r");
    strcpy(str, "./sample_testout/");
    strcat(str, sample_testout_files[i]);
    fp_sample_testout = fopen(str, "r");

    str_p = 0;
    str[0] = '\0';
    ch_out = fgetc(fp_sample_out);
    ch_testout = fgetc(fp_sample_testout);
    while(ch_out != EOF && ch_testout != EOF) {
      if(ch_out == ch_testout) {
        str[str_p] = ch_out;
        str_p++;
      } else {
        break;
      }
      ch_out = fgetc(fp_sample_out);
      ch_testout = fgetc(fp_sample_testout);
    }

    str[str_p] = '\0';
    str_p++;
    
    // get last '\n' index of str_p then divide it
    int str_divi_p = 0;
    for(j=str_p-1;j>=0;j--) {
      if(str[j] == '\n') {
        str[j] = '\0';
        str_divi_p = j+1;
        break;
      }
    }

    if(ch_out != EOF || ch_testout != EOF) {
      fprintf(fp, "\nFailed %s:\n", sample_in_files[i]);
      if(str_divi_p != 0) {
        fprintf(fp, "%s", str);
      }

      fprintf(fp, "\n<<<==== testout =======\n");
      fprintf(fp, "%s", str + str_divi_p);
      while(ch_testout != EOF) {
        fprintf(fp, "%c", ch_testout);
        ch_testout = fgetc(fp_sample_testout);
      }

      fprintf(fp, "\n+++++++++ out +++++++++\n");
      fprintf(fp, "%s", str + str_divi_p);
      while(ch_out != EOF) {
        fprintf(fp, "%c", ch_out);
        ch_out = fgetc(fp_sample_out);
      }

      fprintf(fp, "\n====================>>>\n");
    }
    fclose(fp_sample_out);
    fclose(fp_sample_testout);
  }
  fclose(fp);
  return 1;
}

int showError(char type)
{
  switch(type) {
    case 0:
      printf("Error: autotest command error!\nYou can input this command for help:\n\tautotest --help");
    break;
    case 1:
      printf("Error: your test case is wrong!\nPlease check your sample_in.txt and sample_out.txt");
    break;
    case 2:
      printf("Error: autotest command error!\nargument \"-s\" should be number");
    break;
    default:
      printf("Error: autotest command error!\nYou can input this command for help:\n\tautotest --help");
    break;
  }
  exit(0);
}