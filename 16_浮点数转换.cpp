#include <iostream>

using namespace std;

// 单精度Float16 使用16位存储
// 1  5 10 位长
// +-+--------+-----------------------+
// |S| Exp | Fraction |
// +-+--------+-----------------------+
// 15 14 10 9 0 位编号 (从右边开始为0)
// 偏正值 +15

// 单精度Float32 使用32位存储
// 1 8 23 位长
// +-+--------+-----------------------+
// |S| Exp | Fraction |
// +-+--------+-----------------------+
// 31 30 23 22 0 位编号 (从右边开始为0)
// 偏正值 +127

// 单精度Double64 使用64位存储
// 1 11 52 位长
// +-+--------+-----------------------+
// |S| Exp | Fraction |
// +-+--------+-----------------------+
// 63 62 52 51 0 位编号 (从右边开始为0)
// 偏正值 +1023

struct float16_t {
    float16_t(unsigned short us16) {
        value = us16;
    }
    float16_t(float f32) { // Float32 to Float16
        unsigned int tmp = *((unsigned int *)&f32);
        value = (tmp >> 16) & 0x8000; // 符号位
        // 减去原偏正值, 加上现偏正值
        value |= ((((tmp >> 23) - 127 + 15) & 0x1f) << 10); // 指数位
        value |= ((tmp >> 13) & 0x3ff); // 余数位
    }
    operator float() { // Float16 to Float32
        unsigned int tmp = (value & 0x8000) << 16; // 符号位
        // 减去原偏正值, 加上现偏正值
        tmp |= (((((value >> 10) & 0x1f) - 15 + 127) & 0xff) << 23); // 指数位
        tmp |= ((value & 0x03ff) << 13); // 余数位
        return *((float *)&tmp);
    }
    unsigned short value;
};

int main(int argc, char* argv[])
{
    cout << 0.1f + float16_t(0.1f) << endl;
    return 0;
}
