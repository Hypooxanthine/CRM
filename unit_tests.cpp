#include "unit_tests.h"

#include <iostream>
#include <sstream>

#include "todo.h"
#include "interaction.h"
#include "contact.h"

#define VAL value
#define BEGIN_TEST(val) {\
    auto VAL = val;\
    std::ostringstream ossExpected, ossResult;\
    std::cout << std::endl << "\x1B[33mTest on VAL = " << #val << " :\033[0m\t\t" << std::endl;

#define TEST(x, expected) {\
    ossExpected = std::ostringstream();\
    ossExpected << expected;\
    ossResult = std::ostringstream();\
    ossResult << x;\
    std::cout << "\x1B[36mValue " << #x << "\033[0m\t\t" << std::endl;\
    std::cout << "-Expected : " << std::endl << expected << std::endl << "-Result :" << std::endl << x << std::endl;\
    if (std::string(ossExpected.str()) == std::string(ossResult.str())) std::cout << "\x1B[32m-> OK\033[0m\t\t";\
    else std::cout << "\x1B[31m-> BAD RESULT\033[0m\t\t";\
    std::cout << std::endl << std::endl;}
#define END_TEST }

void UnitTest::Test_Todo()
{
    BEGIN_TEST(Todo::parseDate("02/11/2023"));
    TEST(VAL.has_value(), 1);
    if(VAL.has_value()) TEST(VAL.value(), Date(2, 11, 2023));
    END_TEST;

    BEGIN_TEST(Todo::parseDate("02 11 2023"));
    TEST(VAL.has_value(), 0);
    if(VAL.has_value()) TEST(VAL.value(), "No value");
    END_TEST;

    BEGIN_TEST(Todo::parseDate("bad date"));
    TEST(VAL.has_value(), 0);
    if(VAL.has_value()) TEST(VAL.value(), "No value");
    END_TEST;

    BEGIN_TEST(Todo::parseNumber("25"));
    TEST(VAL.has_value(), 1);
    if(VAL.has_value()) TEST(VAL.value(), 25);
    END_TEST;

    BEGIN_TEST(Todo::parseNumber("-25"));
    TEST(VAL.has_value(), 0);
    if(VAL.has_value()) TEST(VAL.value(), "No value");
    END_TEST;

    BEGIN_TEST(Todo("Rappeler le client"));
    TEST(VAL.content, "Rappeler le client");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler @date 2/3/2023"));
    TEST(VAL.content, "Rappeler");
    TEST(VAL.date, Date(2, 3, 2023));
    END_TEST;

    BEGIN_TEST(Todo("Rappeler@date 2/3/2023"));
    TEST(VAL.content, "Rappeler@date 2/3/2023");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler\n@date 2/3/2023"));
    TEST(VAL.content, "Rappeler");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler @date 2/3/2023\nLigne non prise en compte"));
    TEST(VAL.content, "Rappeler");
    TEST(VAL.date, Date(2, 3, 2023));
    END_TEST;

    BEGIN_TEST(Todo("Rappeler le client.", Date(1, 1, 2023)));
    TEST(VAL.content, "Rappeler le client.");
    TEST(VAL.date, Date(1, 1, 2023));
    END_TEST;
}

void UnitTest::Test_Interaction()
{
    BEGIN_TEST(Interaction("Conférence sur zoom.", Date(1, 1, 2023)));
    TEST(VAL.content, "Conférence sur zoom.");
    TEST(VAL.date, Date(1, 1, 2023));
    END_TEST;

    BEGIN_TEST(Interaction("Conférence sur zoom.\n@todo Rappeler"));
    TEST(VAL.content, "Conférence sur zoom.");
    TEST(VAL.date, Date::today());
    TEST(VAL.todos.getSize(), 1);
    if(VAL.todos.getSize() > 0) TEST(VAL.getTodos().getFront(), Todo("Rappeler"));
    END_TEST;

    BEGIN_TEST(Interaction("@todo Rappeler."));
    TEST(VAL.content, "");
    TEST(VAL.date, Date::today());
    TEST(VAL.todos.getSize(), 1);
    if(VAL.todos.getSize() > 0) TEST(VAL.getTodos().getFront(), Todo("Rappeler."));
    END_TEST;

    BEGIN_TEST(Interaction("Anniversaire @date 5/12/2022"));
    TEST(VAL.content, "Anniversaire @date 5/12/2022");
    TEST(VAL.date, Date::today());
    TEST(VAL.todos.getSize(), 0);
    END_TEST;
}
