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
	//��Ʈ����� ��� Replicated Using ���� ��ũ �س����Ƿ�

	//���������� �ѹ� �Ҹ��� �� ( 1.�ʱ�ȭ + 2.���ø����̼����� Ŭ�� �Ѹ��� )
	check(GetAbilitySystemComponent());
	check(GameplayEffecClass);

	UAbilitySystemComponent* pASC = GetAbilitySystemComponent();

	FGameplayEffectContextHandle ContextHandle = pASC->MakeEffectContext();
	//ContextHandle.AddSourceObject(this);

	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHadle = pASC->MakeOutgoingSpec(GameplayEffecClass, 1.f, ContextHandle);

	pASC->ApplyGameplayEffectSpecToTarget(*(SpecHadle.Data.Get()), pASC);

	//Primary Attribute�� �ʱ�ȭ�ϱ� ���� �ʿ��� ���� ����: ASC �� �ϴ� �����ؾ��� ( null�� �ƴϾ�� ��) 
	// ,Attribute set�� �ϴ� �����Ǿ� �� �ʱ�ȭ ���� -->Attribute Actor Infoä�ﶧ �ϸ� ��
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

