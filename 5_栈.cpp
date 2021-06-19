#include <cstdio>

enum stack_status
{
    stack_ok = 0,
    stack_full,
    stack_empty
};

// 使用低地址作为栈顶，堆栈指针初始化为-1
// 压栈时堆栈指针自增，出栈时堆栈指针自减
template <typename T>
class stack
{
public:
    stack(int len);
    ~stack();

    stack_status push(T t);
    stack_status pop(T& t);

private:
    int index{-1};
    T* buffer{nullptr};
    int length{0};
};

template <typename T>
stack<T>::stack(int len)
    : length(len)
{
    if (len >= 0) {
        buffer = new T[len];
    }
}

template <typename T>
stack<T>::~stack()
{
    delete[] buffer;
    buffer = nullptr;
    index = -1;
    length = 0;
}

// 先自增堆栈指针再存值
template <typename T>
stack_status stack<T>::push(T t)
{
    if (index + 1 >= length) {
        return stack_full;
    }
    buffer[++index] = t;
    return stack_ok;
}

// 先取值再自增堆栈指针
template <typename T>
stack_status stack<T>::pop(T& t)
{
    if (index <= -1) {
        return stack_empty;
    }
    t = buffer[index--];
    return stack_ok;
}

int main(int argc, char* argv[])
{
    int len = 10;
    stack<int> stack(len);
    for (int k = 0; k < len + 2; k++) {
        if (stack.push(k) != stack_ok) {
            printf("stack full\n");
        }
        else {
            printf("push %d\n", k);
        }
    }
    for (int k = 0; k < len + 2; k++) {
        int tmp;
        if (stack.pop(tmp) != stack_ok) {
            printf("stack empty\n");
        }
        else {
            printf("pop %d\n", tmp);
        }
    }
    return 0;
}
