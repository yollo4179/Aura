// copyright

#include"AbilitySystem/MH_AttributeSet.h"
#include"Player/AuraPlayerState.h"
#include"Character/AuraCharacter.h"
#include "Actor/MH_EffectActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AMH_EffectActor::AMH_EffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(m_pMeshComponent);
	m_pSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	m_pSphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMH_EffectActor::BeginPlay()
{
	Super::BeginPlay();

	/*Delegate Registelation*/
	m_pSphere->OnComponentBeginOverlap.AddDynamic(this, &AMH_EffectActor::OnOverlapBegin);
	m_pSphere->OnComponentEndOverlap.AddDynamic(this, &AMH_EffectActor::OnOverlapEnd);
}


void AMH_EffectActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* pAura = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMH_AttributeSet* pAttributeSet = Cast<UMH_AttributeSet>(pAura->GetAbilitySystemComponent()->GetAttributeSet(UMH_AttributeSet::StaticClass()));

		UMH_AttributeSet* pMutableAttributeSet = const_cast<UMH_AttributeSet*>(pAttributeSet);
		//pMutableAttributeSet->SetHealth();

		float m_HealthDelta = 25.f; // Example value, you can set this to whatever you need
		pMutableAttributeSet->SetHealth(pAttributeSet->GetHealth() + m_HealthDelta);


		
		pMutableAttributeSet->SetMana(pAttributeSet->GetMana() + m_HealthDelta);
		Destroy();
	}


}
void AMH_EffectActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

