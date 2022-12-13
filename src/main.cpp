#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

#include "HUD/mainwindow.h"

#include "ExtData/dbinterface.h"
#include "UnitTests/unit_tests.h"

int main(int argc, char** argv)
{
    DBInterface::Init();

    QApplication app(argc, argv);

    // UnitTest::Test_Date();
    // UnitTest::Test_Todo();
    // UnitTest::Test_Interaction();

    // UnitTest::Test_ContactManager();
    // UnitTest::Test_InteractionManager();
    // UnitTest::Test_TodoManager();
    // UnitTest::Test_Json();
    // UnitTest::Test_DBInterface();

    QTranslator translator;
    QStringList languages;
    languages << "English" << "French";

    QString selected = QInputDialog::getItem(nullptr, "Select language", "Language", languages);

    if(selected == "French")
    {
        translator.load(":french.qm");
        app.installTranslator(&translator);
    }

    MainWindow win;

    win.show();

    return app.exec();
}
