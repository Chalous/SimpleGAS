#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SimpleGameplayAbility.generated.h"

class ASimpleGASCharacter;

UENUM(BlueprintType)
enum class ESimpleAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class SIMPLEGAS_API USimpleGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	ASimpleGASCharacter* GetCharacterFromActorInfo();

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "SimpleAbility")
	ESimpleAbilityActivationPolicy AbilityActivationPolicy = ESimpleAbilityActivationPolicy::OnTriggered;

	// ������ֻ������herocharacter�����ö����Ƕ�����Ҫ��һ��week�Ͳ�ͬ��soft��ɶ��ͬ��ʹ�ó���
	TWeakObjectPtr<ASimpleGASCharacter> CachedCharacter;
};
