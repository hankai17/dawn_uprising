#include<iostream>
#include<stack>
#define FLAG_TRUE 1
#define FLAG_FALSE 0

struct tree_node {
  int data;
  struct tree_node* ldata;
  struct tree_node* rdata;
};

void print(tree_node* root) {
  if (root == NULL) {
    return;
  }
  std::stack<tree_node*> s;
  s.push(root);
  while(!s.empty()) {
    root = s.top();
    s.pop();
    std::cout<<root->data<<" ";
    if (root->rdata != NULL) {
      s.push(root->rdata);
    }
    if (root->ldata != NULL) {
      s.push(root->ldata);
    }
  }
}

//��ӡ������ ������� �ȴ�ӡ��
void recursor_print(tree_node* root) {
  if (root == NULL) {
    return;
  }
  std::cout<<root->data<<" ";
  recursor_print(root->ldata);
  recursor_print(root->rdata);
}

int get_height(tree_node* head, int l) {
  if (head == NULL) {
    return l;
  }
  return std::max(get_height(head->ldata,l + 1),get_height(head->rdata, l + 1));
}

void set_edge_map(tree_node* head, int l, tree_node* (*map)[2] ) {
  if (head == NULL) {
    return;
  }
  map[l][0] = map[l][0] == NULL ? head : map[l][0];
  map[l][1] = head;

  set_edge_map(head->ldata, l + 1, map);
  set_edge_map(head->rdata, l + 1, map);
}

void print_leaf(tree_node* head, int l) {
  if (head == NULL) {
   return; 
  }
  if (head->ldata == NULL && head->rdata == NULL) {
    std::cout<<head->data<<" "<<std::endl;
  }
  print_leaf(head->ldata, l + 1);
  print_leaf(head->rdata, l + 1);
}

int main() {
  //�������
  tree_node  node1, node2, node3, node4, node5, node6, node7, node8;
  node1.data = 1; node1.ldata = NULL; node1.rdata = NULL;
  node2.data = 2; node2.ldata = NULL; node2.rdata = NULL;
  node3.data = 3; node3.ldata = NULL; node3.rdata = NULL;
  node4.data = 4; node4.ldata = NULL; node4.rdata = NULL;
  node5.data = 5; node5.ldata = NULL; node5.rdata = NULL;
  node6.data = 6; node6.ldata = NULL; node6.rdata = NULL;
  node7.data = 7; node7.ldata = NULL; node7.rdata = NULL;
  node8.data = 8; node8.ldata = NULL; node8.rdata = NULL;

  //��������ϵ
  node1.ldata = &node2;
  node1.rdata = &node6;

  node2.ldata = NULL;
  node2.rdata = &node3;

  node3.ldata = &node4;
  node3.rdata = &node5;

  node6.ldata = NULL;
  node6.rdata = &node7;

  node7.ldata = &node8;
  node7.rdata = NULL;

  recursor_print(&node1);
  std::cout<<"\n";
  print(&node1);

  int height = get_height(&node1, 0);
  std::cout<<"height = "<<height<<std::endl;
  print_leaf(&node1, 0);

  tree_node* node_map[height][2];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      node_map[i][j] = NULL;
    }
  }
  std::cout<<sizeof(node_map)/sizeof(node_map[0])<<"----"<<std::endl;
  //set_edge_map(&node1, 0, node_map, sizeof(node_map)/sizeof(node_map[0]));
  set_edge_map(&node1, 0, node_map);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < 2; j++) {
      std::cout<<(node_map[i][j])->data<<std::endl;
    }
  }

  return EXIT_SUCCESS;
}
