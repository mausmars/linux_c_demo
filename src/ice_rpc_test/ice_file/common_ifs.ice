#define COMMON_IFS

module squarepro{
module ifs{
	class HostInfo{
		string host;	// 主机
		int port;		// 端口
	};

	interface ICommonService {
		["amd","ami"]HostInfo getServiceHostInfo(string serviceId); //获取服务端口
	};
	
};
};