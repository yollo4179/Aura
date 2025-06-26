// copyright
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"Character/EnemyCharacter.h"
#include"Interact/EnemyInterface.h"
#include "Player/AuraPlayerController.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;  
	// 서버에서 어떤 개체의 변화가 있을때 그 서버에서의 변화는 모든 클라이언트에 전달되거나 복사된다. 
	//그러니까 여러 장치에서 변화가 일어난는것에 대한 개념을 가지게된다.
	//서버에서의 변화0-> 클라이언트에 뿌리기
	//컨트롤러더 그 과정에 참여하도록 하는것(복사된 개체가 되는 것)을 잊지 말것
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	//자동으롷 싱글톤. 
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(nullptr != SubSystem)
	{
		SubSystem->AddMappingContext(AuraContext, 0); //0은 우선순위. 0이 가장 높다.
	}
	//LoaclPlayer만이 이값이 널이 아니므로 SubSystem에서 터지지 않고 넘어간다.
	

	//이제 이 컨트롤러는 AuraContext에 정의된 입력을 사용할 수 있다.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false); //커서가 캡쳐되는 동안 숨기지 않음
	SetInputMode(InputModeData); //게임과 UI 모두에서 입력을 받을 수 있도록 설정


}
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}
void AAuraPlayerController::CheckIfVitalInfoChanged()
{


}
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();

}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit = {};
	GetHitResultUnderCursor(ECC_Visibility,false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = ThisActor; 
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (nullptr == ThisActor)
	{
		if (nullptr != LastActor)
			LastActor->UnHighlightActor();
	}
	else
	{
		if (nullptr == LastActor)
			ThisActor->HighlightActor();


		else if (LastActor != ThisActor) {
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
	}
	//LastActor == nullptr &&This Actor ==nullptr 
	//do nth
	//LastActor == nullptr &&This Actor == mon 1 
	// highlight this
	//LastActor == mon 2 &&This Actor == mon 1 
	// UnHighlight mon2 Highlight mon1
	//LastActor == mon 1 &&This Actor == nullptr
	//UnHighlight mon 1 
	//LastActor == mon 1 &&This Actor == mon 1 
	//do nth





	if (ThisActor&&true ==ThisActor->GetHighlighted())
	{
		FHitResult HitResult{};
		AEnemyCharacter* pEnemy = Cast<AEnemyCharacter>(ThisActor);
		DrawDebugSphere(GetWorld(),pEnemy->GetActorLocation(),40.F,10.F,FColor::Red,false,-1.f);
	}




}
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();	
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //앞으로 이동하는 방향
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //오른쪽으로 이동하는 방향
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Forward, MoveValue.Y); //앞뒤 이동
		ControlledPawn->AddMovementInput(Right, MoveValue.X); //양옆 이동
	}


}
