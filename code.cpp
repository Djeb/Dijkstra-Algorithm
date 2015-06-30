#include "flib.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace flib;
using namespace std;

class Dij{
	vector<Node> web;
	PriorityQueue frontier;
	vector<unsigned int> came_from;
	vector<unsigned int> cost_far;
	unsigned int current;
	ifstream in;
public:
	int cost(Orientation &a, Orientation &b){
		return std::sqrt(std::pow((b.lon - a.lon), 2.0) + std::pow((b.lat - a.lat), 2.0));
	}
	bool start(unsigned int start, unsigned int goal){
		frontier.put(start, 0);
		came_from[start] = start;
		cost_far[start] = 0;
		while(!frontier.empty()){
			current = frontier.get();
			if (current  == goal)
				break;
			for (int i = 0; i < web[current].lsize(); ++i){
				int new_cost = cost_far[current] +  cost(web[current].get_orient(), web[current].get_link(i).get_orient());
				unsigned int next = web[current].get_link(i).get_id();
				if (new_cost < cost_far[next]){
					cost_far[next] = new_cost;
					frontier.put(next, new_cost);
					came_from[next] = current;
				}
			}
		}
	}
	float get_length(float lon1, float lon2, float lat1, float lat2){
		return std::sqrt((lon2 - lon1)*(lon2 - lon1) + (lat2 - lat1)*(lat2 - lat1));
	}
	bool read_raw(char* filename){
                in.open(filename);
                if(!in)
                	return false;
           
               	while(!in.eof()){
					int a, b;
					float lon1, lon2, lat1, lat2;
					in >> a >> b >> lon1 >> lat1 >> lon2 >> lat2;
					float l = get_length(lon1, lon2, lat1, lat2);
					if(web.size() <= (a > b? a:b)){
						web.resize(web.size() + (a > b? a:b) + 1);
					}
                    web[a].push(Orientation(lon1, lat1), b, Orientation(lon2, lat2));
                	web[b].push(Orientation(lon2, lat2), a, Orientation(lon1, lat1));
                }
                came_from.resize(web.size());
                cost_far.resize(web.size(), INF);
                in.close();
                return true; 
    }
	void print(int a, int b){
		cout << a << " " << b;
		for(int i = 0; i < came_from.size(); ++i)
			if(came_from[i] > 0){
				cout << endl;
				cout << i << ' ' << came_from[i];
			}
	}
};

int main(int argc, char** argv){
	if (argc < 4){
		cout << "need 4 args. Use - <filename> <start node> <goal node>" << endl;
		return 1;
	}
	Dij algo;
	if(!algo.read_raw(argv[1])){
	 	cout << "file " << argv[1] << " not found or can't be open!" << endl;
        return 1;
    }
   	algo.start(stoi(argv[2]), stoi(argv[3]));
   	algo.print(stoi(argv[2]), stoi(argv[3]));

	return 0;
}