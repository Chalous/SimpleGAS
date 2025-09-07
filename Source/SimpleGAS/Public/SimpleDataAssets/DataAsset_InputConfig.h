#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"


class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FSimpleGASInputActionConfig
{
	GENERATED_BODY();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"), Category = "InputAbility")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputAbility")
	UInputAction* InputAction = nullptr;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

UCLASS()
class SIMPLEGAS_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// ����ӳ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputAbility")
	UInputMappingContext* DefaultMappingContext;

	// һ������action
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"), Category = "InputAbility")
	TArray<FSimpleGASInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"), Category = "InputAbility")
	TArray<FSimpleGASInputActionConfig> AbilityInputActions;

	// �����ҽ�ɫ�󶨵�tag�¶�Ӧ��action
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	
};
