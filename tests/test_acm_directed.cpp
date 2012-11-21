#include <iostream>
#include "Graph.hpp"
#include "Acm.hpp"
#include "Exporter.hpp"

int main(){
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> min_tree( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT );
  Acm<> acm;
  Exporter<> exporte(GraphTypes::NODES);

  /*
    Graphe de l'annale: contrôle continu Novembre 2008
    C2 vers C1, C7 vers C1, C8 vers C1, C6 vers C2, C2 vers C3, C4 vers C3, C5 vers C4, C3 vers C5, C1 vers C6, C6 vers C7 et C7 vers C8

    coût(s2,s1)=1, coût(s7,s1)=0, coût(s8,s1)=3, coût(s6,s2)=9, coût(s2,s3)=4, coût(s4,s3)=5, coût(s5,s4)=7,coût(s3,s5)=6, coût(s1,s6) = 2, coût(s6,s7)=10, coût(s7,s8) = 11
  */
  graph.add_edge(2,1, 1);
  graph.add_edge(7,1, 0);
  graph.add_edge(8,1, 3);
  graph.add_edge(6,2, 9);
  graph.add_edge(2,3, 4);
  graph.add_edge(4,3, 5);
  graph.add_edge(5,4, 7);
  graph.add_edge(3,5, 6);
  graph.add_edge(1,6, 2);
  graph.add_edge(6,7, 10);
  graph.add_edge(7,8, 11);

  try{
    std::cout << exporte.toGraphviz(graph) << std::endl << std::endl;

    min_tree = acm.prim(graph);
    std::cout << "Prim:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

    min_tree = acm.kruskal(graph);
    std::cout << "Kruskal:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;
  }
  catch(std::invalid_argument & iv){
    std::cout << "Caught invalid_argument exception:" << std::endl << iv.what() << std::endl;
  }
  catch(std::logic_error & le){
    std::cout << "Caught logic_error exception:" << std::endl << le.what() << std::endl;
  }
  catch(std::exception & e){
    std::cout << "Caught exception:" << std::endl << e.what() << std::endl;
  }
  catch(...){
    std::cout << "Caught unexpected exception." << std::endl;
  }

  return 0;
}