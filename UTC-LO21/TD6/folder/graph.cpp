#include<list>
#include<vector>
#include<iostream>
#include<string>
#include "graph.h"
using namespace std;

Graph::Graph(const string& n, size_t nb): adj(nb), name(n) {
    // vector<list<unsigned int>> adj = v(vector<list<unsigned int>> s'initialize toute seule a une liste vide
};

const string& getName() const { return name;};
size_t getNbVertices() const { return adj.size(); };
size_t getNbEdges() const { 
    int cunt;
    /*
    for (size_t i = 0; i < adj.size(); i++) {
        cunt += adj[i].size();
    }
    */
   for (auto it = adj.begin(); it != adj.end(); ++it) {
    cunt += it->size(); // ou (*it).size();
   }
   // for (atuo& l : adj) nbedges += l.size(); // : est <=> l'operateur "in"
};
void addEdge(unsigned int i, unsigned int j) {
    if (i >= adj.size()) {throw GraphException("i is too bigh. OuttaGraphException")}
    if (j >= adj.size()) {throw GraphException("j is too bigh. OuttaGraphException")}
    adj[i].push_back(j);
};
void removeEdge(unsigned int i, unsigned int j) {
    if (i >= adj.size() || j >= adj.size()) throw GraphException("sommet inexistant");
    auto it = find(adj[i].begin(), adj[i].end(), j);
    if (it == adj[i].end()) throw GraphException("elimination d'un arc inexistant");
    adj[i].erase(it);
};
const list<unsigned int>& getSuccessors(unsigned int i) const {

};
const list<unsigned int> getPredecessors(unsigned int i) const {
    list<unsigned int> res;
    for (size_t j = 0; j < adj.size(); j++)
        if (count(adj[j].begin(), adj[j].end(), i) != 0)
            res.push_back(j);
    return res;
};

ostream& operator<<(ostream& f, const Graph& G) {
    f << "Graph " << G.getName() << "\n";
    for (size_t i = 0; i < G.getNbVerticies(); i++) {
        f << i << ":";
        for (auto& j : G.getSuccessors(i)) f << j << ";";
        f << "\n";
    }
    return f;
};