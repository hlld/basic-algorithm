#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<vector<vector<float>>>> tensor4d;
typedef vector<int> dim4d;

// 获取4D张量的维度
void shape(tensor4d& data, dim4d& dim) {
    if (data.empty() || data[0].empty() || 
            data[0][0].empty() || data[0][0][0].empty()) {
        return;
    }
    dim.resize(4);
    dim[0] = data.size();
    dim[1] = data[0].size();
    dim[2] = data[0][0].size();
    dim[3] = data[0][0][0].size();
}

// 创建指定维度的4D张量[N, C, H, W]
void create(tensor4d& data, dim4d& dim, float val=0) {
    if (dim.size() != 4 || dim[0] < 1 || dim[1] < 1 || 
            dim[2] < 1 || dim[3] < 1) {
        return;
    }
    data.resize(dim[0]);
    for (int kn = 0; kn < dim[0]; ++kn) {
        data[kn].resize(dim[1]);
        for (int kc = 0; kc < dim[1]; ++kc) {
            data[kn][kc].resize(dim[2]);
            for (int kh = 0; kh < dim[2]; ++kh) {
                data[kn][kc][kh].resize(dim[3], val);
            }
        }
    }
}

// 填充4D张量的宽高维度
// 输入输出不能是同一个张量对象的引用
void pad(tensor4d& inputs, tensor4d& outputs, int height, int width) {
    dim4d dim;
    shape(inputs, dim);
    if (dim.size() != 4 || height < 0 || width < 0) {
        return;
    }
    if (height == 0 && width == 0) {
        outputs = inputs;
        return;
    }
    dim[2] += 2 * height;
    dim[3] += 2 * width;
    create(outputs, dim);
    for (int kn = 0; kn < dim[0]; ++kn) {
        for (int kc = 0; kc < dim[1]; ++kc) {
            for (int kh = height; kh < dim[2] - height; ++kh) {
                for (int kw = width; kw < dim[3] - width; ++kw) {
                    outputs[kn][kc][kh][kw] = inputs[kn][kc][kh - height][kw - width];
                }
            }
        }
    }
}

// 执行2D卷积得到输出
// 输入输出不能是同一个张量对象的引用
void conv2d(tensor4d& inputs, tensor4d& outputs, tensor4d& weights, 
        int kernel, int stride, int padding) {
    dim4d in_dim, weight_dim, out_dim;
    shape(inputs, in_dim);
    shape(weights, weight_dim);
    if (in_dim.size() != 4 || weight_dim.size() != 4 || in_dim[1] != weight_dim[1] || 
            weight_dim[2] != kernel || weight_dim[3] != kernel || 
                kernel < 1 || stride < 1 || padding < 0) {
        return;
    }
    // 计算输出张量的维度
    out_dim.resize(4);
    out_dim[0] = in_dim[0];
    out_dim[1] = weight_dim[0];
    out_dim[2] = (in_dim[2] - kernel + 2 * padding) / stride + 1;
    out_dim[3] = (in_dim[3] - kernel + 2 * padding) / stride + 1;
    create(outputs, out_dim);
    // 对输入张量进行0填充
    tensor4d tmp;
    pad(inputs, tmp, padding, padding);
    dim4d tmp_dim;
    shape(tmp, tmp_dim);
    // 计算4D张量的卷积输出
    for (int kn = 0; kn < out_dim[0]; ++kn) {
        for (int ko = 0; ko < out_dim[1]; ++ko) { // 输出通道数
            int idx_h = 0;
            for (int kh = 0; kh < tmp_dim[2] - kernel + 1; kh += stride) { // 纵向滑窗次数
                int idx_w = 0;
                for (int kw = 0; kw < tmp_dim[3] - kernel + 1; kw += stride) { // 横向滑窗次数
                    float sum = 0;
                    for (int kc = 0; kc < in_dim[1]; ++kc) { // 当前窗口跨通道卷积
                        float val = 0;
                        for (int j = 0; j < kernel; ++j) {
                            for (int k = 0; k < kernel; ++k) {
                                val += tmp[kn][kc][kh + j][kw + k] * weights[ko][kc][j][k];
                            }
                        }
                        sum += val;
                    }
                    outputs[kn][ko][idx_h][idx_w] = sum;
                    ++idx_w;
                }
                ++idx_h;
            }
        }
    }
}

void print(tensor4d& data) {
    dim4d dim;
    shape(data, dim);
    if (dim.size() != 4) {
        return;
    }
    cout << "Tensor4D:" << endl;
    for (int kn = 0; kn < dim[0]; ++kn) {
        for (int kc = 0; kc < dim[1]; ++kc) {
            for (int kh = 0; kh < dim[2]; ++kh) {
                for (int kw = 0; kw < dim[3]; ++kw) {
                    cout << data[kn][kc][kh][kw] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    tensor4d inputs, outputs, weights;
    dim4d in_dim{1, 1, 7, 7}, weight_dim{1, 1, 3, 3};
    create(inputs, in_dim);
    for (int j = 0; j < 7; ++j) {
        for (int k = 0; k < 7; ++k) {
            inputs[0][0][j][k] = j + k;
        }
    }
    print(inputs);
    create(weights, weight_dim, 1);
    print(weights);
    conv2d(inputs, outputs, weights, 3, 2, 2);
    print(outputs);
    return 0;
}
