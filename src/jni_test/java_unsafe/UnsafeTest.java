import sun.misc.Unsafe;

import java.lang.reflect.Field;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

//https://www.yasinshaw.com/articles/59

/**
 * gradle
 * <p>
 * compileJava{
 * options.encoding = "UTF-8"
 * <p>
 * options.compilerArgs << '-XDignore.symbol.file'
 * options.fork = true // may not needed on 1.8
 * options.forkOptions.executable = 'javac' // may not needed on 1.8
 * }
 * <p>
 * 或
 * javac -XDignore.symbol.file UnsafeTest.java
 */

public class UnsafeTest {
    private static Unsafe unsafe;

    static {
        unsafe = Unsafe();
    }

    private static Unsafe Unsafe() {
        try {
            Field field = Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            return (Unsafe) field.get(null);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void printData(long address, int size) {
        for (int i = 0; i < size; i += 8) {
            byte v = unsafe.getByte(address + i);
            System.out.print(v + ",");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        boolean isRun = true;
        int size = 1 * 1024 * 1024;  //1m

        int n = 50;
        List<Long> addresses = new LinkedList();

        String readme = "---------------------------------------------\n" +
                "0:结束\n" +
                "1:创建内存\n" +
                "2:回收\n";
        try {
            for (; isRun; ) {
                System.out.println(readme);
                Scanner input = new Scanner(System.in);
                int num = input.nextInt();
                switch (num) {
                    case 0:
                        isRun = false;
                        break;
                    case 1:
                        System.out.println("创建内存");
                        for (int i = 0; i < n; i++) {
                            long address = unsafe.allocateMemory(size);
                            unsafe.setMemory(address, size, (byte) 0);
                            addresses.add(address);
                        }
                        System.out.println("当前内存大小 size=" + addresses.size() + "m");
                        break;
                    case 2:
                        System.out.println("回收全部内存");
                        for (long addr : addresses) {
                            unsafe.freeMemory(addr);
                        }
                        addresses.clear();
                        break;
                    default:
                        break;
                }
            }
        } catch (OutOfMemoryError ex) {
            System.err.println(ex);
            ex.printStackTrace();
        } catch (Exception ex) {
            System.err.println(ex);
            ex.printStackTrace();
        }
    }
}
