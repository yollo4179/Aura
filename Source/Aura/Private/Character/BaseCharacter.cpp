// copyright



#include "Character/BaseCharacter.h"
#include"AbilitySystemComponent.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_pWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	m_pWeapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	m_pWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);




}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffecClass, float Level)const 
{
	//애트리뷰는 모두 Replicated Using 으로 마크 해놨으므로

	//서버에서만 한번 불리면 됌 ( 1.초기화 + 2.레플리케이션으로 클라에 뿌리기 )
	check(GetAbilitySystemComponent());
	check(GameplayEffecClass);

	UAbilitySystemComponent* pASC = GetAbilitySystemComponent();

	FGameplayEffectContextHandle ContextHandle = pASC->MakeEffectContext();
	//ContextHandle.AddSourceObject(this);

	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHadle = pASC->MakeOutgoingSpec(GameplayEffecClass, 1.f, ContextHandle);

	pASC->ApplyGameplayEffectSpecToTarget(*(SpecHadle.Data.Get()), pASC);

	//Primary Attribute를 초기화하기 위해 필요한 전제 조건: ASC 가 일단 존재해야함 ( null이 아니어야 함) 
	// ,Attribute set이 일단 생성되어 야 초기화 가능 -->Attribute Actor Info채울때 하면 됌
}
void ABaseCharacter::InitDefaultAttributes() const
{
	ApplyEffectToSelf(m_PrimaryEffectClass,1.f);
	ApplyEffectToSelf(m_SecondaryEffectClass,1.f);
	ApplyEffectToSelf(m_VitalEffectClass, 1.f);
}

 UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent()const 
{
	 return m_pAbilitySystemComponent;
}

