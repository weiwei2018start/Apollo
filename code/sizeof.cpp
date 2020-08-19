// 计算某个类型的占字节数

int ssizeof() {
    double str[2];
    int ret = (char*)(&str[1]) - (char*)(&str[0]);
    
    return ret;
}

template <typename T>
int sizeOf(const T &t){
    return (char*)(&t+1)-(char*)&t;
}

int main() {
    
    cout << ssizeof() << endl;
    double a;
    cout << sizeOf(a) << endl;
    cout << "double type:" << sizeof(double) << endl;
    
    
    return 0;
}


