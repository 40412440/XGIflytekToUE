// Copyright 2023 Xiao Gang. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "XGiFlyTekRealTimeSTTRespType.generated.h"


USTRUCT(BlueprintType)
struct FXGiFlyTekRealTImeSTTRespInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString sid;
};


USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTTranslateData
{
	GENERATED_BODY()

	/**
	 * ҵ���ʶ�ֶΣ��������빦�ܺ�ֵΪ trans
	 * ���빦�ܱ�ʶ
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString biz;

	/**
	 * Ŀ�����ַ����ı����
	 * 	��ԭʼ�ı�src��Ӧ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString dst;
	/**
	 * ���������ʶ
	 * ���Ϊ true����ʶ���������������
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	bool isEnd;

	/**
	 * תд������
	 * ��0��ʼ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 segId;

	/**
	 * �ͷ����ԭʼ�ı�
	 * ��Ƶ��Ӧ��ʶ���ı�
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString src;

	/**
	 * ������ͱ�ʶ
	 * 0-���ս����1-�м���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 type;


	/**
	 * ���������������еĿ�ʼʱ�䣬��λ����(ms)
	 * �м�����bgΪ׼ȷֵ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 bg;


	/**
	 * ���������������еĽ���ʱ�䣬��λ����(ms)
	 * �м�����edΪ0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 ed;

};


USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateCWData
{
	GENERATED_BODY()

	/**
	 * ��ʶ����
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString w;

	/**
	 * �ʱ�ʶ
	 * n-��ͨ�ʣ�s-˳���ʣ������ʣ���p-���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString wp;
};


USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateWSData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	TArray<FXGiFlyTekRealTimeSTTNoTranslateCWData> cw;
	/**
	 * ���ڱ����еĿ�ʼʱ�䣬��λ��֡��1֡=10ms
	 * ���������������еĿ�ʼʱ��Ϊ(bg+wb*10)ms
	 * �м����� wb Ϊ 0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 wb;

	/**
	 * ���ڱ����еĽ���ʱ�䣬��λ��֡��1֡=10ms
	 * ���������������еĽ���ʱ��Ϊ(bg+we*10)ms
	 * �м����� we Ϊ 0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 we;
};



USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateRTData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	TArray<FXGiFlyTekRealTimeSTTNoTranslateWSData> ws;
};





USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateSTData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString bg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString ed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	TArray<FXGiFlyTekRealTimeSTTNoTranslateRTData> rt;


	/**
	 * ������ͱ�ʶ
	 * 0-���ս����1-�м���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FString type;
};



USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateCNData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FXGiFlyTekRealTimeSTTNoTranslateSTData st;
};


USTRUCT(BlueprintType)
struct FXGiFlyTekRealTimeSTTNoTranslateData
{
	GENERATED_BODY()

	/**
	 * �Ʋ����������
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	FXGiFlyTekRealTimeSTTNoTranslateCNData cn;


	/**
	 * תд������
	 * ��0��ʼ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG iFylTek RealTime STT")
	int32 seg_id;
};
