// Copyright 2023 Xiao Gang. All Rights Reserved.
#include "XGTTSPlayVoiceComponent.h"
#include "XGTTSSubsystem.h"
#include "Kismet/GameplayStatics.h"

bool UXGTTSPlayVoiceComponent::Init(int32& SampleRate)
{
	NumChannels = 1;
	SampleRate = 16000;

	return true;

}

int32 UXGTTSPlayVoiceComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
		//��Ҫ�ж��Ƿ�Ϊ��
/*
	UGameInstance* MyGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UXGTTSSubsystem* TTSSubsystem =	MyGameInstance->GetSubsystem<UXGTTSSubsystem>();*/

	//����Խ��
	if (PlayIndex > UXGTTSSubsystem::FinalUEData.Num() - 1)
	{
		for (int32 SoundIndex = 0; SoundIndex < 1024; SoundIndex++)
		{
			OutAudio[SoundIndex]=0;
		}
		return 1024;
	}
	//��Ҫ�Ż�

	for (int32 SoundIndex=0; SoundIndex<1024; SoundIndex++)
	{

		if (PlayIndex > UXGTTSSubsystem::FinalUEData.Num() - 1)
		{
			return 1024;
		}
		OutAudio[SoundIndex] = UXGTTSSubsystem::FinalUEData[PlayIndex];
		PlayIndex++;


	}



	return 1024;

}

