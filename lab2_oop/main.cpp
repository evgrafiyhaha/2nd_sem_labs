#include "List.h"
int main()
{
    List<int> cont;
    for (int i = 0; i < 10; i++) {
        cont.add(i);
    }
    int arr[] = {1,2,3,4,5};

    cont.add_range(arr,5);
    for (int i = 0; i < cont.get_length(); i++) {
        std::cout << cont[i] << " ";
    }
    std::cout << std::endl;
    int i = 7;
    std::cout << cont.get_index(i) << std::endl;

    std::cout << cont.get_elem(7) << std::endl;

    int j = 44;
    cont.set_elem(7,j);
    std::cout << cont.get_elem(7) << std::endl;

    cont.remove_elem(7);
    std::cout << cont.get_elem(7) << std::endl;

    std::cout << std::endl;
    int* badArr = cont.to_array();
    std::cout << badArr[3] <<std::endl;

    List<int> cont2 = {1,2,3};
    cont2.add(52);

    cont = cont2;
    std::cout << cont[0] << " " << cont.get_length() << std::endl;

    List<int> cont3 = {5,33};
    cont.add_range(cont3);
    for (int c = 0; c < cont.get_length(); c++) {
        std::cout << "/ " << cont[c] << std::endl;
    }
    List<int> cont4 = cont3;

    List<int> cont5 = std::move(cont4);

    std::cout << "Count = " << std::distance(cont.begin(), cont.end()) << std::endl;
    return 0;
}