// copyright

#pragma once

UENUM(BlueprintType)
enum class eEffectApplicationPolicy :uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};

UENUM(BlueprintType)
enum class eEffectRemovalPolicy :uint8
{
	RemoveOnEndOverlap,
	DoNotRemove,
};
class  UAbilitySystemComponent;


#include"GameplayEffectTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MH_EffectActor.generated.h"


USTRUCT(BlueprintType)
struct FInstantEffectData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf< UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectApplicationPolicy eApplicationPolicy = eEffectApplicationPolicy::DoNotApply;

	//�ٷ� ������ ������

};
USTRUCT(BlueprintType)
struct FDurationEffectData
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> EffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectApplicationPolicy eApplicationPolicy = eEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectRemovalPolicy eEffectRemovalPolicy = eEffectRemovalPolicy::DoNotRemove;
	
	//�ð��� ������ ����� (��� ����Ʈ ����Ʈ �Ҵ�)
};

USTRUCT(BlueprintType)
struct FInfiniteEffectData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> EffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectApplicationPolicy eApplicationPolicy = eEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectRemovalPolicy eEffectRemovalPolicy = eEffectRemovalPolicy::DoNotRemove;
	//� �̺�Ʈ ���� �ÿ��� �����-> ���� ���, ������ ������ �����, �ƴϸ� ��� ������
};

/*Ǯ��*/
USTRUCT(BlueprintType)
struct FEffectPoolData
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	eEffectApplicationPolicy EffectApplicationPolicy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	eEffectRemovalPolicy eEffectRemovalPolicy = eEffectRemovalPolicy::DoNotRemove;
};



UCLASS()
class AURA_API AMH_EffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMH_EffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:


	UFUNCTION(BlueprintCallable)//�翬��, �����÷��� ����Ʈ�� �����Ǹ� �������Ʈ���� ȣ���ؾ��Ѵ�. 
	void ApplyEffectToTarget(AActor* _pTargetActor, TSubclassOf <class UGameplayEffect> _EffectClass);
	/*Call ApplyEffects*/
	UFUNCTION(BlueprintCallable)
	void ApplyEffectOnBeginOverlap(AActor* pTargetActor);
	UFUNCTION(BlueprintCallable)
	void ApplyEffectOnEndOverlap(AActor* pTargetActor);


	//Remove Effects 
	UFUNCTION(BlueprintCallable)
	void RemoveEffectsOnEndOverlap(AActor* pTargetActor);

	UFUNCTION(Blueprintcallable)
	void RemoveEffect(AActor* pTargetActor);



	/*UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* pTargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* pTargetActor);*/


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Effects")
	bool bDestroyOnEffectRemoval = { false };// ����Ʈ�� ���ŵǸ� ���͸� �ı����� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Effects")
	bool bShouldRemove= { true };// ����Ʈ�� ���ŵǸ� ���͸� �ı����� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="GAS|Effects")
	TArray<FInstantEffectData> InstantEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Effects")
	TArray<FDurationEffectData> DurationEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Effects")
	TArray<FInfiniteEffectData> InfiniteEffects;



	UPROPERTY(EditAnywhere, Category ="GAS|Level")
	float fEffectActorLevel = {};
private:
	/*For Map*/
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent *>ActiveEffectHandles;
	UPROPERTY()
	TArray<FEffectPoolData> EffectPool;
	UFUNCTION()
	void CreateEffectPool();

};



