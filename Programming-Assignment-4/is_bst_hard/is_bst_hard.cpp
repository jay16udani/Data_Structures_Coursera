#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(vector<Node>& tree, int index, vector <int> &result)
  {
	  
	  if(tree[index].left == -1 && tree[index].right == -1)
	  {
		  result.push_back(tree[index].key);
		  return;
	  }
	  
	  if(tree[index].left != -1 && tree[index].key == tree[tree[index].left].key)
	  {
		  result.clear();
		  return;
	  }
	  
	  if((tree[index].left != -1) && (tree[index].key != tree[tree[index].left].key))
		in_order_traversal(tree, tree[index].left, result);
	
	  result.push_back(tree[index].key);
	  
	  if(tree[index].right != -1)
		in_order_traversal(tree, tree[index].right, result);
  }

  
bool merge_vector(vector<int> &left, vector<int> &right, vector<int> &a_b)
{
   a_b.clear();
   while ((int)(left.size()) > 0 || (int)(right.size()) > 0) {
      if ((int)(left.size()) > 0 && (int)(right.size()) > 0) {
         if ((left.front()) > (right.front())) {
            return false;
			/*a_b.push_back((left.front()));
            left.erase(left.begin());*/
         } 
   else {
			a_b.push_back((right.front()));
            right.erase(right.begin());
        }
      }  else if ((int)(left.size()) > 0) {
            for (int i = 0; i < (int)(left.size()); i++){
               a_b.push_back(left.at(i));
			}
            break;
      }  else if ((int)(right.size()) > 0) {
            for (int i = 0; i < (int)(right.size()); i++){
               a_b.push_back(right.at(i));
			}
            break;
      }
   }
   return true;
}

bool is_sorted(vector<int> &a_b)
{
   if (a_b.size() <= 1)
      return true;
 
   vector<int> left, right;
   
   int middle = ((int)a_b.size()+ 1) / 2;
 
   for (int i = 0; i < middle; i++) {
      left.push_back(a_b.at(i));
   }

   for (int i = middle; i < (int)a_b.size(); i++) {
      right.push_back(a_b.at(i));
   }
 
   bool temp1 = is_sorted(left);
   bool temp2 = is_sorted(right);
   bool temp3 = merge_vector(left,right,a_b);
   
   if(!temp1 || !temp2 || !temp3)
	   return false;
   else
	   return true;
}


bool IsBinarySearchTree(vector<Node>& tree, int index)
{
	if(tree.size() == 0)
		return true;
	
	vector <int> result;
	
	in_order_traversal(tree, index, result);
	if(result.size() == 0)
		return false;
	else if(is_sorted(result))
		return true;
	else
		return false;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree,0)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
