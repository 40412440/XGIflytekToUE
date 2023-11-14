// Copyright 2023 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <IWebSocket.h>
#include "Thread/ConsumeSoundRunnable.h"
#include "XGKeDaXunFeiSoundBPLibrary.h"
#include "XGTTSSubsystem.generated.h"

// ͷ��Ϣ ��ʽ+�����ݴ�С
// ��ʽ������Ϣ �������ݸ�ʽ������
// ������Ϣ���� +���ݴ�С
//  ����������
//12���ֽ�
struct FXGWaveHeard
{
	//4���ֽ�
	int8 ChunkID[4];
	//4���ֽ� 36+���ݴ�С ������ ChunkID  ChunkSize 4+ 24 +8 =36
	uint32 ChunkSize;
	//4���ֽ� 
	int8 Format[4];
};

//24���ֽ�
struct FXGWaveFmt
{
	//4���ֽ� 
	int8 SubChunkID[4];
	//4���ֽ� 16�ֽ� ������SubChunkID  SubChunkSize 2+2+4+4+2+2 =16
	uint32 SubChunkSize;
	//2���ֽ� 1 
	uint16 AudioFormat;
	//2���ֽ� 1
	uint16 NumChannel;
	//4���ֽ� 16000
	uint32 SampleRate;
	//4���ֽ� byte
	uint32 ByteRate;
	//2���ֽ�  2���ֽڶ���
	uint16 BlockAlign;
	//2���ֽ�  16λ
	uint16 BitsForSample;



};
//8���ֽ�
struct FXGWaveData
{
	//4���ֽ�
	int8 DataChunkID[4];
	//4���ֽ�
	uint32 DataChunkSize;

};
//׷�Ӷ���������




/**
 *
 */
UCLASS()
class XGKEDAXUNFEISOUND_API UXGTTSSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{

	GENERATED_BODY()
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;




public:
	UFUNCTION(BlueprintCallable)
		void CreateSocket();
	UFUNCTION(BlueprintCallable)
		void CloseSocket();

public:
	UFUNCTION(BlueprintCallable)
		void ConvertPCMToWav();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject))
		USoundWave* PlayWavAudioInScene(const UObject* WorldContextObject);


public:
	static TArray<float> FinalUEData;
	TArray<int16> OriginPCMData;
	TArray<uint8> FinalPCMData;
	// FString AudioStr= TEXT("");
	void SampleRateConvert(float CurrentSR, float TargetSR, int32 NumChannels, const TArray<int16>& CurrentRecordedPCMData, int32 NumSamplesToConvert, TArray<int16>& OutConverted);
protected:

	void OnConnected();
	void OnConnectionError(const FString& Error);
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnMessage(const FString& Message);
	void OnMessageSent(const FString& MessageString);

protected:
	TSharedPtr<IWebSocket> Socket;
	FString ServerURL = TEXT("");
	FString ServerProtocol = TEXT("");


protected:

	FString HMACSHA256(FString APPSecreet, FString Data);
};
