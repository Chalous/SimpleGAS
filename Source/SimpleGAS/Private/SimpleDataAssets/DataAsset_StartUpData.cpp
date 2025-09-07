#include "SimpleDataAssets/DataAsset_StartUpData.h"
#include "SimpleComponents/SimpleASC.h"
#include "SimpleAbility/SimpleGameplayAbility.h"

void UDataAsset_StartUpData::GiveToASC(USimpleASC* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilites(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilites(ReactiveAbilities, InASCToGive, ApplyLevel);

	for (const FSimpleAbilitySet& AbilitySet : SimpleStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}

void UDataAsset_StartUpData::GrantAbilites(const TArray<TSubclassOf<USimpleGameplayAbility>>& InAbilitesToGive, USimpleASC* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<USimpleGameplayAbility>& Ability : InAbilitesToGive)
	{
		if (!Ability) continue;

		// 初始化ability变量，将对应的数据赋值
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		// 将ability存进ASC中
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

bool FSimpleAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}