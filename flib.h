#include <queue>
#include <utility>
#include <climits>
#include <cmath>
#ifndef INF
   #define INF INT_MAX
#endif

namespace flib{
   
   class Orientation{
      public:
         Orientation(){
            this->lon = 0.0;
            this->lat = 0.0;
         }
         Orientation(float &lon, float &lat){
            this->lon = lon;
            this->lat = lat;
         }
         void set_zero(){
            this->lon = 0.0;
            this->lat = 0.0;
         }
         void set(float &lon, float &lat){
            this->lon = lon;
            this->lat = lat;
         }
         float lon;
         float lat;
      }; 
   
   
   class Link{
         Orientation self_orientation;
         unsigned int id;
      public:
         Link(){
            this->self_orientation.set_zero();
            this->id = 0;
         }
         Link(Orientation &self_orientation, unsigned int &id){
            this->self_orientation = self_orientation;
            this->id = id;
         }
         Link(float &lon, float &lat, unsigned int id){
            this->self_orientation.set(lon, lat);
            this->id = id;
         }
         Orientation& get_orient(){
            return self_orientation;
         }
         unsigned int get_id(){
            return id;
         }
      };
   
   
   class Node{
         std::vector<Link> links;
         Orientation self_orientation;
         bool is_visited;
         unsigned long mark;
      public:
         Node(){
            this->is_visited = false;
            this->mark = 0;
            this->self_orientation.set_zero();
         }
         Node(float &lon, float &lat){
            this->self_orientation.set(lon, lat);
            this->mark = INF;
            this->is_visited = false;
         }
         void toggle(){
            this->is_visited = true;
         }
         void set_mark(unsigned long &mark){
            this->mark = mark;
         }
         void push(Orientation self_orientation, unsigned int lid, Orientation link_orientation){
            this->self_orientation = self_orientation;
            links.push_back(Link(link_orientation, lid));
         }
         unsigned long &get_mark(){
            return this->mark;
         }
         int lsize(){
            return links.size();
         }
         Orientation& get_orient(){
            return self_orientation;
         }
         Link& get_link(unsigned int i){
            return links[i];
         }
   }; 

   
   
   class PriorityQueue{ 
         std::priority_queue<std::pair< int, int >, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > elements;
      public:
         bool empty(){
            return elements.empty();
         }
         void put(int element, int priority){
            this->elements.emplace(priority, element);
         }
         int get(){
            int item = elements.top().second;
            elements.pop();
            return item;
         }
      };
   
   
   long ManhattanHeuristic(Orientation &a, Orientation &b){
         return std::abs(a.lat - b.lat) + std::abs(a.lon - b.lon);
      }
      long ChebishevHeuristic(Orientation &a, Orientation &b){
         return std::max(std::abs(a.lon - b.lon), std::abs(a.lat - b.lat));
      }
      long EuclidHeuristic(Orientation &a, Orientation &b){
         return std::sqrt(std::pow((a.lon - b.lon), 2.0) + std::pow((a.lat - b.lat), 2.0));
      }
   
}

