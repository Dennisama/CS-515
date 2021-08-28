/** CS515 Lab 10
File: DisjointSet.h
Name: Biao Zhang
Section: 01
Date: 11/22/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
/* Sets are disjoint if the sets are all pairwise disjoint.                  *
 * For example, the sets {1,2}, {3,6}, {10,41} are  disjoint,                *
 * whereas the sets {3,2}, {2,8} are not, due to the common element 2.       *
 * A disjoint set is a set containing disjoint sets. Another name   		 *
 * for this data structure is the union-find.                                *
 * 
 * This particular implementation uses an uptree that is built with an       *
 * underlying std::map. All elements are int type                            *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#include <map>
using namespace std;

template <typename T>
class DisjointSet{
private:
    std::map<T, T> parents; // access to set representitives
    std::map<T, int> depths; // used for path compression
public:
    DisjointSet(){};
    
    /**
	 * Creates a singleton set from the parameter.
	 */
    void createSet(T p){
        parents[p] = p;
        depths[p] = 0;
    }
    
    /**
	 * Finds and returns the representative of the set which contains the
	 * parameter. Implements path compression.
	 */
    T findSet(T p){
        if (p != parents[p])
            parents[p] = findSet(parents[p]);
        return parents[p];
    }
    
    /**
	 * Combines the sets which contain the parameters. Return false if two 
     * parameters are already in the same set; otherwise, union the two sets
     * by rank and return true
	 */
    bool unionSets(T p, T q){
        T p_id = findSet(p);
        T q_id = findSet(q);

        if (p_id == q_id)
            return false;

        if (depths[p_id] > depths[q_id])
            parents[q_id] = p_id;
        else {
            parents[p_id] = q_id;
            if (depths[p_id] == depths[q_id])
                depths[q_id]++;
        }
        return true;
    }
    
};
