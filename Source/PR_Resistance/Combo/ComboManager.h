// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "PR_Resistance/Combo/Action.h"
#include "Animation/AnimInstance.h"
#include "PR_Resistance/SlotMotionProcess.h"

#include <functional>
#include "ComboManager.generated.h"

/**
 *
 */
class UAttack;
class APR_ResistanceCharacter;
UCLASS()
class PR_RESISTANCE_API UComboManager : public UObject
{
	GENERATED_BODY()
public:
	UComboManager();
	~UComboManager();

protected:
	TMap<FName, const FAction*> Actions;
	TMap<ActionInput, const FAction*> StartActions;
	const FAction* mCurAction = nullptr;
	UAnimInstance* mOwnerAnimInst = nullptr;
	UAnimMontage* mCurDynmMontage = nullptr;

	std::function<void()> ComboEndEvent;
	std::function<void()> ActionChangeEvent;

        //UObject������ RPC�� �Ұ��� �ϱ� ������ ���ٷ� Function�� �Ѱ��־� PR_ResistanceCharaceter���� �����Ų��.
	APR_ResistanceCharacter* mOwner;


	bool mbIsWait = false;
	float mCurWaitTime = 0.0f;
	float mEalsedTime = 0.0f;
	float mAnimationElapsedTime = 0.0f;
public:
	UAttack* mState = nullptr;
	

	void Init(APR_ResistanceCharacter* _SlotMotionQueue , UDataTable* actionTable, UAnimInstance* animInstance);
	void Update(float deltaTime);
	bool StartAttack(FName firstAttack);
	void StartWaitInput();
	void PushInput(ActionInput inputType);
	void BindComboAndEvent(std::function<void()> function);
	void BindActionChangeEvent(std::function<void()> function);
	void SetComboEnd();

protected:
	bool ChangeAction(FName actionName);
	bool ChangeAction(const FAction* action);

	void PlayerSlotAnimation(FName slotName, UAnimSequenceBase* animSequence);
	void StopSlotAnimation(FName slotName);
};
