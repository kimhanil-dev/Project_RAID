// Fill out your copyright notice in the Description page of Project Settings.


#include "UDodge.h"
#include "PR_Resistance/StatesSystem/CharacterDataArchive.h"
#include "PR_Resistance/Interface/IStaminaProvider.h"
#include "PR_Resistance/Chara/PR_ResistanceCharacter.h"

#include <cassert>

UDodge::UDodge()
{
	mDesc.StateType = (uint8)CharacterState::CS_DODGE;
	mDesc.Priority = 11;
}

UDodge::~UDodge()
{
}

bool UDodge::_Init()
{
	void* buffer = nullptr;
	if (GetCharacterDataArchive()->GetData("Status", &buffer))
	{
		mChracterStatus = (FStatus*)buffer;
		if (mSPProvider->UseStamina(mChracterStatus->maxStamina * mChracterStatus->DodgeStamina))
		{
			mElapsedTime = 0.0f;
			if (GetCharacterDataArchive()->GetData("MovementSpeed", &buffer))
			{
				mMaxWalkSpeed = (float*)buffer;
				(*mMaxWalkSpeed) = mChracterStatus->DodgeDistance / mChracterStatus->DodgeTime;
			}

			if (GetCharacterDataArchive()->GetData("CharacterVelocity", &buffer))
			{
				FVector* velocity = (FVector*)buffer;
				if (GetCharacterDataArchive()->GetData("LastInputVector", &buffer))
				{
					FVector* lastInputVector = (FVector*)buffer;
					(*velocity) = (*lastInputVector) * (*mMaxWalkSpeed);
				}
			}
		}
		else
		{
			mDesc.bIsEnd = true;
		}
	}

	GetCharaDataWithLog("AnimTable", &buffer);
	{
		UDataTable* animTable = static_cast<UDataTable*>(buffer);
		mDodgaAnim = animTable->FindRow<FCharacterAnimationData>(TEXT("Dodge"), nullptr)->mAnimation;
	}
	GetCharaDataWithLog("AnimInstance", &buffer);
	{
		mAnimInstance = static_cast<UAnimInstance*>(buffer);
		
		mAnimInstance->OnMontageEnded.AddDynamic(this, &UDodge::OnAnimEnd);
	}
	GetCharaDataWithLog("RootComponent", &buffer);
	{
		mCharacterRootComponent = static_cast<USceneComponent*>(buffer);
	}
	GetCharaDataWithLog("Owner", &buffer);
	{
		mOwner = static_cast<APR_ResistanceCharacter *>(buffer);
	}

	
	return true;
}


bool UDodge::Begin(uint8 prevState)
{
	if(prevState == (uint8)CharacterState::CS_JUMP 
	|| prevState == (uint8)CharacterState::CS_JUMPDASH)
		return false;

	assert(mSPProvider == nullptr);

	mOwner->PlaySlotAnimation(TEXT("DefaultSlot"), mDodgaAnim);

	return true;
}

void UDodge::Update(float deltaTime)
{
	if (mElapsedTime >= (mDodgaAnim->GetPlayLength() *0.5f))
	{
		(*mMaxWalkSpeed) = 0.0f;
		mElapsedTime = 0.0f;
		mDesc.bIsEnd = true;
	}
	else
	{
		mElapsedTime+= deltaTime;
	}
}

void UDodge::End()
{
}

void UDodge::SetProvider(IStaminaProvider* provider)
{
	assert(provider == nullptr);
	mSPProvider = provider;
}

void UDodge::OnAnimEnd(UAnimMontage* motange, bool bInterrupted)
{
	if(mDodgeAnim == motange)
	{
		mDesc.bIsEnd = true;
	}
}
