#ifndef _XPathFinding
#define _XPathFinding

#include <list>
#include <deque>
#include "Graph.hpp"
#include "GraphFunctor.hpp"


template <typename Type=GraphTypes::Default>
class XPathFinding
{
private:
  std::map<GraphTypes::node_id, GraphTypes::Cost> _distance_from_source;

  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > _best_predecessors;
  
  Graph<> _resultGraph;

  std::list<GraphTypes::Path> _foundPaths;

  void _reset();

  //Xdijkstra
  void _init(const Graph<Type> & graph,
	     const GraphFunctor::EdgeWeighter<Type> & getCost,
	     const GraphTypes::node_id & sourceNode,
	     std::list<GraphTypes::node_id> & candidates);

  std::list<GraphTypes::node_id> _allClosest(const std::list<GraphTypes::node_id> & candidates);

  void _add_edges(const Graph<Type> & graph,
		  const GraphFunctor::EdgeWeighter<Type> & getCost,
		  const std::list<GraphTypes::node_id> allClosest);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates,
		     const std::list<GraphTypes::node_id> & allClosest);

  void _update_tables(const Graph<Type> & graph,
		      const GraphFunctor::EdgeWeighter<Type> & getCost,
		      const std::list<GraphTypes::node_id> allClosest);

  //Xbellman: greedy
  void _init(const Graph<Type> & graph,
	     const GraphTypes::node_id & sourceNode,
	     std::list<GraphTypes::node_id> & candidates,
	     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  std::deque<GraphTypes::node_id> _coupe(const Graph<Type> & graph,
					 const std::list<GraphTypes::node_id> & candidates);

  void _update_tables(const Graph<Type> & graph,
		      const GraphFunctor::EdgeWeighter<Type> & getCost,
		      const std::deque<GraphTypes::node_id> & waiting_for_insertion,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _insert_waiting_nodes(const Graph<Type> & graph,
			     const GraphFunctor::EdgeWeighter<Type> & getCost,
			     std::deque<GraphTypes::node_id> & waiting_for_insertion);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates,
		     const std::deque<GraphTypes::node_id> & waiting_for_insertion);

  void _greedy_bellman(const Graph<Type> & graph,
		       const GraphFunctor::EdgeWeighter<Type> & getCost,
		       const GraphTypes::node_id & sourceNode,
		       const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  //Xbellman: dynamic
  void _init(const Graph<Type> & graph,
	     const GraphTypes::node_id & sourceNode,
	     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _update_tables(const Graph<Type> & graph,
		      const GraphFunctor::EdgeWeighter<Type> & getCost,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _build_result_graph(const Graph<Type> & graph,
			  const GraphFunctor::EdgeWeighter<Type> & getCost,
			  const GraphTypes::node_id & sourceNode);

  void _dynamic_bellman(const Graph<Type> & graph,
			const GraphFunctor::EdgeWeighter<Type> & getCost,
			const GraphTypes::node_id & sourceNode,
			const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  //particular paths
  std::list<GraphTypes::Path> _paths_to(const GraphTypes::node_id & target);
  

public:
  XPathFinding();

  void Xdijkstra(const Graph<Type> & graph,
		 const GraphFunctor::EdgeWeighter<Type> & getCost,
		 const GraphTypes::node_id & sourceNode
		 ) throw(GraphException::InvalidOperation);

  void Xdijkstra(const Graph<Type> & graph,
		 const GraphTypes::node_id & sourceNode
		 ) throw(GraphException::InvalidOperation);

  void dual_Xdijkstra(Graph<Type> & graph,
		      const GraphFunctor::EdgeWeighter<Type> & getCost,
		      const GraphTypes::node_id & targetNode
		      ) throw(GraphException::InvalidOperation);

  void dual_Xdijkstra(Graph<Type> & graph,
		      const GraphTypes::node_id & targetNode
		      ) throw(GraphException::InvalidOperation);

  void Xbellman(const Graph<Type> & graph,
		const GraphFunctor::EdgeWeighter<Type> & getCost,
		const GraphTypes::node_id & sourceNode,
		const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		) throw(GraphException::InvalidOperation);

  void Xbellman(const Graph<Type> & graph,
		const GraphTypes::node_id & sourceNode,
		const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		) throw(GraphException::InvalidOperation);

  void dual_Xbellman(Graph<Type> & graph,
		     const GraphFunctor::EdgeWeighter<Type> & getCost,
		     const GraphTypes::node_id & targetNode,
		     const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		     ) throw(GraphException::InvalidOperation);

  void dual_Xbellman(Graph<Type> & graph,
		     const GraphTypes::node_id & targetNode,
		     const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		     ) throw(GraphException::InvalidOperation);

  const std::list<GraphTypes::Path> & paths_to(const GraphTypes::node_id & target) throw(GraphException::InvalidOperation);

  const std::list<GraphTypes::Path> & Xbetween(const Graph<Type> & graph,
					       const GraphFunctor::EdgeWeighter<Type> & getCost,
					       const GraphTypes::node_id & source,
					       const GraphTypes::node_id & target,
					       const GraphTypes::Algorithms::SearchAlgorithm & algo=GraphTypes::Algorithms::DIJKSTRA
					       ) throw(GraphException::InvalidOperation);

  const std::list<GraphTypes::Path> & Xbetween(const Graph<Type> & graph,
					       const GraphTypes::node_id & source,
					       const GraphTypes::node_id & target,
					       const GraphTypes::Algorithms::SearchAlgorithm & algo=GraphTypes::Algorithms::DIJKSTRA
					       ) throw(GraphException::InvalidOperation);

  const std::map<GraphTypes::node_id, GraphTypes::Cost> & distances()const;

  const std::map<GraphTypes::node_id, GraphTypes::node_id> & predecessors()const;

  const Graph<Type> & resultGraph()const;

  const std::list<GraphTypes::Path> & foundPaths()const;

};

#include "XPathFinding.cpp"

#endif
