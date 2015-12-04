#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct AVLNode {
  int key;
  int height;
  AVLNode *left;
  AVLNode *right;
//  AVLNode(): {}
  AVLNode(int k): key(k), height(1), left(NULL), right(NULL) {}
};

typedef AVLNode* node;

int height(node p) {
  return p ? p->height : 0;
}

int balance_factor(node p) {
  return height(p->right) - height(p->left);
}

void fix_height(node p) {
  int hl = height(p->left);
  int hr = height(p->right);
  p->height = (hl > hr ? hl : hr) + 1;
}

node right_rotate(node p) {
  node q = p->left;
  p->left = q->right;
  q->right = p;
  fix_height(p);
  fix_height(q);
  return q;
}

node left_rotate(node p) {
  node q = p->right;
  p->right = q->left;
  q->left = p;
  fix_height(p);
  fix_height(q);
  return q;
}

node balance(node p) {
  fix_height(p);
  if (balance_factor(p) == 2) {
    if (balance_factor(p->right) < 0) 
      p->right = right_rotate(p->right);
    return left_rotate(p);
  }
  if (balance_factor(p) == -2) {
    if (balance_factor(p->left) > 0) 
      p->left = left_rotate(p->left);
    return right_rotate(p);
  }
  return p;
}

node insert(node root, int k) {
  if (!root) return new AVLNode(k);
  if (k < root->key) 
    root->left = insert(root->left, k);
  else 
    root->right = insert(root->right, k);
  return balance(root);
}

node get_min(node root) {
  if (!root) return nullptr;
  return root->left ? get_min(root->left) : root;
}

node remove_min(node root) {
 if (!root) return nullptr;
 if (!root->left) {
  return root->right;
 }
 root->left = remove_min(root->left);
 return balance(root);
}

bool contains(node root, int k) {
  if (!root) return false;
  if (root->key == k) return true;
  return k < root->key? contains(root->left, k) : contains(root->right, k);
}

node remove(node root, int k) {
//  if (!contains(root, k)) return nullptr;
  if (!root) return nullptr;
  if (k < root->key) {
    root->left = remove(root->left, k);
  } else if (k > root->key) {
    root->right = remove(root->right, k);
  } else {
    node l = root->left;
    node r = root->right;
    delete root;
    if (!r) return l;
    node min = get_min(r);
    min->right = remove_min(root->right);
    min->left = l;
    return balance(min);
  }
  return balance(root);
}


bool is_balanced(node root) {
  if (!root) return true;
  int bfactor = balance_factor(root);
//  cout << "balance factor is: " << bfactor << endl;
  if (bfactor != -1 && bfactor != 0 && bfactor != 1) return false;
  return true;
}

bool is_bst(node root) {
  

}

bool test() {
  node root = nullptr;
  set<int> nodes;
  for (int i = 1; i <= 100; i++) {
    if (i % 2 == 0) {
      nodes.insert(i);
      root = insert(root, i);
    }
  }

  for (int i = 1; i <= 100; i++) {
    bool in_the_tree = contains(root, i);
    bool in_the_set = (nodes.find(i) != nodes.end());
    if (in_the_tree != in_the_set) return false;
  }
  if (!is_balanced(root)) {
    cout << "The tree is imbalanced!" << endl;
    return false;
  } else {
    cout << "Insert test success!" << endl;
  }

  for (int i = 0; i < 100000; i++) {
    if (!contains(root, i)) {
      nodes.insert(i);
      root = insert(root, i);
    }
  }

  for (int i = 0; i < 100000; i++) {
    if (i % 3 == 0) {
      nodes.erase(i);
      root = remove(root, i);
    }
  }
  for (int i = 0; i < 100000; i++) {
    bool in_the_tree = contains(root, i);
    bool in_the_set = (nodes.find(i) != nodes.end());
    if (in_the_tree != in_the_set) {
      cout << "Remove fail!" << endl;
      return false;
    }
  }

  if (!is_balanced(root)) {
    cout << "The tree is imbalanced!" << endl;
    return false;
  } else {
    cout << "Remove test success!" << endl;
  }

  if (!is_bst(root)) {
    cout << "The tree is not a binary search tree!" << endl;
    return false;
  } else {
    cout << "Binary Search Tree check pass!" << endl;
  }

  return true;
}

int main() {
  if (!test()) 
    cout << "Fail!" << endl;
  else 
    cout << "All test cases passed!" << endl;
  return 0;
}




