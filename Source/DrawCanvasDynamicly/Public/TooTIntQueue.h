// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include <queue>


#include "TootIntQueue.generated.h"



/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class DRAWCANVASDYNAMICLY_API UTootIntQueue : public UObject
{
  GENERATED_BODY()

    public:
     UTootIntQueue();
     ~UTootIntQueue();



    UFUNCTION(BlueprintCallable, Category = "TOOT")
    bool Dequeue(int32& value);
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    bool Enqueue(const int32& value);
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void Empty();
    UFUNCTION(BlueprintPure, Category = "TOOT")
    bool IsEmpty();
    UFUNCTION(BlueprintPure, Category = "TOOT")
    bool Peek(int32& value);



    private:
    std::queue<int32> mMainQueue;




};
