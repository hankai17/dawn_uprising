#include<iostream>
#include<list>

void delete_backwards(std::list<int>& l, int k) {
  if((int)l.size() < k) {
    return;
  } else if((int)l.size() == k) {
    l.pop_front();
    return;
  } else {
    std::list<int>::iterator it = l.begin();
    while(it != l.end()) {
      k--;
      it++;
    }
    k++;
    //std::cout<<"fun k="<<k<<std::endl;

    it = l.begin();
    while(k != 0) {
      k++;
      it++;
    }
    l.erase(++it);
  }
  return;
}
int main()
{
  std::list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);
  l.push_back(6);
  delete_backwards(l, 2);

  std::list<int>::iterator it = l.begin();
  while(it != l.end()) {
    std::cout<<*it<<" ";
    it++;
  }
  return 0;
}

int main1()
{
  std::list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);
  l.push_back(6);
  std::cout<<"input backwards:";
  char K[2] = {0};
  std::cin>>K;
  int count = atoi(K);
  std::cout<<"K="<<count<<std::endl;
  delete_backwards(l, count);

  std::list<int>::iterator it = l.begin();
  while(it != l.end()) {
    std::cout<<*it<<" ";
    it++;
  }
  return 0;
}
