// Copyright 2020 Michael Palmer & Paradigm Game Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_ClearBlackboardValue();
};
