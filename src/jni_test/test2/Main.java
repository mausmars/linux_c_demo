import sun.misc.Unsafe;
import java.lang.reflect.Field;

public class Main {
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

    public static void main(String[] args){
        int size = 64; //64字节

        MemoryDemo test = new MemoryDemo();
        long addr = test.jmalloc(size);
        System.out.println("c point addr = "+addr);

        Unsafe unsafe = Unsafe();
        for (int i = 0; i < size; i += 8) {
            byte v = unsafe.getByte(addr + i);
            System.out.print(v + ",");
        }
        System.out.println();

        test.jfree(addr);
    }
}