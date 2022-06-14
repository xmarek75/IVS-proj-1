//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Pavel Marek <xmarek75@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Pavel Marek
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//
class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = { 15, 5, 4, 8 };
        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }
    BinaryTree tree;
};

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode) {
    auto result = tree.InsertNode(0);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key,0);

    auto result2 = tree.InsertNode(0);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result.second);

}
TEST_F(NonEmptyTree, InsertNode) {
    auto result = tree.InsertNode(0);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key,0);

    auto result2 = tree.InsertNode(0);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result.second);

    auto result3 = tree.InsertNode(10);
    EXPECT_FALSE(result3.first);
    EXPECT_EQ(result3.second->key, 10);
}

TEST_F(EmptyTree, DeleteNode) {
    auto result1 = tree.DeleteNode(1234);
    EXPECT_FALSE(result1);
    tree.InsertNode(1234);
    auto result3 = tree.DeleteNode(1234);
    EXPECT_TRUE(result3);

}
TEST_F(NonEmptyTree, DeleteNode) {
    auto result1 = tree.DeleteNode(1234);
    EXPECT_FALSE(result1);
    tree.InsertNode(1234);
    auto result3 = tree.DeleteNode(1234);
    EXPECT_TRUE(result3);
    auto result4 = tree.DeleteNode(5);
    EXPECT_TRUE(result4);

}
TEST_F(EmptyTree, FindNode) {
    auto result1 = tree.FindNode(15);
    EXPECT_EQ(result1, nullptr);
    tree.InsertNode(15);
    auto result2 = tree.FindNode(15);
    EXPECT_TRUE(result2->key == 15 );
}
TEST_F(NonEmptyTree, FindNode) {
    auto result1 = tree.FindNode(1597456414);
    EXPECT_EQ(result1, nullptr);
    tree.InsertNode(15);
    auto result2 = tree.FindNode(15);
    EXPECT_TRUE(result2->key == 15 );
}
TEST_F(TreeAxioms, Axiom1){
    std::vector<Node_t *> vector1{};
    tree.GetLeafNodes(vector1);
    for(auto node : vector1)
    {
        EXPECT_EQ(node->color, BLACK);
    }
}
TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> vector1{};
    tree.GetAllNodes(vector1);
    for (auto node : vector1)
    {
        if (node->color == RED)
        {
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }
}
TEST_F(TreeAxioms, Axiom3)
{

}
/*** Konec souboru black_box_tests.cpp ***/
