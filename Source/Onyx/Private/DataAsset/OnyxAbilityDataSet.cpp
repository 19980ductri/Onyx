// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/OnyxAbilityDataSet.h"

FOnyxAbilityInfo UOnyxAbilityDataSet::FindAbilityInfoByTag(const FGameplayTag& AbilityTag)
{
	for (const FOnyxAbilityInfo& Info : AbilityInfos)
	{
		if (AbilityTag.MatchesTagExact(Info.AbilityTag))
		{
			return Info;
		}
	}
	return FOnyxAbilityInfo();
}
