# C++ Tips

In this chapter, I would like to share what I've learned about C++ as well as the questions that puzzled me before. I'm **definitely not** an expert in C++, instead, I'm a **newbie** who is eager to learn! Therefore, there might things not correct in what I've written, please feel free to contact me and let me know! 

Some of the contents are taken from the lecture notes when I was studying at UNSW or from other sources like blogs, forums, etc, I will put references to those contents if they are free to share. 

When I was studying at C++, we used **C++20 standard**, hence, don't be surprised if you see some C++20 features. However, most of the content is compatible with C++11 or newer.

## Concepts of Class

Class can represent concepts, such as **person**, **animal**, etc.

There are two generic relations in **Object Oriented Programming (OOP)**:

- **Composition**:

  - Relations between **data members**. 

  - For example, we can implement a class represents concept of complex numbers, then there can be two data members in the class, which represents the **imaginary part** and the **real part**. They make up the complex number: real + i * im. 

    ```c++
    class Complex {
    public:
    	double im; // imaginary part
        double re; // real part
    ...
    };
    ```

- **Inheritance**:

  - Relations between **classes**.

  - For example, we can implement a class to represent the concept of **animals**. However, **animals** are generic definitions, we can further derive it into smaller concepts such as **land animals**, etc. By doing, so we might encounter a situation to represent a concept of **dogs**. We can see, the way we reach **dogs** is through a **derivation**. We have a **parent** concept **of animals** and a child concept of the **dogs**. Dogs **are a subset of animals** and they have the **common attributes** that animals have. So we can say dogs **inherit** the attributes of animals. They have eyes, they can move, and so on, but they also have **unique attributes** that not all animals have, such as their vocalization is "wolf" instead of "meow". 

    ```c++
    class Animal {
    public:
    	void move(void){} 	// common attributes
        int neyes; 			
    ...
    };
    
    class Dog: public Animal {
    public:
        auto sound(void) const -> std::String {
            return std::String("Wolf");
        } 	// unique attributes
    };
    ```

The **Inheritance** feature in C++ looks awesome, it makes programming more natural and closer to our daily life. However, we need to fully understand the principles and rules under the hood to drive this powerful feature. Otherwise, we will scratching our head and figuring our why things not work as we expect!

![](/home/kukuku/Myreviews/lang/content/img/cpp-meme.jpeg) 

The following contents relate to the questions I've confronted when learning C++. 

### Constructors and Destructors

#### Exception Safety?

TODO

### Member functions?

TODO

#### Name Mangling

- Difference static vs non-static, scopes are different!
- Why  same function names doesn't conflict at linking satge?
  - name mangling! rules? _ZN6Method6methodEv
  - member functions vs normal functions?
    - member functions can be override! defined as weak symbols, but why?
    - virtual functions don't have symbols! 
- Stored where? Text sectors. `nm program | grep fun name`

## Memory Resources

### How big is my class?

One commonly asked question is what is the size of my **structure** and **class** in C++. In C++, structure and class are almost the same except for the default visibility. So let's have a look at how to calculate the size of a class. 

#### What if my class is empty?

```c++
// 1 byte
class Empty {  
};
```

An empty class takes one byte rather than zero bytes. This is because, classes internally are some data structures implemented by the compiler, and will be stored in the memory. Two different classes will have different virtual addresses. That's why they occupy one byte in the memory though they are empty classes. 

#### What if we consider the underlying architecture?

```c++
// considering the underlying architecture
class A {
public:
    long a;
};
```

How big is the above class? You may say 8 bytes! Really!? This might not be true. As we all know, normally our machine has 32 bits and 64 bits depending on the underlying CPU architecture. Nowadays, our laptops or desktops are usually 64 bits machines such as my Dell Inspiron 7590 armed with Intel Skylake+++++......But we also have 32 bits machine! The **long** type on 32 bits machine is **4 bytes** (see [C Data Types](https://en.wikipedia.org/wiki/C_data_types) for more details)! So be very careful about those architecture-dependent data types as well as pointers!

#### What if we consider alignment?

```c++
// considering the alignment
class A {
public:
    long a;
    char b;
};
```

In the above example, we see a char type member is below the long type member, let's assume we are using a 64-bit machine. Then how big is this class? You mat say 5 bytes without hesitation. But this is not always true! We need to consider compilers' behaviours as well. The compiler might **align** the data structure to maximize the optimization and improve performance (You can see more details on [Data structure alignment](https://en.wikipedia.org/wiki/Data_structure_alignment) and [Purpose of padding](https://stackoverflow.com/questions/119123/why-isnt-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member/119134#119134)).

To verify this let's see some more tests.

```c++
// alignment? The output are generated on my machine, might be diffrent on yours!

// 1 byte
class CharOnly {
public:
  char b;
};

// char after int, 8 bytes
// 8 bytes
class IntChar {
public:
  int a;
  char b;
};

// char before int
// 8 bytes
class CharInt {
public:
  char a;
  int b;
};

// char before long
// 16 bytes
class CharLong {
public:
  char a;
  long b;
};

// Int before long
// 16 bytes
class IntLong {
public:
  int a;
  long b;
};

// Int after long
// 16 bytes
class LongInt {
public:
  long a;
  int b;
};
```

On my machine, the compiler doesn't do an alignment to *CharOnly*, hence it's 1 byte only. But it will do an alignment to the other classes. No matter we place a char type member before or after the int type member. The compiler will align the data to a multiple of 4 bytes. While if we place char or int type before/after a long type member, the compiler will align the data to a multiple of 8 bytes.

#### What if we have member functions in class?

In C++, functions defined inside a class are called member functions. Those member functions can be **virtual** or **non-virtual**. And the non-virtual member functions can be **static** or **non-static**. Let's take a look at those.

```c++
// 1 byte
class Method {
public: 
  void method(void) {}
};

// 1 byte
class InlineMethod {
public: 
  inline void method(void) {}
};

// 1 byte
class StaticMethod {
public:
  static void static_method(void) {} 
};

// 8 bytes
class VirtualMethod {
public:
  virtual void method(void) {} 
};

// 8 bytes
class PureVirtualMethod {
public:
  virtual void method(void) = 0; 
};
```

In the above example, except for the member functions implemented as virtual functions or pure virtual functions, all other classes are 1 byte. If we are using virtual functions inside the class, then an **extra pointer to the class's vTable** will get stored as the first data member in the class to allow a dynamic binding at runtime. If the member functions are implemented just like normal functions then there will be **no vTables allocated**. The golden rules in C++, **you only pay for what you need**!

We will discuss how vTables resolve the current function to call at runtime in later sections. However, now lets into more details into C++'s compilers treat non-virtual member functions.

```cpp
// 1 byte
class Method {
public: 
  void method(void) {
    cout << "class method" << '\n';
  }
};

// 1 byte
class InlineMethod {
public: 
  inline void method(void) {
    cout << "inline class method" << '\n';
  }
};

// 1 byte
class StaticMethod {
public:
  static void static_method(void) {
    cout << "static class method" << '\n';
  } 
};

// 8 bytes
class VirtualMethod {
public:
  virtual void virtual_method(void) {} 
};

// 8 bytes
class PureVirtualMethod {
public:
  virtual void pure_virtual_method(void) = 0; 
};
```

##### Non-virtual member functions

In C++, both **non-static** and **static** member functions in the class **don't occupy** the memory space of that class. However, if we add a virtual keyword to those functions, then we must take the pointer to the **vTable** into account when we calculate the size of that class. To understand why member functions don't occupy the size of a class, we need to understand where how member functions operate under the hood.

##### How does member function work at assembly level?

Member functions are code, no matter how many instances of this class you created, there is no point to duplicate the code of member functions in a particular class. But when I was studying C++, I always think if we create an object (an instance of a class), then we invoke this object's member functions to retrieve some member data of this object, then how does the compiler know where is this object's member data stored?

```cpp
// memfun.cpp
class Age {
public:
    Age(int x): age_(x) {}
    
    int get_age() {
        return age_;
    }
  
private:
    int age_;
};

int main (void) {
    Age myage{25};
    std::cout << myage.get_age() << '\n';
    // you can imagine we invoke
    // get_age(&myage)
}
```

In C++, when we invoke the non-static member functions, the compiler will pass **this** pointer implicitly to the member function. That's the secret of how member functions access data members. Let's verify this using the above piece of code by inspecting the assembly code. We can use the `objdump` tool on Linux. 

```assembly
00000000000012ba <_ZN3Age7get_ageEv>:
    int get_age() {
    12ba:       f3 0f 1e fa             endbr64 
    12be:       55                      push   %rbp
    12bf:       48 89 e5                mov    %rsp,%rbp
    12c2:       48 89 7d f8             mov    %rdi,-0x8(%rbp)
        return age_;
    12c6:       48 8b 45 f8             mov    -0x8(%rbp),%rax
    12ca:       8b 00                   mov    (%rax),%eax
    }
    12cc:       5d                      pop    %rbp
    12cd:       c3                      ret    
    12ce:       66 90                   xchg   %ax,%ax

```

Above is the assembly code generated by the GNU c++ compiler. *rbp* and *rsp* are two registers manipulating stack on x86. We saw `mov %rdi,-0x8(%rbp)` stores a value in *rdi* to the stack, then finally this value gets copied to *eax* register. We don't dive deep into what those registers are and what is the calling convention of x86_64. If you are interested please see another article about x86_64 assembly (TODO ref). Here what we need to know is *eax* stores the return value. And the *rdi* stores the first argument of our *get_age()* function. However, we see there are no explicitly defined arguments in *get_age()*! The compiler implicitly generates one for us. Is **this** pointer pointing to the current object? Let's verify this using GDB!

```shell
# compile the code with non-optimizsation and with symbol information
>g++ -O0 -g ./memfun.cpp -o ./memfun
# run GDB
>gdb ./memfun
# set break point
>b get_age
# run the program
>r
# checkout the assembly view, as we want to see more details
>layout asm
# single step to execute each instruction until we reach `mov (%rax),%eax`
>si
...
# Now the rax contains the `this` pointer, as we only have one data member age_,
# the first element `this` pointer points to is the age_.
# If we print out the value pointed by `this`, we will see 25 as expected!
> p *(int *)$rax
```

##### Virtual member functions

In the previous example, we've seen that non-virtual member functions don't add extra size to the class, but if we are using virtual member functions, then an extra size of the pointer to a **vTable** will be added to the class. Lets look at an example.

```cpp
// vmemfun.cpp
#include <iostream>

class Age {
public:
    Age(int x): age_(x) {}

    int get_age() {
        // std::cout << "this points @" << this << '\n';
        // std::cout << "age_ is @" << &age_ << '\n';
        return age_;
    }

    virtual bool is_young() {
        return age_ < 25;
    }
  
private:
    int age_;
};

int main (void) {
    Age myage{25};
    std::cout << myage.get_age() << '\n';
}
```

 Here we add a virtual member function named *is_young()*, let's see what will change at assembly level.

```assembly
00000000000012c8 <_ZN3Age7get_ageEv>:
    int get_age() {
    12c8:       f3 0f 1e fa             endbr64 
    12cc:       55                      push   %rbp
    12cd:       48 89 e5                mov    %rsp,%rbp
    12d0:       48 89 7d f8             mov    %rdi,-0x8(%rbp)
        return age_;
    12d4:       48 8b 45 f8             mov    -0x8(%rbp),%rax
    12d8:       8b 40 08                mov    0x8(%rax),%eax # before was mov (%rax),%eax
    }
    12db:       5d                      pop    %rbp
    12dc:       c3                      ret    
    12dd:       90                      nop
```

 We see in the above assembly code, the main difference is to use **this** pointer to get `age_`, this time we do `mov 0x8(%rax),%eax` to add 8 bytes to **this** pointer to get the data member we want. That's because the compiler stored the **vTable** pointer as our first data member! Let's use GDB to verify this assumption.

```assembly
# compile the code with non-optimizsation and with symbol information
>g++ -O0 -g ./vmemfun.cpp -o ./vmemfun
# run GDB
>gdb ./vmemfun
# set break point
>b get_agesad
# run the program
>r
# let's see what is data structure the `this` pointer points to  
>p *this
# this = 0x7fffffffe1f0: {_vptr.Age = 0x555555557d78 <vtable for Age+16>,age_ = 25}
```

As we expected, the first data member is the **vTable** pointer! 

### What if we consider inheritance?

In C++, we can inherit from other classes, this feature will add a little bit difficulty when we try to calculate the size of the class. Let's take a look at the following example. 

```cpp
// 16 bytes
class Person {
public:
  virtual std::string occupation() {
    return std::string("Unknown occupation.\n");
  }
private:
  char* name_;
};

// 24 bytes
class Student : public Person {
public:
  std::string occupation() override {
    return std::string("Student.\n");
  }
    
  virtual int salary() {
      return 0;
  }
private:
  int id_;
};

// 24 bytes
class Tutor : public Student {
public:
  std::string occupation() override {
    return std::string("Student and tutor.\n");
  }
    
  int salary() override {
    return 60;
  }
};
```

In the above example, we have a basic class Person, and derived class Student and Tutor. On my machine, the size of the Person class is 16 bytes (8 bytes for the **vTable** pointer and 8 bytes for the char type pointer). And both the student class and the Tutor classes are 24 bytes (8 bytes for **the vTable** pointer, 8 bytes for char type pointer, 4 bytes for int, and 4 bytes for padding). We can see here, although we have two virtual member functions in both Student and Person classes, only one **vTable** is allocated.

Now let's add a little bit more complexity, what if we have a class that has multiple inheritances from other basic classes (also known as **Diamond inheritance**)?

```cpp
// 4 bytes
class A {
  int a;
};

// 8 bytes
class B: public A {
  int b;
};

// 8 bytes
class C: public A {
  int c;
};

// 20 bytes
class D: public B, C {
  int d;
};
```

On my machine, class A is 4 bytes and both class B and C are inherited from class A which have 8 bytes as expected. However, why class D is 20 bytes in total? That's because D is inherited from both B and C, and B and C are inherited from class A, according to C++'s rule, class A will be duplicated to separate the inheritance path! So 20 bytes is the size of B (4 bytes of b + 4 bytes of a) + the size of C (4 bytes of c + 4 bytes of a) + the size of D (4 bytes of d). To avoid such problems and ambiguity, we will use **the virtual** keyword to mark the inherited class (TODO see ref for more details)!

  ```cpp
  // 4 bytes
  class A {
    int a;
  };
  
  // 16 bytes
  class B: public A {
  public:
    virtual void fun_B() {}
  private:
    int b;
  };
  
  // 16 bytes
  class C: public A {
  public:
    virtual void fun_C() {}
  private:
    int c;
  };
  
  // 40 bytes
  class D: public B, C {
    int d;
  };
  ```

With this example, our D class becomes 40 bytes, This is because both B and C are 16 bytes due to padding, and since two separate class A will be generated, our class D will have 40 bytes (32 bytes for B and C + 4 bytes for c and padding 4 bytes).

Dimond inheritance is a tricky corner case, we will look at this in a later section (TODO See Ref)

## Visibility: public, protected or private?

TODO:

## Runtime Polymorphism 

- vtable layout: https://shaharmike.com/cpp/vtable-part2/

TODO:

- Dimond inheritance?
  - constructors?
  - virtual funcitions?
  - what if we have one two virtual functions with same names in two different inherited classes? How to resolve?
- polymorphism

## References