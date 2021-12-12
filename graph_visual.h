#pragma once
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "cs225/PNG.h"
#include "graph.h"
#include "streamer.h"

using namespace std;
using namespace cs225;

class GraphVisual {
 public:
  struct Node {
    Node() {
      radius = 0;
      center = make_pair(0, 0);
      streamer = Streamer();
      hue = 0;
    }
    Node(unsigned r, pair<int, int> c, Streamer s, unsigned h)
        : radius(r), center(c), streamer(s), hue(h) {
      velocity = make_pair(0.0, 0.0);
      nextCenter = c;
    };
    unsigned radius;  //--based on views, average for dataset is 193,470
    pair<int, int> center;
    Streamer streamer;
    unsigned hue;
    pair<double, double> velocity;
    pair<int, int> nextCenter;
  };
  GraphVisual();
  GraphVisual(Graph graph, unsigned width, unsigned height);
  void Arrange();
  // GraphVisual();
  // attractForce();
  // repelForce();

  void drawNode(const Node& n, PNG& png);
  vector<Node> getNodes();
  void drawEdge(const Node& n1, const Node& n2, PNG& png);
  void drawAllEdges(PNG& png);
  // checkNodeNodeOverlap(HSLAPixel::point center1, unsigned radius1,
  // HSLAPixel::point center2, unsigned radius2);
  // checkBorderNodeOverlap(HSLAPixel::point center, unsigned radius);

  // drawGraph(); //calls drawAllNodes() and drawAllEdges()
  // drawAllNodes();
  // drawAlEdges();
  // findEdgePointOnCircle(HSLAPixel::point center1, unsigned radius1,
  // HSLAPixel::point center2, unsigned radius2);

 private:
  float CalcAngle(pair<int, int> thisPoint, pair<int, int> otherPoint);
  pair<double, double> CalcComponents(double force, float angleDeg);
  double CalcDistance(const Node& n1, const Node& n2);
  pair<double, double> CalcRepulsionForce(const Node& n1, const Node& n2);
  pair<double, double> CalcAttractionForce(const Node& n1, const Node& n2);

  Graph g_;

  unsigned width_;
  unsigned height_;
  unsigned forceConst_;
  // unsigned kAverageViewers = 193470;
  double kAreaConst = 0.08;
  unsigned kMaxIterations = 100;
  double KDisplaceThreshold = 100;

  double kRepConst = 1000;
  double kAttractConst = 0.1;
  double kSpringDist = 100;
  double kDamping = 0.5;

  vector<pair<unsigned, unsigned>> kRadiusGrouping = {
      {0, 15},      {7500, 19},    {25000, 24},    {100000, 30},
      {250000, 35}, {1000000, 40}, {10000000, 50}, {178000000, 70}};

  vector<unsigned> kHueVector = {279, 246, 224, 186, 99, 44, 25, 0};

  // normalization constants
  // double kUpperBound = 20;
  // double kShift = 5;
  // double kMaxViews = 178500544;
  // double kMinViews = 5;

  // clipping constants
  // unsigned kClipValue = 540000;

  vector<Node> nodes_;
  vector<vector<unsigned>> adjMatrix_;

  // vars found experimentally:
  /*
    #iterations for simulation
    optimal dist between vertices constant k = C * sqrt(area/num vertices)
  */
};
