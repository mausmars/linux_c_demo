==================================================
执行顺序说明
#生成class
$ javac MemoryDemo.java

#生成 .h文件
$ javah MemoryDemo

实现.c文件

#生成HelloWorld.o文件
$ gcc -fPIC -I $JAVA_HOME/include -I $JAVA_HOME/include/linux -c MemoryDemo.c

#动态库名字 memorydemo。生成 libmemorydemo.so.1.0 动态库文件
$ gcc -shared -Wl,-soname,libmemorydemo.so.1  -o libmemorydemo.so.1.0 MemoryDemo.o

$ cp libmemorydemo.so.1.0 libmemorydemo.so

#环境
$ export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH

编译添加 -XDignore.symbol.file 解决Unsafe问题
#执行
javac -XDignore.symbol.file Main.java
java Main


=============================
Java类型	本地类型	描述
boolean	jboolean	C/C++8位整型
byte	jbyte	C/C++带符号的8位整型
char	jchar	C/C++无符号的16位整型
short	jshort	C/C++带符号的16位整型
int	jint	C/C++带符号的32位整型
long	jlong	C/C++带符号的64位整型e
float	jfloat	C/C++32位浮点型
double	jdouble	C/C++64位浮点型
Object	jobject	任何Java对象，或者没有对应java类型的对象
Class	jclass	Class对象
String	jstring	字符串对象
Object[]	jobjectArray	任何对象的数组
boolean[]	jbooleanArray	布尔型数组
byte[]	jbyteArray	比特型数组
char[]	jcharArray	字符型数组
short[]	jshortArray	短整型数组
int[]	jintArray	整型数组
long[]	jlongArray	长整型数组
float[]	jfloatArray	浮点型数组
double[]	jdoubleArray	双浮点型数组