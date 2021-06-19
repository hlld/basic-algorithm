#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int splitstr_c(int argc, char* argv[])
{
    int num[100], cnt = 0;
    char buf[100], *p = NULL;
    // read single line
    while (gets(buf) != NULL) {
        p = strtok(buf, " ");
        if (!p) {
            break;
        }
        num[cnt++] = atoi(p);
        while ((p = strtok(NULL, " ")) != NULL) {
            num[cnt++] = atoi(p);
        }
    }
    for (int k = 0; k < cnt; k++) {
        printf("%d ", num[k]);
    }
    printf("\n");
    return 0;
}

int splitstr_cpp(int argc, char* argv[])
{
    int num[100], cnt = 0;
    string str, tmp;
    // read single line
    while (getline(cin, str)) {
        if (!str.size()) {
            break;
        }
        istringstream iss(str);
        while (getline(iss, tmp, ' ')) {
            num[cnt++] = atoi(tmp.c_str());
        }
    }
    for (int k = 0; k < cnt; k++) {
        printf("%d ", num[k]);
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
    return splitstr_cpp(argc, argv);
}
