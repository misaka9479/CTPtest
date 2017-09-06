#include "stdafx.h"
#include "TradeApi.h"
#include "ThostFtdcTraderApi.h"
#include"ThostFtdcMdApi.h"

#pragma comment(lib,"thostmduserapi.lib")
#pragma comment(lib,"thosttraderapi.lib")

using namespace std;

int main()
{
	auto api = CThostFtdcTraderApi::CreateFtdcTraderApi("./trade_con/");
	spi tdspi(api);
	api->RegisterSpi( &tdspi);
	api->RegisterFront("tcp://58.247.171.146:51205");
	api->SubscribePublicTopic(THOST_TERT_RESTART);
	api->SubscribePrivateTopic(THOST_TERT_RESTART);
	api->Init();
	api->Join();
    return 0;
}

