#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 256
#define MAX_BUF_SIZE 1024

int main(int argc, char **argv) {
    char *filename;
    char parameter;
    int count = 0, word_count = 0;
    FILE *fp;
    char buf[MAX_BUF_SIZE];

    // 解析命令行参数
    if (argc == 2) {
        parameter = '-'; // 默认值为字符数统计
        filename = argv[1];
    } else if (argc == 3) {
        parameter = argv[1][1];
        filename = argv[2];
    } else {
        printf("Usage: WordCount [-c/-w] [filename]\n");
        return 1;
    }

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    while (fgets(buf, MAX_BUF_SIZE, fp)) {
        int len = strlen(buf);
        int i;
        for (i = 0; i < len; i++) {
            if (parameter == 'c') {
                count++;
            } else if (isspace(buf[i])) {
                word_count++;
            }
        }
        if (parameter == 'c') {
            count++; // 统计换行符
        } else {
            word_count++; // 统计最后一个单词
        }
    }

    fclose(fp);

    // 输出结果
    if (parameter == 'c') {
        printf("字符数：%d\n", count);
    } else {
        printf("单词数：%d\n", word_count);
    }

    return 0;
}
