import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class MallocTest2 {
    private static MemoryDemo memoryDemo;

    static {
        memoryDemo = new MemoryDemo();
    }

    public static void main(String[] args) {
        boolean isRun = true;
        int size = 444;  //10m

        int n = 1;
        List<Long> addresses = new LinkedList();

        String readme = "---------------------------------------------\n" +
                "0:结束\n" +
                "1:malloc 创建内存\n" +
                "2:free 回收\n";
        try {

            System.out.println("创建内存");
            for (int i = 0; i < n; i++) {
                long address = memoryDemo.jmalloc(size);
                addresses.add(address);
            }
            System.out.println("当前内存大小 size=" + addresses.size() + "m");
            Thread.sleep(1000);

            System.out.println("回收全部内存");
            for (long addr : addresses) {
                memoryDemo.jfree(addr);
            }
            addresses.clear();
        } catch (OutOfMemoryError ex) {
            System.err.println(ex);
            ex.printStackTrace();
        } catch (Exception ex) {
            System.err.println(ex);
            ex.printStackTrace();
        }
    }
}
