//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Pavel Marek <xmarek75@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Pavel Marek
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"



//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

TEST(Tests1, MatrixConstructor)
{
    Matrix x1{};
    EXPECT_EQ(x1.get(0,0),0);
    Matrix x2{3,3};
    EXPECT_ANY_THROW(Matrix(1,0));
    EXPECT_ANY_THROW(Matrix(0,1));

}
TEST(Tests2,MatrixSet)
{
    Matrix x1{2,3};
    EXPECT_TRUE(x1.set(1,1,15));
    EXPECT_FALSE(x1.set(3,2,15));
    Matrix x2{2,3};

    Matrix x3{3,3};
    bool result1 = x3.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    EXPECT_TRUE(result1);

    bool result2 = x2.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    EXPECT_FALSE(result2);
    Matrix x4{};
    bool result3 = x4.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    EXPECT_FALSE(result3);
}
TEST(Tests3, MatrixGet)
{
    Matrix x1{3,3};
    x1.set(1,2,15);
    double result1 = x1.get(1,2);
    EXPECT_EQ(result1,15);

    Matrix x2{3,3};
    x2.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    int k=1;
   for(int i = 0; i < 3; i++)
   {
       for(int j = 0; j < 3; j++)
       {
           double result2 = x2.get(i,j);
           EXPECT_EQ(result2,k);
           k+=1;
       }
   }
   EXPECT_ANY_THROW(x1.get(3,3));
}
TEST(Tests4,MatrixOperatorEqual)
{
    Matrix x1{};
    Matrix x2{};
    bool result1 = x1 == x2;
    EXPECT_TRUE(result1);
    Matrix x3{2,2};
    EXPECT_ANY_THROW(x1.operator==(x3));
    Matrix x4{3,3};
    x2.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    Matrix x5{3,3};
    x5.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,0,6},
            {7,8,9},
    });
    EXPECT_FALSE(x4.operator==(x5));

    Matrix x6{1,1};
    Matrix x7{1,1};
    EXPECT_TRUE(x6 == x7);



}
TEST(Tests5,MatrixOperatorPlus)
{
    Matrix x1{};
    x1.set(0,0,1);
    Matrix x2{};
    Matrix result = x1 + x2;
    EXPECT_EQ(result.get(0,0),1);
    Matrix x3{2,2};
    EXPECT_ANY_THROW(x1 + x3);
}
TEST(Tests6,MatrixOperatorScalar)
{
    Matrix x1{1,1};
    x1.set(0,0,4);
    Matrix result1 = x1.operator*(2);
    Matrix x2{1,1};
    x2.set(0,0,8);
    EXPECT_EQ(result1,x2);

    Matrix result2 = x1.operator*(x2);
    EXPECT_EQ(result1,x2);
    Matrix x3{3,3};
    x3.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,0,6},
            {7,8,9},
    });
    EXPECT_ANY_THROW(x1.operator*(x3));
}
TEST(Tests7,MatrixSolveEquation)
{
    Matrix x1{2,2};
    x1.set(std::vector<std::vector< double > >{
            {1,2},
            {1,3},
    });
    auto result1 = x1.solveEquation(std::vector<double> {6,3});
    std::vector<double> answer1 = {12, -3};
    EXPECT_EQ(answer1,result1);
    //test pocet radku != prave strane
    EXPECT_ANY_THROW(x1.solveEquation(std::vector<double> {6,3,12}));
    //test Determinant = 0
    Matrix x2{3,3};
    x2.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    EXPECT_ANY_THROW(x2.solveEquation(std::vector<double> {6,3,12}));
    //test matice neni ctvercova
    Matrix x3{2,3};
    x2.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
    });
    EXPECT_ANY_THROW(x3.solveEquation(std::vector<double> {6,3,12}));

    //matice 1x1
    Matrix a1{};
    a1.set(0,0,1);
    EXPECT_ANY_THROW(a1.inverse());
    auto result_a1 = a1.solveEquation({1});
    EXPECT_EQ(result_a1,std::vector<double> {1});

    //matice 4x4
    Matrix a2{4,4};
    a2.set(std::vector<std::vector< double > >{
            {1,2,3,4},
            {40,5,6,7},
            {7,8,9,10},
            {11,12,15,1},
    });
    auto result_a2 = a2.solveEquation({1,2,1,1});

}
TEST(Tests8,MatrixTransponse)
{
    Matrix x1{2,2};
    x1.set(std::vector<std::vector< double > >{
            {1,2},
            {3,4},
    });
    Matrix x2{2,2};
    x2.set(std::vector<std::vector< double > >{
            {1,3},
            {2,4},
    });
    Matrix result1 = x1.transpose();
    EXPECT_EQ(result1,x2);

    Matrix x3{};
    EXPECT_EQ(x3.transpose(),x3);

}
TEST(Tests9,MatrixInverse)
{
    Matrix x1{2,2};
    x1.set(std::vector<std::vector< double > >{
            {1,2},
            {2,5},
    });
    Matrix x2{2,2};
    x2.set(std::vector<std::vector< double > >{
            {5,-2},
            {-2,1},
    });
    Matrix result1 = x1.inverse();
    EXPECT_EQ(x2,result1);


    Matrix x3{4,2};
    x3.set(std::vector<std::vector< double > >{
            {5,-2},
            {-2,1},
            {5,-2},
            {-2,1},
    });
    EXPECT_ANY_THROW(x3.inverse());

    Matrix x4{3,3};
    x4.set(std::vector<std::vector< double > >{
            {1,2,3},
            {4,5,6},
            {7,8,9},
    });
    EXPECT_ANY_THROW(x4.inverse());
    Matrix x5{3,3};
    x5.set(std::vector<std::vector< double > >{
            {1,2,3},
            {1,4,3},
            {1,8,4},
    });
    Matrix x6{3,3};
    x6.set(std::vector<std::vector< double > >{
            {-4,8,-3},
            {-0.5,0.5,0},
            {2,-3,1},
    });
    EXPECT_EQ(x5.inverse(),x6);

    Matrix x7{1,1};
    x7.set(0,0,1);
    EXPECT_ANY_THROW(x7.inverse());


}

/*** Konec souboru white_box_tests.cpp ***/
