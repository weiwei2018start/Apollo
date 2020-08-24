//
//  main.cpp
//  HelloWorld1
//
//  Created by skyplan on 2020/6/30.
//  Copyright © 2020 skyplan. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <stdio.h>
using namespace std;

/*
 
 参考文章： https://www.cnblogs.com/WindSun/p/11444429.html
 C++11智能指针介绍
 智能指针主要用于管理在堆上分配的内存，它将普通的指针封装为一个栈对象。当栈对象的生存周期结束后，会在析构函数中释放掉申请的内存，从而防止内存泄漏。C++ 11中最常用的智能指针类型为shared_ptr,它采用引用计数的方法，记录当前内存资源被多少个智能指针引用。该引用计数的内存在堆上分配。当新增一个时引用计数加1，当过期时引用计数减一。只有引用计数为0时，智能指针才会自动释放引用的内存资源。对shared_ptr进行初始化时不能将一个普通指针直接赋值给智能指针，因为一个是指针，一个是类。可以通过make_shared函数或者通过构造函数传入普通指针。并可以通过get函数获得普通指针。

 为什么要使用智能指针
 智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域是，类会自动调用析构函数，析构函数会自动释放资源。所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手动释放内存空间。
 */


/**
 
 */
void test_unique_ptr() {
    unique_ptr<string> p1 (new string ("test"));   //#4
    unique_ptr<string> p2;                    //#5
    //p2 = p1;//编译代码，此时会报错！
    
    unique_ptr<string> p3;
    p3 = unique_ptr<string>(new string("hello"));
    cout << *p3 << endl;
    
    p2  = move(p1);
    cout << "p2:" << *p2 << endl;
//    cout << " p1:" << *p1 << endl;  运行崩溃
}

/**
 shared_ptr实现共享式拥有概念。多个智能指针可以指向相同对象，该对象和其相关资源会在“最后一个引用被销毁”时候释放。从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数use_count()来查看资源的所有者个数。除了可以通过new来构造，还可以通过传入auto_ptr, unique_ptr,weak_ptr来构造。当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。

 shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的), 在使用引用计数的机制上提供了可以共享所有权的智能指针。

 成员函数：

 use_count 返回引用计数的个数

 unique 返回是否是独占所有权( use_count 为 1)

 swap 交换两个 shared_ptr 对象(即交换所拥有的对象)

 reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少

 get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.如
 */
void test_shared_ptr() {
    string *s1 = new string("s1");
    shared_ptr<string> ps1(s1);
    shared_ptr<string> ps2(s1);
    ps2 = ps1;
    
    cout << ps1.use_count() << endl;    //2
    cout << ps2.use_count() << endl;    //2
    cout << ps1.unique() << endl;    //0
    
    string *s3 = new string("s3");
    shared_ptr<string> ps3(s3);
    
    cout << (ps1.get()) << endl;    //033AEB48
    cout << ps3.get() << endl;    //033B2C50
    swap(ps1, ps3);    //交换所拥有的对象
    cout << (ps1.get())<<endl;    //033B2C50
    cout << ps3.get() << endl;    //033AEB48
    
    cout << ps1.use_count()<<endl;    //1
    cout << ps2.use_count() << endl;    //2
    ps2 = ps1;
    cout << ps1.use_count()<<endl;    //2
    cout << ps2.use_count() << endl;    //2
    ps1.reset();    //放弃ps1的拥有权，引用计数的减少
    cout << ps1.use_count()<<endl;    //0
    cout << ps2.use_count()<<endl;    //1
}

/*
 share_ptr虽然已经很好用了，但是有一点share_ptr智能指针还是有内存泄露的情况，当两个对象相互使用一个shared_ptr成员变量指向对方，会造成循环引用，使引用计数失效，从而导致内存泄漏。

 weak_ptr 是一种不控制对象生命周期的智能指针, 它指向一个 shared_ptr 管理的对象. 进行该对象的内存管理的是那个强引用的shared_ptr， weak_ptr只是提供了对管理对象的一个访问手段。weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。
 */

class B;    //声明
class A
{
public:
    shared_ptr<B> pb_;
    ~A()
    {
        cout << "A delete\n";
    }
};

class B
{
public:
    shared_ptr<A> pa_;
    ~B()
    {
        cout << "B delete\n";
    }
};

void test_weak_ptr() {
    shared_ptr<B> pb(new B());
    shared_ptr<A> pa(new A());
    cout << pb.use_count() << endl;    //1
    cout << pa.use_count() << endl;    //1
    pb->pa_ = pa;
    pa->pb_ = pb;
    cout << pb.use_count() << endl;    //2
    cout << pa.use_count() << endl;    //2
}

int main() {
    //test_unique_ptr();
//    test_shared_ptr();
    
    test_weak_ptr();
    
    return 0;
}

