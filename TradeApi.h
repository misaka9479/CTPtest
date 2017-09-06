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

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	void OnFrontConnected(){
		cout << "���ӳɹ�[OnFrontConnected]" << endl;
		cout << "==============================" << endl;

		///��½����[OnRspUserLogin]
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
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	void OnFrontDisconnected(int nReason){
		cout << "���ӶϿ�[OnFrontDisconnected]" << endl;
		cout << "==============================" << endl;
		switch (nReason)
		{
			case( 0x1001 ):
				cout << "�����ʧ��:" << nReason << endl;
				break;
			case( 0x1002 ):
				cout << "����дʧ��:" << nReason << endl;
				break;
			case( 0x2001 ):
				cout << "����������ʱ:" << nReason << endl;
				break;
			case( 0x2002 ):
				cout << "��������ʧ��:" << nReason << endl;
				break;
			case( 0x2003 ):
				cout << "�յ�������:" << nReason << endl;
				break;
		}
	};
	
	///�ͻ�����֤��Ӧ
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "�ͻ�����֤��Ӧ[OnRspAuthenticate]" << endl;
		cout << "���͹�˾����:" << pRspAuthenticateField->BrokerID << endl;
		cout << "�û�����:" << pRspAuthenticateField->UserID << endl;
		cout << "�û��˲�Ʒ��Ϣ:" << pRspAuthenticateField->UserProductInfo << endl;
		cout << "==============================" << endl;
	};
	
	///��¼������Ӧ
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "��¼������Ӧ[OnRspUserLogin]" << endl;
		cout << "������:" << pRspUserLogin->TradingDay << endl;
		cout << "��¼�ɹ�ʱ��:" << pRspUserLogin->LoginTime << endl;
		cout << "���͹�˾����:" << pRspUserLogin->BrokerID << endl;
		cout << "�û�����:" << pRspUserLogin->UserID << endl;
		cout << "����ϵͳ����:" << pRspUserLogin->SystemName << endl;
		cout << "ǰ�ñ��:" << pRspUserLogin->FrontID << endl;
		cout << "�Ự���:" << pRspUserLogin->SessionID << endl;
		cout << "��󱨵�����:" << pRspUserLogin->MaxOrderRef << endl;
		cout << "������ʱ��:" << pRspUserLogin->SHFETime << endl;
		cout << "������ʱ��:" << pRspUserLogin->DCETime << endl;
		cout << "֣����ʱ��;" << pRspUserLogin->CZCETime << endl;
		cout << "�н���ʱ��;" << pRspUserLogin->FFEXTime << endl;
		cout << "��Դ����ʱ��:" << pRspUserLogin->INETime << endl;
		cout << "==============================" << endl;
		
		///
		CThostFtdcQrySettlementInfoField q;
		memset(&q, 0, sizeof(q));
		strcpy_s(q.BrokerID, "9999");
		strcpy_s(q.InvestorID, "101327");
		api->ReqQrySettlementInfo( &q, 1);

	};

	///�ǳ�������Ӧ
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "�ǳ�������Ӧ[OnRspUserLogout]" << endl;
		cout << "���͹�˾����:" << pUserLogout->BrokerID << endl;
		cout << "�û�����:" << pUserLogout->UserID << endl;
		cout << "==============================" << endl;

	};

	///�û��������������Ӧ
	void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ʽ��˻��������������Ӧ
	void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "����¼��������Ӧ[OnRspOrderInsert]" << endl;
		cout << "���͹�˾����:" << pInputOrder->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pInputOrder->InvestorID << endl;
		cout << "��Լ����:" << pInputOrder->InstrumentID << endl;
		cout << "��������:" << pInputOrder->OrderRef << endl;
		cout << "�û�����:" << pInputOrder->UserID << endl;
		cout << "�����۸�����:" << pInputOrder->OrderPriceType << endl;
		cout << "��������:" << pInputOrder->Direction << endl;
		cout << "��Ͽ�ƽ��־:" << pInputOrder->CombOffsetFlag << endl;
		cout << "���Ͷ���ױ���־:" << pInputOrder->CombHedgeFlag << endl;
		cout << "�۸�:" << pInputOrder->LimitPrice << endl;
		cout << "����:" << pInputOrder->VolumeTotalOriginal << endl;
		cout << "��Ч������:" << pInputOrder->TimeCondition << endl;
		cout << "GTD����:" << pInputOrder->GTDDate << endl;
		cout << "�ɽ�������:" << pInputOrder->VolumeCondition << endl;
		cout << "��С�ɽ���:" << pInputOrder->MinVolume << endl;
		cout << "��������:" << pInputOrder->ContingentCondition << endl;
		cout << "ֹ���:" << pInputOrder->StopPrice << endl;
		cout << "ǿƽԭ��:" << pInputOrder->ForceCloseReason << endl;
		cout << "�Զ������־:" << pInputOrder->IsAutoSuspend << endl;
		cout << "ҵ��Ԫ:" << pInputOrder->BusinessUnit << endl;
		cout << "������:" << pInputOrder->RequestID << endl;
		cout << "�û�ǿ����־:" << pInputOrder->UserForceClose << endl;
		cout << "��������־:" << pInputOrder->IsSwapOrder << endl;
		cout << "����������:" << pInputOrder->ExchangeID << endl;
		cout << "Ͷ�ʵ�Ԫ����:" << pInputOrder->InvestUnitID << endl;
		cout << "�ʽ��˺�:" << pInputOrder->AccountID << endl;
		cout << "���ִ���:" << pInputOrder->CurrencyID << endl;
		cout << "���ױ���:" << pInputOrder->ClientID << endl;
		cout << "IP��ַ:" << pInputOrder->IPAddress << endl;
		cout << "Mac��ַ:" << pInputOrder->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///Ԥ��¼��������Ӧ
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Ԥ�񳷵�¼��������Ӧ
	void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������������Ӧ
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "��������������Ӧ[OnRspOrderAction]" << endl;
		cout << "���͹�˾����:" << pInputOrderAction->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pInputOrderAction->InvestorID << endl;
		cout << "������������:" << pInputOrderAction->OrderActionRef << endl;
		cout << "��������:" << pInputOrderAction->OrderRef << endl; 
		cout << "������:" << pInputOrderAction->RequestID << endl;
		cout << "ǰ�ñ��:" << pInputOrderAction->FrontID << endl;
		cout << "�Ự���:" << pInputOrderAction->SessionID << endl;
		cout << "����������:" << pInputOrderAction->ExchangeID << endl;
		cout << "�������:" << pInputOrderAction->OrderSysID << endl;
		cout << "������־:" << pInputOrderAction->ActionFlag << endl;
		cout << "�۸�:" << pInputOrderAction->LimitPrice << endl;
		cout << "�����仯:" << pInputOrderAction->VolumeChange << endl;
		cout << "�û�����:" << pInputOrderAction->UserID << endl;
		cout << "��Լ����:" << pInputOrderAction->InstrumentID << endl;
		cout << "Ͷ�ʵ�Ԫ����:" << pInputOrderAction->InvestUnitID << endl;
		cout << "IP��ַ:" << pInputOrderAction->IPAddress << endl;
		cout << "Mac��ַ:" << pInputOrderAction->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///��ѯ��󱨵�������Ӧ
	void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "��ѯ��󱨵�������Ӧ[OnRspQueryMaxOrderVolume]" << endl;
		cout << "���͹�˾����:" << pQueryMaxOrderVolume->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pQueryMaxOrderVolume->InvestorID << endl;
		cout << "��Լ����:" << pQueryMaxOrderVolume->InstrumentID << endl;
		cout << "��������:" << pQueryMaxOrderVolume->Direction << endl;
		cout << "��ƽ��־:" << pQueryMaxOrderVolume->OffsetFlag << endl;
		cout << "Ͷ���ױ���־:" << pQueryMaxOrderVolume->HedgeFlag << endl;
		cout << "�������������:" << pQueryMaxOrderVolume->MaxVolume << endl;
		cout << "==============================" << endl;
	};

	///Ͷ���߽�����ȷ����Ӧ
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "Ͷ���߽�����ȷ����Ӧ[OnRspSettlementInfoConfirm]" << endl;
		cout << "���͹�˾����:" << pSettlementInfoConfirm->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pSettlementInfoConfirm->InvestorID << endl;
		cout << "ȷ������:" << pSettlementInfoConfirm->ConfirmDate << endl;
		cout << "ȷ��ʱ��:" << pSettlementInfoConfirm->ConfirmTime << endl;
		cout << "==============================" << endl;

	};

	///ɾ��Ԥ����Ӧ
	void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ɾ��Ԥ�񳷵���Ӧ
	void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ������¼��������Ӧ
	void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ���������������Ӧ
	void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ѯ��¼��������Ӧ
	void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲���������Ӧ
	void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������������������Ӧ
	void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������¼��������Ӧ
	void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "���͹�˾����:" << pOrder->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pOrder->InvestorID << endl;
		cout << "��Լ����:" << pOrder->InstrumentID << endl;
		cout << "��������:" << pOrder->OrderRef << endl;
		cout << "�û�����:" << pOrder->UserID << endl;
		cout << "�����۸�����:" << pOrder->OrderPriceType << endl;
		cout << "��������:" << pOrder->Direction << endl;
		cout << "��Ͽ�ƽ��־:" << pOrder->CombOffsetFlag << endl;
		cout << "���Ͷ���ױ���־:" << pOrder->CombHedgeFlag << endl;
		cout << "�۸�:" << pOrder->LimitPrice << endl;
		cout << "����:" << pOrder->VolumeTotalOriginal << endl;
		cout << "��Ч������:" << pOrder->TimeCondition << endl;
		cout << "GTD����:" << pOrder->GTDDate << endl;
		cout << "�ɽ�������:" << pOrder->VolumeCondition << endl;
		cout << "��С�ɽ���:" << pOrder->MinVolume << endl;
		cout << "��������:" << pOrder->ContingentCondition << endl;
		cout << "ֹ���:" << pOrder->StopPrice << endl;
		cout << "ǿƽԭ��:" << pOrder->ForceCloseReason << endl;
		cout << "�Զ������־:" << pOrder->IsAutoSuspend << endl;
		cout << "ҵ��Ԫ:" << pOrder->BusinessUnit << endl;
		cout << "������:" << pOrder->RequestID << endl;
		cout << "���ر������:" << pOrder->OrderLocalID << endl;
		cout << "����������:" << pOrder->ExchangeID << endl;
		cout << "��Ա����:" << pOrder->ParticipantID << endl;
		cout << "�ͻ�����:" << pOrder->ClientID << endl;
		cout << "��Լ�ڽ������Ĵ���:" << pOrder->ExchangeInstID << endl;
		cout << "����������Ա����:" << pOrder->TraderID << endl;
		cout << "��װ���:" << pOrder->InstallID << endl;
		cout << "�����ύ״̬:" << pOrder->OrderSubmitStatus << endl;
		cout << "������ʾ���:" << pOrder->NotifySequence << endl;
		cout << "������:" << pOrder->TradingDay << endl;
		cout << "������:" << pOrder->SettlementID << endl;
		cout << "�������:" << pOrder->OrderSysID << endl;
		cout << "������Դ:" << pOrder->OrderSource << endl;
		cout << "����״̬:" << pOrder->OrderStatus << endl;
		cout << "��������:" << pOrder->OrderType << endl;
		cout << "��ɽ�����:" << pOrder->VolumeTraded << endl;
		cout << "ʣ������:" << pOrder->VolumeTotal << endl;
		cout << "��������:" << pOrder->InsertDate << endl;
		cout << "ί��ʱ��:" << pOrder->InsertTime << endl;
		cout << "����ʱ��:" << pOrder->ActiveTime << endl;
		cout << "����ʱ��:" << pOrder->SuspendTime << endl;
		cout << "����޸�ʱ��:" << pOrder->UpdateTime << endl;
		cout << "����ʱ��:" << pOrder->CancelTime << endl;
		cout << "����޸Ľ���������Ա����:" << pOrder->ActiveTraderID << endl;
		cout << "�����Ա���:" << pOrder->ClearingPartID << endl;
		cout << "���:" << pOrder->SequenceNo << endl;
		cout << "ǰ�ñ��:" << pOrder->FrontID << endl;
		cout << "�Ự���:" << pOrder->SessionID << endl;
		cout << "�û��˲�Ʒ��Ϣ:" << pOrder->UserProductInfo << endl;
		cout << "״̬��Ϣ:" << pOrder->StatusMsg << endl;
		cout << "�û�ǿ����־:" << pOrder->UserForceClose << endl;
		cout << "�����û�����:" << pOrder->ActiveUserID << endl;
		cout << "���͹�˾�������:" << pOrder->BrokerOrderSeq << endl;
		cout << "��ر���:" << pOrder->RelativeOrderSysID << endl;
		cout << "֣�����ɽ�����:" << pOrder->ZCETotalTradedVolume << endl;
		cout << "��������־:" << pOrder->IsSwapOrder << endl;
		cout << "Ӫҵ�����:" << pOrder->BranchID << endl;
		cout << "Ͷ�ʵ�Ԫ����:" << pOrder->InvestUnitID << endl;
		cout << "�ʽ��˺�:" << pOrder->AccountID << endl;
		cout << "���ִ���:" << pOrder->CurrencyID << endl;
		cout << "IP��ַ:" << pOrder->IPAddress << endl;
		cout << "Mac��ַ:" << pOrder->MacAddress << endl;
		cout << "==============================" << endl;

	};

	///�����ѯ�ɽ���Ӧ
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "���͹�˾����:" << pTrade->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pTrade->InvestorID << endl;
		cout << "��Լ����:" << pTrade->InstrumentID << endl;
		cout << "��������:" << pTrade->OrderRef << endl;
		cout << "�û�����:" << pTrade->UserID << endl;
		cout << "����������:" << pTrade->ExchangeID << endl;
		cout << "�ɽ����:" << pTrade->TradeID << endl;
		cout << "��������:" << pTrade->Direction << endl;
		cout << "�������:" << pTrade->OrderSysID << endl;
		cout << "��Ա����:" << pTrade->ParticipantID << endl;
		cout << "�ͻ�����:" << pTrade->ClientID << endl;
		cout << "���׽�ɫ:" << pTrade->TradingRole << endl;
		cout << "��Լ�ڽ������Ĵ���:" << pTrade->ExchangeInstID << endl;
		cout << "��ƽ��־:" << pTrade->OffsetFlag << endl;
		cout << "Ͷ���ױ���־:" << pTrade->HedgeFlag << endl;
		cout << "�۸�:" << pTrade->Price << endl;
		cout << "����:" << pTrade->Volume << endl;
		cout << "�ɽ�ʱ��:" << pTrade->TradeDate << endl;
		cout << "�ɽ�ʱ��:" << pTrade->TradeTime << endl;
		cout << "�ɽ�����:" << pTrade->TradeType << endl;
		cout << "�ɽ�����Դ:" << pTrade->PriceSource << endl;
		cout << "����������Ա����:" << pTrade->TraderID << endl;
		cout << "���ر������:" << pTrade->OrderLocalID << endl;
		cout << "�����Ա���:" << pTrade->ClearingPartID << endl;
		cout << "ҵ��Ԫ:" << pTrade->BusinessUnit << endl;
		cout << "���:" << pTrade->SequenceNo << endl;
		cout << "������:" << pTrade->TradingDay << endl;
		cout << "������:" << pTrade->SettlementID << endl;
		cout << "���͹�˾�������:" << pTrade->BrokerOrderSeq << endl;
		cout << "�ɽ���Դ:" << pTrade->TradeSource << endl;
		cout << "==============================" << endl;

	};

	///�����ѯͶ���ֲ߳���Ӧ
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "��Լ����:" << pInvestorPosition->InstrumentID << endl;
		cout << "���͹�˾����:" << pInvestorPosition->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pInvestorPosition->InvestorID << endl;
		cout << "�ֲֶ�շ���:" << pInvestorPosition->PosiDirection << endl;
		cout << "Ͷ���ױ���־:" << pInvestorPosition->HedgeFlag << endl;
		cout << "�ֲ�����:" << pInvestorPosition->PositionDate << endl;
		cout << "���ճֲ�:" << pInvestorPosition->YdPosition << endl;
		cout << "���ճֲ�:" << pInvestorPosition->Position << endl;
		cout << "��ͷ����:" << pInvestorPosition->LongFrozen << endl;
		cout << "��ͷ����:" << pInvestorPosition->ShortFrozen << endl;
		cout << "���ֶ�����:" << pInvestorPosition->LongFrozenAmount << endl;
		cout << "���ֶ�����:" << pInvestorPosition->ShortFrozenAmount << endl;
		cout << "������:" << pInvestorPosition->OpenVolume << endl;
		cout << "ƽ����:" << pInvestorPosition->CloseVolume << endl;
		cout << "���ֽ��:" << pInvestorPosition->OpenAmount << endl;
		cout << "ƽ�ֽ��:" << pInvestorPosition->CloseAmount << endl;
		cout << "�ֲֳɱ�:" << pInvestorPosition->PositionCost << endl;
		cout << "�ϴ�ռ�õı�֤��:" << pInvestorPosition->PreMargin << endl;
		cout << "ռ�õı�֤��:" << pInvestorPosition->UseMargin << endl;
		cout << "����ı�֤��:" << pInvestorPosition->FrozenMargin << endl;
		cout << "������ʽ�:" << pInvestorPosition->FrozenCash << endl;
		cout << "�����������:" << pInvestorPosition->FrozenCommission << endl;
		cout << "�ʽ���:" << pInvestorPosition->CashIn << endl;
		cout << "������:" << pInvestorPosition->Commission << endl;
		cout << "ƽ��ӯ��:" << pInvestorPosition->CloseProfit << endl;
		cout << "�ֲ�ӯ��:" << pInvestorPosition->PositionProfit << endl;
		cout << "�ϴν����:" << pInvestorPosition->PreSettlementPrice << endl;
		cout << "���ν����:" << pInvestorPosition->SettlementPrice << endl;
		cout << "������:" << pInvestorPosition->TradingDay << endl;
		cout << "������:" << pInvestorPosition->SettlementID << endl;
		cout << "���ֳɱ�:" << pInvestorPosition->OpenCost << endl;
		cout << "��������֤��:" << pInvestorPosition->ExchangeMargin << endl;
		cout << "��ϳɽ��γɵĳֲ�:" << pInvestorPosition->CombPosition << endl;
		cout << "��϶�ͷ����:" << pInvestorPosition->CombLongFrozen << endl;
		cout << "��Ͽ�ͷ����:" << pInvestorPosition->CombShortFrozen << endl;
		cout << "���ն���ƽ��ӯ��:" << pInvestorPosition->CloseProfitByDate << endl;
		cout << "��ʶԳ�ƽ��ӯ��:" << pInvestorPosition->CloseProfitByTrade << endl;
		cout << "���ճֲ�:" << pInvestorPosition->TodayPosition << endl;
		cout << "��֤����:" << pInvestorPosition->MarginRateByMoney << endl;
		cout << "��֤����(������) :" << pInvestorPosition->MarginRateByVolume << endl;
		cout << "ִ�ж���:" << pInvestorPosition->StrikeFrozen << endl;
		cout << "ִ�ж�����:" << pInvestorPosition->StrikeFrozenAmount << endl;
		cout << "����ִ�ж���:" << pInvestorPosition->AbandonFrozen << endl;
		cout << "==============================" << endl;

	};

	///�����ѯ�ʽ��˻���Ӧ
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ������Ӧ
	void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���ױ�����Ӧ
	void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ��֤������Ӧ
	void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ����������Ӧ
	void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������Ӧ
	void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ʒ��Ӧ
	void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ��Ӧ
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���߽�������Ӧ
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout << "�����ѯͶ���߽�������Ӧ[OnRspQrySettlementInfo]" << endl;
		cout << "������:" << pSettlementInfo->TradingDay << endl;
		cout << "������:" << pSettlementInfo->SettlementID << endl;
		cout << "���͹�˾����:" << pSettlementInfo->BrokerID << endl;
		cout << "Ͷ���ߴ���:" << pSettlementInfo->InvestorID << endl;
		cout << "���:" << pSettlementInfo->SequenceNo << endl;
		cout << "��Ϣ����:" << endl << pSettlementInfo->Content << endl;
		cout << "==============================" << endl;

	};

	///�����ѯת��������Ӧ
	void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ͻ�֪ͨ��Ӧ
	void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ϣȷ����Ӧ
	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������֤������Ӧ
	void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������������֤������Ӧ
	void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�����������Ա����Ȩ����Ӧ
	void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ʒ���ۻ���
	void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ʒ��
	void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�����̺�Լ����������Ӧ
	void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������Ȩ��Լ��������Ӧ
	void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������������Ӧ
	void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ȩ���׳ɱ���Ӧ
	void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ȩ��Լ��������Ӧ
	void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯִ��������Ӧ
	void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯѯ����Ӧ
	void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���������Ӧ
	void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯת����ˮ��Ӧ
	void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����ǩԼ��ϵ��Ӧ
	void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����Ӧ��
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����֪ͨ
	void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///�ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///����¼�����ر�
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///������������ر�
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///��Լ����״̬֪ͨ
	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};

	///����������֪ͨ
	void OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {};

	///����֪ͨ
	void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};

	///��ʾ������У�����
	void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {};

	///ִ������֪ͨ
	void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {};

	///ִ������¼�����ر�
	void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///ִ�������������ر�
	void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///ѯ��¼�����ر�
	void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {};

	///����֪ͨ
	void OnRtnQuote(CThostFtdcQuoteField *pQuote) {};

	///����¼�����ر�
	void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {};

	///���۲�������ر�
	void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {};

	///ѯ��֪ͨ
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};

	///��֤���������û�����
	void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {};

	///����������������ر�
	void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///�������֪ͨ
	void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {};

	///�������¼�����ر�
	void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {};

	///�����ѯǩԼ������Ӧ
	void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯԤ����Ӧ
	void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯԤ�񳷵���Ӧ
	void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����֪ͨ��Ӧ
	void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���͹�˾���ײ�����Ӧ
	void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���͹�˾�����㷨��Ӧ
	void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������û�����
	void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���з��������ʽ�ת�ڻ�֪ͨ
	void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {};

	///���з����ڻ��ʽ�ת����֪ͨ
	void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {};

	///���з����������ת�ڻ�֪ͨ
	void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {};

	///���з�������ڻ�ת����֪ͨ
	void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {};

	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

	///�ڻ������ڻ��ʽ�ת����֪ͨ
	void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {};

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {};

	///�ڻ������ѯ�������֪ͨ
	void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {};

	///�ڻ����������ʽ�ת�ڻ�����ر�
	void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

	///�ڻ������ڻ��ʽ�ת���д���ر�
	void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {};

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {};

	///�ڻ������ѯ����������ر�
	void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {};

	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {};

	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ڻ������ڻ��ʽ�ת����Ӧ��
	void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ڻ������ѯ�������Ӧ��
	void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���з������ڿ���֪ͨ
	void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {};

	///���з�����������֪ͨ
	void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {};

	///���з����������˺�֪ͨ
	void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {};
};
