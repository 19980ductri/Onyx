#pragma once


#include "CoreMinimal.h"
#include "OnyxAnimInstanceBase.h"
#include "OnyxAnimLinkedLayer.generated.h"


class UOnyxHeroAnimInstance;

UCLASS()
class UOnyxAnimLinkedLayer : public UOnyxAnimInstanceBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UOnyxHeroAnimInstance *GetOnyxHeroAnimInstance() const;
};
