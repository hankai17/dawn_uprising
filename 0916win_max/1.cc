#include<iostream>
#include<stdio.h>
#include<deque>
#define ARRAY_SIZE 8
#define WIN_SIZE 3

void get_win_max(int* a) {
  std::deque<int> qmax;
  std::deque<int> result;
  for(int i = 0; i < ARRAY_SIZE; i++) {
    if(!qmax.empty()) {
      if(a[i] <= a[qmax.back()]) {
        qmax.push_back(i);
        //while(i - qmax.front() + 1 > WIN_SIZE && !qmax.empty()) {
        while(!qmax.empty() && (i - qmax.front() + 1 > WIN_SIZE) ) {
          qmax.pop_front();
        }
      } else {
        //while(a[i] > a[qmax.back()] && !qmax.empty()) {
        while(!qmax.empty() && a[i] > a[qmax.back()]) {
          qmax.pop_back();
        }
        qmax.push_back(i);
      }
    } else {
      qmax.push_back(i);
    }

    if(i >= WIN_SIZE -1) {
      int tmp = qmax.front();
      result.push_back(tmp);
    }
  }
  while(!result.empty()) {
    std::cout<<a[result.front()]<<std::endl;
    result.pop_front();
  }
  return;
}

int main()
{
  int array[ARRAY_SIZE] = {4, 3, 5, 4, 3, 3, 6, 7 };

  get_win_max(array);
  return 0;
}

