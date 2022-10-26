#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "unit_tests.h"

int main(int argc, char *argv[])
{
    Test_Todo();
    Test_Interaction();
    Test_Contact();

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "Projet_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
