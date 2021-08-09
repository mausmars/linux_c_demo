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
        int size = 10 * 1024 * 1024;  //10m

        int n = 5;
        List<Long> addresses = new LinkedList();

        String readme = "---------------------------------------------\n" +
                "0:结束\n" +
                "1:malloc 创建内存\n" +
                "2:free 回收\n";
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
                            long address = memoryDemo.jmalloc(size);
                            addresses.add(address);
                        }
                        System.out.println("当前内存大小 size=" + addresses.size() + "m");
                        break;
                    case 2:
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
