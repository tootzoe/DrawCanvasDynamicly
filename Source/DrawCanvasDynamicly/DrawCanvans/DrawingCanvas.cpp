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



#include "DrawCanvasDynamicly/DrawCanvans/DrawingCanvas.h"

#include "Engine/Texture2D.h"






UDrawingCanvas::UDrawingCanvas()
{

}


UDrawingCanvas::~UDrawingCanvas()
{

}

void UDrawingCanvas::InitializeCanvas(const int32 pixelsHor, const int32 pixelsVer)
{
    mCanvasWidth = pixelsHor;
    mCanvasHeight = pixelsVer;

    DynamicCanvas = UTexture2D::CreateTransient(mCanvasWidth, mCanvasHeight);

#if  WITH_EDITORONLY_DATA
     DynamicCanvas->MipGenSettings =  TextureMipGenSettings::TMGS_NoMipmaps;
#endif

    DynamicCanvas->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    DynamicCanvas->SRGB = 1;
    DynamicCanvas->AddToRoot();
    DynamicCanvas->Filter = TextureFilter::TF_Nearest;
    DynamicCanvas->UpdateResource();

    mEchoUpdTextureRegion = std::unique_ptr<FUpdateTextureRegion2D> (new FUpdateTextureRegion2D(0,0 , 0 , 0 , mCanvasWidth, mCanvasHeight ));

    mBytePerPiexl = 4; // r,g,b,a
    mBufferPitch = mBytePerPiexl * mCanvasWidth;
    mBufferSize = mBufferPitch * mCanvasHeight;
    mCanvasPixelData = std::unique_ptr<uint8[]>(new uint8[mBufferSize]);

    ClearCanvas();

}

void UDrawingCanvas::UpdCanvas()
{
    if(mEchoUpdTextureRegion){
        DynamicCanvas->UpdateTextureRegions((int32)0, (uint32)1, mEchoUpdTextureRegion.get(),
                                            (uint32)mBufferPitch, (uint32)mBytePerPiexl, mCanvasPixelData.get());
    }

}

void UDrawingCanvas::ClearCanvas()
{
    uint8* pixPtr = mCanvasPixelData.get();
    memset(pixPtr, 255, mBufferSize);

    UpdCanvas();

}

void UDrawingCanvas::InitializeDrawingTools(const int32 BrushRadius)
{
    mBrushRadius = BrushRadius;
    mBrushBufferSize = mBrushRadius * 2 * mBrushRadius * 2 * mBytePerPiexl;
    mBrushPiexlData = std::unique_ptr<uint8[]>(new uint8[mBrushBufferSize]);

    uint8* tmpPtr = mBrushPiexlData.get();

    for (int px = -mBrushRadius; px < mBrushRadius; ++px) {
        for (int py = -mBrushRadius; py < mBrushRadius; ++py) {
            int32 tx = px + mBrushRadius;
            int32 ty = py + mBrushRadius;
            tmpPtr = mBrushPiexlData.get() + (tx + ty * 2 * mBrushRadius) * mBytePerPiexl;
            if (px * px + py * py < mBrushRadius * mBrushRadius) {
                setPixelColor(tmpPtr, 150, 200, 0,255 );// black , alpha=255
            }else{
                setPixelColor(tmpPtr, 0,0, 0,0 );// black , alpha=0
            }
        }

    }
}



void UDrawingCanvas::DrawDot(const int32 PixelCoordX, const int32 PixelCoordY)
{
    uint8* tmpPtr = mCanvasPixelData.get();
    uint8* tmpBrushPtr = mBrushPiexlData.get();

    for (int px  = -mBrushRadius; px  < mBrushRadius; ++px ) {
        for (int py = -mBrushRadius; py < mBrushRadius; ++py) {
            int32 tx = px + mBrushRadius;
            int32 ty = py + mBrushRadius;
            tmpBrushPtr = mBrushPiexlData.get() + (tx + ty * 2 * mBrushRadius) * mBytePerPiexl;
            if (*(tmpBrushPtr + 3) == 255) {

                int32 cx = PixelCoordX + px;
                int32 cy = PixelCoordY + py;

                if (cx >= 0 && cx < mCanvasWidth && cy >= 0 && cy < mCanvasHeight)  {
                    tmpPtr = mCanvasPixelData.get() +  (cx + cy * mCanvasWidth ) * mBytePerPiexl;
                    setPixelColor(tmpPtr, *(tmpBrushPtr + 2), *(tmpBrushPtr + 1), *(tmpBrushPtr  ), *(tmpBrushPtr + 3)  );
                }

            }

        }
    }

    UpdCanvas();
}

void UDrawingCanvas::InitializeDecal(const UTexture2D *DecalTexture)
{
     auto tmpMipsArr = DecalTexture->GetPlatformMips() ;
    FTexture2DMipMap* tmpMipMap = reinterpret_cast<FTexture2DMipMap*>(  tmpMipsArr.GetData()[0] );

      FByteBulkData* rawImgData = &tmpMipMap->BulkData;

      // lock
    uint8* formatedImgData = static_cast<uint8*>(rawImgData->Lock(LOCK_READ_ONLY));
    mDecalWidth = DecalTexture->GetSurfaceWidth();
    mDecalHeight = DecalTexture->GetSurfaceHeight();
    mDecalBufferSize = mDecalWidth * mDecalHeight * mBytePerPiexl;
    mDecalImgData = std::unique_ptr<uint8[]> (new uint8[mDecalBufferSize]);

    uint8* tmpPtr = mDecalImgData.get();

    memcpy(tmpPtr , formatedImgData , mDecalBufferSize);

    //unlock
    rawImgData->Unlock();



}

void UDrawingCanvas::DrawDecal(const int32 PixelCoordX, const int32 PixelCoordY)
{
    uint8* canvasPtr = mCanvasPixelData.get();
    const uint8* decalPtr = mDecalImgData.get();

    for (int px = -(mDecalWidth / 2); px < (mDecalWidth / 2); ++px) {
        for (int py = -(mDecalHeight / 2); py < (mDecalHeight / 2); ++py) {

            int32 tbx = px + mDecalWidth  / 2;
            int32 tby = py + mDecalHeight  / 2;

            decalPtr = mDecalImgData.get() + ( tbx + tby * mDecalWidth) * mBytePerPiexl;

            if (*(decalPtr + 3) == 255 ) {

                int32 tx = PixelCoordX + px;
                int32 ty = PixelCoordY + py;

                if (tx >= 0 && tx < mCanvasWidth && ty >=0 && ty < mCanvasHeight) {
                    canvasPtr = mCanvasPixelData.get() + ( tx + ty * mCanvasWidth) * mBytePerPiexl;
                  setPixelColor(canvasPtr, *(decalPtr + 2), *(decalPtr + 1), *(decalPtr + 0), *(decalPtr + 3  ));
                }
            }
        }

    }

    UpdCanvas();

}

void UDrawingCanvas::setPixelColor(uint8 *&ptr, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
    *ptr = blue; // b first
    *(ptr + 1) = green; //  g
    *(ptr + 2) = red; //  g
    *(ptr + 3) = alpha; //  g
}
