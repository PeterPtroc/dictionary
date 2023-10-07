#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 定义了结构体Word
typedef struct Word {
  char *word;
  char *meaning;
} Word;

// 单词列表
struct Word *words;
int word_count = 0;

// 读取用户输入
char *read_user_input(const char *prompt) {
  static char input[256];
  printf("%s", prompt);
  fgets(input, sizeof(input), stdin);
  input[strlen(input)-1] = '\0';
  fflush(stdin);
  return input;
}


// 添加单词
void add_word() {
  // 申请内存
  Word *word = (Word *)malloc(sizeof(Word));

  // 输入单词和释义
  char *input = read_user_input("please input word:");
  word->word = (char *)malloc(strlen(input) + 1);
  strcpy(word->word, input);
  input = read_user_input("please input meaning:");
  word->meaning = (char *)malloc(strlen(input) + 1);
  strcpy(word->meaning, input);

  // 添加到单词列表
  words = (Word *)realloc(words, sizeof(Word) * (word_count + 1));
  words[word_count] = *word;
  word_count++;

  // 释放内存
  free(word);
}

// 查看单词
void view_words() {
  for (int i = 0; i < word_count; i++) {
    printf("%d. %s: %s\n", i + 1, words[i].word, words[i].meaning);
  }
}

// 复习单词
void review_words() {
  // 随机选择一个单词
  int index = rand() % word_count;

  // 显示释义
  printf("please input word with this meaning:%s\n", words[index].meaning);

  // 用户输入单词
  char *input = read_user_input("");

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
  // 设置随机种子为时间
  srand(time(NULL));

  // 菜单
  int choice = 0;
  while (1) {

    printf(
            "\nwelcome to XiaoNiu dictionary, please choose:\n"
            "1. add new word\n"
            "2. view current words\n"
            "3. review words\n"
            "4. exit\n");
    // 读取用户输入
    choice = getchar();
    // 转换为整型
    choice = choice - '0';
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
