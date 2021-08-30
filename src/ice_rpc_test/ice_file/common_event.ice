#define COMMON_EVENT

//每个单独的服务器有要这个这个接口，用作服务器间的响应
module squarepro{
module event{
	//事件接口
	class IEvent{
	};
	
	////每个单独的服务器有要这个这个接口，用作服务器间的响应
	interface IEventService {
		["amd","ami"]void handle(IEvent event);//处理事件接口
	};
	
};
};