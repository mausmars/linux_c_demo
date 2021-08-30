#define SERVER_BATTLE

#ifndef COMMON_EVENT
#include "common_event.ice" 
#endif

#ifndef SERVER_MODEL
#include "server_model.ice"
#endif

//战场
module squarepro{
module battle{
    class CreateBattleRequest{
        int battleType;
        int battleKeyId;
        int battleSubType;                  //1=pvp; 2=pve
        squarepro::model::BattleTeamLList battleTeam;
    };

	//战场服务接口
	interface IBattleService{
		//创建一个战场（战场原型id，参与者id列表）
		["amd","ami"] void createBattle(CreateBattleRequest request);
	};
	
	//战场结果事件
	class BattleResultEvent extends squarepro::event::IEvent{
		long userId; 			        //用户id
		long battleId;			        //战场id
        int result;                     //0失败，1胜利，2平局
        int battleSubType;              //1=pvp; 2=pve
        int consumeTime;                //战场耗时
        int firstturn;                  //谁先手 1=我方，2=对方
        int matchType;                  //1=积分匹配（杯）2=竞技场

        squarepro::model::UserStatistics selfStatistics;  //自己用户统计信息
        squarepro::model::UserStatistics enemyStatistics; //对方用户统计信息

        int activityType;               // 活动类型
        long activityId;                // 活动id
	};
};
};
