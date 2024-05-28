// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDataArchive.generated.h"
/**
 * 
 */
 UCLASS()
class PR_RESISTANCE_API UCharacterDataArchive : public UObject
{
	GENERATED_BODY()
private:
	TMap<FName,void*> mDatas;
public:
	UCharacterDataArchive();
	~UCharacterDataArchive();

	/*
	* clear data map
	*/
	void Init();
	/*
	* key : �����͸� ã���� ���� Ű��
	* data : ������ ������, �������� �����ֱ�� AddData�� ���� ��ü�� å������.
	*/
	bool AddData(FName key, void* data);
	/*
	* Ű�� �ش��ϴ� �����͸� Archive���� �����Ѵ�.
	*/
	void RemoveData(FName key);
	/*
	*  data : �� ���޿� ������
	*  return : false �� ã�� ����, true ã�� ����
	*/
	bool GetData(FName key, _Out_ void** data);
};
