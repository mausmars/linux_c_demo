#define SERVER_MODEL

#ifndef COMMON_BASETYPE
#include "common_basetype.ice"
#endif

module squarepro{
module model{
    class UserTroop;
    class UserHero;
    class BattleTeam;
    ["java:type:java.util.LinkedList<UserTroop>"] sequence<UserTroop> UserTroopLList;
    ["java:type:java.util.LinkedList<UserHero>"] sequence<UserHero> UserHeroLList;
	["java:type:java.util.LinkedList<BattleTeam>"] sequence<BattleTeam> BattleTeamLList;

    class UserHero{
        int hid;        // 英雄id
        int level;      // 英雄等级
    };

    class MatchParams{
        int matchPoolId;          // 匹配池id（对应PBMatchPool表id）
        int expectPoolId;         // 期望池(大池中的每个小池)
        int matchBattleType;      // 战场类型（1普通，101活动1,102活动2,103活动3,99新手数据）

        int arenaScore;           // 奖杯数
        //1竞技场匹配参数
        int winCount;             // 胜场数
        int failCount;            // 负场数
        //int botLeaderLevel;     // 机器人等级
        //squarepro::basetype::IntAList botHeroLevels; // 机器人英雄等级
        bool botFixedName;        // 是否固定机器人名字

        bool onlyBot;             // 该字段为测试或连败使用
        int correctDifficulty;    // 修正难度
        long activityId;          // 活动id
        int activityConfigId;     // 活动id

        string faceToken;         // 面对面匹配码
    };

	class UserTroop{
		long userId;                                // 用户id
		string name;                                // 用户名字
		string icon;                                // 用户头像
		int level;                                  // 用户等级
        int playerType;                             // 1 user; 2 npc
        int leaderId;                               // boss形象id
        int leaderSkill;                            // boss技能id
        UserHeroLList heros;                        // 出阵英雄id
        int difficulty;                             // 机器人难度
        string logicNodeId;                         // 逻辑服节点id
        MatchParams matchParams;                    // 匹配参数
	};

    //战斗列表
	class BattleInfo{
		string host;							//战场服host
		int port;								//战场服端口
		long battleId;				        	//战场id
	};

    class BattleTeam{
    	UserTroop userTroop;
    };

    //日志相关用户统计信息
    class UserStatistics{
        int round;           //记录到的回合数
        int eliminate;       //消除总数量
        int skill;           //消除技能棋子总数量
        int lordskill;       //我方使用主公技总次数

        int level;              //用户等级
        UserHeroLList heros;    //出阵英雄
        int arenaScore;         //奖杯数
        int difficulty;         //机器人难度
        int conwins;            //连胜数
    };
};
};



