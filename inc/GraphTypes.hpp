#ifndef GRAPHTYPES
#define GRAPHTYPES

#include <list>

class GraphTypes{
public:

  typedef unsigned long node_id;

  typedef float Cost;

  typedef std::list<node_id> Path;

  enum EdgeType{DIRECTED, UNDIRECTED};

  enum EdgeState{WEIGHTED, UNWEIGHTED};

  enum What{NODES, CONTENTS};

  enum NodeType{CONTAINER, NOCONTENT};

  enum Default{DEFAULT};

  struct Exceptions
  {
    enum Verbosity{BRIEVE, VERBOSE};
  };

  struct Iterator
  {
    enum Type{SIMPLE, DOUBLE};
  };

  struct Algorithms
  {
    typedef unsigned int Color;

    enum SearchAlgorithm{DIJKSTRA, BELLMAN};

    enum AlgorithmicClass{GREEDY, DYNAMIC};

    enum ComputingValidity{UNDEFINED, VALID, INVALID};

    enum OptimizationType{MAXIMIZE, MINIMIZE};

    static const float POSITIVE_INFINITY;
    static const float NEGATIVE_INFINITY;
  };

};

#endif
