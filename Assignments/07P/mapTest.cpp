/* CS515 Assignment 7
File: mapTest.cpp
Name: Biao Zhang
Section: 1
Date: 10/29/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
/* These are test for map inerface methods using Google Test */
#ifdef DEBUG
#define bug_out(t) cout << "+++++++++++++++++++++++++++++" << endl; \
    cout << t << endl; \
    cout << "+++++++++++++++++++++++++++++" << endl;
#else
#define bug_out(testM)
#endif
#include "map.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//The constructor should create a map with zero size
TEST(MapTest, constructorCreatesZeroSizeMap)
{
    Map testM;
    EXPECT_EQ(0, testM.size());
}

//Inserting into an empty map should return true and result in a size of one
TEST(MapTest, insertWhileEmptyReturnsTrueAndMapSizeIsOne)
{
    Map testM;
    EXPECT_TRUE(testM.insert("0000","Zero"));
    EXPECT_EQ(1, testM.size());
}

//Inserting a key that already exists should fail and not change the map size
TEST(MapTest, insertOfSameKeyReturnsFalseAndMapSizeRemainsSame)
{
    Map testM;
    testM.insert("0000","Zero");
    testM.insert("0001","One");
    EXPECT_EQ(2, testM.size());
    EXPECT_FALSE(testM.insert("0000","zeRo"));
    EXPECT_EQ(2, testM.size());
    EXPECT_FALSE(testM.insert("0001","oNe"));
    EXPECT_EQ(2, testM.size());
}

//Accessing an existing item using [] should return correct value and not
//change the map size
TEST(MapTest, indexOperatorOfExistingKeyReturnsProperValueAndSizeIsSame)
{
    Map testM;
    testM.insert("0000","Zero");
    testM.insert("0001","One");
    testM.insert("0002","Two");
    EXPECT_EQ(3, testM.size());// new one
    EXPECT_STREQ("Zero",testM["0000"].c_str());
    EXPECT_EQ(3, testM.size());
}
    
//Using [] to set an item in an empty map should add the item with an
//appropriate value and increase the map size to one
TEST(MapTest, indexOperatorOnEmptyMapProperlySetsValueAndSizeIsOne)
{
    Map testM;
    testM["0001"] = "One";
    EXPECT_STREQ("One",testM["0001"].c_str());
    EXPECT_EQ(1, testM.size());
}

//Using [] to set an item in a map that already contains other items
//inserts and updates the size appropriately
TEST(MapTest, indexOperatorOnMissingKeyProperlySetsValueAndIncrementsSize)
{
    Map testM;
    testM.insert("0001","One");
    testM.insert("0002","Two");
    EXPECT_EQ(2, testM.size());
    testM["0003"] = "Three";
    EXPECT_STREQ("Three",testM["0003"].c_str());
    EXPECT_EQ(3, testM.size());
}

//Erasing a key that exists in the map succeeds and decrements the map size
TEST(MapTest, eraseOfExistingKeyReturnsTrueAndDecrementsSize)
{
    Map testM;
    testM.insert("0001","One");
    testM.insert("0002","Two");
    EXPECT_EQ(2, testM.size());
    EXPECT_TRUE(testM.erase("0001"));
    EXPECT_EQ(1, testM.size());
}

//Erase on an empty map fails and keeps the map size at zero
TEST(MapTest, eraseOnEmptyMapReturnsFalseAndSizeRemainsZero)
{
    Map testM;
    EXPECT_FALSE(testM.erase("0001"));
    EXPECT_EQ(0, testM.size());
}

//Erase of a non-existant key fails and does not change the map size
TEST(MapTest, eraseOfMissingKeyReturnsFalseAndSizeRemainsSame)
{
    Map testM;
    testM.insert("0001","One");
    testM.insert("0002","Two");
    EXPECT_EQ(2, testM.size());
    EXPECT_FALSE(testM.erase("0003"));
    EXPECT_EQ(2, testM.size());
}

//Using the copy constructor results in two maps of the same, correct size
TEST(MapTest, copyConstructorMakesCorrectSize)
{
    Map m1;
    m1.insert("0001","One");
    m1.insert("0002","Two");

    Map m2(m1);
    EXPECT_EQ(m1.size(),m2.size());
    EXPECT_EQ(2,m2.size());
}

//Using the copy constructor with an existing map makes its own
//copy, such that if the value associated with a key is changed
//in the copy it does not change the associated value in the
//original, and inserts/erases on either won't affect the other.
TEST(MapTest, copyConstructorMakesSeparateCopy)
{
    Map m1;
    m1.insert("0001","One");
    m1.insert("0002","Two");

    Map m2(m1);
    m1.erase("0001");
    m2.insert("0003","Three");
    EXPECT_EQ(1,m1.size());
    EXPECT_EQ(3,m2.size());
    m2["0002"] = "tWO";
    EXPECT_FALSE(m1["0002"] == m2["0002"]);
}

//Using the assignment operator results in two maps of the same, correct size
TEST(MapTest, assignmentOperatorMakesCorrectSize)
{
    Map m2;
    m2.insert("0001","One");
    m2.insert("0002","Two");

    Map m1(m2);
    m1.insert("0003","Three");
    m2 = m1;

    EXPECT_EQ(m1.size(), m2.size());
    EXPECT_EQ(3, m2.size());
}

//Using the assignment operator with an existing map makes its own
//copy, such that if the value associated with a key is changed
//in the copy it does not change the associated value in the
//original, and inserts/erases on either won't affect the other.
TEST(MapTest, assignmentMakesSeparateCopy)
{
    Map m2;
    m2.insert("0001","One");

    Map m1(m2);
    m1.insert("0002","Two");
    m2 = m1;

    m1.erase("0001");
    m2.insert("0003","Three");
    EXPECT_EQ(1,m1.size());
    EXPECT_EQ(3,m2.size());
    m2["0002"] = "twO";
    EXPECT_FALSE(m1["0002"] == m2["0002"]);

}

//Using the assignment operator with an existing map with over 1000 items
//makes a copy that has correct keys/values at a couple of places deep within
//the map (values that aren't at either end of the range of keys used).
TEST(MapTest, assignmentWithManyItemsHasCorrectValues)
{
    int i;
    string prefix;
    Map m1;
    const int bigValue = 1050;
    for (i = 0; i < bigValue; i++) {
        if (i < 10)
            prefix = "000";
        else if (i < 100)
            prefix = "00";
        else if (i < 1000)
            prefix = "0";
        else
            prefix = "";

        m1.insert(prefix + to_string(i),to_string(i));
    }
    EXPECT_EQ(bigValue,m1.size());

    Map m2;
    m2 = m1;
    EXPECT_EQ(bigValue,m2.size());
    vector<string> deeptest {"0005","0052","0153","0234","0554",
                             "0601","0812","0926","1004","1035"};
    for (string str : deeptest) {
        EXPECT_EQ(m1[str],m2[str]);
    }
}

// Insert method basis path I
TEST(MapTest, mapInsertMethodBasisPathOne)
{
    Map testM;
    // Insert from the null
    testM.insert("0005","Five");
    EXPECT_EQ(1,testM.size());
    EXPECT_STREQ("Five",testM["0005"].c_str());

    // Insert right node
    EXPECT_TRUE(testM.insert("0006","Six"));
    EXPECT_EQ(2,testM.size());
    EXPECT_STREQ("Six",testM["0006"].c_str());

    // Insert left node
    EXPECT_TRUE(testM.insert("0004","Four"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("Four",testM["0004"].c_str());

    // Insert the same node
    EXPECT_FALSE(testM.insert("0004","Six"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("Four",testM["0004"].c_str());

    bug_out(testM);
}

// Insert method basis path II
TEST(MapTest, mapInsertMethodBasisPathTwo)
{
    Map testM;
    // Insert from the null
    testM.insert("0005","Five");
    EXPECT_EQ(1,testM.size());
    EXPECT_STREQ("Five",testM["0005"].c_str());

    // Insert right node
    EXPECT_TRUE(testM.insert("0008","Eight"));
    EXPECT_EQ(2,testM.size());
    EXPECT_STREQ("Eight",testM["0008"].c_str());

    // Insert left node
    EXPECT_TRUE(testM.insert("0006","Six"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("Six",testM["0006"].c_str());

    // Insert the same node
    EXPECT_FALSE(testM.insert("0005","Six"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("Five",testM["0005"].c_str());

    bug_out(testM);
}

// Insert method basis path III
TEST(MapTest, mapInsertMethodBasisPathThree)
{
    Map testM;
    // Insert from the null
    testM.insert("0005","Five");
    EXPECT_EQ(1,testM.size());
    EXPECT_STREQ("Five",testM["0005"].c_str());

    // Insert left node
    EXPECT_TRUE(testM.insert("0003","Three"));
    EXPECT_EQ(2,testM.size());
    EXPECT_STREQ("Three",testM["0003"].c_str());

    // Insert left node
    EXPECT_TRUE(testM.insert("0001","One"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("One",testM["0001"].c_str());

    // Insert the same node
    EXPECT_FALSE(testM.insert("0003","Two"));
    EXPECT_EQ(3,testM.size());
    EXPECT_STREQ("Three",testM["0003"].c_str());

    bug_out(testM);
}

// Erase method basis path I
TEST(MapTest, mapEraseMethodBasisPathOne)
{
    Map testM;
    EXPECT_FALSE(testM.erase("0001"));

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0006","Six");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());
    bug_out(testM);

    EXPECT_FALSE(testM.erase("0009"));
    EXPECT_EQ(11,testM.size());

    EXPECT_TRUE(testM.erase("0013"));
    EXPECT_EQ(10,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0006"));
    EXPECT_EQ(9,testM.size());
    bug_out(testM);

    EXPECT_FALSE(testM.erase("0013"));
    EXPECT_EQ(9,testM.size());

    EXPECT_TRUE(testM.erase("0002"));
    EXPECT_EQ(8,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0003"));
    EXPECT_EQ(7,testM.size());
    bug_out(testM);
}

// Erase method basis path II
TEST(MapTest, mapEraseMethodBasisPathTwo)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0006","Six");
    testM.insert("0008","Eight");
    testM.insert("0012","Twelve");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    EXPECT_EQ(15,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0010"));
    EXPECT_EQ(14,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0013"));
    EXPECT_EQ(13,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0017"));
    EXPECT_EQ(12,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0015"));
    EXPECT_EQ(11,testM.size());
    bug_out(testM);

    EXPECT_FALSE(testM.erase("0013"));
    EXPECT_EQ(11,testM.size());

    EXPECT_TRUE(testM.erase("0001"));
    EXPECT_EQ(10,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0002"));
    EXPECT_EQ(9,testM.size());
    bug_out(testM);
}

// Erase method basis path III
TEST(MapTest, mapEraseMethodBasisPathThree)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0009","Nine");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0007","Seven");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    testM.insert("0008","Eight");
    EXPECT_EQ(14,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0010"));
    EXPECT_EQ(13,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0007"));
    EXPECT_EQ(12,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0013"));
    EXPECT_EQ(11,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0020"));
    EXPECT_EQ(10,testM.size());
    bug_out(testM);

    EXPECT_TRUE(testM.erase("0019"));
    EXPECT_EQ(9,testM.size());
    bug_out(testM);

    EXPECT_FALSE(testM.erase("0007"));
    EXPECT_EQ(9,testM.size());
}

// Find method basis path I
TEST(MapTest, mapFindMethodBasisPathOne)
{
    Map testM;
    Map::Iterator it_0 = testM.find("0001");
    EXPECT_TRUE(it_0 == testM.end());

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.find("0000");
    EXPECT_TRUE(it_1 == testM.end());

    Map::Iterator it_2 = testM.find("0006");
    EXPECT_TRUE(it_2 == testM.end());
}

// Find method basis path II
TEST(MapTest, mapFindMethodBasisPathTwo)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0006","Six");
    testM.insert("0008","Eight");
    testM.insert("0012","Twelve");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    EXPECT_EQ(15,testM.size());

    Map::Iterator it_1 = testM.find("0007");
    bug_out("The key is " << (*it_1).key <<
    " and the value is " << (*it_1).data << endl);

    Map::Iterator it_2 = testM.find("0006");
    bug_out("The key is " << (*it_2).key <<
    " and the value is " << (*it_2).data << endl);
}

// Begin method basis path I
TEST(MapTest, mapBeginMethodBasisPathOne)
{
    Map testM;
    Map::Iterator it_0 = testM.begin();
    EXPECT_TRUE(it_0 == testM.end());

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.begin();
    bug_out("The key is " << (*it_1).key <<
    " and the value is " << (*it_1).data << endl);
}

// Begin method basis path II
TEST(MapTest, mapBeginMethodBasisPathTwo)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0009","Nine");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0007","Seven");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    testM.insert("0008","Eight");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.begin();
    bug_out("The key is " << (*it_1).key <<
    " and the value is " << (*it_1).data << endl);

    testM.erase("0010");
    testM.erase("0013");
    testM.erase("0014");
    testM.erase("0019");
    testM.erase("0007");
    testM.erase("0009");
    testM.erase("0008");
    testM.erase("0020");
    testM.erase("0017");
    testM.erase("0005");
    testM.erase("0015");
    EXPECT_EQ(0,testM.size());
    Map::Iterator it_0 = testM.begin();
    EXPECT_TRUE(it_0 == testM.end());
}

// End method basis path I
TEST(MapTest, mapEndMethodBasisPathOne)
{
    Map testM;
    Map::Iterator it_0 = testM.end();
    EXPECT_TRUE((*it_0).right == 0);

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.end();
    EXPECT_TRUE((*it_1).right == 0);
}

// End method basis path II
TEST(MapTest, mapEndMethodBasisPathTwo)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0009","Nine");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0007","Seven");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    testM.insert("0008","Eight");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.end();
    EXPECT_TRUE((*it_1).right == 0);

    testM.erase("0010");
    testM.erase("0013");
    testM.erase("0014");
    testM.erase("0019");
    testM.erase("0007");
    testM.erase("0009");
    testM.erase("0008");
    testM.erase("0020");
    testM.erase("0017");
    testM.erase("0005");
    testM.erase("0015");
    EXPECT_EQ(0,testM.size());

    Map::Iterator it_0 = testM.end();
    EXPECT_TRUE((*it_0).right == 0);
}

// [] operator basis path I
TEST(MapTest, mapOperatorBasisPathOne)
{
    Map testM;
    EXPECT_EQ(0,testM.size());
    EXPECT_TRUE("" == testM["0010"]);
    EXPECT_EQ(1,testM.size());
    bug_out(testM);
    testM["0010"] = "Ten";
    EXPECT_EQ(1,testM.size());
    bug_out(testM);

    testM["0005"] = "Five";
    EXPECT_EQ(2,testM.size());
    bug_out(testM);

    testM["0015"] = "Fifteen";
    EXPECT_EQ(3,testM.size());
    bug_out(testM);

    testM["0002"] = "Two";
    EXPECT_EQ(4,testM.size());
    bug_out(testM);

    EXPECT_TRUE("" == testM["0007"]);
    EXPECT_EQ(5,testM.size());
    bug_out(testM);
    testM["0007"] = "Seven";
    EXPECT_EQ(5,testM.size());
    bug_out(testM);

    testM["0013"] = "Thirteen";
    EXPECT_EQ(6,testM.size());
    bug_out(testM);

    testM["0019"] = "Nineteen";
    EXPECT_EQ(7,testM.size());
    bug_out(testM);

    EXPECT_FALSE(testM.insert("0013","Thirteen"));
    EXPECT_FALSE(testM.insert("0019","Nineteen"));

    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    EXPECT_TRUE("Eight" == testM["0008"]);
    EXPECT_TRUE("Seventeen" == testM["0017"]);
}

// [] Operator basis path II
TEST(MapTest, mapOperatorBasisPathTwo)
{
    Map testM;

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0006","Six");
    testM.insert("0008","Eight");
    testM.insert("0012","Twelve");
    testM.insert("0014","Fourteen");
    testM.insert("0017","Seventeen");
    testM.insert("0020","Twenty");
    EXPECT_EQ(15,testM.size());


    EXPECT_TRUE("Twelve" == testM["0012"]);
    testM["0012"] = "Yahaha";
    bug_out(testM);

    EXPECT_TRUE("Twenty" == testM["0020"]);
    testM["0020"] = "Hayaya";
    bug_out(testM);

    testM["0011"] = "Hohoho";
    bug_out(testM);
}

// Iterator Dereference operator basis path
TEST(MapTest, mapItDereferenceOperatorBasisPath)
{
    Map testM;
    Map::Iterator it_0 = testM.find("0001");
    EXPECT_TRUE((*it_0).right == 0);

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.find("0013");
    EXPECT_TRUE((*it_1).key == "0013");
    EXPECT_TRUE((*it_1).data == "Thirteen");

    bug_out(testM);
    Map::Iterator it_2 = testM.find("0013");
    (*it_2).key = "0004";
    (*it_2).data = "Yahaha";
    bug_out(testM);
}

// Iterator Arrow operator basis path
TEST(MapTest, mapItArrowOperatorBasisPath)
{
    Map testM;
    Map::Iterator it_0 = testM.find("0001");
    EXPECT_TRUE(it_0->right == 0);

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_1 = testM.find("0013");
    EXPECT_TRUE(it_1->key == "0013");
    EXPECT_TRUE(it_1->data == "Thirteen");

    bug_out(testM);
    Map::Iterator it_2 = testM.find("0008");
    it_2->key = "0004";
    it_2->data = "Yahaha";
    bug_out(testM);
}

// Iterator Equality operator basis path
TEST(MapTest, mapItEqualityBasisPath)
{
    Map testM;
    Map::Iterator it_00 = testM.find("0001");
    Map::Iterator it_01 = testM.end();
    EXPECT_TRUE(it_00 == it_01);

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_10 = testM.find("0013");
    Map::Iterator it_11 = testM.begin();
    EXPECT_FALSE(it_10 == it_11);

    Map::Iterator it_20 = testM.find("0001");
    Map::Iterator it_21 = testM.begin();
    EXPECT_TRUE(it_20 == it_21);

    Map::Iterator it_30 = testM.find("0991");
    Map::Iterator it_31 = testM.end();
    EXPECT_TRUE(it_30 == it_31);
}

// Iterator Inequality operator basis path
TEST(MapTest, mapItInequalityBasisPath)
{
    Map testM;
    Map::Iterator it_00 = testM.find("0001");
    Map::Iterator it_01 = testM.end();
    EXPECT_FALSE(it_00 != it_01);

    testM.insert("0010","Ten");
    testM.insert("0005","Five");
    testM.insert("0015","Fifteen");
    testM.insert("0002","Two");
    testM.insert("0007","Seven");
    testM.insert("0013","Thirteen");
    testM.insert("0019","Nineteen");
    testM.insert("0001","One");
    testM.insert("0003","Three");
    testM.insert("0008","Eight");
    testM.insert("0017","Seventeen");
    EXPECT_EQ(11,testM.size());

    Map::Iterator it_10 = testM.find("0013");
    Map::Iterator it_11 = testM.begin();
    EXPECT_TRUE(it_10 != it_11);

    Map::Iterator it_20 = testM.find("0001");
    Map::Iterator it_21 = testM.begin();
    EXPECT_FALSE(it_20 != it_21);

    Map::Iterator it_30 = testM.find("0991");
    Map::Iterator it_31 = testM.end();
    EXPECT_FALSE(it_30 != it_31);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
