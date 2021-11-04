// copyright @민지

#include "Structs/Abilities/FMAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "Structs/Character/BaseCharacter.h"

UFMAttributeSet::UFMAttributeSet()
{

}

void UFMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();

	if (Attribute == GetMaxHealthAttribute())
	{
		AbilityComp->ApplyModToAttributeUnsafe(GetHealthAttribute(), EGameplayModOp::Additive, NewValue);
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AbilityComp->ApplyModToAttributeUnsafe(GetManaAttribute(), EGameplayModOp::Additive, NewValue);
	}
}

void UFMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	/**
	* GameplayEffect가 적용됐을때 GameplayEffect가 수정한 Attribute가 Data를 통해 받아와진다.
	* Data를 이용해 Damage를 계산하고 Health를 감소 시킨다던가 BaseCharacter의 이벤트 함수를 호출하는 용도의 함수
	*/


	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		//Addtive일 경우 EvaluatedData.Magnitude가 가변적일 경우를 대비해 저장해둔다.
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	AActor* TargetActor = nullptr;
	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();

	ABaseCharacter* TargetCharacter = nullptr;
	TargetCharacter = Cast<ABaseCharacter>(TargetActor);


	/**
	* Damage Attribute가 들어왔을때 Health를 감소시키는 로직
	*/
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ABaseCharacter* SourceCharacter = nullptr;

		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			if (SourceController)
			{
				SourceCharacter = Cast<ABaseCharacter>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ABaseCharacter>(SourceActor);
			}
		}

		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
		}

		if (TargetCharacter)
		{
			TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
			TargetCharacter->HandleHealthChanged(LocalDamageDone, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp mana
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
		}
	}
}

void UFMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UFMAttributeSet, Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME(UFMAttributeSet, MaxHealth);
	DOREPLIFETIME_CONDITION_NOTIFY(UFMAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME(UFMAttributeSet, MaxMana);
}

void UFMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, Health, OldValue);
}

void UFMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, MaxHealth, OldValue);
}

void UFMAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, Mana, OldValue);
}

void UFMAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, MaxMana, OldValue);
}