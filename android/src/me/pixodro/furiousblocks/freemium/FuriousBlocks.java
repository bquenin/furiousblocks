package me.pixodro.furiousblocks.freemium;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.PowerManager;
import org.cocos2dx.lib.Cocos2dxActivity;

public class FuriousBlocks extends Cocos2dxActivity {
    PowerManager.WakeLock wakeLock;
    private static Activity me = null;

    protected void onCreate(Bundle savedInstanceState) {
        me = this;
        super.onCreate(savedInstanceState);
        PowerManager powerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
        wakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock Tag");
    }

    @Override
    protected void onResume() {
        super.onResume();
        wakeLock.acquire();
    }

    @Override
    protected void onPause() {
        super.onPause();
        wakeLock.release();
    }

    static {
        System.loadLibrary("furiousblocks");
    }

    public static void openURL(String url) {
        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setData(Uri.parse(url));
        me.startActivity(intent);
    }
}
