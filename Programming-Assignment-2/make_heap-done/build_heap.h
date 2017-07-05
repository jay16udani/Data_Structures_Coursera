#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

void print(vector<int> v)
{
  for(int i = 0; i < v.size(); i++) std::cout << v[i] << " ";
  std::cout << std::endl;
}


class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
	
	//print(data_);
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  
  int leftchild(int i)
  {
	  return (2*i) + 1;
  }
  
  int rightchild(int i)
  {
	  return (2*i)+2;
  }
  
  void siftdown(int i)
  {
	  int minindex = i;
	  int left = leftchild(i);
	  
	  if(left < static_cast<int>(data_.size()) && data_[left]<data_[minindex])
		  minindex = left;
	  
	  int right = rightchild(i);
	  
	  if(right <static_cast<int>(data_.size()) && data_[right]<data_[minindex])
		  minindex = right;
	  
	  if(i!=minindex)
	  {
		  swap(data_[i], data_[minindex]);
		  swaps_.push_back(make_pair(i, minindex));
		  siftdown(minindex);
	  }
  }

  void GenerateSwaps() {
    swaps_.clear();
    /*/ The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i){
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
	}*/
	
	//faster implementation
	for(int i=(static_cast<int>(data_.size()))/2; i>=0; i--)
		siftdown(i);

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
