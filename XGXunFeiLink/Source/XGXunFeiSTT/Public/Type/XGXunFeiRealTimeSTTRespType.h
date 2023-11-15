// Copyright 2023 Xiao Gang. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "XGXunFeiRealTimeSTTRespType.generated.h"

/**
 * FXGXunFeiRealTImeSTTRespInfo
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTImeSTTRespInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString sid;
};

/**
 * FXGXunFeiRealTimeSTTTranslateData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTTranslateData
{
	GENERATED_BODY()

	/**
	 * ҵ���ʶ�ֶΣ��������빦�ܺ�ֵΪ trans
	 * ���빦�ܱ�ʶ
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString biz;

	/**
	 * Ŀ�����ַ����ı����
	 * 	��ԭʼ�ı�src��Ӧ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString dst;
	/**
	 * ���������ʶ
	 * ���Ϊ true����ʶ���������������
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	bool isEnd;

	/**
	 * תд������
	 * ��0��ʼ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 segId;

	/**
	 * �ͷ����ԭʼ�ı�
	 * ��Ƶ��Ӧ��ʶ���ı�
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString src;

	/**
	 * ������ͱ�ʶ
	 * 0-���ս����1-�м���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 type;


	/**
	 * ���������������еĿ�ʼʱ�䣬��λ����(ms)
	 * �м�����bgΪ׼ȷֵ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 bg;


	/**
	 * ���������������еĽ���ʱ�䣬��λ����(ms)
	 * �м�����edΪ0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 ed;

};

/**
 * FXGXunFeiRealTimeSTTNoTranslateCWData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateCWData
{
	GENERATED_BODY()

	/**
	 * ��ʶ����
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString w;

	/**
	 * �ʱ�ʶ
	 * n-��ͨ�ʣ�s-˳���ʣ������ʣ���p-���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString wp;
};

/**
 * FXGXunFeiRealTimeSTTNoTranslateWSData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateWSData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	TArray<FXGXunFeiRealTimeSTTNoTranslateCWData> cw;
	/**
	 * ���ڱ����еĿ�ʼʱ�䣬��λ��֡��1֡=10ms
	 * ���������������еĿ�ʼʱ��Ϊ(bg+wb*10)ms
	 * �м����� wb Ϊ 0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 wb;

	/**
	 * ���ڱ����еĽ���ʱ�䣬��λ��֡��1֡=10ms
	 * ���������������еĽ���ʱ��Ϊ(bg+we*10)ms
	 * �м����� we Ϊ 0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 we;
};


/**
 * FXGXunFeiRealTimeSTTNoTranslateRTData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateRTData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	TArray<FXGXunFeiRealTimeSTTNoTranslateWSData> ws;
};




/**
 * FXGXunFeiRealTimeSTTNoTranslateSTData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateSTData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString bg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString ed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	TArray<FXGXunFeiRealTimeSTTNoTranslateRTData> rt;


	/**
	 * ������ͱ�ʶ
	 * 0-���ս����1-�м���
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FString type;
};


/**
 * FXGXunFeiRealTimeSTTNoTranslateCNData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateCNData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FXGXunFeiRealTimeSTTNoTranslateSTData st;
};

/**
 * FXGXunFeiRealTimeSTTNoTranslateData
 */
USTRUCT(BlueprintType)
struct FXGXunFeiRealTimeSTTNoTranslateData
{
	GENERATED_BODY()

	/**
	 * �Ʋ����������
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	FXGXunFeiRealTimeSTTNoTranslateCNData cn;


	/**
	 * תд������
	 * ��0��ʼ
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XG XunFei RealTime STT")
	int32 seg_id;
};
