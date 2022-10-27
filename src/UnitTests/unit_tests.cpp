#include "UnitTests/unit_tests.h"

#include <iostream>
#include <sstream>

#include "DataStructures/todo.h"
#include "DataStructures/interaction.h"
#include "DataStructures/contact.h"
#include "DataStructures/contactmanager.h"
#include "DataStructures/interactionmanager.h"
#include "DataStructures/todomanager.h"
#include "DataStructures/date.h"

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

    BEGIN_TEST(Interaction("Rdv avec le client.\n@todo Confirmer commande 12\n@todo Confirmer commande 13 @date 02/02/2023"));
    TEST(VAL.content, "Rdv avec le client.");
    TEST(VAL.date, Date::today());
    TEST(VAL.todos.getSize(), 2);
    auto expected = Interaction("Rdv avec le client.", Date::today());
    expected.getTodos().add(Todo("Confirmer commande 12"));
    expected.getTodos().add(Todo("Confirmer commande 13 @date 02/02/2023"));
    TEST(VAL, expected);
    END_TEST;
}

void UnitTest::Test_ContactManager()
{
    BEGIN_TEST(ContactManager());
        VAL.add(Contact(1, "nom1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today()));
        VAL.add(Contact(2, "nom2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today()));
        VAL.add(Contact(3, "nom3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today()));
        TEST(VAL.getSize(), 3);
    END_TEST;

    BEGIN_TEST(ContactManager());
        VAL.add(Contact(1, "nom1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today()));
        VAL.add(Contact(2, "nom2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today()));
        VAL.add(Contact(3, "nom3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today()));
        VAL.remove(Contact(2, "nom2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today()));
        TEST(VAL.getSize(), 2);

        auto expected = ContactManager();
        expected.add(Contact(1, "nom1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today()));
        expected.add(Contact(3, "nom3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today()));
        TEST(VAL, expected);
    END_TEST;
}

void UnitTest::Test_InteractionManager()
{
    BEGIN_TEST(InteractionManager());
        VAL.add(Interaction("Rdv avec le client1.\n@todo Confirmer commande n 121."));
        VAL.add(Interaction("Rdv avec le client2.\n@todo Confirmer commande n 122."));
        VAL.add(Interaction("Rdv avec le client3.\n@todo Confirmer commande n 123."));
        TEST(VAL.getSize(), 3);
    END_TEST;

    BEGIN_TEST(InteractionManager());
        VAL.add(Interaction("Rdv avec le client1.\n@todo Confirmer commande n 121."));
        VAL.add(Interaction("Rdv avec le client2.\n@todo Confirmer commande n 122."));
        VAL.add(Interaction("Rdv avec le client3.\n@todo Confirmer commande n 123."));
        VAL.remove(Interaction("Rdv avec le client2.\n@todo Confirmer commande n 122."));
        TEST(VAL.getSize(), 2);

        auto expected = InteractionManager();
        expected.add(Interaction("Rdv avec le client1.\n@todo Confirmer commande n 121."));
        expected.add(Interaction("Rdv avec le client3.\n@todo Confirmer commande n 123."));
        TEST(VAL, expected);
    END_TEST;
}

void UnitTest::Test_TodoManager()
{
    BEGIN_TEST(TodoManager());
        VAL.add(Todo("Confirmer commande n 121."));
        VAL.add(Todo("Confirmer commande n 122."));
        VAL.add(Todo("Confirmer commande n 123."));
        TEST(VAL.getSize(), 3);
    END_TEST;

    BEGIN_TEST(TodoManager());
        VAL.add(Todo("Confirmer commande n 121."));
        VAL.add(Todo("Confirmer commande n 122."));
        VAL.add(Todo("Confirmer commande n 123."));
        VAL.remove(Todo("Confirmer commande n 122."));
        TEST(VAL.getSize(), 2);

        auto expected = TodoManager();
        expected.add(Todo("Confirmer commande n 121."));
        expected.add(Todo("Confirmer commande n 123."));
        TEST(VAL, expected);
    END_TEST;
}

void UnitTest::Test_Date()
{
    BEGIN_TEST(Date(1, 1, 2023));
        TEST(+VAL.getDay(), 1);
        TEST(+VAL.getMonth(), 1);
        TEST(+VAL.getYear(), 2023);
    END_TEST;

    BEGIN_TEST(Date::today());
        TEST(VAL, "27/10/2022"); // Will fail tomorrow and after.
    END_TEST;
}
