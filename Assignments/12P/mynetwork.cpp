/* CS515 Assignment 12
File: mynetwork.cpp
Name: Biao Zhang
Section: 1
Date: 12/08/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
#include "DisjointSet.h"
#include "PQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
using namespace std;

struct Edge
{
    string node_1, node_2;
    int _weight;

    Edge(){}
    Edge(string n_1, string n_2, int w) : node_1(n_1), node_2(n_2), _weight(w){}

    bool operator >=(const Edge& E) {return _weight >= E._weight;}
    bool operator <(const Edge& E) {return _weight < E._weight;}
};



int main(int argc, char * argv[]){
    //The number of arguments are incorrect.
    if(argc != 2) {
        cerr << "Wrong number of arguments" << endl;
        exit(1);
    }

    //Open file and read data
    ifstream f(argv[1]);
    if(f.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    set<string> vertices;
    set<string>::iterator vertices_it;
    stack<string> starters;
    PQueue<Edge,10000> min_Edges;
    string str, node_1, node_2;
    int _weight;
    bool is_start = true;
    if(f.is_open()) {
        while (getline(f, str)){
            stringstream row(str);
            row >> node_1 >> node_2 >> _weight;
            vertices.insert(node_1);
            vertices.insert(node_2);
            if (is_start) {
                starters.push(node_1);
                is_start = false;
            }
            Edge e(node_1, node_2, _weight);
            min_Edges.insert(e);
        }
        f.close();
    }

    //Kruskal MST
    map<string, list<string> > F;
    map<string, list<string> >::iterator F_it;
    DisjointSet<string> s;
    map<string, bool> is_visited;
    map<string, bool>::iterator visited_it;
    for (vertices_it = vertices.begin(); vertices_it != vertices.end(); vertices_it++)
        s.createSet(*vertices_it);
    while (!min_Edges.isEmpty()){
        Edge min_e = min_Edges.findMin();
        min_Edges.deleteMin();
        if (s.findSet(min_e.node_1) != s.findSet(min_e.node_2)) {
            F[min_e.node_1].push_back(min_e.node_2);
            F[min_e.node_2].push_back(min_e.node_1);
            visited_it = is_visited.find(min_e.node_1);
            if (visited_it == is_visited.end())
                is_visited[min_e.node_1] = false;
            visited_it = is_visited.find(min_e.node_2);
            if (visited_it == is_visited.end())
                is_visited[min_e.node_2] = false;
            s.unionSets(s.findSet(min_e.node_1), s.findSet(min_e.node_2));
        }
    }

    string _command, end_node, v;
    //bool is_exist;
    map<string, string> parent;
    queue<string> tmp;
    stack<string> print_result;
    string starter = starters.top();
    cout << '<' << starter << "># ";
    while (cin >> _command) {
        if (_command.compare("ping") == 0) {
            cin >> end_node;
            // The following refers to codes in connectChecker.cpp in 10L
            if (starter.compare(end_node) == 0) {
                // When the starter is identical to the end
                // skip to the next query.
                cout << " From: " << starter << endl;
            } else {
                vertices_it = vertices.find(end_node);
                if (vertices_it == vertices.end()) {
                    // If it is a non-exiting node
                    cout << "Cannot find node. Available nodes are:" << endl;
                    for (vertices_it = vertices.begin(); vertices_it != vertices.end(); vertices_it++)
                        cout << *vertices_it << endl;
                } else {
                    // If it is an exiting node
                    is_visited[starter] = true;
                    tmp.push(starter);
                    while (!tmp.empty() && tmp.front() != end_node) {
                        v = tmp.front();
                        tmp.pop();
                        F_it = F.find(v);
                        if (F_it != F.end()) {
                            for (auto const& a : F[v]) {
                                if (!is_visited[a]) {
                                    is_visited[a] = true;
                                    tmp.push(a);
                                    parent[a] = v;
                                }
                            }
                        }
                    }

                    /*if (!tmp.empty() && tmp.front() == end_node)
                        is_exist = true;
                    else
                        is_exist = false;*/

                    //if (is_exist) {
                        v = end_node;
                        while (v.compare(starter) != 0) {
                            print_result.push(v);
                            v = parent[v];
                        }
                        print_result.push(v);

                        cout << " From: " << starter << endl;
                        print_result.pop();
                        while (print_result.top().compare(end_node) != 0) {
                            cout << "   To: " << print_result.top() << endl;
                            print_result.pop();
                        }
                        cout << "   To: " << print_result.top() << endl;
                        print_result.pop();
                    /*} else {
                        cout << "Cannot find node. Available nodes are:" << endl;
                        for (vertices_it = vertices.begin(); vertices_it != vertices.end(); vertices_it++)
                            cout << *vertices_it << endl;
                    }*/

                    //Clean all containers for later use.
                    parent.clear();
                    for( auto it = is_visited.begin(); it != is_visited.end(); it++)
                    {
                        if (it->second)
                            it->second = false;
                    }
                    while (!tmp.empty())
                        tmp.pop();
                }
            }
        } else if (_command.compare("ssh") == 0) {
            cin >> end_node;
            vertices_it = vertices.find(end_node);
            if (vertices_it == vertices.end()) {
                cout << "Cannot find node. Available nodes are:" << endl;
                for (vertices_it = vertices.begin(); vertices_it != vertices.end(); vertices_it++)
                    cout << *vertices_it << endl;
            } else {
                starters.push(end_node);
                starter = starters.top();
            }
        } else if (_command.compare("exit") == 0) {
            starters.pop();
            if (starters.empty())
                break;
            starter = starters.top();
        } else
            cout << "unknown command" << endl;
        cout << '<' << starter << "># ";
    }

    return 0;
}
