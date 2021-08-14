#include <cstdio>
#include <string>

using namespace std;

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
    stack_status pop();
    T top() { return buffer[index]; };
    int size() { return index + 1; };

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
stack_status stack<T>::pop()
{
    if (index <= -1) {
        return stack_empty;
    }
    index--;
    return stack_ok;
}

// 小猿同学持别热心肠，喜欢帮助同事，听闻有一个同事需要搬家连忙过去帮忙。
// 小猿将物品放到箱子里。再将小箱子放到大箱子里。小猿奕然忘了用了几个箱子，
// 你能帮帮它吗?[]代表一个箱子，[]3代表3个箱子，[[]3]代表1个大箱子里放了
// 3个小箱子一共有4个箱子，[[]3]2代表有2个大箱子，
// 每个大箱子里放了3个小箱子，一共有8个箱子，假设输入均合法。
int count_box(string s)
{
    stack<int> st(s.size());
    for (int k = 0; k < s.size(); k++) {
        if (s[k] == '[') {
            st.push(0); // 标记压入[符号
        }
        else if (s[k] == ']') {
            int num = 1;
            while (st.top() != 0) { // 处理当前层[]
                num += st.top();
                st.pop();
            }
            st.pop();
            st.push(num);
        }
        else { // 处理后缀数字
            int t = st.top() * (s[k] - '0');
            st.pop();
            st.push(t);
        }
    }
    int res = 0;
    while (st.size() > 0) { // 统计箱子个数
        res += st.top();
        st.pop();
    }
    return res;
}

int main(int argc, char* argv[])
{
    printf("%d\n", count_box("[[]2][[]3]2"));
    return 0;
}
