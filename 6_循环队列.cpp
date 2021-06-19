#include <cstdio>

enum queue_status
{
    queue_ok = 0,
    queue_full,
    queue_empty
};

// 循环队列开辟一段首尾相连的连续存储空间，以顺时针方向
// 从队列尾入队，从队列头出队，初始时队列头索引与队列尾
// 索引同为0，循环入队出队的过程中，队列头索引始终在追
// 赶队列尾索引，当头索引与尾索引值相等时队列为空，当
// 队列尾索引加1余缓存长度等于队列头索引时队列为满，队列
// 的实际可存储空间为缓存长度减1
template <typename T>
class queue
{
public:
    queue(int len);
    ~queue();

    queue_status push(T t);
    queue_status pop(T& t);
    T& operator[](int index);
    T at(int index);
    int size() {return real_size;}

private:
    int front{0}, rear{0};
    T* buffer{nullptr};
    int length{0}, real_size{0};
};

template <typename T>
queue<T>::queue(int len)
    : length(len)
{
    if (len >= 0) {
        buffer = new T[len];
    }
}

template <typename T>
queue<T>::~queue()
{
    delete[] buffer;
    buffer = nullptr;
    length = real_size = front = rear = 0;
}

template <typename T>
queue_status queue<T>::push(T t)
{
    if (((rear + 1) % length) == front) {
        return queue_full;
    }
    rear = (rear + 1) % length;
    buffer[rear] = t;
    real_size++;
    return queue_ok;
}

template <typename T>
queue_status queue<T>::pop(T& t)
{
    if (front == rear) {
        return queue_empty;
    }
    front = (front + 1) % length;
    t = buffer[front];
    real_size--;
    return queue_ok;
}

// 返回引用可修改队列内数值
template <typename T>
T& queue<T>::operator[](int index)
{
    return buffer[(front + 1 + index) % length];
}

template <typename T>
T queue<T>::at(int index)
{
    return buffer[(front + 1 + index) % length];
}

int main(int argc, char* argv[])
{
    int len = 10;
    queue<int> queue(len);
    for (int k = 0; k < len + 2; k++) {
        if (queue.push(k) != queue_ok) {
            printf("queue full\n");
        }
        else {
            printf("push %d\n", k);
        }
    }
    for (int k = 0; k < queue.size(); k++) {
        printf("get %d\n", queue.at(k));
    }
    queue[0] = 100;
    for (int k = 0; k < len + 2; k++) {
        int tmp;
        if (queue.pop(tmp) != queue_ok) {
            printf("queue empty\n");
        }
        else {
            printf("pop %d\n", tmp);
        }
    }
    return 0;
}
