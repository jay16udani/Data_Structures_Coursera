#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
	Query *nextquery;
};

class QueryProcessor {
    int bucket_count;
	vector <Query **> hash_table;
	vector <Query *> pointers_2_query;
	
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count)
	{
		for(int i=0;i<bucket_count;i++)
		{
			pointers_2_query.push_back(NULL);
			hash_table.push_back(&(pointers_2_query[i]));
		}
	}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void processQuery(const Query& query) {
		if (query.type == "check")
		{	
            Query *temp = NULL;
			if(pointers_2_query[query.ind] != NULL)
			{
				temp = (pointers_2_query[query.ind]); //creating a pointer iterator
				while(temp!=NULL)
				{
					std::cout << (temp)->s << " ";
					temp = ((*temp).nextquery);
				}
			}
			std::cout << "\n";

		}
		else if (query.type == "find")
		{
			int list_number = hash_func(query.s);
			bool was_found = false;
			Query *temp = NULL;
			if(pointers_2_query[list_number] != NULL)
			{
				temp = pointers_2_query[list_number]; //creating a pointer iterator
				while(temp!=NULL)
				{
					if((temp)->s == query.s)
					{
						was_found = true;
						break;
					}
					temp = (*temp).nextquery;
				}
			}
			std::cout << (was_found ? "yes\n" : "no\n");
		}
		else if (query.type == "add")
		{
			int list_number = hash_func(query.s);
			Query *temp = NULL;
			if(pointers_2_query[list_number] != NULL)
			{
				temp = pointers_2_query[list_number];
			}
			
			if(pointers_2_query[list_number] == NULL)
			{
				pointers_2_query[list_number] = new Query;
				pointers_2_query[list_number]->nextquery = NULL;
				pointers_2_query[list_number]->s = query.s;
			}
			else
			{
				bool was_found = false;
				Query *temp_new = pointers_2_query[list_number]; //creating a pointer iterator
				
				while(temp_new!=NULL)
				{
					if((temp_new)->s == query.s)
					{
						was_found = true;
						break;
					}
					temp_new = (*temp_new).nextquery;
				}
				if(was_found == false)
				{
					pointers_2_query[list_number] = new Query;
					pointers_2_query[list_number]->s = query.s;
					pointers_2_query[list_number]->nextquery = temp;
				}
			}
		}
				
		else if (query.type == "del")
		{
			int list_number = hash_func(query.s);
			Query *temp = NULL;
			if(pointers_2_query[list_number] != NULL)
			{
				temp = pointers_2_query[list_number];
				int j=0;
				while(temp!=NULL)
				{
					if(((*temp).s == query.s) && ((*temp).nextquery==NULL) && (j!=0)) //last query in the list: simply delete it
					{
						Query *del_pointer = pointers_2_query[list_number];
						for(int i=0;i<j-1;i++)
							del_pointer = (*del_pointer).nextquery;
						(*del_pointer).nextquery = NULL;
						delete (temp);
					}
					else if(((*temp).s == query.s) && ((*temp).nextquery==NULL) && (j==0)) //first query in the list
					{
						delete (temp);
						pointers_2_query[list_number] = NULL;
					}
					else if(((*temp).s == query.s) && ((*temp).nextquery!=NULL) && (j!=0)) //query somewhere in the middle
					{
						Query *del_pointer1 = pointers_2_query[list_number];
						Query *del_pointer2 = pointers_2_query[list_number];
						for(int i=0;i<j-1;i++)
							del_pointer1 = (*del_pointer1).nextquery;
						for(int i=0;i<j+1;i++)
							del_pointer2 = (*del_pointer2).nextquery;
						
						(*del_pointer1).nextquery = del_pointer2;
						delete (temp);
					}
					 //delete the first query in the list when there are more than one queries in that list
					else if(((*temp).s == query.s) && ((*temp).nextquery!=NULL) && (j==0))
					{
						Query *del_pointer = (pointers_2_query[list_number])->nextquery;
						pointers_2_query[list_number] = del_pointer;
						delete(temp);
					}
					temp = (*temp).nextquery;
					j++;
				}
			}
		}
	}

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
