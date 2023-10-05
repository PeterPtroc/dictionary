#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 定义了结构体Word，它的两个成员word和meaning都是大小为256字节的字符型数组，用来储存单词及释义
//同时使用typedef函数为Word创建一个一个别名Word（从网上学到的，这样就可以直接用Word指向结构体而不用struct Word，方便了）
typedef struct Word {
  char word[256];
  char meaning[256];
} Word;

// 单词列表
struct Word *words;                            //定义了一个指向Word结构体的指针，命名为words
int word_count = 0;                            //单词计数，后面常用

// 添加单词
void add_word() {                              //这里定义了一个函数，名叫add_word()
  // 申请内存
  Word *word = (Word *)malloc(sizeof(Word));
  /*
  这段代码包含两个内容
  1、Word *word 定义了一个指向 Word 结构体的指针，命名为word注意这个word，是用来储存新单词的指针，和words区分开
  2、(Word *)malloc(sizeof(Word)) 使用 malloc() 函数来申请 sizeof(Word) 大小的内存（sizeof是获取变量所占空间的函数）并将其指针存储在 word 变量中
  总之Word *word = (Word *)malloc(sizeof(Word)); 用于动态分配 Word 结构体的大小的内存，并将指向该内存的指针赋给 word 变量
  */

  // 输入单词和释义
  printf("please input word:");                                    //输入提示
  fgets(word->word, sizeof(word->word), stdin);                    //这里又比较复杂，用fgets函数读取输入内容，word->word嘛，看下面对于word->meaning的解释就懂了（确实是我取名问题，懒得改了）
  fflush(stdin);
  printf("please input meaning:");
  fgets(word->meaning, sizeof(word->meaning), stdin);
  fflush(stdin);
  /*
word->meaning
首先呢，在这个函数中我们定义了word是指向结构体Word的指针
而meaning呢又是Word的成员
然后呢->这一坨的作用是将 word 指针指向的结构体中的 meaning 成员的内存地址返回给 meaning 变量
因此word->meaning 也可以写成 (*word).meaning
总而言之这段代码先读取了数据，再访问 Word 结构体的 meaning 成员，而后将读取的数据存储在word指针指向的内存中，也就是Word
  */


  // 去除换行符
  word->word[strcspn(word->word, "\n")] = '\0';                    //使用strcspn函数将换行符替换为结束符
  word->meaning[strcspn(word->meaning, "\n")] = '\0';




  // 添加到单词列表
  words = (Word *)realloc(words, sizeof(Word) * (word_count + 1));
  /*
realloc是用来重新分配内存，以此节约程序的内存开销
用法：指针名=（数据类型*）realloc（要改变内存大小的指针名，新的大小）
realloc()函数的返回值是一个指针，指向重新分配的内存。这个指针的类型是 void *，即通用指针，
但是Word是结构体类型，所以我们需要将realloc()函数的返回值转换为Word类型的指针，能将它赋给words指针，也就是(Word *)的作用
总之，这句话的意思是计算新的结构体Word的大小，按照大小为其重新分配内存，然后把words指针指向新分配的内存位置
  */
 
  words[word_count] = *word;
/*
words[word_count] 是指向单词列表中最后一个单词的指针,而*word 是指向新单词的指针
总之，words[word_count] = *word用于将新单词复制到单词列表中最后一个单词的位置
*/
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
  char input[256];
  fgets(input, sizeof(input), stdin);          //这里有个小问题，问什么这里写的是input而非&input？因为input是个数组，数组名input本身储存的就是地址，就不用&取地址了
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
    fflush(stdin);
    printf(
            "\nwelcome to XiaoNiu dictionary, please choose:\n"
            "1. add new word\n"
            "2. view current words\n"
            "3. review words\n"
            "4. exit\n");
    char input[256];
    fgets(input, sizeof(input), stdin);
    choice = strtol(input, NULL, 10);

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
