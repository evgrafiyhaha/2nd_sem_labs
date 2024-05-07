#include "Testing.h"

void runTests() {
    List<int> cont = {0, 1, 2, 3, 4};
    std::cout << "Start List:" << std::endl << cont << std::endl;
    try {
        additionTests(cont);
        deletionTests(cont);
        getsTests(cont);
        extraTests(cont);
        iteratorTests(cont);
        std::cout << std::endl;
    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
    }
}

template <typename T>
void additionTests(List<T> &lst) {
    std::cout << "PUBLIC METHODS TESTS:" << std::endl;
    std::cout << "TEST_1: void add(const T& elem); " << std::endl;
    lst.add(5);
    std::cout << lst << std::endl;

    std::cout << "TEST_2: void add_range(const list<T>& lst); " << std::endl;
    List<int> lst2 = {6, 7, 8};
    lst.add_range(lst2);
    std::cout << lst << std::endl;

    std::cout << "TEST_3: void add_range(T* arr, int size); " << std::endl;
    int arr[] = {9, 10};
    lst.add_range(arr, 2);
    std::cout << lst << std::endl;
}

template <typename T>
void deletionTests(List<T> &lst) {
    std::cout << "TEST_4: void remove_elem(int index); " << std::endl;
    lst.remove_elem(7);
    std::cout << lst << std::endl;
}

template <typename T>
void getsTests(List<T> &lst) {
    std::cout << "TEST_5: int get_length() const; " << std::endl;
    std::cout << lst.get_length() << std::endl;

    std::cout << "TEST_6: T& get_elem(int index); " << std::endl;
    std::cout << lst.get_elem(6) << std::endl;

    std::cout << "TEST_7: T& operator[](int index); " << std::endl;
    std::cout << lst[6] << std::endl;

    std::cout << "TEST_8: int get_index(T &elem) const; " << std::endl;
    int elem = 12;
    std::cout << lst.get_index(elem) << std::endl;

    std::cout << "TEST_9: void set_elem(int index,const T& elem); " << std::endl;
    int elem2 = 52;
    lst.set_elem(4,elem2);
    std::cout << lst << std::endl;
}

template <typename T>
void extraTests(List<T> &lst) {
    std::cout << "TEST_10: T* to_array(); " << std::endl;
    int* arr = lst.to_array();
    for (int i = 0;i < lst.get_length();i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arr;

    std::cout << "TEST_11: list<T> combine(const list<T>& lst); " << std::endl;
    List<int> lst3 = {54, 4, 8};
    List<int> lst4 = lst.combine(lst3);
    std::cout << lst4 << std::endl;

    std::cout << "TEST_12: void sort(int (*comp)(const T& r1, constT& r2)); " << std::endl;
    lst4.sort(List<int>::compare);
    std::cout << lst4 << std::endl;

    std::cout << "TEST_13: List<std::string> tests" << std::endl;
    List<std::string> lst5 = {"Hello", "Dear"};
    std::string temp = "World!";
    lst5.add(temp);
    lst5.remove_elem(1);
    std::cout << lst5.get_index(temp) << std::endl;
}

template <typename T>
void iteratorTests(List<T> &lst) {
    std::cout << std::endl << "ITERATOR TESTS:" << std::endl;
    std::cout << "TEST_14: std::distance " << std::endl;
    std::cout << std::distance(lst.begin(), lst.end()) << std::endl;

    std::cout << "TEST_15: First(); is_end(); next(); value() " << std::endl;
    Iterator<int> it(lst);
    for (it.First(); !it.is_end(); it.next())
        std::cout << it.value() << " ";
    std::cout << std::endl;
}