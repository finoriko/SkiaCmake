#include <math.h>
#include <jni.h>
#include <android/bitmap.h>

#include "core/SkCanvas.h"
#include "core/SkGraphics.h"
#include "core/SkSurface.h"
#include "core/SkString.h"
#include "core/SkTime.h"
#include "core/SkMath.h"
#include "core/SkRefCnt.h"
extern "C" JNIEXPORT jstring

JNICALL Java_skia_skia_com_skiacmake_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    jint r = SkClampMax(1,5);
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL Java_skia_skia_com_skiacmake_MainActivity_drawIntoBitmap(JNIEnv* env,
                                                                         jobject thiz, jobject dstBitmap, jlong elapsedTime)
{
    // Grab the dst bitmap info and pixels
    AndroidBitmapInfo dstInfo;
    void* dstPixels;
    AndroidBitmap_getInfo(env, dstBitmap, &dstInfo);
    AndroidBitmap_lockPixels(env, dstBitmap, &dstPixels);

    SkImageInfo info = SkImageInfo::MakeN32Premul(dstInfo.width, dstInfo.height);

    // Create a surface from the given bitmap
  /*  SkAutoTUnref<SkSurface> surface(SkSurface::NewRasterDirect(info, dstPixels, dstInfo.stride));
    SkCanvas* canvas = surface->getCanvas();*/

    SkBitmap bitmap;
    bitmap.installPixels(info, dstPixels, info.minRowBytes());
    SkCanvas canvas(bitmap);
    //canvas.drawText(text, length, x, y, paint);
    // Draw something "interesting"

    // Clear the canvas with a white color
    canvas.drawColor(SK_ColorWHITE);

    // Setup a SkPaint for drawing our text
    SkPaint paint;
    paint.setColor(SK_ColorBLACK); // This is a solid black color for our text
    paint.setTextSize(SkIntToScalar(30)); // Sets the text size to 30 pixels
    paint.setAntiAlias(true); // We turn on anti-aliasing so that the text to looks good.

    // Draw some text
    SkString text("Skia is Best!");
    SkScalar fontHeight = paint.getFontSpacing();
    canvas.drawText(text.c_str(), text.size(), // text's data and length
                     10, fontHeight,            // X and Y coordinates to place the text
                     paint);                    // SkPaint to tell how to draw the text

    // Adapt the SkPaint for drawing blue lines
    paint.setAntiAlias(false); // Turning off anti-aliasing speeds up the line drawing
    paint.setColor(0xFF0000FF); // This is a solid blue color for our lines
    paint.setStrokeWidth(SkIntToScalar(2)); // This makes the lines have a thickness of 2 pixels

    // Draw some interesting lines using trig functions
    for (int i = 0; i < 100; i++)
    {
        float x = (float)i / 99.0f;
        float offset = elapsedTime / 1000.0f;
        canvas.drawLine(sin(x * M_PI + offset) * 800.0f, 0,   // first endpoint
                         cos(x * M_PI + offset) * 800.0f, 800, // second endpoint
                         paint);                               // SkPapint to tell how to draw the line
    }

    SkPaint paintR;
    paint.setColor(0xFFFF0000);
    canvas.drawLine(0,0,1000,1000,paint);


//    canvas.drawPoint()
    SkRect rect;
    //rect.
    // Unlock the dst's pixels
    AndroidBitmap_unlockPixels(env, dstBitmap);
}