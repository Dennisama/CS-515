/* CS515 Assignment 5
File: mapTest.cpp
Name: Biao Zhang
Section: 1
Date: 10/15/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
/* These are test for map inerface methods using Google Test */
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
