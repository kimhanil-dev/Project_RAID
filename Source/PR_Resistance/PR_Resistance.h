// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(PRR, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(PRR,Verbosity,TEXT("%s"), *ABLOG_CALLINFO)																// ���� �̸�, �Լ�, ���� ������ �߰��� �α�
#define ABLOG(Verbosity, Format, ...) UE_LOG(PRR, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))		// ABLOG_S�� ���� ���ڿ��� �߰� ������ ������ �α�

