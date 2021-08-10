import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class MallocTest {
    private static MemoryDemo memoryDemo;

    static {
        memoryDemo = new MemoryDemo();
    }

    public static void main(String[] args) {
        boolean isRun = true;
         int count=1;
        int size = count * 1024 * 1024;  //count*1m

        int n = 1;
        List<Long> addresses = new LinkedList();

        String readme = "---------------------------------------------\n" +
                "0:结束\n" +
                "1:malloc创建内存 并造成野指针\n" +
                "2:malloc创建内存 不造成野指针\n" +
                "3:free 回收\n";
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
                        System.out.println("创建内存 并造成野指针");
                        for (int i = 0; i < n; i++) {
                            memoryDemo.jmalloc(size);
                            //long address = memoryDemo.jmalloc(size);
                            //addresses.add(address);
                        }
                        System.out.println("当前内存大小 size=" + addresses.size() * count * n + "m");
                        break;
                    case 2:
                        System.out.println("创建内存 不造成野指针");
                        for (int i = 0; i < n; i++) {
                            long address = memoryDemo.jmalloc(size);
                            addresses.add(address);
                        }
                        System.out.println("当前内存大小 size=" + addresses.size() * count * n + "m");
                        break;
                    case 3:
                        System.out.println("回收全部内存");
                        for (long addr : addresses) {
                            memoryDemo.jfree(addr);
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
