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

    // ���������в���
    if (argc == 2) {
        parameter = '-'; // Ĭ��ֵΪ�ַ���ͳ��
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
            count++; // ͳ�ƻ��з�
        } else {
            word_count++; // ͳ�����һ������
        }
    }

    fclose(fp);

    // ������
    if (parameter == 'c') {
        printf("�ַ�����%d\n", count);
    } else {
        printf("��������%d\n", word_count);
    }

    return 0;
}
