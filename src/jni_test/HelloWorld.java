public class HelloWorld {
	public native void test1();

	public native TestBean test2(TestBean bean);

	static {
		// c动态库名字
		System.loadLibrary("helloworld");
	}

	public static void main(String[] args) {
		HelloWorld test = new HelloWorld();
		test.test1();

		TestBean testBean = new TestBean();
		testBean.setName("Test");
		testBean.setAge(111);

		testBean = test.test2(testBean);
		
		System.out.println("name=" + testBean.getName());
		System.out.println("age=" + testBean.getAge());
	}
}