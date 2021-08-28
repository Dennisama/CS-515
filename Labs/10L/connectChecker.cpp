/** CS515 Lab 10
File: connectChecker.cpp
Name: Biao Zhang
Section: 01
Date: 11/22/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

void printGraph(map<char, list<char> > &graph)
{
    map<char, list<char> >::iterator graph_it;
    list<char>::iterator it;

    for (graph_it = graph.begin();
         graph_it != graph.end(); graph_it++)
    {
        cout << (*graph_it).first << ": "; 
        for (it = (*graph_it).second.begin();
             it != (*graph_it).second.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
}

int main() {
    
    // build the graph 
    map<char, list<char> > graph;
    map<char, list<char> >::iterator graph_it;
    char v1, v2, start, end;
    map<char, bool> is_visited;
    map<char, bool>::iterator visited_it;
    map<char, char> parent;
    bool is_shortest;
    queue<char> tmp;
    stack<char> print_result;
    char v;

    //Process graph input
    while((cin >> v1) && v1 != '?')
    {
        if (!(cin >> v2)) // Bad input !
            break;
        //REPLACE WITH CODE TO STORE EDGE IN GRAPH
        graph[v1].push_back(v2);
        //Visited map for later use
        visited_it = is_visited.find(v1);
        if (visited_it == is_visited.end())
            is_visited[v1] = false;
        visited_it = is_visited.find(v2);
        if (visited_it == is_visited.end())
            is_visited[v2] = false;
    }

    // display stored graph if compiled with -DDEBUG_PRINT
#ifdef DEBUG_PRINT
    printGraph(graph);
#endif

    //Process queries
    while (cin >> start >> end)
    {
        //REPLACE WITH CODE TO STORE OR PROCESS QUERIES
        cin >> v1; //grab the next '?'
        if (v1 != '?')
            break;
        is_visited[start] = true;
        tmp.push(start);
        while (!tmp.empty() && tmp.front() != end) {
            v = tmp.front();
            tmp.pop();
            graph_it = graph.find(v);
            if (graph_it != graph.end()) {
                for (char a : graph[v]) {
                    if (!is_visited[a]) {
                        is_visited[a] = true;
                        tmp.push(a);
                        parent[a] = v;
                    }
                }
            }
        }

        if (!tmp.empty() && tmp.front() == end)
            is_shortest = true;
        else
            is_shortest = false;

        if (is_shortest) {
            v = end;
            while (v != start) {
                print_result.push(v);
                v = parent[v];
            }
            print_result.push(v);

            cout << "from " << start << " to " << end
                 << " : path found." << endl;
            while (print_result.top() != end) {
                cout << print_result.top() << " ";
                print_result.pop();
            }
            cout << print_result.top() << endl;
            print_result.pop();
        } else {
            cout << "from " << start << " to " << end
                 << " : path not found." << endl;
        }

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

