#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Packets
{
public:
	Packets()
	{
		this->drop =false ;
	}

	int arrival_time;
	int processing_time;
	bool drop;
	int position;
};

void start_process(int number_packets, int buffer_size, Packets* pointer)
{
	queue <Packets *> buffer; // buffer containing the addresses of the packets
	
	int processing_times[number_packets]; //array containing the answers
	int prev=0; //variable created for deciding the start of processing time for next packet
	
	while(!((buffer.empty()) && (pointer->position==(number_packets+1)))) //continue till buffer is not empty and we reach the dummy packet
	{
		int temp2 = (int)buffer.size();
		
		//pushing packets into the queue until the queue is full
		for(int i=0;i<(buffer_size-temp2);i++)	//continue to put packets until according to the empty space
		{
			if(pointer->position==number_packets+1)	//if we reach the dummy packet, we do not move forward
				break;
			
			else if(pointer->drop==true)	//if the current packet has been selected to drop
			{
				i--;											//since the packet was dropped, we continue to fill the buffer
				processing_times[(pointer->position)-1] = -1;
				int temp_arrival_time = pointer->arrival_time;
				int temp_processing_time = pointer->processing_time;

				pointer++;
	
				if((pointer->arrival_time == temp_arrival_time) || (pointer->arrival_time < prev))	//if arrival time of dropped packet is same as the new packet, then drop this new packet too
					pointer->drop = true;															//also drop it we the new packets arrival time has already elapsed in the answer array
			}
			
			else
			{
				buffer.push(pointer);
				
				if(pointer->processing_time==0)		//if processing time is 0, then we can take one more packet
					i--;
				
				pointer++;
				
				if((int)buffer.size()==buffer_size)
				{
					break;
				}
			}
		}
		
		//compute processing times
		if(!buffer.empty())
		{
			Packets* temp = buffer.front();
			buffer.pop();
			
			if(temp->arrival_time > prev)
				prev = temp->arrival_time;
			
			processing_times[(temp->position)-1] = prev;
			prev += temp->processing_time;
			
			if(pointer->arrival_time < prev)
				pointer->drop = true;
		}
	}
	
	for(int i=0;i<number_packets;i++)
		cout << processing_times[i] << endl;
}

int main()
{
	int buffer_size;
	int number_packets;
	cin >> buffer_size >> number_packets;
	
	vector <Packets> packets;
	packets.resize(number_packets+1); //extra space for dummy packet at end to indicate end of input packets
	
	Packets* first = &packets[0];
	
	for(int i=0;i<number_packets;i++)
	{
		cin >> packets[i].arrival_time >> packets[i].processing_time;
		packets[i].position = i+1;
	}
	
	//setting the value of the dummy packet
	packets[number_packets].arrival_time = 0;
	packets[number_packets].processing_time = 0;
	packets[number_packets].position = number_packets +1;
	
	//start
	start_process(number_packets,buffer_size,first);
	
	return 0;
}