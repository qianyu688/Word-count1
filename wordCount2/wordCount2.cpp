// wordCount2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 函数声明
int count_chars(FILE* fp);
int count_words(FILE* fp);

int main(int argc, char* argv[]) {
    FILE* fp = NULL;
    char* filename;
    char parameter;
    errno_t err; // 用于存储 fopen_s 的错误代码

    // 检查参数数量
    if (argc != 3) {
        printf("Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    // 解析参数
    parameter = argv[1][1];
    filename = argv[2];

    // 使用 fopen_s 替换 fopen，并检查错误代码
    err = fopen_s(&fp, filename, "r");
    if (err != 0) {
        perror("Error opening file");
        return 1;
    }

    // 根据参数统计字符数或单词数
    if (parameter == 'c' || parameter == 'w') {
        if (parameter == 'c') {
            printf("字符数：%d\n", count_chars(fp));
        }
        else if (parameter == 'w') {
            printf("单词数：%d\n", count_words(fp));
        }
    }
    else {
        printf("Invalid parameter\n");
    }

    // 关闭文件
    fclose(fp);

    return 0;
}

// 统计字符数
int count_chars(FILE* fp) {
    int ch, count = 0;
    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }
    rewind(fp); // 重置文件指针位置，以便其他函数可以读取文件
    return count;
}

// 统计单词数
int count_words(FILE* fp) {
    int ch, in_word = 0, count = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch) || ch == ',') { // 遇到空格、水平制表符、换行符或逗号
            if (in_word) {
                count++;
                in_word = 0;
            }
        }
        else {
            in_word = 1;
        }
    }
    // 最后一个单词可能没有遇到分隔符，需要额外检查
    if (in_word) {
        count++;
    }
    rewind(fp); // 重置文件指针位置，以便其他函数可以读取文件
    return count;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
