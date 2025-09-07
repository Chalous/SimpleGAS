// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleCharacter/SimpleGASCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "SimpleDataAssets/DataAsset_InputConfig.h"
#include "SimpleComponents/SimpleGASInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimpleComponents/SimpleASC.h"
#include "SimpleDataAssets/DataAsset_StartUpData.h"
#include "Engine/LocalPlayer.h"


ASimpleGASCharacter::ASimpleGASCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SimpleASC = CreateDefaultSubobject<USimpleASC>(TEXT("SimpleAbilitySystemComponent"));
}

void ASimpleGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASimpleGASCharacter::PossessedBy(AController* NewController)
{
	// 初始化ability system component
	Super::PossessedBy(NewController);
	if (SimpleASC)
	{
		SimpleASC->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
		if (!CharacterStartUpData.IsNull())
		{
			if (UDataAsset_StartUpData* LoadedData = CharacterStartUpData.LoadSynchronous())
			{
				LoadedData->GiveToASC(SimpleASC);
			}
		}
	}
}

void ASimpleGASCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	SimpleASC->OnAbilityInputPressed(InInputTag);
}

void ASimpleGASCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	SimpleASC->OnAbilityInputReleased(InInputTag);
}

void ASimpleGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimpleGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 1. 先判断输入配置资源，如果没有，就直接中断进程并打印信息，
	// 因为InputConfigDataAsset是类默认值，需要玩家设置的，如果没设置则为空，要提醒玩家设置
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))

	// 2. 获取本地玩家实例
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	// 3. 获取本地玩家的子系统，子系统为增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	// 4. 判断增强输入子系统是否为空
	checkf(Subsystem, TEXT("enhanced input local player subsystem is null"));

	// 5. 将InputConfigDataAsset里的输入映射内容添加给本地角色的增强输入子系统
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	// 6. 将角色当前的输入组件转换成我们自定义的warrior输入组件
	USimpleGASInputComponent* SimpleGASInputComponent = CastChecked<USimpleGASInputComponent>(PlayerInputComponent);

	SimpleGASInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

UAbilitySystemComponent* ASimpleGASCharacter::GetAbilitySystemComponent() const
{
	return GetSimpleASC();
}

