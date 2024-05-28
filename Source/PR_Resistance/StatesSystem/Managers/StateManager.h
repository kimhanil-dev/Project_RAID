// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PR_Resistance/StatesSystem/StateDesc.h"
#include "PR_Resistance/StatesSystem/CState.h"
#include "StateManager.generated.h"

/**
 * 
 */

 USTRUCT(BlueprintType)
 struct FChracterState
 {
	GENERATED_BODY()
	public:
	UPROPERTY()
		TMap<uint8, UCState*> mStateContainer;
 };

 UCLASS(ClassGroup = (FSM), meta = (BlueprintSpawnableComponent))
class PR_RESISTANCE_API UStateManager : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(Replicated)
		TArray<FChracterState> mStateContiners;

	UPROPERTY(Replicated)
		UCharacterDataArchive* mCDArchive = nullptr;

	UPROPERTY(Replicated)
		UCState* mCurState = nullptr;

	TQueue<FStateDesc> mStateChangeCalls;
	FChracterState mStates; // State����Ʈ�� �����Ϳ��� ������ �ֵ���
public:
	UStateManager();
	//UStateManager(int stateTypeNum = 1);
	//UStateManager(CharacterDataArchive * const archive);
	virtual ~UStateManager();

	/*
	* Init ȣ�� ������ AddArchiveData�� ȣ��Ǿ�� �մϴ�.
	*/
	virtual bool Init();
	virtual void LoadStates() {}
	/*
	* State������ �õ��մϴ�.
	* FStateDesc�� Priority�� ���� �����ϰų� �����մϴ�.
	* ���� �����ӿ� �õ��˴ϴ�.
	*/
	UFUNCTION(Reliable, Server)
		virtual void TryChangeState(uint8 stateType);
	/*
	* ���� ���¸� �����ŵ�ϴ�.
	*/
	UFUNCTION(Reliable, Server)
	void SetStateEnd(uint8 stateType);
	/*
	* Priroty�� �����ϰ� ��� ���¸� �����մϴ�.
	*/
	UFUNCTION(Reliable, Server)
		void SetState(uint8 stateType);

	// UActorComponent
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FStateDesc GetCurStateDesc();

	/*
	* key : �����͸� ã���� ���� Ű���Դϴ�.
	* data : ������ �������Դϴ�. �������� �����ֱ�� �Լ��� ȣ���� ��ü�� å�������մϴ�.
	* return : ������ true, ���н� false�� �����մϴ�.
	*/
		bool AddArchiveData(FName key, void* data);
		void RemoveArchiveData(FName key);


	UFUNCTION(BlueprintCallable, Category = FSM, meta = (DisplayName = "AddStateData"))
		void AddStateData_bp(const int index, const uint8 stateName, const UCState* newState, UCState*& ret);

	UFUNCTION(BlueprintCallable, Category = FSM, meta = (DisplayName = "GetCurStateData"))
		void GetCurState_bp(UCState*& curState);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
public: //Event
	// ���°� ���Ҷ����� ȣ��									prevState		curState
	DECLARE_EVENT_TwoParams(UStateManager, FChangeEvent, uint8, uint8);
	FChangeEvent& OnStateChange();

	inline void BindStateChangeCall(const TBaseDelegate<void, uint8, uint8> func)
	{
		mChangeEvent.Add(func);
	}

private: // Event
	FChangeEvent mChangeEvent;
protected:
        UFUNCTION(Reliable,Server)
	virtual void Update(float deltaTime);

	UCharacterDataArchive * GetCharacterDataArchive();
	void SetCharacterDataArchive(UCharacterDataArchive* archive);

	void ChangeStateContainer(int index);
	bool ChangeState(UCState* newState);
public:
#define AddStateData_uint8(Index, State, StateClass) AddStateData(Index, static_cast<uint8>(State),NewObject<StateClass>())
#define SetDefaultState_uint8(Index, State) SetDefaultState(Index, static_cast<uint8>(State))
	void SetDefaultState(int index, uint8 state);
	UCState* AddStateData(int index, uint8 stateName, UCState* newState, bool isDoInit = true);
	UCState* GetStateData(int index, uint8 stateName);
};
