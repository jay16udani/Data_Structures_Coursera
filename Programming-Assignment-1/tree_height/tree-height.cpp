#include <algorithm>
#include <iostream>
#include <vector>

class Node;
//int current_level; //for queue

class Node {
public:
    std::vector<Node *> children;

    void addchild(Node *child)
	{
		children.push_back(child);
	}	
	
};

 int tree_traversal(Node *nextnode, int n) //for queue, make return type void
 {
	 
	 std::vector <Node *> queue;
	 /***********implementation using queue (bit slow)****************/
	 /*int level_number=1;
	 current_level=0;
	 
	 queue.push_back(nextnode);
	 int queue_pointer =0;
	 int nodes_covered =0;
	 
	 //try to implement of bfs in O(n)////
	 while(nodes_covered!=n)
	 {
		 if(queue[queue_pointer]->children.size()!=0)
			queue.insert(queue.end(),queue[queue_pointer]->children.begin(),queue[queue_pointer]->children.end());
		 
		 nodes_covered++;
		 queue_pointer++;
	 }
	 
	 
	 while(1)
	 {
		 current_level++;
		 int prev_level = level_number;
		 level_number = 0;
		 for(int i=0;i < prev_level;i++)
		 {
			 level_number+=queue[0]->children.size();
			 
			 queue.erase(queue.begin());
		 }
		 
		 if(level_number==0)		
			break;
	 }*/
	 
	 
	 /****************implementation using recursion**********************/
	 if(nextnode->children.size()==0)
		 return 1;
	 
	 int maxheight = 0;
	 for(int i=0;i<nextnode->children.size();i++)
	 {
		 int depth = tree_traversal(nextnode->children[i],n);
		 if(depth > maxheight)
			 maxheight = depth;
	 }
	 
	 return (maxheight+1);
 }
	 

int main()
{
	int n;
	std::cin >> n;
	int root;
	std::vector<Node> nodes;
	nodes.resize(n);

	for (int child_index = 0; child_index < n; child_index++)
	{
		int parent_index;
		std::cin >> parent_index;
		if(parent_index == -1)
			root = child_index;			
		else
			nodes[parent_index].addchild(&nodes[child_index]);
	}

	if(n==1)
	{
	  std::cout << 1 <<std::endl;
	  return 0;
	}
	else
	{
		int answer = tree_traversal(&nodes[root],n); //for recursion
		//tree_traversal(&nodes[root],n); //for queue
		
		//std::cout << current_level << std::endl; //uncomment this for queue
		std::cout << answer << std::endl;	//for recursion
		return 0;
	}
}

////////////////not my idea...though nice solution//////////////////////////////
/*
#include <iostream>
#include <vector>
#include <algorithm>

class TreeHeight {
  int n;             
  std::vector<int> parent;

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> parent[i];
  }
  
  int compute_height() {
	int maxHeight = 0;
	std::vector<int> heights;
	for (int i=0; i<parent.size(); i++) 
		heights.push_back(0);
	for (int vertex = 0; vertex < n; vertex++) {
		if (heights[vertex] != 0)
			continue;
		int height = 0;
		for (int i = vertex; i != -1; i = parent[i]) {
			if (heights[i] != 0) {
				height += heights[i];   
				break;
			}
			height++;
		}
		maxHeight = std::max(maxHeight, height);
		for (int i = vertex; i != -1; i = parent[i]) {
			if (heights[i] != 0)
				break;
			heights[i] = height--;
		}
	}
	return maxHeight;
  }

  int old_compute_height() {
    int maxHeight = 0;
    for (int vertex = 0; vertex < n; vertex++) {
      int height = 0;
      for (int i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
*/