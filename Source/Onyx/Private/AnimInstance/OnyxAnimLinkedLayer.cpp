#include "AnimInstance/OnyxAnimLinkedLayer.h"

#include "AnimInstance/OnyxHeroAnimInstance.h"

UOnyxHeroAnimInstance* UOnyxAnimLinkedLayer::GetOnyxHeroAnimInstance() const
{
	return Cast<UOnyxHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
