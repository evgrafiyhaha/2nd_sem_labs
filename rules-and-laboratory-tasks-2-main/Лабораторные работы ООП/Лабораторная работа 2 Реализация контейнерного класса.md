# Лабораторная работа №2 "Реализация контейнерного класса"

## Задание

Разработать шаблонный контейнерный класс в соответствии с вариантом, а также класс итератора к нему. Протестировать разработанный класс. Для каждого варианта указан список публичных методов и пояснения к ним – это минимальный набор методов, которые необходимо реализовать для данного варианта. Если операция не может быть выполнена, необходимо выбросить исключение.

Студентом по желанию могут быть реализованы и другие методы, которые он сочтет полезными и применимыми для данного класса.

При разработке следует руководствоваться принципами ООП. Использование контейнеров из библиотек запрещено. В рамках лабораторной работы необходимо использовать следующие паттерны: свойства (properties), итератор (iterator).

## Тестирование

Тестирование производить при помощи тестовой программы (достаточно консольной). Проверить необходимо все публичные методы реализованного класса.

## Бонусные задания

1. Возможно использование специальной библиотеки для тестирования (в этом случае ожидается базовое понимание механизмов работы библиотеки тестирования, используемых в ней макросов).
2. Реализация дополнительных методов, входящих в состав библиотек std и Qt.

## Класс итератора

Класс, необходимый для реализации всех вариантов:

|Метод|Пояснение|
|:----------|:----------|
|`Iterator<T>(тип_контейнера_из_варианта<T> container_obj)`|конструктор, принимающий объект контейнерного класса, который необходимо обойти с помощью данного итератора|
|`Iterator<T> next()`|перейти к следующему объекту в контейнере|
|`T value()`|получить значение текущего объекта в контейнере|
|`bool is_end()`|указывает ли итератор на конечный фиктивный элемент контейнера, следующий за последним реальным. Нужен для определения конца итерирования|
|`Iterator<T> &operator++()`|префиксный инкремент, эквивалентен next()|
|`T &operator*()`|оператор разыменования, эквивалентен value()|
|`bool operator ==(Iterator<T> &b)`|оператор сравнения|
|`bool operator !=(Iterator<T> &b)`|оператор сравнения|

## Задания по вариантам

### Вариант 0 Список

|Метод|Пояснение|
|:----------|:----------|
|`list();`|конструктор по умолчанию|
|`list(const list<T>& lst);`|конструктор копирования|
|`list(list<T>&& list);`|конструктор перемещения|
|`explicit list(std::initializer_list<T> lst);`|явный конструктор со списком инициализации|
|`~list();`|деструктор|
|`list<T>& operator =(const list<T>& lst);`|перегрузка оператора присваивания
|`int get_length() const;`|получить текущий размер списка|
|`void add(const T& elem);`|добавить элемент в конец списка|
|`void add_range(const list<T>& lst);`|добавить список элементов в конец списка|
|`void add_range(T* arr, int size);`|добавить массив элементов в конец списка|
|`void set_elem(int index,const T& elem);`|изменить элемент списка по индексу|
|`T& get_elem(int index);`|получить элемент списка по индексу|
|`void remove_elem(int index);`|удалить элемент списка по индексу|
|`list<T> combine(const list<T>& lst);`|объединение списка с другим списком (метод возвращает новый список, содержащий сначала элементы текущего списка, затем, переданного в Combine)|
|`void sort(int (*comp)(const T& r1, constT& r2));`|отсортировать список используя переданный компаратор|
|`int get_index(T &elem) const;`|если содержится в списке элемент T, возвращает индекс элемента или -1 в случае, если элемент не найден|
|`T* to_array();`|создать новый массив, в который необходимо записать все элементы вектора|
|`T& operator[](int index);`|доступ к элементу аналогично массиву|

### Вариант 1 Матрица
<table>
<tr>
    <th>Метод</th>
    <th>Пояснение</th>
</tr>
<tr>
    <td><code>matrix(unsigned int n, unsigned int m);</code></td>
    <td>конструктор, создающий пустую матрицу заданного размера</td>
</tr>
<tr>
    <td><code>matrix(const matrix&lt;T>& matr);</code></td>
    <td>конструктор копирования</td>
</tr>
<tr>
    <td><code>matrix(matrix&lt;T>&& matr);</code></td>
    <td>конструктор перемещения</td>
</tr>
<tr>
    <td><code>explicit matrix(std::initializer_list&lt;std::initializer_list&lt;T>> lst);</code></td>
    <td>конструктор со списком инициализации</td>
</tr>
<tr>
    <td><code>~matrix();</code></td>
    <td>деструктор</td>
</tr>
<tr>
    <td><code>matrix&lt;T>& operator =(const matrix&lt;T>& matr);</code></td>
    <td>перегрузка оператора присваивания для двух матриц типа Т</td>
</tr>
<tr>
    <td><code>matrix&lt;T>& operator +=(const matrix&lt;T>& matr);</code></td>
    <td>перегрузка оператора += для двух матриц типа Т</td>
</tr>
<tr>
    <td><code>matrix&lt;T>& operator -=(const matrix&lt;T>& matr);</code></td>
    <td>перегрузка оператора -= для двух матриц типа Т</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;friend matrix<_T> operator +(const matrix<_T>& m1, const matrix<_T>& m2);</code></td>
    <td>перегрузка оператора + для двух матриц</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator -(const matrix<_T>& m1, const matrix<_T>& m2);</code></td>
    <td>перегрузка оператора - для двух матриц</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator *(const matrix<_T>& m1, const matrix<_T>& m2);</code></td>
    <td>перегрузка оператора * для двух матриц</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator +(const matrix<_T>& m1, double num);</code></td>
    <td>перегрузка оператора + для сложения матрицы с числом</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator -(const matrix<_T>& m1, double num);</code></td>
    <td>перегрузка оператора – для вычисления разности матрицы с числом</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator /(const matrix<_T>& m1, double num);</code></td>
    <td>перегрузка оператора / для вычисления частного матрицы с числом</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend matrix<_T> operator *(const matrix<_T>& m1, double num);</code></td>
    <td>перегрузка оператора * для умножения матрицы с числом</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend std::ostream& operator <<(std::ostream& os, const matrix<_T>& matr);</code></td>
    <td>перегрузка оператора << для вывода класса в поток (cout к примеру)</td>
</tr>
<tr>
    <td><code>void set_elem(unsigned int i, unsigned int j,const T& elem);</code></td>
    <td>метод изменения элемента матрицы по индексу</td>
</tr>
<tr>
    <td><code>T& get_elem(unsigned int i, unsigned int j);</code></td>
    <td>метод получения элемента матрицы по индексу</td>
</tr>
<tr>
    <td><code>T& operator ()(unsigned int i, unsigned int j);</code></td>
    <td>метод получения элемента матрицы по индексу, через синтаксис круглых скобок. matrix(i, j)</td>
</tr>
<tr>
    <td><code>bool is_square();</code></td>
    <td>метод проверки матрицы на квадратную</td>
</tr>
<tr>
    <td><code>unsigned int get_row() const;</code></td>
    <td>метод получения числа строк матрицы</td>
</tr>
<tr>
    <td><code>unsigned int get_columns() const;</code></td>
    <td>метод получения числа столбцов матрицы</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_begin();</code></td>
    <td>метод получения итератора на начало матрицы (первый элемент)</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_end();</code></td>
    <td>метод получения итератора на конец матрицы (конец – это фиктивный элемент, следующий за последним в матрице)</td>
</tr>
</table>

### Вариант 2 Математический вектор

<table>
<tr>
    <th>Метод</th>
    <th>Пояснение</th>
</tr>
<tr>
    <td><code>m_vector(int length);</code></td>
    <td>конструктор с указанием размерности</td>
</tr>
<tr>
    <td><code>m_vector(const m_vector&lt;T>& vect);</code></td>
    <td>конструктор копирования</td>
</tr>
<tr>
    <td><code>m_vector (m_vector &lt;T>&& vect);</code></td>
    <td>конструктор перемещения</td>
</tr>
<tr>
    <td><code>explicit m_vector(std::initializer_list&lt;T> lst);</code></td>
    <td>конструктор со списком инициализации</td>
</tr>
<tr>
    <td><code>~m_vector();</code></td>
    <td>деструктор</td>
</tr>
<tr>
    <td><code>m_vector&lt;T>& operator =(const m_vector&lt;T>& lst);</code></td>
    <td>перегрузка оператора присваивания</td>
</tr>
<tr>
    <td><code>int get_length() const;</code></td>
    <td>получить текущий размер</td>
</tr>
<tr>
    <td><code>void set_elem(int index,const T& elem);</code></td>
    <td>изменить элемент вектора по индексу</td>
</tr>
<tr>
    <td><code>T& get_elem(int index);</code></td>
    <td>получить элемент списка по индексу</td>
</tr>
<tr>
    <td><code>T* to_array();</code></td>
    <td>создать новый массив, в который необходимо записать все элементы вектора</td>
</tr>
<tr>
    <td><code>T& operator[](int index);</code></td>
    <td>доступ к элементу, аналогично массиву</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend std::ostream& operator <<(std::ostream& os, const m_vector<_T>& lst);</code></td>
    <td>перегрузка оператора << для вывода класса в поток (cout к примеру)</td>
</tr>
<tr>
    <td><code>m_vector&lt;T>& operator +=(const m_vector&lt;T>& vect);</code></td>
    <td>перегрузка оператора +=, к this добавлется vect</td>
</tr>
<tr>
    <td><code>m_vector&lt;T>& operator -=(const m_vector&lt;T>& vect);</code></td>
    <td>перегрузка оператора -=, из this вычитается vect</td>
</tr>
<tr>
    <td><code>m_vector&lt;T>& operator *=(const T& val);</code></td>
    <td>перегрузка оператора *=, каждый элемент this домножается на val</td>
</tr>
<tr>
    <td><code>m_vector&lt;T>& operator /=(const T& val);</code></td>
    <td>перегрузка оператора /=, каждый элемент this делится на val</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend m_vector<_T> operator +(const m_vector<_T>& v1, const m_vector<_T>& v2);</code></td>
    <td>перегрузка оператора += к v1 добавлется v2</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend m_vector<_T> operator -(const m_vector<_T>& v1, const m_vector<_T>& v2);</code></td>
    <td>перегрузка оператора -, из v1 вычитается v2</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend m_vector<_T> operator *(const m_vector<_T>& v1, const T& val);</code></td>
    <td>перегрузка оператора *, каждый элемент v1 домножается на val</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend m_vector<_T> operator /(const m_vector<_T>& v1, const T& val);</code></td>
    <td>перегрузка оператора /, каждый элемент v1 делится на val</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_begin();</code></td>
    <td>метод получения итератора на начало вектора (первый элемент)</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_end();</code></td>
    <td>метод получения итератора на конец списка (фиктивный элемент, следующий за последним в векторе)</td>
</tr>
</table>

### Вариант 3 Множество (добавляемые элементы уникальны)

<table>
<tr>
    <th>Метод</th>
    <th>Пояснение</th>
</tr>
<tr>
    <td><code>set();</code></td>
    <td>конструктор по умолчанию</td>
</tr>
<tr>
    <td><code>set(const set&lt;T>& s);</code></td>
    <td>конструктор копирования</td>
</tr>
<tr>
    <td><code>set (set &lt;T>&& s);</code></td>
    <td>конструктор перемещения</td>
</tr>
<tr>
    <td><code>explicit set(std::initializer_list&lt;T> lst);</code></td>
    <td>конструктор со списком инициализации</td>
</tr>
<tr>
    <td><code>~set();</code></td>
    <td>деструктор</td>
</tr>
<tr>
    <td><code>set&lt;T>& operator =(const set&lt;T>& lst);</code></td>
    <td>перегрузка оператора присваивания</td>
</tr>
<tr>
    <td><code>int get_length() const;</code></td>
    <td>получить текущий размер</td>
</tr>
<tr>
    <td><code>bool contains(const T& elem);</code></td>
    <td>проверить наличие в множестве элемента</td>
</tr>
<tr>
    <td><code>void add(const T& elem);</code></td>
    <td>добавить элемент в множество</td>
</tr>
<tr>
    <td><code>void remove(const T& elem);</code></td>
    <td>удалить элемент из множества</td>
</tr>
<tr>
    <td><code>T* to_array();</code></td>
    <td>создать новый массив, в который необходимо записать все элементы вектора</td>
</tr>
<tr>
    <td><code>set&lt;T>& union(const set&lt;T>& s);</code></td>
    <td>результат – объединение this с s</td>
</tr>
<tr>
    <td><code>set&lt;T>& intersection(const set&lt;T>& s);</code></td>
    <td>результат – пересечение this с s</td>
</tr>
<tr>
    <td><code>set&lt;T>& subtract(const set&lt;T>& s);</code></td>
    <td>результат – разность this и s</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend std::ostream& operator <<(std::ostream& os, const set<_T>& lst);</code></td>
    <td>перегрузка оператора << для вывода класса в поток (cout к примеру)</td>
</tr>
<tr>
    <td><code>set&lt;T>& operator +=(const set&lt;T>& s);</code></td>
    <td>перегрузка оператора += результат –объединение множеств this и s</td>
</tr>
<tr>
    <td><code>set&lt;T>& operator *=(const set&lt;T>& s);</code></td>
    <td>перегрузка оператора *=, результат –  пересечение множеств this и s</td>
</tr>
<tr>
    <td><code>set&lt;T>& operator /=(const set&lt;T>& s);</code></td>
    <td>перегрузка оператора /=, разность множеств this и s</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend set<_T> operator +(const set<_T>& s1, const set<_T>& s2);</code></td>
    <td>перегрузка оператора + результат – объединение множеств v1 и v2</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend set<_T> operator *(const set<_T>& s1, const set<_T>& s2);</code></td>
    <td>перегрузка оператора *, результат – пересечение множеств v1 и v2</td>
</tr>
<tr>
    <td><code>template&lt;typename _T&gt;<br>friend set<_T> operator /(const set<_T>& s1, const set&lt;T>& s2);</code></td>
    <td>перегрузка оператора /, разность множеств v1 и v2</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_begin();</code></td>
    <td>метод получения итератора на начало множества (первый элемент)</td>
</tr>
<tr>
    <td><code>Iterator&lt;T> iterator_end();</code></td>
    <td>метод получения итератора на конец множества (фиктивный элемент, следующий за последним в множестве)</td>
</tr>
<tr>
    <td><code>void clear();</code></td>
    <td>очистить множество</td>
</tr>
</table>

### Бонусный вариант Дерево

Не более 5 человек из группы могут заменить свой вариант на бонусный.

На этот вариант нет четкого описания методов, его требуется составить самостоятельно, после чего утвердить у преподавателя. Не допускается сдача бонусных заданий с одинаковыми методами. Лабораторная будет засчитана первому сдавшему.
