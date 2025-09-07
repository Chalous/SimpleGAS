#include "SimpleAbility/SimpleGameplayAbility.h"
#include "SimpleComponents/SimpleASC.h"
#include "SimpleCharacter/SimpleGASCharacter.h"

ASimpleGASCharacter* USimpleGameplayAbility::GetCharacterFromActorInfo()
{
	if (!CachedCharacter.IsValid())
	{
		CachedCharacter = Cast<ASimpleGASCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedCharacter.IsValid() ? CachedCharacter.Get() : nullptr;
}

void USimpleGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == ESimpleAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void USimpleGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ESimpleAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}
