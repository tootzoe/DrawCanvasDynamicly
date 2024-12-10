/**************************************************************************
**   Copyright @ 2024 TOOTzoe.com
**   Special keywords: thor 12/10/2024 2024
**   Environment variables:
**
**
**
**   E-mail : toot@tootzeo.com
**   Tel    : 13802205042
**   Website: http://www.tootzoe.com
**
**************************************************************************/



#ifdef Q_CC_MSVC
#pragma execution_character_set("UTF-8")
#endif


//------------------------------------------------------------------------

#pragma once


#include <memory>
#include "Engine/Texture2D.h"
#include "UObject/Object.h"

#include "DrawingCanvas.generated.h"


UCLASS(Blueprintable, BlueprintType)
class DRAWCANVASDYNAMICLY_API UDrawingCanvas : public UObject
{
        GENERATED_BODY()

public:
   explicit UDrawingCanvas();
    ~UDrawingCanvas();

    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void InitializeCanvas(const int32 pixelsHor, const int32 pixelsVer);

    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void UpdCanvas( );
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void ClearCanvas( );
    //
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void InitializeDrawingTools(const int32 BrushRadius);

    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void DrawDot(const int32 PixelCoordX, const int32 PixelCoordY);

    //decals
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void InitializeDecal(const UTexture2D* DecalTexture);
    UFUNCTION(BlueprintCallable, Category = "TOOT")
    void DrawDecal(const int32 PixelCoordX, const int32 PixelCoordY);

    //



    UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="TOOT")
    UTexture2D* DynamicCanvas;




private:

    void setPixelColor(uint8*& ptr , uint8 red, uint8 green, uint8 blue, uint8 alpha);

    std::unique_ptr<uint8[]> mCanvasPixelData;
    int mCanvasWidth;
    int mCanvasHeight;
    int mBytePerPiexl;
    int mBufferPitch;
    int mBufferSize;

    std::unique_ptr<FUpdateTextureRegion2D> mEchoUpdTextureRegion;

    //brush tool
    std::unique_ptr<uint8[]> mBrushPiexlData;
    int mBrushRadius;
    int mBrushBufferSize;

    //Decal tool
    std::unique_ptr<uint8[]> mDecalImgData;
    int mDecalWidth;
    int mDecalHeight;
    int mDecalBufferSize;
};

