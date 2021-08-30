#define COMMON_GM

#ifndef COMMON_BASETYPE
#include "common_basetype.ice" 
#endif

module squarepro{
module gm{

    //事件接口
    class GmLuaPayloadRequest{
        string luaPayload;
        string scriptType; // luaj groovy
    };


	//执行接口
	interface IGmService{
		["amd","ami"] string luaEvaluate(GmLuaPayloadRequest request);  //执行lua
	};

};
};