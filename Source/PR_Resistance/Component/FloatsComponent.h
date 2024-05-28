// Fill out your copyright notice in the Description page of Project Settings.

#pragma once 

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatsComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFloatListener : public UInterface
{
	GENERATED_BODY()
};

class PR_RESISTANCE_API IFloatListener
{
	GENERATED_BODY()
public:
	virtual void ListenFloat(int index, float newFloat) = 0;
};


DECLARE_DYNAMIC_DELEGATE_FourParams(FDele_CheckCondition, uint8, Index, float, originValue, float, newValue, float, prevValue);

UCLASS( ClassGroup=(Float), meta=(BlueprintSpawnableComponent) )
class PR_RESISTANCE_API UFloatsComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<TArray<IFloatListener*>*> mListeners;
	UPROPERTY();
	TArray<float> mFloats;
	UPROPERTY();
	TArray<float> mOriginFloats;

public:	
	// Sets default values for this component's properties
	UFloatsComponent();
	~UFloatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	//native call
	void	MakeFloats(uint8 size); // size ���� ��ŭ float�� ���� �մϴ�. 0 ~ (size -1), ������ 0 ~ (size - 1) ������ �� ���� �����˴ϴ�.
	bool	AddListener(IFloatListener* newFloatListener, uint8 index); // index�� �ش�Ǵ� float�� �������� ������ �����մϴ�.
	void	AddConditionChecker(FDele_CheckCondition func, uint8 index);
	
	int		PushBack(float newValue); // ����� ��ȯ�մϴ�.

	int		GetSize();
	bool	Set(const float newValue, uint8 index);		// index�� �ش��ϴ� float�� �������� ������ false ��ȯ
	bool	Get(uint8 index, float& out);				// index�� �ش��ϴ� float�� �������� ������ false ��ȯ
public: //blueprint call

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisplayName = "MakeFloats"))
	void MakeFloats_bp(uint8 size);

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisplayName = "PushBack"))
		void PushBack_bp(float newValue, int& size);

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisplayName = "Get"))
	void Get_bp(uint8 index, float& value, bool& isValid);

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisplayName = "Set"))
	void Set_bp(float newValue, uint8 index, bool& isValid);

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisPlayName = "AddConditionChecker"))
	void AddConditionChecker_bp(uint8 index, const FDele_CheckCondition& func);

	UFUNCTION(BlueprintCallable, Category = Floats, meta = (DisPlayName = "AddListener"))
		void AddListener_bp(uint8 index, const TScriptInterface<IFloatListener>& newFloatListener);
	
	/*DECLARE_EVENT_TwoParams(UFloatsComponent, FConditionEvent, uint8, float);
	FConditionEvent& OnStateChange();

	inline void BindStateChangeCall( func)
	{
		mChangeEvent.Add(func);
	}*/

private:
	TArray<TArray<FDele_CheckCondition>> mConditionCheckers;
};
