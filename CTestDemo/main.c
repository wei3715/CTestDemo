//
//  main.c
//  CTestDemo
//
//  Created by mac on 2018/8/3.
//  Copyright © 2018年 mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
struct student{
    int age;
    float height;
    char *name;
};

struct student1{
    int age;
    float height;
    char *name;
}s2 = {12,190,"smail"};//存放在全局区,在声明的时候进行初始化

struct{
    int age;
    float height;
    char *name;
}s3;
//匿名结构体，只能在声明的后面使用结构体变量s3

int main(int argc, const char * argv[]) {
     printf("***************************下面测试栈区，数据区（全局区，静态区，字符常量区），代码区内存*********************\n");
    //1.测试数据类型占的字节数
    void testType(void);
    testType();
    

    //2.测试栈区主要存放函数参数和局部变量
    void testStack(int a);
    testStack(5);
    
    //3.测试字符常量区
    void testCString(void);
    testCString();
    
    //4.测试函数指针
    //声明函数指针，名字pfunc-->返回值int，有两个int类型参数
    int (*pfunc)(int a,int b);
    int add(int,int);
    //函数指针指向函数首地址
    pfunc = add;
    //通过函数指针调用函数 (*pfunc)表示获取函数
    int a = (*pfunc)(12,12);
    printf("a==%d\n",a);
    
    //5.测试函数指针作为函数参数
    int mutiply(int (*func)(int,int),int n1,int n2);
    int b = mutiply(add,3,4);
    printf("b==%d\n",b);
    
    //6.指针函数：返回类型是指针类型的函数
    int *testPointerFunc(int a);
    int *p = testPointerFunc(100);// 执行完这句话,testPointerFunc里面的局部变量t就释放掉了，如果代码量不是很多的话，t可能释放掉了但是内容还在原来内存里存放着没有被占用，如果代码量多的话，可能这块内存就被占用了，这块内存里面存放的就不是t的值了。但是p指向的还是原来那块内存
   
    printf("p地址==%p，p内容==%d\n",p,*p); //这里按照原来的内存地址去取t值，如果t是局部变量，那么t在上句代码执行完就已经释放了，如果代码量很多，那么可能t释放之后，内存被占用就无法访问到t值了
    
    //7:这个只是对变量值得副本进行了交换，并没有改变原来内存存储的值
    //7.1值传递
    printf("************************************************值传递类型********************************************\n");
    void swap1 (int a, int b);
    int swapA = 5,swapB = 6;
    int *pointerA = &swapA,*pointerB = &swapB;
    printf("外部参数交换前指针变量（地址）pointerA==%p,pointerB==%p\n",pointerA,pointerB);
    swap1(swapA, swapB);
    printf("值传递类型函数外部交换后值swapA==%d，swapB==%d\n",swapA,swapB);
   
    
    //这个只是对指针变量的副本进行了交换，仍然没有改变原来内存存储的值
    printf("************************************************指针传递，仅交换指针值********************************************\n");
    void swap2 (int *a, int *b);
    swap2(pointerA, pointerB);
    printf("指针值交互函数外交换后变量值swapA==%d,swapB==%d\n",swapA,swapB);
    
    //7.2 指针（地址）传递参数
    //通过指针访问元内存内容，交换指针指向的内存内部的值，真正改变了原来内存存储的值
    printf("************************************************指针传递，交换指针指向的变量值********************************************\n");
    void swap3 (int *a, int *b);
    swap3(pointerA, pointerB);
    printf("指针地址传递类型函数外交换后变量值swapA==%d,swapB==%d\n",swapA,swapB);
    printf("*********************************************************************************************\n");
    //8.测试函数返回值
    //这里不存在问题：原因getNum0函数内的局部变量a，在函数返回后就没有再访问使用了
    int getNum0(void);
    int numResult0 = getNum0();
    printf("函数返回值==%d\n",numResult0);
    
    //返回指针会存在隐患问题：原因是在getNum1函数结束后，getNum1函数里的局部变量a已经标记为释放状态，但又在printf函数内访问局部变量a这块内存
    int *getNum1(void);
    int *numResult1 = getNum1(); //a内存已经释放
    printf("函数返回值==%d\n",*numResult1);
    
    //这样不存在问题的原因是：num1的生命周期不是在函数getNum2返回后就释放了，而是在main函数返回后才会释放
    int *getNum2(int *p);
    int num1 = 10;
    int *numResult2 = getNum2(&num1);
    printf("函数返回值==%d\n",*numResult2);
    
    //9.数组返回类型
    int *getArr(void);
    int *arrPointer = getArr();
    //arrPointer这个指针指向的是数组的首元素地址，*arrPointer表示解引用，取出首元素
    printf("数组返回类型，通过指针查看首元素值==%d\n",*arrPointer);
    
    //arrPointer+1表示偏移一个元素的地址（1表示一个元素的地址），这里数组存放值是int类型，所以偏移4个字节
    //*(arrPointer+1)表示解引用，取出对应值
    printf("数组返回类型，通过指针查看第二个元素值==%d\n",*(arrPointer+1));
    
    printf("************************************下面测试堆内存******************************\n");
    //1
    void testMalloc(void);
    testMalloc();
    
    //2
    void testCalloc(void);
    testCalloc();
    
    //3
//    void testRealloc(void);
//    testRealloc();
    
    //测试野指针1
    void testWildPointer01(void);
    testWildPointer01();
    
    //测试野指针2
    void testWildPointer02(void);
    testWildPointer02();
    
    //3:void
    void swapAll(void *p1,void*p2,int size);
//    int swapAllA = 10;
//    int swapAllB = 5;
//    swapAll(&swapAllA, &swapAllB, 4);
//    printf("函数外部交换后swapAllA==%d,swapAllA==%d\n",swapAllA,swapAllB);
    
    double swapAllA = 123.567;
    double swapAllB = 590.786;
    swapAll(&swapAllA, &swapAllB, 8);
    printf("函数外部交换后swapAllA==%lf,swapAllA==%lf\n",swapAllA,swapAllB);
    
    //测试结构体
    void testStruct(void);
    testStruct();
    
    s2.name = "willBe";
    printf("全局结构体变量s2.name = %s\n",s2.name);
    
    s3.name = "stronger";
    printf("匿名结构体s3.name = %s\n",s3.name);
    
    //测试结构体初始化
    void testInitStruct(void);
    testInitStruct();
    
    //结构体指针
    struct student *structPointer = NULL;
    struct student s4 = {17,180,"ku"};
    structPointer = &s4;
    
    //通过指针变量获取结构体里的数据可以直接 指针变量->height,
    printf("通过结构体指针访问 s4.name= %s,年龄==%d，身高==%f\n",(*structPointer).name,structPointer->age,structPointer->height);
    
    //测试把结构体放到堆内存上
    void testMallocStruct(void);
    testMallocStruct();
    
    //测试宏定义的使用
    void testDefine(void);
    testDefine();
    return 0;
}

/*******************************下面测试栈区，数据区（全局区，静态区，字符常量区），代码区内存************************/
//1.测试数据类型占的字节数
void testType(){
    printf("****************************************测试数据类型占的字节数*************************************\n");
    //数据类型占用的字节数和系统（64位，32位）是有关系的
    printf("char所占字节数 == %ld\n",sizeof(char));
    printf("short所占字节数 == %ld\n",sizeof(short));
    printf("int所占字节数 == %ld\n",sizeof(int));
    printf("long所占字节数 == %ld\n",sizeof(long));
    printf("float所占字节数 == %ld\n",sizeof(float));
    printf("double所占字节数 == %ld\n",sizeof(double));
    printf("long double所占字节数 == %ld\n",sizeof(long double));
    
    //-左对齐 %-7表示输出7位整数，左对齐
    printf("t=%-7d\n", 3);
    //默认右对齐，输出9位字符，保留两位小数
    printf("t=%9.2f\n",345.567);
    
}

//2.测试栈区主要存放函数参数和局部变量
//栈区：编译器自动分配释放内存。主要存放函数的参数值（a），局部变量值等（bb）；
void testStack(int a){
    printf("**********************************测试栈区主要存放函数参数和局部变量*****************************\n");
    int bb = 345;
    printf("a==%d,bb==%d\n",a,bb);
}

//3.测试字符常量区
void testCString(){
    printf("*******************************测试字符常量区**************************\n");
    //创建c语言“字符串”方式
    
    //1
    //会自动在后面添加结束标志/0
    char ch[] = "study";
    
    //2.
    //需要手动添加元素\0,否则打印乱码
//    char ch[] = {'s','t','u','d','y','\0'};
    
    //%s会根据首地址一直取到\0为止
    printf("ch==%s\n",ch);
    printf("ch长度==%ld\n",sizeof(ch));
    
    //3.通过指针，p变量存放在栈区，但是指向的字符常量内容存在字符常量区
    //把一个字符数组的第一个元素地址赋给了指针变量p
    char *p = "study";
    
    //%s会一直取到\0为止
    printf("p==%s\n",p);
    printf("p存放的地址==%p\n",p);
    
    
    void testCString01 (void);
    testCString01();
    //结论：发现g1的内存地址和p的内存地址完全一样！！！
    /*字符常量区的工作原理：创建一个字符串常量时，先从字符常量区查找看有没有相同内容的内存，会先去找有没有同样内容的字符串，有的话直接共用这块内存，没有的话再开辟新的内存放入变量值
    字符串常量是不可变的，一旦改变就会生成一个新的变量，开辟一个新的内存*/
    
   
    
    // t1是可变的局部变量，是存放在栈中的
    char t1[] = "study";
    t1[1] = 'h';
    printf("t1字符数组的首地址：%p\n",t1);
    printf("t1字符串==%s\n",t1);
    //结论：同样的内容，t1和p的内存地址是不同的，因为t1是“字符数组”，不是字符常量，ch是可以进行改变的
}

void testCString01 (){
    char *g1 = "study";
    printf("g1存放的地址==%p\n",g1);
}


//4.测试函数指针
int add (int a,int b){
    printf("*******************************测试函数指针**************************\n");
    return a+b;
}

//5.测试函数指针作为函数参数
int mutiply(int (*func)(int,int),int n1,int n2){
    printf("*******************************测试函数指针作为函数参数**************************\n");
   return (*func)(n1,n2)*n2;
}

//6.指针函数：返回类型是指针类型的函数
int t = 0;//这样声明的t，存放在全局区，全局区的变量在程序结束后，才会释放
int *testPointerFunc(int a){
    printf("***************************指针函数：返回类型是指针类型的函数***********************\n");
    //这里如果用局部变量t，局部变量存放在栈区，会有warning，原因：局部变量放到栈里面，函数执行完就释放。函数外面再引用就有可能有问题
    t = a+100;
    return &t;
}

//7.测试函数传递类型
//函数体内接收到的参数，是原参数的副本（值传递）
//交换的只是原参数另行拷贝的副本内存内容
void swap1 (int a, int b){
    printf("值传递类型函数内接收到的参数地址a==%p,b==%p\n",&a,&b);
    int temp = a;
    a = b;
    b = temp;
    printf("值传递类型函数内部交换后a==%d,b==%d\n",a,b);
}

//交换的只是原参数指针变量另行拷贝的副本内存内容
void swap2 (int *a, int *b){
    printf("函数内接收到的参数地址a==%p,b==%p\n",a,b);
    int *temp = a;
    a = b;
    b = temp;
    printf("函数内交换后变量值a==%d,b==%d\n",*a,*b);
}

//通过指针取出指针指向的内存变量值，真正交换指向的内容值
void swap3 (int *a, int *b){
    printf("函数内接收到的参数地址a==%p,b==%p\n",a,b);
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("函数内交换后变量内容a==%d,b==%d\n",*a,*b);
}

//8.函数返回值问题
int getNum0(){
    printf("*******************************测试函数返回值问题**************************\n");
    int a = 123;
    return a;  //返回的是a的副本值（对原来a的进行copy，上面那个a就交由栈管理释放，这个copy的值返回给函数）
    
}

//warning：Address of stack memory associated with local variable 'a' returned
//解决方法1：将a声明为全局变量，增长a的生命周期
//解决方法2：将a声明为静态变量（添加static修饰），增长a的生命周期（这样存放在栈里面的指针变量a就可以保证指向的是一块固定的内存，而不会随时可能释放）
//但是方法1，2 的解决方法，a要等到程序结束后才释放，生命周期过于长了，有点浪费内存
//如果非得要返回函数指针类型的话，可以用方法3
//解决方法3：直接传入指针变量类型

//也可以测试野指针情况3：返回一个存放在栈里的指针
int *getNum1(){
    static int a = 123;
    return &a; //出现一个野指针问题
    
}

int *getNum2(int *a){
    *a = 345;
    return a; //返回的是p1的副本--->但是指向是明确的，肯定指向345这个变量内存
    
}

//9.返回数组类型：
int *getArr(){
    static int arr[] = {12,345};
    return arr;
}

/***************************************************下面测试堆内存*************************************************/
// 1.测试Malloc
void testMalloc(){
    printf("*******************************测试Malloc*************************\n");
    //p指针在栈里面
    //malloc开辟的内存在堆里面
    //malloc没有对开辟的内存进行清0 处理
    int *p0 = malloc(sizeof(int)); //如果不释放，会导致内存泄漏
    if (p0!=NULL) {//保证p在指向一块开辟成功的堆内存
        //给指向的堆里面的值赋值
        printf("malloc未赋值前*p0==%d\n",*p0);
        *p0 = 234;
    } else {
        exit(1);
    }
    
    printf("malloc赋值后*p0==%d\n",*p0);
    
    free(p0);//释放内存
    p0 = NULL;//如果不赋值NULL（给指针变量清零），那么可能导致野指针存在
}

//2.测试Calloc
void testCalloc(){
    printf("*******************************测试Calloc*************************\n");
    //calloc会对分配的内存进行清0处理
    //int t[5]
    int *p1 = calloc(5, sizeof(int));//分配五个int类型的字节数的内存（5*4=20字节）
    if (p1!=NULL) {
        for (int i = 0; i<5; i++) {
            printf("calloc未赋值前t[%d]=%d\n",i,*(p1+i));
            *(p1+i) = i+2; //初始化i+2
        }
        for (int i = 0; i<5; i++) {
            printf("calloc赋值后变量值t[%d]=%d\n",i,*(p1+i));
        }
        free(p1);
        p1 = NULL;
    } else {
        exit(1);
    }
    
}

//3.测试realloc，不安全函数，放弃测试
void testRealloc(){
    printf("*******************************测试realloc*************************\n");
    int *p2 = malloc(5*sizeof(int));//分配五个int类型的字节数的内存（5*4=20字节）
    if (p2!=NULL) {
        for (int i = 0; i<5; i++) {
            *(p2+i) = i+2; //初始化i+2
        }
        for (int i = 5; i<10; i++) {
            *(p2+i) = i+5; //初始化i+2
        }
        
        printf("原来内存地址p2==%p\n",p2);
        int  *newP = realloc(p2, 10);
        printf("扩大内存后地址newP==%p\n",newP);
        if (newP!=NULL) {//分配成功
           
            for (int i = 0; i<10; i++) {
                printf("realloc赋值后变量值t[%d]=%d\n",i,*(newP+i));
            }
            
            free(newP);
            p2 = NULL;//(realloc会负责原来指针p的释放，所以不用free(p)),但是要清零，防止野指针存在
            newP = NULL;
        } else {
            p2 = newP;
            free(p2);
            p2 = NULL;
            printf("扩展内存失败");
            exit(1);
        }
        
        
        
 
    } else {
        exit(1);
    }
    
   
    
}

//4.1 测试野指针1
void testWildPointer01(){
    printf("*******************************测试野指针1*************************\n");
    int *p3 = malloc(sizeof(int));
    *p3 = 123;
    //释放的是p指向的堆内存：将malloc开辟的这块内存标记为“释放”，表示别的程序可以使用这块内存了，但并不一定是马上释放，程序代码多时可能占用这块内存，程序代码不多那么这块内存内容依然存在
    //但是p指针值还是原来那个值，还是指向原来的内存位置
    free(p3); //释放不代表p指向NULL
    
    //解决野指针方法(释放掉p指向的内存后，将p指针置为空，让p不再指向任何内存)
    p3 = NULL;
    
    if (p3!=NULL) {//这样根本防止不了野指针
        *p3 = 456; //p-->野指针
        printf("释放指针后仍使用，*p3==%d\n",*p3);
    }

}

//4.2 测试野指针2
void testWildPointer02(){
    printf("*******************************测试野指针2*************************\n");
    //未初始化的指针不可以使用
    int *p4;
    //初始化为不指向任何内存，然后直接赋值也是错误的
//    int *p4 = NULL;
    
    p4 = malloc(sizeof(int));
    //会有警告：Variable 'p2' is uninitialized when used here
    if (p4!=NULL) {
        *p4 = 123;
        printf("未初始化就是用指针p造成野指针出现的情况，*p4==%d\n",*p4);
        
        free(p4);
        p4 = NULL;
    } else {
        exit(1);
    }
}

//void 指针实现通用的交换方式(和oc里面id类型比较像)
void swapAll(void *p1,void*p2,int size){
    double temp;
    
    //因为char只占用一个字节的内存，所以可以拆分所有的数据类型，一个一个字节单元进行数据转化
    char *changeP1 = (char*)p1;
    char *changeP2 = (char*)p2;
    for (int i = 0; i<size; i++) {
       
        temp = *changeP1;
        *changeP1 = *changeP2;
        *changeP2 = temp;
        
        ++changeP1;
        ++changeP2;
    }
//    printf("函数内部交换后*changeP1==%d,*changeP2==%d\n",*p1,*p2);
    
}

//结构体
void testStruct(){
    printf("*******************************测试结构体*************************\n");
    //s1局部变量存放在栈区
    struct student s1;
    s1.age = 18;
    s1.name = "zww";
    s1.height = 170.0;
    printf("学生结构体name内存字节数==%lu，s1.name==%s\n",sizeof(s1.name),s1.name);
}

//结构体变量初始化
void testInitStruct(){
    struct student s1 = {18,172,"smail"};
    printf("初始化学生结构体s1.name==%s\n",s1.name);
}

//把结构体放入堆里面
void testMallocStruct(){
    struct student *s5 = NULL;
    s5 = malloc(sizeof(struct student));
    if (s5!=NULL) {
        s5->height = 234.0;
        (*s5).name = "haha";
        printf("放入堆中的结构体所占字节数==%lu,s3.height==%f\n",sizeof(struct student),s5->height);
        free(s5);
        s5 = NULL;
        
    }else {
        exit(1);
    }
}

//宏定义：在我们程序预处理阶段进行一个替换
#define PI 3.1415926

//取消某个宏定义
//#undef PI
#define NAME "ZWW"

//含参
#define sum(a,b) a+b
#define MAX(a,b) ((a)>(b)?(a):(b))

//特殊标志符:
//参数名前加上#做字符串处理
#define String(a) #a

// ##：字符串连接符
#define MyFunc(name) void name##Init(void);

// \:行连接符
#define HelloGirl(name) void name##Func(void){ \
 \
 printf("测试反斜杠行连接符的使用\n"); \
}

//声明一个函数
MyFunc(person)
//实现
void personInit(){
    printf("测试##字符串连接符\n");
}

HelloGirl(zww)

//测试宏定义
void testDefine(){
    printf("*******************************测试宏定义*************************\n");
    printf("标准c语言自带“行数宏”==%d\n",__LINE__);
    printf("标准c语言自带“文件名宏”==%s\n",__FILE__);
    printf("标准c语言自带“日期宏”==%s\n",__DATE__);
    printf("自定义宏PI==%f, NAME==%s\n",PI,NAME);
    printf("自定义含参数宏sum(a,b)==%d, MAX(a,b)==%f\n",sum(10, 20),MAX(37.8, 2.34));
    
    printf("使用#，不用使用双引号修饰参数==%s\n",String(haha)); //不用String("haha")
    personInit();
    zwwFunc();
}

//测试编译
void testGCCCompile(){
     printf("*******************************测试编译个阶段（第20讲文件夹）*************************\n");
    /**
     xcode只是一个人性化的编辑代码工具
     主要通过终端命令行的形式来验证GCC预编译-编译-汇编-连接等各过程生成的文件
     gcc -v 查看gcc的版本号，看是否已安装gcc
     1.vi hello.c  //编辑文件
     2.点击i进入输入模式
     #include <stdio.h>
     int main(int argv, const char * argc[]){
     printf("hello gcc!\n");
     return 0;
     }
     
     3.查看 cat hello.c
     3.1带有代码行的查看方式： cat -n hello.c
     4 执行 ./hello
     
     预编译阶段（处理宏定义指令（替换），条件编译指令，头文件包含指令）
     一步到位的编译指令（将原文件直接输出一个可执行文件）：
     1.1命令行： gcc hello.c -o hello
     会生成hello.c 的可执行文件hello
     
     一：第一步预处理指令（生成预处理文件）
     命令行： gcc - E hello.c -o hello.i
     会生成hello.c 对应的预处理文件 hello.i
     查看某个函数的过滤命令行：（grep是搜索含有关键字printf的意思）
     cat -n hello.i | grep printf
     
     二：编译（生成汇编代码,一些指令集合）
     命令行：
     gcc - S hello.i -o hell.s
     
     我们C语言编译好的文件，运行时变量，代码等占用不同的内存分区，这个内存分区的决定就在我们编译好生成的这个汇编里面的指令划分一个段，比如有代码段，数据段，堆栈段、主要由我们汇编语言指令决定
     
     三：汇编（生成输出文件，把汇编代码翻译成机器码0101）

     命令行：
     gcc -c hello.s -o hello.o
     
     四：连接器(把汇编器输出的很多文件和需要的库文件连接成一个文件)
     命令行：
     gcc hello.o -o hello
     
     */
}
