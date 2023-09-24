#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义了结构体Word，它的两个成员word和meaning都是大小为256字节的字符型数组，用来储存单词及释义
//同时使用typedef函数为Word创建一个一个别名Word（从网上学到的，这样就可以直接用Word指向结构体而不用struct Word，方便了）
typedef struct Word {
  char word[256];
  char meaning[256];
} Word;

// 单词列表
struct Word *words;                            //定义了一个指向Word结构体的指针，命名为words
int word_count = 0;                            //你总得知道你存了多少个词吧

// 添加单词
void add_word() {                              //这里定义了一个函数，名叫add_word()
  // 申请内存
  Word *word = (Word *)malloc(sizeof(Word));
  /*
  这段代码包含两个内容
  1、Word *word 定义了一个指向 Word 结构体的指针，命名为word。
  2、(Word *)malloc(sizeof(Word)) 使用 malloc() 函数来申请 sizeof(Word) 大小的内存（sizeof是获取变量所占空间的函数）并将其指针存储在 word 变量中。
  */

  // 输入单词和释义
  printf("please input word:");                 //输入提示
  scanf("%s", word->word);                      //这里又比较复杂，用scanf函数读取输入内容，word->word嘛，看下面对于word->meaning的解释就懂了（确实是我取名问题，懒得改了）
  printf("please input meaning:");
  scanf("%s", word->meaning);
  /*
word->meaning
首先呢，在这个函数中我们定义了word是指向结构体Word的指针
而meaning呢又是Word的成员
然后呢->这一坨的作用是将 word 指针指向的结构体中的 meaning 成员的内存地址返回给 meaning 变量
因此word->meaning 也可以写成 (*word).meaning
总而言之这段代码先读取了数据，再访问 Word 结构体的 meaning 成员，而后将读取的数据存储在word指针指向的内存中，也就是Word
  */



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
  // 随机选择一个单词
  int index = rand() % word_count;

  // 显示释义
  printf("please input word:%s\n", words[index].meaning);

  // 用户输入单词
  char input[256];
  scanf("%s", input);

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
  int choice;
  while (1) {
    printf("please choose:\n"
           "1. add new word\n"
           "2. view current words\n"
           "3. review words\n"
           "4. exit\n");
    scanf("%d", &choice);

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
