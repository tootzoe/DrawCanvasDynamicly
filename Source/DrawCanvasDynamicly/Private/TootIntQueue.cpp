// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawCanvasDynamicly/Public/TootIntQueue.h"







UTootIntQueue::UTootIntQueue()
{


}

UTootIntQueue::~UTootIntQueue()
{
}

bool UTootIntQueue::Dequeue(int32 &value)
{
     UE_LOG(LogTemp, Warning, TEXT("Dequeue() called......22....."));
    //mMainQueue.pop();
    return true;
}

bool UTootIntQueue::Enqueue(const int32 &value)
{
    // mMainQueue.push(value);
     UE_LOG(LogTemp, Warning, TEXT("Enqueue() called......22....."));
     return true;
}

void UTootIntQueue::Empty()
{
  //  mMainQueue.emplace()
    UE_LOG(LogTemp, Warning, TEXT("Empty() called......22....."));

}

bool UTootIntQueue::IsEmpty()
{
     UE_LOG(LogTemp, Warning, TEXT("IsEmpty() called......22....."));
    return mMainQueue.empty();
}

bool UTootIntQueue::Peek(int32 &value)
{
     UE_LOG(LogTemp, Warning, TEXT("Peek() called......22....."));
   //value = mMainQueue.back();
    return true;
}
