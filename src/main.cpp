#include "mainwindow.h"

#include "ExtData/dbinterface.h"
#include "UnitTests/unit_tests.h"

int main()
{
    DBInterface::Init();

    // UnitTest::Test_Date();
    // UnitTest::Test_Todo();
    // UnitTest::Test_Interaction();

    // UnitTest::Test_ContactManager();
    // UnitTest::Test_InteractionManager();
    // UnitTest::Test_TodoManager();
    // UnitTest::Test_Json();
    UnitTest::Test_DBInterface();
    return 0;
}
