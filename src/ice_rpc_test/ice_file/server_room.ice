#define SERVER_ROOM

#ifndef COMMON_BASETYPE
#include "common_basetype.ice"
#endif

#ifndef COMMON_EVENT
#include "common_event.ice"
#endif

#ifndef SERVER_MODEL
#include "server_model.ice"
#endif

module squarepro{
module room{
	class MatchupRequest{
        squarepro::model::UserTroop userTroop;
	};

	//房间服务接口
	interface IRoomService{
		["amd","ami"] void matchup(MatchupRequest request);  // 匹配战场
		["amd","ami"] void cancelMatchup(long userId);       // 取消匹配
	};

    //房间匹配成功事件
	class MatchRoomSucceedEvent extends squarepro::event::IEvent{
		long userId; 			                // 用户id
		long battleId;						    // 战场id
		string host;						    // 战场服host
		int port;							    // 战场服端口
		string nodeId;							// 节点id
        string battleUserToken;                 // 战场验证码
        int battleSubType;                      //1=pvp; 2=pve
        int matchType;
        //日志相关
        squarepro::model::UserStatistics selfStatistics;  //自己用户统计信息
        squarepro::model::UserStatistics enemyStatistics; //对方用户统计信息

        int activityType;               // 活动类型
        long activityId;                // 活动id
	};
};
};