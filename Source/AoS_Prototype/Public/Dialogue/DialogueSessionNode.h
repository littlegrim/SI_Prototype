
#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "DialogueSessionNode.generated.h"

UENUM(BlueprintType)
enum class EEmotion : uint8
{
    Neutral,
    Anger,
    Fear,
    Disgust,
    Contempt,
    Joy,
    Sadness,
    Surprise,
    Cocky,
    Thoughtful,
    Nervous
};

UCLASS(Blueprintable)
class UDialogueSessionNode : public UGenericGraphNode
{
    GENERATED_BODY()
public:
    UDialogueSessionNode();
    ~UDialogueSessionNode();

#if WITH_EDITOR
    virtual FText GetNodeTitle() const override;

    virtual void SetNodeTitle(const FText& NewTitle) override;
#endif

    UFUNCTION(BlueprintCallable)
    FText GetDialogueText() const { return Dialogue; }

    UPROPERTY(EditDefaultsOnly, Category = "DialogueOptions")
    bool bIsDefaultStartingNode;
    UPROPERTY(EditDefaultsOnly, Category = "DialogueOptions")
    bool bIsNickSpeaking;

private:

    UPROPERTY(EditDefaultsOnly, Category = "DialogueOptions")
    FText Dialogue;
    UPROPERTY(EditDefaultsOnly, Category = "DialogueOptions")
    EEmotion RelatedEmotion;
};