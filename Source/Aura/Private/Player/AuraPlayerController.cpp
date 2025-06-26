// copyright
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include"Character/EnemyCharacter.h"
#include"Interact/EnemyInterface.h"
#include "Player/AuraPlayerController.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;  
	// �������� � ��ü�� ��ȭ�� ������ �� ���������� ��ȭ�� ��� Ŭ���̾�Ʈ�� ���޵ǰų� ����ȴ�. 
	//�׷��ϱ� ���� ��ġ���� ��ȭ�� �Ͼ�°Ϳ� ���� ������ �����Եȴ�.
	//���������� ��ȭ0-> Ŭ���̾�Ʈ�� �Ѹ���
	//��Ʈ�ѷ��� �� ������ �����ϵ��� �ϴ°�(����� ��ü�� �Ǵ� ��)�� ���� ����
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	//�ڵ����� �̱���. 
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(nullptr != SubSystem)
	{
		SubSystem->AddMappingContext(AuraContext, 0); //0�� �켱����. 0�� ���� ����.
	}
	//LoaclPlayer���� �̰��� ���� �ƴϹǷ� SubSystem���� ������ �ʰ� �Ѿ��.
	

	//���� �� ��Ʈ�ѷ��� AuraContext�� ���ǵ� �Է��� ����� �� �ִ�.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false); //Ŀ���� ĸ�ĵǴ� ���� ������ ����
	SetInputMode(InputModeData); //���Ӱ� UI ��ο��� �Է��� ���� �� �ֵ��� ����


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
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //������ �̵��ϴ� ����
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //���������� �̵��ϴ� ����
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Forward, MoveValue.Y); //�յ� �̵�
		ControlledPawn->AddMovementInput(Right, MoveValue.X); //�翷 �̵�
	}


}
