// Copyright 2023 Xiao Gang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// ͷ��Ϣ ��ʽ+�����ݴ�С
// ��ʽ������Ϣ �������ݸ�ʽ������
// ������Ϣ���� +���ݴ�С
//  ����������
//12���ֽ�
struct FXGiFlyTekWaveHeard
{
	//4���ֽ�
	int8 ChunkID[4];
	//4���ֽ� 36+���ݴ�С ������ ChunkID  ChunkSize 4+ 24 +8 =36
	uint32 ChunkSize;
	//4���ֽ� 
	int8 Format[4];
};

//24���ֽ�
struct FXGiFlyTekWaveFmt
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
struct FXGiFlyTekWaveData
{
	//4���ֽ�
	int8 DataChunkID[4];
	//4���ֽ�
	uint32 DataChunkSize;

};
//׷�Ӷ���������