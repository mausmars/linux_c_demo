#define COMMON_BASETYPE

//这个定义了基本的集合类型，避免多次定义数据结构
module squarepro{
module basetype{
		//----------------------------
		//基本类型Wrap包装，用于基本类型的com.zeroc.Ice.Object的传递
		class ByteWrap{
			byte value;
		};
		class ShortWrap{
			short value;
		};
		class IntWrap{
			int value;
		};
		class LongWrap{
			long value;
		};
		class FloatWrap{
			float value;
		};
		class DoubleWrap{
			double value;
		};
		class StringWrap{
			string value;
		};
		//----------------------------
		//数组类型
		sequence<byte> ByteArray;
		sequence<short> ShortArray;
		sequence<int> IntArray;
		sequence<long> LongArray;
		sequence<float> FloatArray;
		sequence<double> DoubleArray;
		sequence<string> StringArray;
		
		//Object 数组 
		sequence<Object> Object1Array;
		sequence<Object*> ObjectPrx1Array;
		//-------------------------------------
		//LinkedList类型
		["java:type:java.util.LinkedList<Byte>"] sequence<byte> ByteLList;
		["java:type:java.util.LinkedList<Short>"] sequence<short> ShortLList;
		["java:type:java.util.LinkedList<Integer>"] sequence<int> IntLList;
		["java:type:java.util.LinkedList<Long>"] sequence<long> LongLList;
		["java:type:java.util.LinkedList<Float>"] sequence<float> FloatLList;
		["java:type:java.util.LinkedList<Double>"] sequence<double> DoubleLList;
		["java:type:java.util.LinkedList<String>"] sequence<string> StringLList;
		["java:type:java.util.LinkedList<com.zeroc.Ice.Value>"] sequence<Object> ObjectLList;
		["java:type:java.util.LinkedList<com.zeroc.Ice.ObjectPrx>"] sequence<Object*> ObjectPrxLList;
		//-------------------------------------
		//ArrayList类型
		["java:type:java.util.ArrayList<Byte>"] sequence<byte> ByteAList;
		["java:type:java.util.ArrayList<Short>"] sequence<short> ShortAList;
		["java:type:java.util.ArrayList<Integer>"] sequence<int> IntAList;
		["java:type:java.util.ArrayList<Long>"] sequence<long> LongAList;
		["java:type:java.util.ArrayList<Float>"] sequence<float> FloatAList;
		["java:type:java.util.ArrayList<Double>"] sequence<double> DoubleAList;
		["java:type:java.util.ArrayList<String>"] sequence<string> StringAList;
		["java:type:java.util.ArrayList<com.zeroc.Ice.Value>"] sequence<Object> ObjectAList;
		["java:type:java.util.ArrayList<com.zeroc.Ice.ObjectPrx>"] sequence<Object*> ObjectPrxAList;
		//-------------------------------------
		//HashMap类型
		dictionary<string, Object> StringObjectHMap;
		dictionary<int, Object> IntObjectHMap;
		dictionary<long, Object> LongObjectHMap;
		
		dictionary<string, Object*> StringObjectPrxHMap;
		dictionary<int, Object*> IntObjectPrxHMap;
		dictionary<long, Object*> LongObjectPrxHMap;
		//-------------------------------------
		//ConcurrentHashMap类型
		["java:type:java.util.concurrent.ConcurrentHashMap<String,com.zeroc.Ice.Value>:java.util.Map<String, com.zeroc.Ice.Value>"] dictionary<string, Object> StringObjectCMap;
		["java:type:java.util.concurrent.ConcurrentHashMap<Long,com.zeroc.Ice.Value>:java.util.Map<Long, com.zeroc.Ice.Value>"] dictionary<long, Object> LongObjectCMap;
		["java:type:java.util.concurrent.ConcurrentHashMap<Integer,com.zeroc.Ice.Value>:java.util.Map<Integer, com.zeroc.Ice.Value>"] dictionary<int, Object> IntObjectCMap;
		
		["java:type:java.util.concurrent.ConcurrentHashMap<String,com.zeroc.Ice.ObjectPrx>:java.util.Map<String, com.zeroc.Ice.ObjectPrx>"] dictionary<string, Object*> StringObjectPrxCMap;
		["java:type:java.util.concurrent.ConcurrentHashMap<Long,com.zeroc.Ice.ObjectPrx>:java.util.Map<Long, com.zeroc.Ice.ObjectPrx>"] dictionary<long, Object*> LongObjectPrxCMap;
		["java:type:java.util.concurrent.ConcurrentHashMap<Integer,com.zeroc.Ice.ObjectPrx>:java.util.Map<Integer, com.zeroc.Ice.ObjectPrx>"] dictionary<int, Object*> IntObjectPrxCMap;
		//-------------------------------------
};
};
