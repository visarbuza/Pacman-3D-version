#include "route_planner.h"


void RoutePlanner::sort(std::vector<Node> *v) {
  std::sort(v->begin(), v->end(), [](const Node first, const Node second){
    return first > second;
  });
}

int RoutePlanner::heuristic(int x1, int y1, int x2, int y2) {
  return std::abs(x2 - x1) + std::abs(y2 - y1);
}

bool RoutePlanner::checkValidTile(int x, int y, std::map<std::pair<int, int>, bool> &map) {
  std::pair<int, int> temp(x, y);
  if (map.find(temp) != map.end()) {
    return !map[temp];
  }
  return false;
}

void RoutePlanner::addTopOpen(Node &current, std::vector<Node> &openList, std::map<std::pair<int, int>, bool> &map) {
  openList.push_back(current);
  std::pair<int, int> temp(current.x, current.y);
  map.erase(temp);
}

void RoutePlanner::expandNeighbors(Node &current, int goal[2], std::vector<Node> &openList, std::map<std::pair<int, int>, bool> &map) {
  int x = current.x;
  int y = current.y;
  int g = current.g;

  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    if (checkValidTile(x2, y2, map)) {
      int g2 = g + 1;
      int h2 = heuristic(x2, y2, goal[0], goal[1]);
      Node node(x2, y2);
      node.g = g2;
      node.h = h2;
      node.f = g2 + h2;
      node.parent = &current;
      addTopOpen(node, openList, map);
    }
  }
}

std::vector<std::pair<int, int>> RoutePlanner::search(std::map<std::pair<int, int>, bool> map, int start[2], int end[2]) {
  std::vector<Node> open {};
  std::vector<std::pair<int, int>> result{};

  Node node(start[0], start[1]);
  node.g = 0;
  node.h = heuristic(start[0], start[1], end[0], end[1]);
  node.f = node.g + node.h;
  addTopOpen(node, open, map);

  while (open.size() > 0) {
    sort(&open);
    auto current = open.back();
    open.pop_back();
    std::pair<int, int> temp(current.x, current.y);
    map.erase(temp);
    result.push_back(temp);

    if (current.x == end[0] && current.y == end[1]) {
      return result;
    }

    expandNeighbors(current, end, open, map);
  }
  return result;
}