# Problem
假设有一亿篇英文文章(Document)，每篇文章都有若干个单词(Word)组成，例如(long years ago, there are a frog)，现在需要你设计一个系统，这个系统在接受一亿篇文章作为输入后，能够快速回答下列问题:
* 包含某个单词的所有文章集合，例如包含”years”的所有文章。
* 包含某几个连续单词组成的词组的所有文章集合，例如包含”long years”的所有文章。

编码要求，使用c++语言，自己设计和定义算法和数据结构。

# Solution
* trie + inverted indexing
* forword indexing
