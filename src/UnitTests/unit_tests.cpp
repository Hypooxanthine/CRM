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
#include "ExtData/JsonInterface.h"
#include "ExtData/dbinterface.h"

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
    if (x == expected) std::cout << "\x1B[32m-> OK\033[0m\t\t";\
    else std::cout << "\x1B[31m-> BAD RESULT\033[0m\t\t";\
    std::cout << std::endl << std::endl;}
#define END_TEST }

void UnitTest::Test_Todo()
{
    BEGIN_TEST(Todo("Rappeler le client"));
    TEST(VAL.content, (std::string)"Rappeler le client");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler @date 2/3/2023"));
    TEST(VAL.content, (std::string)"Rappeler");
    TEST(VAL.date, Date(2, 3, 2023));
    END_TEST;

    BEGIN_TEST(Todo("Rappeler@date 2/3/2023"));
    TEST(VAL.content, (std::string)"Rappeler@date 2/3/2023");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler\n@date 2/3/2023"));
    TEST(VAL.content, (std::string)"Rappeler");
    TEST(VAL.date, Date::today());
    END_TEST;

    BEGIN_TEST(Todo("Rappeler @date 2/3/2023\nLigne non prise en compte"));
    TEST(VAL.content, (std::string)"Rappeler");
    TEST(VAL.date, Date(2, 3, 2023));
    END_TEST;

    BEGIN_TEST(Todo("Rappeler le client.", Date(1, 1, 2023)));
    TEST(VAL.content, (std::string)"Rappeler le client.");
    TEST(VAL.date, Date(1, 1, 2023));
    END_TEST;
}

void UnitTest::Test_Interaction()
{
    BEGIN_TEST(Interaction("Conférence sur zoom.", Date(1, 1, 2023)));
    TEST(VAL.content, (std::string)"Conférence sur zoom.");
    TEST(VAL.date, Date(1, 1, 2023));
    END_TEST;

    BEGIN_TEST(Interaction("Conférence sur zoom.\n@todo Rappeler"));
    TEST(VAL.content, (std::string)"Conférence sur zoom.");
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
    TEST(VAL.content, (std::string)"Rdv avec le client.");
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
        VAL.add(Contact("prenom1", "nom1", "entreprise1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today(), Date::today()));
        VAL.add(Contact("prenom2", "nom2", "entreprise2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today(), Date::today()));
        VAL.add(Contact("prenom3", "nom3", "entreprise3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today(), Date::today()));
        TEST(VAL.getSize(), 3);
    END_TEST;

    BEGIN_TEST(ContactManager());
        VAL.add(Contact("prenom1", "nom1", "entreprise1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today(), Date::today()));
        VAL.add(Contact("prenom2", "nom2", "entreprise2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today(), Date::today()));
        VAL.add(Contact("prenom3", "nom3", "entreprise3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today(), Date::today()));
        VAL.remove(Contact("prenom2", "nom2", "entreprise2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today(), Date::today()));
        TEST(VAL.getSize(), 2);

        auto expected = ContactManager();
        expected.add(Contact("prenom1", "nom1", "entreprise1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today(), Date::today()));
        expected.add(Contact("prenom3", "nom3", "entreprise3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today(), Date::today()));
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
        TEST(VAL, Date(9, 12, 2022)); // Will fail tomorrow and after.
    END_TEST;

    BEGIN_TEST(Date::parseDate("02/11/2023"));
    TEST(VAL.has_value(), 1);
    if(VAL.has_value()) TEST(VAL.value(), Date(2, 11, 2023));
    END_TEST;

    BEGIN_TEST(Date::parseDate("02 11 2023"));
    TEST(VAL.has_value(), false);
    END_TEST;

    BEGIN_TEST(Date::parseDate("bad date"));
    TEST(VAL.has_value(), false);
    END_TEST;

    BEGIN_TEST(Date::parseNumber("25"));
    TEST(VAL.has_value(), 1);
    if(VAL.has_value()) TEST(VAL.value(), 25);
    END_TEST;

    BEGIN_TEST(Date::parseNumber("-25"));
    TEST(VAL.has_value(), false);
    END_TEST;
}

void UnitTest::Test_Json()
{

    BEGIN_TEST(ContactManager())
        ContactManager toExport;
            toExport.add(Contact("prenom1", "nom1", "entreprise1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today(), Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
            toExport.add(Contact("prenom2", "nom2", "entreprise2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today(), Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
            toExport.add(Contact("prenom3", "nom3", "entreprise3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today(), Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
                toExport.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toExport.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
        JsonInterface::ExportData(toExport);
        VAL = JsonInterface::ImportData();
    TEST(VAL, toExport);
    END_TEST;

}

void UnitTest::Test_DBInterface()
{
    BEGIN_TEST(ContactManager())
        ContactManager toSave;
            toSave.add(Contact("prenom1", "nom1", "entreprise1", "email1", "06 06 06 06 01", "photos/photo1.png", Date::today(), Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
            toSave.add(Contact("prenom2", "nom2", "entreprise2", "email2", "06 06 06 06 02", "photos/photo2.png", Date::today(), Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
            toSave.add(Contact("prenom3", "nom3", "entreprise3", "email3", "06 06 06 06 03", "photos/photo3.png", Date::today(), Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
                toSave.getBack().getInteractions().add(Interaction("Content2", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content1", Date::today()));
                    toSave.getBack().getInteractions().getBack().getTodos().add(Todo("Content2", Date::today()));
        DBInterface::SaveData(toSave);
        VAL = DBInterface::LoadData();

        TEST(VAL, toSave);
    END_TEST;
}
