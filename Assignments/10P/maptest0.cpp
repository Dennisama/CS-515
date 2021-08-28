#include "unorderedmap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main(){
   UnorderedMap <double, string> m1;

    cout << "\n\nMap test 1\n\n";

    assert( m1.insert(3.1415, "boy") == true);
    assert( m1.insert(2.718, "breeze") == true);
    assert( m1.insert(1.69, "fire") == true);
    assert( m1.insert(1.414, "rose") == true);
    assert( m1.insert(1.69, "ice") == false);

    //cout << m1 << "\n";
    UnorderedMap<double, string>::Iterator iter = m1.begin();
    while (iter != m1.end()){
        cout << iter->key << " and " << iter->data << " ";
        iter++;
    }
    cout << "size: " << m1.size() << " and tsize: "
         << m1.tsize() << endl;

    iter++;
    iter++;

    cout << "\n\nMap test 2\n\n";
    UnorderedMap <double, string> m_1 = m1;
    UnorderedMap<double, string>::Iterator iter_1 = m_1.begin();
    while (iter_1 != m_1.end()){
        cout << iter_1->key << " and " << iter_1->data << " ";
        iter_1++;
    }
    cout << "size: " << m_1.size() << " and tsize: "
         << m_1.tsize() << endl;

    cout << "\n\nMap test 3\n\n";
    assert( m_1.insert(6.718, "boy") == true);
    assert( m_1.insert(3.1415, "breeze") == false);
    assert( m_1.insert(10.23, "fire") == true);
    assert( m1.insert(9.42, "rose") == true);
    assert( m1.insert(12.56, "ice") == true);
    assert( m_1.insert(6.718, "boy") == false);
    assert( m_1.insert(13.141, "breeze") == true);
    assert( m_1.insert(100.23, "fire") == true);
    assert( m1.insert(19.42, "rose") == true);
    assert( m1.insert(22.56, "ice") == true);

    m1 = m_1;
    UnorderedMap<double, string>::Iterator iter1 = m1.begin();
    int i = 0;
    while (iter1 != m1.end()){
        cout << iter1->key << " and " << iter1->data << " ";
        iter1++;
        i++;
    }
    cout << endl;
    cout << "Total count: " << i << endl;
    cout << "size: " << m1.size() << " and tsize: "
         << m1.tsize() << endl;

    cout << "\n\nMap test 4\n\n";
    UnorderedMap<int, int> m2;
    m2[29] = 1;
    m2[34] = 1;
    m2[39] = 1;
    m2[23] = 1;
    m2[87] = 1;
    m2[45] = 1;
    m2[83] = 1;
    m2[22] = 1;
    m2[12] = 1;
    m2[57] = 1;
    m2[21] = 1;
    m2[30] = 1;
    m2[2] = 1;
    m2[26] = 1;
    m2[5] = 1;
    m2[11] = 1;
    m2[32] = 1;
    m2[86] = 1;
    //cout << m2 << "\n\n\n\n\n";

    m2[29] = 2;
    m2[34] = 2;
    m2[39] = 2;
    m2[23] = 2;
    m2[87] = 2;
    m2[45] = 2;
    m2[83] = 2;
    m2[22] = 2;
    m2[12] = 2;
    m2[57] = 2;
    m2[21] = 2;
    m2[30] = 2;
    m2[2] = 2;
    m2[26] = 2;
    m2[5] = 2;
    m2[11] = 2;
    m2[32] = 2;
    m2[86] = 2;
    //cout << m2 << "\n\n";

    UnorderedMap<int, int>::Iterator iter2 = m2.begin();
    i = 0;
    while (iter2 != m2.end()){
        cout << " ("<< iter2->key << ", " << iter2->data << ") ";
        iter2++;
        i++;
    }
    cout << endl;
    cout << "Total count: " << i << endl;
    cout << "size: " << m2.size() << " and tsize: "
         << m2.tsize() << endl;

    cout << "\n\nMap test 5\n\n";
    assert( m2.erase(22) == true);
    assert( m2.erase(34) == true);
    assert( m2.erase(57) == true);
    assert( m2.erase(86) == true);
    assert( m2.erase(30) == true);
    assert( m2.erase(45) == true);
    assert( m2.erase(26) == true);
    assert( m2.erase(34) == false);
    assert( m2.erase(86) == false);

    iter2 = m2.begin();
    i = 0;
    while (iter2 != m2.end()){
        cout << iter2->key << " and " << iter2->data << " ";
        iter2++;
        i++;
    }
    cout << endl;
    cout << "Total count: " << i << endl;
    cout << "size: " << m2.size() << " and tsize: "
         << m2.tsize() << endl;

    assert( m2.insert(50, 3) == true);
    assert( m2.insert(67, 3) == true);
    assert( m2.insert(11, 3) == false);
    assert( m2.erase(83) == true);
    assert( m2.erase(2) == true);
    assert( m2.erase(50) == true);
    assert( m2.erase(21) == true);
    assert( m2.erase(39) == true);
    assert( m2.erase(12) == true);
    assert( m2.erase(5) == true);
    assert( m2.erase(50) == false);
    assert( m2.insert(99, 3) == true);
    assert( m2.erase(11) == true);
    assert( m2.erase(32) == true);
    assert( m2.erase(23) == true);
    assert( m2.erase(87) == true);
    assert( m2.erase(67) == true);
    assert( m2.erase(29) == true);
    assert( m2.erase(99) == true);

    iter2 = m2.begin();
    i = 0;
    while (iter2 != m2.end()){
        cout << iter2->key << " and " << iter2->data << " ";
        iter2++;
        i++;
    }
    cout << endl;
    cout << "Total count: " << i << endl;
    cout << "size: " << m2.size() << " and tsize: "
         << m2.tsize() << endl;

    cout << "\n\nMap test 5\n\n";
    iter1 = m1.find(6.718);
    assert(iter1->data == "boy");
    iter1 = m1.find(100.23);
    assert(iter1->data == "fire");
    iter1 = m1.find(3.1415);
    assert(iter1->data == "boy");
    iter1 = m1.find(3.14);
    assert(iter1 == m1.end());
}
