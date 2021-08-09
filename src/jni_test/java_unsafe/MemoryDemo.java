public class MemoryDemo {
    static {
		// c动态库名字
		System.loadLibrary("memorydemo");
	}

	public native long jmalloc(int size);

	public native void jfree(long point);
}