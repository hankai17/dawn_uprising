#include<iostream>

int count;

//是时候描述一下函数的作用了
//这个函数的作用 把a中的1~n-1放到b 把n放到c 把b上的1~n-1放到c
//思路正确 但是还是写不出代码

void move(char a, char b) {
  std::cout<<"move: " <<a <<"---> "<<b<<std::endl;
  count++;
  return;
}

//函数整体上是整个汉诺塔完成的功能 即将m个塔从one上把所有塔移动到three上(借助two)
void hanno_tower(int m, char one, char two, char three) {
  if(m == 1) {
    move(one, three);
  } else {
    hanno_tower(m-1,one,three,two);
    move(one, three);
    hanno_tower(m-1,two,one,three);
    return;
  }
}
//写不出来的原因：(int m, char one, char two, char three) 这种结构设计不出来

int main()
{
  int m = 64;
  hanno_tower(m, 'a', 'b', 'c'); 
  std::cout<<"count = "<<count<<std::endl;
  return 0;
}

//汉诺塔的 数列推到问题很有意思 
//应该是高中知识 忘了 没写出来 没思路
http://www.cnblogs.com/xxNote/articles/3965739.html
