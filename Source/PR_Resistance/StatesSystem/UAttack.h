// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PR_Resistance/PR_Resistance.h"
#include "PR_Resistance/StatesSystem/CState.h"
#include "PR_Resistance/Interface/IStaminaUser.h"
#include "PR_Resistance/Combo/Action.h"

#include "UAttack.generated.h"
/**
 * 
 */
 class UComboManager;
 class UAnimInstance;
 class UCameraComponent;
 class UDataTable;
 UCLASS()
 class PR_RESISTANCE_API UAttack : public UCState, public IStaminaUser
{
	GENERATED_BODY()
protected:
	IStaminaProvider* mSPProvider = nullptr;
	FStatus* mCharacterStatus = nullptr;

	UPROPERTY()
	UComboManager* mComboManager = nullptr;
	ActionInput* AInput = nullptr;
	UCameraComponent* mCamera = nullptr;
	AActor* mOwner = nullptr;
public:
	UAttack();
	~UAttack();

	bool Begin(uint8 prevState) override;
	void Update(float deltaTime) override;
	void End() override;
	void SetProvider(IStaminaProvider* provider) override;
	void SetStop() override;
	void StopAttack();

protected:
	bool _Init() override;
	void OnChangeAction();
};
