#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>
#include <algorithm>


struct Node {
  int x; 
  int y;
  int g;
  int h;
};

class RoutePlanner {
  private:
    int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    void sort(std::vector<Node> *v);
    int heuristic(int x1, int x2, int y1, int y2);
    bool checkValidTile(int x, int y, std::map<std::pair<int, int>, bool> &map);
    void addTopOpen(Node current, std::vector<Node> &openList, std::map<std::pair<int, int>, bool> &map);
    void expandNeighbors(const Node &current, int goal[2], std::vector<Node> &openList, std::map<std::pair<int, int>, bool> &map);
  public:
    std::vector<std::pair<int, int>> search(std::map<std::pair<int, int>, bool> map, int start[2], int end[2]);
};

#endif