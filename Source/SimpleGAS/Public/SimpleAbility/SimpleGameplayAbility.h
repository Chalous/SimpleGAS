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

	// 弱引用只保存了herocharacter的引用而不是对象本身，要查一下week和不同的soft有啥不同的使用场景
	TWeakObjectPtr<ASimpleGASCharacter> CachedCharacter;
};
