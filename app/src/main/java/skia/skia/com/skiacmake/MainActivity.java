package skia.skia.com.skiacmake;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private SkiaDrawView fMainView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
        fMainView = new SkiaDrawView(this);
        setContentView(fMainView);

        // Example of a call to a native method
//        TextView tv = (TextView) findViewById(R.id.sample_text);
 //       tv.setText(stringFromJNI());

        try {
            // Load Skia and then the app shared object in this order
            System.loadLibrary("skia_android");
            System.loadLibrary("hello_skia_ndk");

        } catch (UnsatisfiedLinkError e) {
            Log.d("HelloSkia", "Link Error: " + e);
            return;
        }
        Timer fAnimationTimer = new Timer();
        fAnimationTimer.schedule(new TimerTask() {
            public void run()
            {
                // This will request an update of the SkiaDrawView, even from other threads
                fMainView.postInvalidate();
            }
        }, 0, 5);
    }
    private class SkiaDrawView extends View {
        Bitmap fSkiaBitmap;
        public SkiaDrawView(Context ctx) {
            super(ctx);
        }

        @Override
        protected void onSizeChanged(int w, int h, int oldw, int oldh)
        {
            // Create a bitmap for skia to draw into
            fSkiaBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            // Call into our C++ code that renders to the bitmap using Skia
            drawIntoBitmap(fSkiaBitmap, SystemClock.elapsedRealtime());

            // Present the bitmap on the screen
            canvas.drawBitmap(fSkiaBitmap, 0, 0, null);
        }
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native String stringFromJNI();
    private native void drawIntoBitmap(Bitmap image, long elapsedTime);
}
