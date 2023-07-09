// Copyright 2023 Xiao Gang. All Rights Reserved.


#include "Core/XGKeDaXunFeiSocketSubsystem.h"
#include "WebSocketsModule.h"
#include "Type/XGKeDaXunFeiSoundSettings.h"
#include "Core/XGAudioCaptureSubsystem.h"

bool UXGKeDaXunFeiSocketSubsystem::bSending = false;
TSharedPtr<IWebSocket> UXGKeDaXunFeiSocketSubsystem::Socket = {};

UXGAudioCaptureSubsystem* UXGKeDaXunFeiSocketSubsystem::XGAudioCaptureSubsystem = nullptr;
bool UXGKeDaXunFeiSocketSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UXGKeDaXunFeiSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Appid = UXGKeDaXunFeiSoundSettings::GetDataBaseSettings()->AppID;
	APIKey = UXGKeDaXunFeiSoundSettings::GetDataBaseSettings()->APIKeySTT;



//	FConsumeSoundRunnable* Runnable1 = new FConsumeSoundRunnable(TEXT("�߳�1"));
//	FConsumeSoundRunnable* Runnable2 = new FConsumeSoundRunnable(TEXT("�߳�2"));
//	FRunnableThread* RunnableThread1 = FRunnableThread::Create(Runnable1, *Runnable1->MyThreadName);
//	FRunnableThread* RunnableThread2 = FRunnableThread::Create(Runnable2, *Runnable2->MyThreadName);
//	Runnable2->Stop();

}

void UXGKeDaXunFeiSocketSubsystem::Deinitialize()
{

}

void UXGKeDaXunFeiSocketSubsystem::Tick(float DeltaTime)
{

}

bool UXGKeDaXunFeiSocketSubsystem::IsTickable() const
{
	 return !IsTemplate(); 
}

TStatId UXGKeDaXunFeiSocketSubsystem::GetStatId() const
{
 RETURN_QUICK_DECLARE_CYCLE_STAT(UXGKeDaXunFeiSocketSubsystem, STATGROUP_Tickables); 
}

void UXGKeDaXunFeiSocketSubsystem::XGBeginSpeachToText(FXGBeginSpeachToTextDelegate InXGBeginSpeachToTextDelegate, FXGSpeachToTextDelegate InXGSpeachToTextDelegat)
{
	if (bSpeechToText)
	{
		return;
	}
	bSpeechToText = true;
	XGBeginSpeachToTextDelegate = InXGBeginSpeachToTextDelegate;
	XGSpeachToTextDelegate = InXGSpeachToTextDelegat;



	CreateSocket();


}

void UXGKeDaXunFeiSocketSubsystem::XGStopSpeachToText()
{
	if (!bSpeechToText)
	{
		return;
	}
	bSpeechToText = false;
	bSending = false;
	XGBeginSpeachToTextDelegate.Clear();
	XGSpeachToTextDelegate.Clear();

	XGAudioCaptureSubsystem->StopCapturingAudio();
	if (VoiceRunnable.IsValid())
	{
		VoiceRunnable->Stop();
	}
	EndSendVoiceData();



}

void UXGKeDaXunFeiSocketSubsystem::CreateSocket()
{

	FModuleManager::Get().LoadModuleChecked("WebSockets");


	FString BaseString = TEXT("");
	FString TS = TEXT("1512041814");
	TS = FString::FromInt(FDateTime::Now().UtcNow().ToUnixTimestamp());
	BaseString = Appid + TS;


	FString MD5BaseString = FMD5::HashAnsiString(*BaseString);


	FSHAHash Hash;
	FSHA1 SHA1;
	SHA1.HMACBuffer(TCHAR_TO_ANSI(*APIKey), APIKey.Len(), TCHAR_TO_ANSI(*MD5BaseString), MD5BaseString.Len(), Hash.Hash);
	FString WrongSigna1 = Hash.ToString();
	FString WrongSigna2 = FBase64::Encode(WrongSigna1);
	FString Signa = FBase64::Encode(Hash.Hash, 20);
	Signa.ReplaceInline(TEXT("="), TEXT("%3D"));

	ServerProtocol = TEXT("ws");
	//ws://rtasr.xfyun.cn/v1/ws?appid=595f23df&ts=1512041814&signa=IrrzsJeOFk1NGfJHW6SkHUoN9CU=&pd=edu
	ServerURL = TEXT("ws://rtasr.xfyun.cn/v1/ws?");
	ServerURL += TEXT("appid=");
	ServerURL += Appid;

	ServerURL += TEXT("&");
	ServerURL += TEXT("ts=");
	ServerURL += TS;

	ServerURL += TEXT("&");
	ServerURL += TEXT("signa=");
	ServerURL += Signa;


	ServerURL += TEXT("&");
	ServerURL += TEXT("pd=edu");
	

	ServerURL += TEXT("&lang=cn&transType=normal&transStrategy=2&targetLang=en");
	//ServerURL += TEXT("&transStrategy=3");

	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);
	Socket->OnConnected().AddUObject(this, &UXGKeDaXunFeiSocketSubsystem::OnConnected);
	Socket->OnConnectionError().AddUObject(this, &UXGKeDaXunFeiSocketSubsystem::OnConnectionError);
	Socket->OnClosed().AddUObject(this, &UXGKeDaXunFeiSocketSubsystem::OnClosed);
	Socket->OnMessage().AddUObject(this, &UXGKeDaXunFeiSocketSubsystem::OnMessage);
	Socket->OnMessageSent().AddUObject(this, &UXGKeDaXunFeiSocketSubsystem::OnMessageSent);

	Socket->Connect();


}

void UXGKeDaXunFeiSocketSubsystem::CloseSocket()
{	
	bSending = false;
	if (Socket.IsValid()&& Socket->IsConnected())
	{
		Socket->Close();
	}

	bSpeechToText = false;
	XGBeginSpeachToTextDelegate.Clear();
	XGSpeachToTextDelegate.Clear();

}

void UXGKeDaXunFeiSocketSubsystem::SendVoiceData(const float* InAudio, int32 NumSamples)
{
	if (Socket.IsValid()&& Socket->IsConnected()&& bSending)
	{
		//�����õ�������ʵ����2048�������� ÿ�������㶼��float����,4���ֽ�,32λ

		//����ÿ64ms ����1024����������Ϣ,һ����������2���ֽ�,16λ.
		//����2048���ֽ�

		TArray<int16> ToChangeAuidoData;
		TArray<uint8> BinaryDataToSend;
		int32 i = 0;
		for (; i < 1024;)
		{	//-1.0~1.0
			ToChangeAuidoData.Add((int16)FMath::Clamp<int32>(FMath::FloorToInt(32767.0f * InAudio[i]), -32768, 32767));
			

			//0100 0010 0001 0010


			uint8 Bytes[2];
			//ȡ�����ݵĵ�λ����
			//0001 0010
			Bytes[0] = (uint8)(ToChangeAuidoData[i] & 0xFF);
			//ȡ�����ݵĸ�λ����
			//100 0010
			Bytes[1] = (uint8)((ToChangeAuidoData[i] >> 8) & 0xFF);

			//01 23 45 67
			//С�˴洢�ѵ�λ���ݷŵ����ֽ�
			BinaryDataToSend.Add(Bytes[0]);
			//С�˴洢�Ѹ�λ���ݷŵ����ֽ�
			BinaryDataToSend.Add(Bytes[1]);

			i++;
		}

		Socket->Send(BinaryDataToSend.GetData(), BinaryDataToSend.Num(), true);




	}



}

void UXGKeDaXunFeiSocketSubsystem::EndSendVoiceData()
{
	if (Socket.IsValid() && Socket->IsConnected() && !bSending)
	{
		FString EndStr = TEXT("{\"end\": true}");

	
	/*	TArray<uint8> MyByteArray;
		const TCHAR* CharPtr = *EndStr;
		const int32 Length = EndStr.Len();
		for (int32 i = 0; i < Length; ++i)
		{
			MyByteArray.Add(static_cast<uint8>(CharPtr[i]));
		}
*/

	/*
		��Ҫע����ǣ�strlen����ֻ�����ڼ�����NULL�ַ���β���ַ����ĳ��ȣ������ʹ����ʱ����Ҫȷ����������ַ�����NULL�ַ���β��
		��UE4�У�ʹ��TCHAR_TO_UTF8��ת�����ַ����Ѿ����Զ������NULL�ַ������Կ���ֱ��ʹ��strlen������
	*/

		const char * CharValue = TCHAR_TO_UTF8(*EndStr);
		int32 Length = strlen(CharValue);
		Socket->Send(CharValue, Length, true);

	}
}

void UXGKeDaXunFeiSocketSubsystem::StopSenVoiceData()
{
	bSending = false;
}

void UXGKeDaXunFeiSocketSubsystem::OnConnected()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void UXGKeDaXunFeiSocketSubsystem::OnConnectionError(const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Error:%s"), *FString(__FUNCTION__), *Error);
	
	bSpeechToText = false;
	XGBeginSpeachToTextDelegate.ExecuteIfBound(false);
	XGBeginSpeachToTextDelegate.Clear();
	XGSpeachToTextDelegate.Clear();


}

void UXGKeDaXunFeiSocketSubsystem::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	UE_LOG(LogTemp, Warning, TEXT("%s StatusCode:%d Reason:%s bWasClean:%d"),
		*FString(__FUNCTION__), StatusCode, *Reason, bWasClean);

	bSending = false;
	bSpeechToText = false;
	XGBeginSpeachToTextDelegate.Clear();
	XGSpeachToTextDelegate.Clear();

	XGAudioCaptureSubsystem->StopCapturingAudio();
	if (VoiceRunnable.IsValid())
	{
		VoiceRunnable->Stop();
	}



}

void UXGKeDaXunFeiSocketSubsystem::OnMessage(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Message:%s"), *FString(__FUNCTION__), *Message);

/*
	TSharedPtr<FJsonObject> ResultObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
	FJsonSerializer::Deserialize(Reader, ResultObj);

	TSharedPtr<FJsonObject> DataObj=  ResultObj->GetObjectField("data");
	TSharedPtr<FJsonObject> cnObj = ResultObj->GetObjectField("cn");
	TSharedPtr<FJsonObject> stObj = ResultObj->GetObjectField("st");
	TArray< TSharedPtr<FJsonValue> > rtArray =  stObj->GetArrayField("rt");
	for (auto& Tmp: rtArray)
	{
		if (TSharedPtr<FJsonObject> InJsonObject = Tmp->AsObject())
		{

		}
	}
*/
	if (!Message.IsEmpty())
	{
		TSharedPtr<FJsonObject> ResultObj;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
		FJsonSerializer::Deserialize(Reader, ResultObj);

		FString MessageAction;





		if (ResultObj->TryGetStringField("action", MessageAction))
		{


			if (MessageAction.Equals(TEXT("started")))
			{
				bSending = true;
				bSpeechToText = true;

				XGAudioCaptureSubsystem->StartCapturingAudio();
				VoiceRunnable = MakeShareable(  new FConsumeSoundRunnable(TEXT("VoiceRunnable")));
				FRunnableThread* RunnableThread1 = FRunnableThread::Create(VoiceRunnable.Get(), *VoiceRunnable->MyThreadName);
				
				
			}


			if (MessageAction.Equals(TEXT("error")))
			{
				bSending = false;
				bSpeechToText = false;

				XGBeginSpeachToTextDelegate.ExecuteIfBound(false);
				XGBeginSpeachToTextDelegate.Clear();
				XGSpeachToTextDelegate.Clear();


			}



			if (MessageAction.Equals(TEXT("result")))
			{
					FString OutText;
					if (ResultObj->TryGetStringField("data", OutText))
					{
						if (!OutText.IsEmpty())
						{
							TSharedPtr<FJsonObject> DataObj;
								TSharedRef<TJsonReader<>> Reader2 = TJsonReaderFactory<>::Create(OutText);
								FJsonSerializer::Deserialize(Reader2, DataObj);

							FString dst;
							FString src;
							FString end;

							bool bDest = DataObj->TryGetStringField(TEXT("dst"), dst);
							bool bSrc = DataObj->TryGetStringField(TEXT("src"), src);
							bool bEnd = DataObj->TryGetStringField(TEXT("ed"), end);
							int32 EndNum = FCString::Atoi(*end);
							bEnd = EndNum > 0 ? true : false;

							if (bDest && bSrc&& bEnd)
							{
								UE_LOG(LogTemp, Warning, TEXT("dst :%s Message [src]:%s"), *dst, *src);
								XGSpeachToTextDelegate.ExecuteIfBound(src,dst);
						
							}



						}


					}
			}

	


		}


		
	}
	

}

void UXGKeDaXunFeiSocketSubsystem::OnMessageSent(const FString& MessageString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s MessageString:%s"), *FString(__FUNCTION__), *MessageString);
}
