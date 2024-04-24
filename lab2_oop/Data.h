#ifndef LAB2_OOP_DATA_H
#define LAB2_OOP_DATA_H

template <typename T>
class Data
{
public:
    Data(T a) : m_data_(a) {}
    void set_data(int a)
    {
        m_data_ = a;
    }
    int data()
    {
        return m_data_;
    }
private:
    T m_data_;
};



#endif //LAB2_OOP_DATA_H
