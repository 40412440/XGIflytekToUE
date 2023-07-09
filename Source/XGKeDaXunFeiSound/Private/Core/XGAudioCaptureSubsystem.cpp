// Copyright 2023 Xiao Gang. All Rights Reserved.

#include "Core/XGAudioCaptureSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Core/XGKeDaXunFeiSocketSubsystem.h"


float* UXGAudioCaptureSubsystem::XGAudio = nullptr;
int32 UXGAudioCaptureSubsystem::XGNumSamples = -1;
TArray<float*>  UXGAudioCaptureSubsystem::InAudios = {};
float* UXGAudioCaptureSubsystem::ToSendData = nullptr;

int32 UXGAudioCaptureSubsystem::IndexSend = 0;

FCriticalSection UXGAudioCaptureSubsystem::XGAudioCriticalSection;
TArray<float> UXGAudioCaptureSubsystem::AudioData = {};
bool UXGAudioCaptureSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UXGAudioCaptureSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//����� ���������ͱ�������
	XGAudioCapture = UAudioCaptureFunctionLibrary::CreateAudioCapture();
	XGAudioCapture->AddGeneratorDelegate(&UXGAudioCaptureSubsystem::OnAudioGenerate);

	if (InAudios.Num() > 0)
	{
		for (auto& SoundPtr : InAudios)
		{
			delete SoundPtr;
			SoundPtr = nullptr;
		}
		InAudios.Empty();
	}


	FScopeLock Lock(&XGAudioCriticalSection);
	AudioData.Empty();

	UXGKeDaXunFeiSocketSubsystem::XGAudioCaptureSubsystem = this;

}

void UXGAudioCaptureSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UXGAudioCaptureSubsystem::Tick(float DeltaTime)
{

}

TStatId UXGAudioCaptureSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UXGAudioCaptureSubsystem, STATGROUP_Tickables);
}

bool UXGAudioCaptureSubsystem::IsTickable() const
{
	return !IsTemplate();
}

void UXGAudioCaptureSubsystem::StartCapturingAudio()
{
/*
	if (InAudios.Num() > 0)
	{
		for (auto& SoundPtr : InAudios)
		{
			delete SoundPtr;
			SoundPtr = nullptr;
		}
		InAudios.Empty();
	}*/

	FScopeLock Lock(&XGAudioCriticalSection);
	if (AudioData.Num()>0)
	{
		AudioData.Empty();
	}


	XGAudioCapture->StartCapturingAudio();
}

void UXGAudioCaptureSubsystem::StopCapturingAudio()
{
	XGAudioCapture->StopCapturingAudio();

	FScopeLock Lock(&XGAudioCriticalSection);
	if (AudioData.Num() > 0)
	{
		AudioData.Empty();
	}



}

bool UXGAudioCaptureSubsystem::IsCapturingAudio()
{
	return XGAudioCapture->IsCapturingAudio();
}

bool UXGAudioCaptureSubsystem::GetAudioCaptureDeviceInfo(FAudioCaptureDeviceInfo& OutInfo)
{	

	bool bGet =	 XGAudioCapture->GetAudioCaptureDeviceInfo(OutInfo);
	UE_LOG(LogTemp, Warning, TEXT("DeviceName:[%s]---NumInputChannels:[%d]----SampleRate:[%d]"), *(OutInfo.DeviceName.ToString()), OutInfo.NumInputChannels, OutInfo.SampleRate);
	return bGet;
}

//��Ҫ�Ż��� 48k ˫ͨ���� 1024 32λ  21.3333ms
//Ŀ������ʱ16k ��ͨ�� 16 λ			64.000ms
void UXGAudioCaptureSubsystem::OnAudioGenerate(const float* InAudio, int32 NumSamples)
{
/*
	UE_LOG(LogTemp, Display, TEXT("OnAudioCapture %f-----%d"), *InAudio, NumSamples);

	XGAudio = const_cast<float*>(InAudio);
	XGNumSamples = NumSamples;

	XGAudio = new float[NumSamples];

	for (int i = 0; i < NumSamples; i++)
	{
		XGAudio[i] = InAudio[i];
	}

	
	InAudios.Add(XGAudio);*/
	
/*
	GWorld->GetGameInstance();
	//UGameInstance* MyGameInstance = UGameplayStatics::GetGameInstance();

	UGameInstance* MyGameInstance = GWorld->GetGameInstance();

	if (MyGameInstance)
	{
		UXGKeDaXunFeiSocketSubsystem* SocketSubsystem=	MyGameInstance->GetSubsystem<UXGKeDaXunFeiSocketSubsystem>();
		SocketSubsystem->SendVoiceData(InAudio, NumSamples);

	}//������ �ڴ�й¶
*/	
	
	FScopeLock Lock(&XGAudioCriticalSection);
	int32 LeftIndex = 0;
	if (IndexSend == 0)
	{
		IndexSend++;
		for (int32 SendIndex = 0; SendIndex<341; SendIndex++)
		{
			AudioData.Add(InAudio[LeftIndex]);
			LeftIndex += 6;
			
			
		}

	}
	else if (IndexSend ==1)
	{

		IndexSend++;
		for (int32 SendIndex = 341; SendIndex < 682; SendIndex++)
		{
			AudioData.Add(InAudio[LeftIndex]);

			LeftIndex += 6;
		}


	}
	else if (IndexSend ==2)
	{

		IndexSend = 0;
		for (int32 SendIndex = 682; SendIndex < 1024; SendIndex++)
		{
			AudioData.Add(InAudio[LeftIndex]);

			LeftIndex += 6;
		}
		
	//	UXGKeDaXunFeiSocketSubsystem::SendVoiceData(ToSendData, NumSamples);
	}

	
	
	





}

