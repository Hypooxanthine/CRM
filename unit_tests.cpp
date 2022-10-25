#include "unit_tests.h"

#include <iostream>

#include "todo.h"
#include "interaction.h"

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

}
