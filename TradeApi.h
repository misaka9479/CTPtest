#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiStruct.h"

using namespace std;

class spi : public CThostFtdcTraderSpi
{
public:
	spi(CThostFtdcTraderApi *api) {
		this->api = api;
	}

	CThostFtdcTraderApi *api;

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	void OnFrontConnected(){
		cout << "连接成功[OnFrontConnected]" << endl;
		cout << "==============================" << endl;

		///登陆请求[OnRspUserLogin]
		CThostFtdcReqUserLoginField req;
		//memset(&req, 0, sizeof(req));
		//strcpy_s(req.BrokerID, "9999");
		//strcpy_s(req.UserID, "101327");
		//strcpy_s(req.Password, "ii1314520");
		memset(&req, 0, sizeof(req));
		strcpy_s(req.BrokerID, "4040");
		strcpy_s(req.UserID, "298295");
		strcpy_s(req.Password, "004156");
		api->ReqUserLogin(&req, 1);
		
	};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	void OnFrontDisconnected(int nReason){
		cout << "连接断开[OnFrontDisconnected]" << endl;
		cout << "==============================" << endl;
		switch (nReason)
		{
			case( 0x1001 ):
				cout << "网络读失败:" << nReason << endl;
				break;
			case( 0x1002 ):
				cout << "网络写失败:" << nReason << endl;
				break;
			case( 0x2001 ):
				cout << "接收心跳超时:" << nReason << endl;
				break;
			case( 0x2002 ):
				cout << "发送心跳失败:" << nReason << endl;
				break;
			case( 0x2003 ):
				cout << "收到错误报文:" << nReason << endl;
				break;
		}
	};
	
	///客户端认证响应
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "客户端认证响应[OnRspAuthenticate]" << endl;
		cout << "经纪公司代码:" << pRspAuthenticateField->BrokerID << endl;
		cout << "用户代码:" << pRspAuthenticateField->UserID << endl;
		cout << "用户端产品信息:" << pRspAuthenticateField->UserProductInfo << endl;
		cout << "==============================" << endl;
	};
	
	///登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "登录请求响应[OnRspUserLogin]" << endl;
		cout << "交易日:" << pRspUserLogin->TradingDay << endl;
		cout << "登录成功时间:" << pRspUserLogin->LoginTime << endl;
		cout << "经纪公司代码:" << pRspUserLogin->BrokerID << endl;
		cout << "用户代码:" << pRspUserLogin->UserID << endl;
		cout << "交易系统名称:" << pRspUserLogin->SystemName << endl;
		cout << "前置编号:" << pRspUserLogin->FrontID << endl;
		cout << "会话编号:" << pRspUserLogin->SessionID << endl;
		cout << "最大报单引用:" << pRspUserLogin->MaxOrderRef << endl;
		cout << "上期所时间:" << pRspUserLogin->SHFETime << endl;
		cout << "大商所时间:" << pRspUserLogin->DCETime << endl;
		cout << "郑商所时间;" << pRspUserLogin->CZCETime << endl;
		cout << "中金所时间;" << pRspUserLogin->FFEXTime << endl;
		cout << "能源中心时间:" << pRspUserLogin->INETime << endl;
		cout << "==============================" << endl;
		
		///
		CThostFtdcQrySettlementInfoField q;
		memset(&q, 0, sizeof(q));
		strcpy_s(q.BrokerID, "9999");
		strcpy_s(q.InvestorID, "101327");
		api->ReqQrySettlementInfo( &q, 1);

	};

	///登出请求响应
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "登出请求响应[OnRspUserLogout]" << endl;
		cout << "经纪公司代码:" << pUserLogout->BrokerID << endl;
		cout << "用户代码:" << pUserLogout->UserID << endl;
		cout << "==============================" << endl;

	};

	///用户口令更新请求响应
	void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金账户口令更新请求响应
	void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "报单录入请求响应[OnRspOrderInsert]" << endl;
		cout << "经纪公司代码:" << pInputOrder->BrokerID << endl;
		cout << "投资者代码:" << pInputOrder->InvestorID << endl;
		cout << "合约代码:" << pInputOrder->InstrumentID << endl;
		cout << "报单引用:" << pInputOrder->OrderRef << endl;
		cout << "用户代码:" << pInputOrder->UserID << endl;
		cout << "报单价格条件:" << pInputOrder->OrderPriceType << endl;
		cout << "买卖方向:" << pInputOrder->Direction << endl;
		cout << "组合开平标志:" << pInputOrder->CombOffsetFlag << endl;
		cout << "组合投机套保标志:" << pInputOrder->CombHedgeFlag << endl;
		cout << "价格:" << pInputOrder->LimitPrice << endl;
		cout << "数量:" << pInputOrder->VolumeTotalOriginal << endl;
		cout << "有效期类型:" << pInputOrder->TimeCondition << endl;
		cout << "GTD日期:" << pInputOrder->GTDDate << endl;
		cout << "成交量类型:" << pInputOrder->VolumeCondition << endl;
		cout << "最小成交量:" << pInputOrder->MinVolume << endl;
		cout << "触发条件:" << pInputOrder->ContingentCondition << endl;
		cout << "止损价:" << pInputOrder->StopPrice << endl;
		cout << "强平原因:" << pInputOrder->ForceCloseReason << endl;
		cout << "自动挂起标志:" << pInputOrder->IsAutoSuspend << endl;
		cout << "业务单元:" << pInputOrder->BusinessUnit << endl;
		cout << "请求编号:" << pInputOrder->RequestID << endl;
		cout << "用户强评标志:" << pInputOrder->UserForceClose << endl;
		cout << "互换单标志:" << pInputOrder->IsSwapOrder << endl;
		cout << "交易所代码:" << pInputOrder->ExchangeID << endl;
		cout << "投资单元代码:" << pInputOrder->InvestUnitID << endl;
		cout << "资金账号:" << pInputOrder->AccountID << endl;
		cout << "币种代码:" << pInputOrder->CurrencyID << endl;
		cout << "交易编码:" << pInputOrder->ClientID << endl;
		cout << "IP地址:" << pInputOrder->IPAddress << endl;
		cout << "Mac地址:" << pInputOrder->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///预埋单录入请求响应
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///预埋撤单录入请求响应
	void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "报单操作请求响应[OnRspOrderAction]" << endl;
		cout << "经纪公司代码:" << pInputOrderAction->BrokerID << endl;
		cout << "投资者代码:" << pInputOrderAction->InvestorID << endl;
		cout << "报单操作引用:" << pInputOrderAction->OrderActionRef << endl;
		cout << "报单引用:" << pInputOrderAction->OrderRef << endl; 
		cout << "请求编号:" << pInputOrderAction->RequestID << endl;
		cout << "前置编号:" << pInputOrderAction->FrontID << endl;
		cout << "会话编号:" << pInputOrderAction->SessionID << endl;
		cout << "交易所代码:" << pInputOrderAction->ExchangeID << endl;
		cout << "报单编号:" << pInputOrderAction->OrderSysID << endl;
		cout << "操作标志:" << pInputOrderAction->ActionFlag << endl;
		cout << "价格:" << pInputOrderAction->LimitPrice << endl;
		cout << "数量变化:" << pInputOrderAction->VolumeChange << endl;
		cout << "用户代码:" << pInputOrderAction->UserID << endl;
		cout << "合约代码:" << pInputOrderAction->InstrumentID << endl;
		cout << "投资单元代码:" << pInputOrderAction->InvestUnitID << endl;
		cout << "IP地址:" << pInputOrderAction->IPAddress << endl;
		cout << "Mac地址:" << pInputOrderAction->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///查询最大报单数量响应
	void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "查询最大报单数量响应[OnRspQueryMaxOrderVolume]" << endl;
		cout << "经纪公司代码:" << pQueryMaxOrderVolume->BrokerID << endl;
		cout << "投资者代码:" << pQueryMaxOrderVolume->InvestorID << endl;
		cout << "合约代码:" << pQueryMaxOrderVolume->InstrumentID << endl;
		cout << "买卖方向:" << pQueryMaxOrderVolume->Direction << endl;
		cout << "开平标志:" << pQueryMaxOrderVolume->OffsetFlag << endl;
		cout << "投机套保标志:" << pQueryMaxOrderVolume->HedgeFlag << endl;
		cout << "最大允许报单数量:" << pQueryMaxOrderVolume->MaxVolume << endl;
		cout << "==============================" << endl;
	};

	///投资者结算结果确认响应
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "投资者结算结果确认响应[OnRspSettlementInfoConfirm]" << endl;
		cout << "经纪公司代码:" << pSettlementInfoConfirm->BrokerID << endl;
		cout << "投资者代码:" << pSettlementInfoConfirm->InvestorID << endl;
		cout << "确认日期:" << pSettlementInfoConfirm->ConfirmDate << endl;
		cout << "确认时间:" << pSettlementInfoConfirm->ConfirmTime << endl;
		cout << "==============================" << endl;

	};

	///删除预埋单响应
	void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///删除预埋撤单响应
	void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告录入请求响应
	void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告操作请求响应
	void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价录入请求响应
	void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价录入请求响应
	void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作请求响应
	void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///批量报单操作请求响应
	void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///申请组合录入请求响应
	void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "经纪公司代码:" << pOrder->BrokerID << endl;
		cout << "投资者代码:" << pOrder->InvestorID << endl;
		cout << "合约代码:" << pOrder->InstrumentID << endl;
		cout << "报单引用:" << pOrder->OrderRef << endl;
		cout << "用户代码:" << pOrder->UserID << endl;
		cout << "报单价格条件:" << pOrder->OrderPriceType << endl;
		cout << "买卖方向:" << pOrder->Direction << endl;
		cout << "组合开平标志:" << pOrder->CombOffsetFlag << endl;
		cout << "组合投机套保标志:" << pOrder->CombHedgeFlag << endl;
		cout << "价格:" << pOrder->LimitPrice << endl;
		cout << "数量:" << pOrder->VolumeTotalOriginal << endl;
		cout << "有效期类型:" << pOrder->TimeCondition << endl;
		cout << "GTD日期:" << pOrder->GTDDate << endl;
		cout << "成交量类型:" << pOrder->VolumeCondition << endl;
		cout << "最小成交量:" << pOrder->MinVolume << endl;
		cout << "触发条件:" << pOrder->ContingentCondition << endl;
		cout << "止损价:" << pOrder->StopPrice << endl;
		cout << "强平原因:" << pOrder->ForceCloseReason << endl;
		cout << "自动挂起标志:" << pOrder->IsAutoSuspend << endl;
		cout << "业务单元:" << pOrder->BusinessUnit << endl;
		cout << "请求编号:" << pOrder->RequestID << endl;
		cout << "本地报单编号:" << pOrder->OrderLocalID << endl;
		cout << "交易所代码:" << pOrder->ExchangeID << endl;
		cout << "会员代码:" << pOrder->ParticipantID << endl;
		cout << "客户代码:" << pOrder->ClientID << endl;
		cout << "合约在交易所的代码:" << pOrder->ExchangeInstID << endl;
		cout << "交易所交易员代码:" << pOrder->TraderID << endl;
		cout << "安装编号:" << pOrder->InstallID << endl;
		cout << "报单提交状态:" << pOrder->OrderSubmitStatus << endl;
		cout << "报单提示序号:" << pOrder->NotifySequence << endl;
		cout << "交易日:" << pOrder->TradingDay << endl;
		cout << "结算编号:" << pOrder->SettlementID << endl;
		cout << "报单编号:" << pOrder->OrderSysID << endl;
		cout << "报单来源:" << pOrder->OrderSource << endl;
		cout << "报单状态:" << pOrder->OrderStatus << endl;
		cout << "报单类型:" << pOrder->OrderType << endl;
		cout << "今成交数量:" << pOrder->VolumeTraded << endl;
		cout << "剩余数量:" << pOrder->VolumeTotal << endl;
		cout << "报单日期:" << pOrder->InsertDate << endl;
		cout << "委托时间:" << pOrder->InsertTime << endl;
		cout << "激活时间:" << pOrder->ActiveTime << endl;
		cout << "挂起时间:" << pOrder->SuspendTime << endl;
		cout << "最后修改时间:" << pOrder->UpdateTime << endl;
		cout << "撤销时间:" << pOrder->CancelTime << endl;
		cout << "最后修改交易所交易员代码:" << pOrder->ActiveTraderID << endl;
		cout << "结算会员编号:" << pOrder->ClearingPartID << endl;
		cout << "序号:" << pOrder->SequenceNo << endl;
		cout << "前置编号:" << pOrder->FrontID << endl;
		cout << "会话编号:" << pOrder->SessionID << endl;
		cout << "用户端产品信息:" << pOrder->UserProductInfo << endl;
		cout << "状态信息:" << pOrder->StatusMsg << endl;
		cout << "用户强评标志:" << pOrder->UserForceClose << endl;
		cout << "操作用户代码:" << pOrder->ActiveUserID << endl;
		cout << "经纪公司报单编号:" << pOrder->BrokerOrderSeq << endl;
		cout << "相关报单:" << pOrder->RelativeOrderSysID << endl;
		cout << "郑商所成交数量:" << pOrder->ZCETotalTradedVolume << endl;
		cout << "互换单标志:" << pOrder->IsSwapOrder << endl;
		cout << "营业部编号:" << pOrder->BranchID << endl;
		cout << "投资单元代码:" << pOrder->InvestUnitID << endl;
		cout << "资金账号:" << pOrder->AccountID << endl;
		cout << "币种代码:" << pOrder->CurrencyID << endl;
		cout << "IP地址:" << pOrder->IPAddress << endl;
		cout << "Mac地址:" << pOrder->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///请求查询成交响应
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "经纪公司代码:" << pTrade->BrokerID << endl;
		cout << "投资者代码:" << pTrade->InvestorID << endl;
		cout << "合约代码:" << pTrade->InstrumentID << endl;
		cout << "报单引用:" << pTrade->OrderRef << endl;
		cout << "用户代码:" << pTrade->UserID << endl;
		cout << "交易所代码:" << pTrade->ExchangeID << endl;
		cout << "成交编号:" << pTrade->TradeID << endl;
		cout << "买卖方向:" << pTrade->Direction << endl;
		cout << "报单编号:" << pTrade->OrderSysID << endl;
		cout << "会员代码:" << pTrade->ParticipantID << endl;
		cout << "客户代码:" << pTrade->ClientID << endl;
		cout << "交易角色:" << pTrade->TradingRole << endl;
		cout << "合约在交易所的代码:" << pTrade->ExchangeInstID << endl;
		cout << "开平标志:" << pTrade->OffsetFlag << endl;
		cout << "投机套保标志:" << pTrade->HedgeFlag << endl;
		cout << "价格:" << pTrade->Price << endl;
		cout << "数量:" << pTrade->Volume << endl;
		cout << "成交时期:" << pTrade->TradeDate << endl;
		cout << "成交时间:" << pTrade->TradeTime << endl;
		cout << "成交类型:" << pTrade->TradeType << endl;
		cout << "成交价来源:" << pTrade->PriceSource << endl;
		cout << "交易所交易员代码:" << pTrade->TraderID << endl;
		cout << "本地报单编号:" << pTrade->OrderLocalID << endl;
		cout << "结算会员编号:" << pTrade->ClearingPartID << endl;
		cout << "业务单元:" << pTrade->BusinessUnit << endl;
		cout << "序号:" << pTrade->SequenceNo << endl;
		cout << "交易日:" << pTrade->TradingDay << endl;
		cout << "结算编号:" << pTrade->SettlementID << endl;
		cout << "经纪公司报单编号:" << pTrade->BrokerOrderSeq << endl;
		cout << "成交来源:" << pTrade->TradeSource << endl;
		cout << "==============================" << endl;

	};

	///请求查询投资者持仓响应
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "合约代码:" << pInvestorPosition->InstrumentID << endl;
		cout << "经纪公司代码:" << pInvestorPosition->BrokerID << endl;
		cout << "投资者代码:" << pInvestorPosition->InvestorID << endl;
		cout << "持仓多空方向:" << pInvestorPosition->PosiDirection << endl;
		cout << "投机套保标志:" << pInvestorPosition->HedgeFlag << endl;
		cout << "持仓日期:" << pInvestorPosition->PositionDate << endl;
		cout << "上日持仓:" << pInvestorPosition->YdPosition << endl;
		cout << "今日持仓:" << pInvestorPosition->Position << endl;
		cout << "多头冻结:" << pInvestorPosition->LongFrozen << endl;
		cout << "空头冻结:" << pInvestorPosition->ShortFrozen << endl;
		cout << "开仓冻结金额:" << pInvestorPosition->LongFrozenAmount << endl;
		cout << "开仓冻结金额:" << pInvestorPosition->ShortFrozenAmount << endl;
		cout << "开仓量:" << pInvestorPosition->OpenVolume << endl;
		cout << "平仓量:" << pInvestorPosition->CloseVolume << endl;
		cout << "开仓金额:" << pInvestorPosition->OpenAmount << endl;
		cout << "平仓金额:" << pInvestorPosition->CloseAmount << endl;
		cout << "持仓成本:" << pInvestorPosition->PositionCost << endl;
		cout << "上次占用的保证金:" << pInvestorPosition->PreMargin << endl;
		cout << "占用的保证金:" << pInvestorPosition->UseMargin << endl;
		cout << "冻结的保证金:" << pInvestorPosition->FrozenMargin << endl;
		cout << "冻结的资金:" << pInvestorPosition->FrozenCash << endl;
		cout << "冻结的手续费:" << pInvestorPosition->FrozenCommission << endl;
		cout << "资金差额:" << pInvestorPosition->CashIn << endl;
		cout << "手续费:" << pInvestorPosition->Commission << endl;
		cout << "平仓盈亏:" << pInvestorPosition->CloseProfit << endl;
		cout << "持仓盈亏:" << pInvestorPosition->PositionProfit << endl;
		cout << "上次结算价:" << pInvestorPosition->PreSettlementPrice << endl;
		cout << "本次结算价:" << pInvestorPosition->SettlementPrice << endl;
		cout << "交易日:" << pInvestorPosition->TradingDay << endl;
		cout << "结算编号:" << pInvestorPosition->SettlementID << endl;
		cout << "开仓成本:" << pInvestorPosition->OpenCost << endl;
		cout << "交易所保证金:" << pInvestorPosition->ExchangeMargin << endl;
		cout << "组合成交形成的持仓:" << pInvestorPosition->CombPosition << endl;
		cout << "组合多头冻结:" << pInvestorPosition->CombLongFrozen << endl;
		cout << "组合空头冻结:" << pInvestorPosition->CombShortFrozen << endl;
		cout << "逐日盯市平仓盈亏:" << pInvestorPosition->CloseProfitByDate << endl;
		cout << "逐笔对冲平仓盈亏:" << pInvestorPosition->CloseProfitByTrade << endl;
		cout << "今日持仓:" << pInvestorPosition->TodayPosition << endl;
		cout << "保证金率:" << pInvestorPosition->MarginRateByMoney << endl;
		cout << "保证金率(按手数) :" << pInvestorPosition->MarginRateByVolume << endl;
		cout << "执行冻结:" << pInvestorPosition->StrikeFrozen << endl;
		cout << "执行冻结金额:" << pInvestorPosition->StrikeFrozenAmount << endl;
		cout << "放弃执行冻结:" << pInvestorPosition->AbandonFrozen << endl;
		cout << "==============================" << endl;

	};

	///请求查询资金账户响应
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易编码响应
	void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约保证金率响应
	void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约手续费率响应
	void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所响应
	void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品响应
	void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者结算结果响应
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "请求查询投资者结算结果响应[OnRspQrySettlementInfo]" << endl;
		cout << "交易日:" << pSettlementInfo->TradingDay << endl;
		cout << "结算编号:" << pSettlementInfo->SettlementID << endl;
		cout << "经纪公司代码:" << pSettlementInfo->BrokerID << endl;
		cout << "投资者代码:" << pSettlementInfo->InvestorID << endl;
		cout << "序号:" << pSettlementInfo->SequenceNo << endl;
		cout << "消息正文:" << endl << pSettlementInfo->Content << endl;
		cout << "==============================" << endl;

	};

	///请求查询转帐银行响应
	void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询客户通知响应
	void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询结算信息确认响应
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询保证金监管系统经纪公司资金账户密钥响应
	void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询仓单折抵信息响应
	void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者品种/跨品种保证金响应
	void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所保证金率响应
	void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所调整保证金率响应
	void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询汇率响应
	void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询二级代理操作员银期权限响应
	void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品报价汇率
	void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品组
	void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询做市商合约手续费率响应
	void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询做市商期权合约手续费响应
	void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单手续费响应
	void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询期权交易成本响应
	void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询期权合约手续费响应
	void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询执行宣告响应
	void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询询价响应
	void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报价响应
	void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询组合合约安全系数响应
	void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询申请组合响应
	void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询转帐流水响应
	void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询银期签约关系响应
	void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///成交通知
	void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///报单录入错误回报
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///合约交易状态通知
	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};

	///交易所公告通知
	void OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {};

	///交易通知
	void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};

	///提示条件单校验错误
	void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {};

	///执行宣告通知
	void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {};

	///执行宣告录入错误回报
	void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///执行宣告操作错误回报
	void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///询价录入错误回报
	void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {};

	///报价通知
	void OnRtnQuote(CThostFtdcQuoteField *pQuote) {};

	///报价录入错误回报
	void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {};

	///报价操作错误回报
	void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {};

	///询价通知
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};

	///保证金监控中心用户令牌
	void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {};

	///批量报单操作错误回报
	void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///申请组合通知
	void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {};

	///申请组合录入错误回报
	void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {};

	///请求查询签约银行响应
	void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋单响应
	void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋撤单响应
	void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易通知响应
	void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司交易参数响应
	void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司交易算法响应
	void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询监控中心用户令牌
	void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///银行发起银行资金转期货通知
	void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {};

	///银行发起期货资金转银行通知
	void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {};

	///银行发起冲正银行转期货通知
	void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {};

	///银行发起冲正期货转银行通知
	void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {};

	///期货发起银行资金转期货通知
	void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

	///期货发起期货资金转银行通知
	void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

	///期货发起查询银行余额通知
	void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {};

	///期货发起银行资金转期货错误回报
	void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

	///期货发起期货资金转银行错误回报
	void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

	///系统运行时期货端手工发起冲正银行转期货错误回报
	void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

	///系统运行时期货端手工发起冲正期货转银行错误回报
	void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

	///期货发起查询银行余额错误回报
	void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {};

	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

	///期货发起银行资金转期货应答
	void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///期货发起期货资金转银行应答
	void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///期货发起查询银行余额应答
	void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///银行发起银期开户通知
	void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {};

	///银行发起银期销户通知
	void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {};

	///银行发起变更银行账号通知
	void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {};
};
