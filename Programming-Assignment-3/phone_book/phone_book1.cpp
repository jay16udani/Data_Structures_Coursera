#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries)
{
	vector<string> result;
    vector <Query *> contacts(10000000);
	
	for(int i=0;i<10000000;i++)
		contacts[i] = NULL;
	
	for(int i=0;i<(int)queries.size();i++)
	{
		if(queries[i].type == "add")
		{
			if(contacts[queries[i].number]!=NULL)
			{
				contacts[queries[i].number]->number = queries[i].number;
				contacts[queries[i].number]->name = queries[i].name;
			}
			else
			{
				Query *new_contact = new Query;
				contacts[queries[i].number] = new_contact;
				contacts[queries[i].number]->number = queries[i].number;
				contacts[queries[i].number]->name = queries[i].name;
			}
		}
		else if(queries[i].type == "find")
		{
			string found = "not found";
			if(contacts[queries[i].number] == NULL)
				result.push_back(found);
			else
			{
				result.push_back((contacts[queries[i].number])->name);
			}
		}
		else
		{
			if(contacts[queries[i].number] != NULL)
				contacts[queries[i].number] = NULL;
		}
	}
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
