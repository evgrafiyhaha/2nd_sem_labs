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

    std::cout << "TEST_2: void addRange(const list<T>& lst); " << std::endl;
    List<int> lst2 = {6, 7, 8};
    lst.addRange(lst2);
    std::cout << lst << std::endl;

    std::cout << "TEST_3: void addRange(T* arr, int size); " << std::endl;
    int arr[] = {9, 10};
    lst.addRange(arr, 2);
    std::cout << lst << std::endl;

    std::cout << "TEST_?: + += reverse " << std::endl;
    List<int> listPlus = lst+lst2;
    listPlus += lst2;
    std::cout << listPlus << std::endl;
    listPlus.reverse();
    std::cout << listPlus << std::endl;
}

template <typename T>
void deletionTests(List<T> &lst) {
    std::cout << "TEST_4: void removeElem(int index); " << std::endl;
    lst.removeElem(7);
    std::cout << lst << std::endl;
}

template <typename T>
void getsTests(List<T> &lst) {
    std::cout << "TEST_5: int getLength() const; " << std::endl;
    std::cout << lst.getLength() << std::endl;

    std::cout << "TEST_6: T& getElem(int index); " << std::endl;
    std::cout << lst.getElem(6) << std::endl;

    std::cout << "TEST_7: T& operator[](int index); " << std::endl;
    std::cout << lst[6] << std::endl;

    std::cout << "TEST_8: int getIndex(T &elem) const; " << std::endl;
    int elem = 12;
    std::cout << lst.getIndex(elem) << std::endl;

    std::cout << "TEST_9: void setElem(int index,const T& elem); " << std::endl;
    int elem2 = 52;
    lst.setElem(4,elem2);
    std::cout << lst << std::endl;
}

template <typename T>
void extraTests(List<T> &lst) {
    std::cout << "TEST_10: T* to_array(); " << std::endl;
    int* arr = lst.to_array();
    for (int i = 0;i < lst.getLength();i++) {
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
    lst5.removeElem(1);
    std::cout << lst5.getIndex(temp) << std::endl;
}

template <typename T>
void iteratorTests(List<T> &lst) {
    std::cout << std::endl << "ITERATOR TESTS:" << std::endl;
    std::cout << "TEST_14: std::distance " << std::endl;
    std::cout << std::distance(lst.begin(), lst.end()) << std::endl;

    std::cout << "TEST_15: First(); is_end(); next(); value() " << std::endl;
    for (auto elem : lst)
        std::cout << elem << " ";
    std::cout << std::endl;
    List<std::string> lst5{"int"};
}