#ifndef LAB2_OOP_ITERATOR_H
#define LAB2_OOP_ITERATOR_H
#include <vector>

template <typename T, typename U>
class Iterator
{
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data)
    {
        m_it_ = m_p_data_->m_data_.begin();
    }
    void First()
    {
        m_it_ = m_p_data_->m_data_.begin();
    }
    void Next()
    {
        m_it_++;
    }
    bool IsDone()
    {
        return (m_it_ == m_p_data_->m_data_.end());
    }
    iter_type Current()
    {
        return m_it_;
    }
private:
    U *m_p_data_;
    iter_type m_it_;
};

#endif //LAB2_OOP_ITERATOR_H
