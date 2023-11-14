// Copyright 2023 Xiao Gang. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioCapture.h"
#include "XGiFlyTekAudioCaptureSubsystem.generated.h"

/**
 *	��������ʹ�õ�����û����Ƶ����ʱ�ᱨ��
 */
 struct FAudioGeneratorHandle;
UCLASS()
class UXGiFlyTekAudioCaptureSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	friend class FXGiFlyTekConsumeVoiceRunnable;
	friend class UXGiFlyTekRealTimeSTTSubsystem;

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:
	
	static UXGiFlyTekAudioCaptureSubsystem* Get();

	void StartCapturingAudio();

	void StopCapturingAudio();

	bool IsCapturingAudio();

	bool GetAudioCaptureDeviceInfo(FAudioCaptureDeviceInfo& OutInfo);

	void AppendVoiceData(const TArray<float>& InVoiceData);

	bool GetVoiceData(TArray<float>& OutVoiceData);

	void ClearVoiceData();

	static void OnAudioGenerate(const float* InAudio, int32 NumSamples);


protected:

	static UXGiFlyTekAudioCaptureSubsystem* iFlyTekAudioCaptureSubsystemPtr;

	UPROPERTY()
	UAudioCapture* XGAudioCapture;

	FAudioGeneratorHandle AudioGeneratorHandle;

	FCriticalSection VoiceDataSection;

	TArray<float> VoiceData;


};