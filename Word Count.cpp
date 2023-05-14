#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义一个函数，用于统计文件中的字符数
int count_chars(FILE *fp) {
  int count = 0; //初始化计数器
  char ch; //定义一个字符变量
  while ((ch = fgetc(fp)) != EOF) { //循环读取文件中的每个字符，直到遇到文件结束符
    count++; //每读取一个字符，计数器加一
  }
  return count; //返回计数器的值
}

//定义一个函数，用于统计文件中的单词数
int count_words(FILE *fp) {
  int count = 0; //初始化计数器
  char ch; //定义一个字符变量
  int in_word = 0; //定义一个标志变量，用于判断是否在单词内部
  while ((ch = fgetc(fp)) != EOF) { //循环读取文件中的每个字符，直到遇到文件结束符
    if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t') { //如果遇到空格，逗号，换行符或制表符
      if (in_word) { //如果之前在单词内部
        count++; //计数器加一
        in_word = 0; //标志变量置为零，表示退出单词
      }
    } else { //如果遇到其他字符
      in_word = 1; //标志变量置为一，表示进入单词
    }
  }
  if (in_word) { //如果文件结束时还在单词内部
    count++; //计数器加一
  }
  return count; //返回计数器的值
}

//主函数
int main(int argc, char *argv[]) {
  FILE *fp; //定义一个文件指针变量
  int result; //定义一个结果变量

  if (argc != 3) { //如果参数个数不等于3（程序名，控制参数，文件名）
    printf("Usage: %s [-c|-w] input_file_name\n", argv[0]); //打印用法提示信息
    exit(1); //退出程序，返回错误码1
  }

  fp = fopen(argv[2], "r"); //以只读模式打开指定的文件，并将文件指针赋给fp

  if (fp == NULL) { //如果打开失败（文件不存在或无权限）
    printf("Error: cannot open file %s\n", argv[2]); //打印错误信息
    exit(2); //退出程序，返回错误码2
  }

  if (strcmp(argv[1], "-c") == 0) { //如果控制参数为-c（统计字符数）
    result = count_chars(fp); //调用count_chars函数，并将返回值赋给result
    printf("字符数：%d\n", result); //打印结果信息
  } else if (strcmp(argv[1], "-w") == 0) { //如果控制参数为-w（统计单词数）
    result = count_words(fp); //调用count_words函数，并将返回值赋给result
    printf("单词数：%d\n", result); //打印结果信息
  } else { //如果控制参数既不是-c也不是-w（无效参数）
    printf("Error: invalid parameter %s\n", argv[1]); //打印错误信息
    exit(3); //退出程序，返回错误码3
  }

  fclose(fp); //关闭文件

  return 0; //正常结束程序，返回0

}
