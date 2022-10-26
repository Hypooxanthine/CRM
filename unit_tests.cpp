#include "unit_tests.h"

#include <iostream>

#include "todo.h"
#include "interaction.h"
#include "contact.h"

void Test_Todo()
{
    std::cout << Todo("Rappeler", Date(1, 1, 2023)) << std::endl;
    std::cout << Todo("Rappeler", Date::today()) << std::endl;
    std::cout << Todo("Rappeler") << std::endl;
    std::cout << Todo("Rappeler @date 5/12/2022") << std::endl;
    std::cout << Todo("Rappeler @date 5/12/2020002") << std::endl;
    std::cout << Todo("Rappeler @date 5/12/2022") << std::endl;
}

void Test_Interaction()
{
    std::cout << Interaction("Conférance sur zoom.", Date(1, 1, 2023)) << std::endl;
    std::cout << Interaction("@todo Rappeler.", Date(1, 1, 2023)) << std::endl;
    std::cout << Interaction("rdv aujourd’hui par tél.", Date::today()) << std::endl;
    std::cout << Interaction("@todo confirmer commande n°146") << std::endl;
    std::cout << Interaction("anniversaire jean luc @date 5/12/2022") << std::endl;
    std::cout << Interaction("@todo Rendre projet cdaa @date 17/12/2022") << std::endl;
    std::cout << Interaction("Rappeler @date 5/12/2022") << std::endl;
}

void Test_Contact()
{

}
