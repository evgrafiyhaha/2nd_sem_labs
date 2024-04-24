#include "Testing.h"

void TestingCont()
{
    std::cout << "Iterator with int" << std::endl;
    Container<int> cont;
    for (int i = 0; i < 10; i++)
        cont.Add(i);
    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
        std::cout << *it->Current() << " ";
    std::cout << std::endl;

    delete it;
}