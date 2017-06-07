#include <iostream>
#include <stack>
#include <string>

typedef struct
{
	char type;
	int position;
}mystack;

int main() {
    std::string text;
    getline(std::cin, text);
	bool c=true;

    std::stack <mystack> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position)
	{
        if((int)text.length()==1)
		{
			c=false;
			std::cout << "1" <<std::endl;
			break;
		}
		char next = text[position];

        if (next == '(' || next == '[' || next == '{')
		{
			mystack temp;
			temp.type=next;
			temp.position=position;
			opening_brackets_stack.push(temp);
        }

        if (next == ')' || next == ']' || next == '}')
		{
            if((next == ')' || next == ']' || next == '}') && opening_brackets_stack.empty())
			{
				std::cout << position+1 <<std::endl;
				c=false;
				break;
			}
			else if(next==')' && opening_brackets_stack.top().type!='(')
			{
				std::cout << position+1 << std::endl;
				c=false;
				break;
			}
			else if(next==')' && opening_brackets_stack.top().type=='(')
				opening_brackets_stack.pop();
			
			else if(next==']' && opening_brackets_stack.top().type!='[')
			{
				std::cout << position+1 << std::endl;
				c=false;
				break;
			}
			
			else if(next==']' && opening_brackets_stack.top().type=='[')
				opening_brackets_stack.pop();
				
			else if(next=='}' && opening_brackets_stack.top().type!='{')
			{
				std::cout << position+1 << std::endl;
				c=false;
				break;
			}
			
			else if(next=='}' && opening_brackets_stack.top().type=='{')
				opening_brackets_stack.pop();
        }
    }
	
	if(c==true && opening_brackets_stack.empty())
		std::cout << "Success" << std::endl;
	
	else if(c==true && (!(opening_brackets_stack.empty())))
		std::cout << (opening_brackets_stack.top().position)+1 << std::endl;
	
    return 0;
}
