#include<iostream>
#include<stack>

//画个图 自己模拟一下应该可以提取出逻辑
void stack_reorder(std::stack<int>& s) {
  std::stack<int> stack_tmp;
  int cur;

    if(stack_tmp.empty())  
      stack_tmp.push(s.top());
    cur = s.top();

  while(!s.empty()) {
    cur = s.top();
    while(cur < stack_tmp.top()) {
      stack_tmp.push(cur);
      s.pop();
      cur = s.top();
    }
    //s: 100 2 1
    //stack_tmp: 4 5 
    while(!stack_tmp.empty()) {
      int i = stack_tmp.top();
      std::cout<<"i = " <<i<<std::endl;
      stack_tmp.pop();
    }
    
    /*

    s.pop(); //弹出最大值 
    //s: 2 1
    //stack_tmp: 4 5 

    while(!stack_tmp.empty()) {
      int tmp = stack_tmp.top();
      if (tmp > cur) {
        break;
      }
      s.push(tmp);
      std::cout<<"tmp = "<<tmp<<std::endl;
      stack_tmp.pop();
    } 

    stack_tmp.push(cur);
    */
  }

  while(!stack_tmp.empty()) {
    std::cout<<stack_tmp.top()<<std::endl;
    stack_tmp.pop();
  }
  
  return;
}

void stack_reorder1(std::stack<int>& s) {
  std::stack<int> s1;
  
  while(!s.empty()) {
    int cur = s.top();
    s.pop();

    while(!s1.empty() && cur > s1.top()) {
      int tmp = s1.top();
      s1.pop();
      s.push(tmp);
    }
        
    s1.push(cur);

  }

  while(!s1.empty()) {
    int tmp = s1.top();
    s1.pop();
    s.push(tmp);
  }
  return;
}

int main()
{
  std::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(100);
  s.push(4);
  s.push(5);

  stack_reorder1(s);

  while(!s.empty()) {
    int t = s.top();
    s.pop();
    std::cout<<t<<std::endl;
  }

  return 0;
}
