#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }
  
  void in_order_traversal(int index)
  {
	  if(left[index] == -1 && right[index] == -1)
	  {
		  cout << key[index] << " ";		  
		  return;
	  }
	  if(left[index]!=-1)
		in_order_traversal(left[index]);
	
	  cout << key[index] << " ";
	  
	  if(right[index]!=-1)
		in_order_traversal(right[index]);
  }
  
  void pre_order_traversal(int index)
  {
	  cout << key[index] << " ";
	  if(left[index] == -1 && right[index] == -1)
		  return;
	  if(left[index] != -1)
		pre_order_traversal(left[index]);
	
	  if(right[index] != -1)
		pre_order_traversal(right[index]);
  }  
  
  void post_order_traversal(int index)
  {
	  if(left[index] == -1 && right[index] == -1)
	  {
		  cout << key[index] << " ";
		  return;
	  }
	  
	  if(left[index] != -1)
		  post_order_traversal(left[index]);
	  
	  if(right[index] != -1)
		  post_order_traversal(right[index]);
	  
	  cout << key[index] << " ";
  }


  void in_order() {
	in_order_traversal(0);
	cout << "\n";
  }

  void pre_order() {
	  pre_order_traversal(0);
	  cout << "\n";
  }

  void post_order() {
	  post_order_traversal(0);
	  cout << "\n";
  }
};

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order();
  t.pre_order();
  t.post_order();
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

