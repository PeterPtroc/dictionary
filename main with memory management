#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxLen 256

/*
动态内存管理想达成的目标（我也不太确定实现没有）：
当输入小于maxLen,由用户输入的长度决定内存占用大小
当输入大于maxLen，仅保留maxLen以使内存用量可控
*/

// 定义结构体Word
typedef struct Word {
  char *word;
  char *meaning;
} Word;

// 单词列表
struct Word *words;
int word_count = 0;

// 添加单词
void add_word() {
  // 申请内存
  Word *word = (Word *)malloc(sizeof(Word));

  // 输入单词和释义
  printf("please input word:");
  word->word = (char *)malloc(sizeof(char) * maxLen);    //这里有个问题malloc(sizeof(char) * 256)和malloc(256)有什么不同，或者说有什么好处
  fgets(word->word, maxLen, stdin);
  fflush(stdin);
  printf("please input meaning:");
  word->meaning = (char *)malloc(sizeof(char) * maxLen);
  fgets(word->meaning, maxLen, stdin);
  fflush(stdin);

  // 去除换行符
  word->word[strcspn(word->word, "\n")] = '\0';
  word->meaning[strcspn(word->meaning, "\n")] = '\0';

  // 添加到单词列表
  words = (Word *)realloc(words, sizeof(Word) * (word_count + 1));
  words[word_count] = *word;
  word_count++;
}

// 查看单词
void view_words() {
  for (int i = 0; i < word_count; i++) {
    printf("%d. %s: %s\n", i + 1, words[i].word, words[i].meaning);
  }
}

// 复习单词
void review_words() {
  // 设置随机种子为时间
  srand(time(NULL));
  // 随机选择一个单词
  int index = rand() % word_count;

  // 显示释义
  printf("please input word with this meaning:%s\n", words[index].meaning);

  // 用户输入单词
  char input[maxLen];
  fgets(input, sizeof(input), stdin);
  input[strcspn(input, "\n")] = '\0';

  // 判断是否答对
  if (strcmp(input, words[index].word) == 0) {
    printf("yes, you are right!\n");
  } else {
    printf("nonono, play genshin to much?\n");
  }
}

int main() {
  // 初始化
  words = NULL;
  word_count = 0;

  // 菜单
  int choice = 0;
  while (1) {
    printf(
            "\nwelcome to XiaoNiu dictionary, please choose:\n"
            "1. add new word\n"
            "2. view current words\n"
            "3. review words\n"
            "4. exit\n");
    char input[maxLen];
    fgets(input, sizeof(input), stdin);
    choice = strtol(input, NULL, 10);
    fflush(stdin);
    // 判断是否储存有单词
    if (word_count == 0 && choice == 3) {
      printf("you have no words to review, add some words !\n");
      continue;
    }
    
    switch (choice) {
      case 1:
        add_word();
        break;
      case 2:
        view_words();
        break;
      case 3:
        review_words();
        break;
      case 4:
        return 0;
      default:
        printf("wrong input!\n");
        break;
    }
  }

  return 0;
}
