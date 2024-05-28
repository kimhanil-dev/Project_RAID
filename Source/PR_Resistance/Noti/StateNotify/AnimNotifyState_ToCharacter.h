// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

// interface
#include "PR_Resistance/Noti/StateNotify/ReceiverInterface/NotifyState_ToCharacterReceiver.h"

#include "AnimNotifyState_ToCharacter.generated.h"

/**
 * 
 */

 /*
    �ִϸ��̼ǿ����� ��κ��� Notification�� ���
    �޴� Actor�� INotifyState_ToCharacterReceiver�� ��ӹ޾ƾ� ��.
    ������ �������̽��� �ִ� EAnimNotifyToCharacterTypes�� ���� ������
 */
UCLASS()
class PR_RESISTANCE_API UAnimNotifyState_ToCharacter : public UAnimNotifyState
{
	GENERATED_BODY()

    // from UAnimNotifyState inherited
    void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

 private:
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    EAnimNotifyToCharacterTypes mType;
};
