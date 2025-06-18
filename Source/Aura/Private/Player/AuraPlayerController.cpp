// copyright


#include "Player/AuraPlayerController.h"
#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"

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
	check(SubSystem);

	SubSystem->AddMappingContext(AuraContext, 0); //0�� �켱����. 0�� ���� ����.

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
