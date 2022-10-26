#include "unit_tests.h"

#include <iostream>
#include <vector>
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
    std::cout << Interaction("Conferance sur zoom.", Date(1, 1, 2023)) << std::endl;
    std::cout << Interaction("@todo Rappeler.", Date(1, 1, 2023)) << std::endl;
    std::cout << Interaction("rdv aujourd'hui par tel.", Date::today()) << std::endl;
    std::cout << Interaction("@todo confirmer commande n 146") << std::endl;
    std::cout << Interaction("anniversaire jean luc @date 5/12/2022") << std::endl;
    std::cout << Interaction("Rendre @todo projet cdaa @date 17/12/2022") << std::endl;
    std::cout << Interaction("Rappeler @date 5/12/2022") << std::endl;
}

void Test_Contact()
{
    Contact c1 = Contact("1", "Ismail", "is@gmail.com", "3484", "photo1", Date(1, 1, 2023) , {} );
    std::cout << Contact("1", "Ismail", "is@gmail.com", "3484", "photo1", Date(1, 1, 2023) , {} ) << std::endl;
    std::cout << Contact(c1)  << std::endl;
    std::cout << Contact("1", "Alexandre", "al@gmail.com", "8475", "photo2", Date(10, 2, 2024) , {} )  << std::endl;
}
