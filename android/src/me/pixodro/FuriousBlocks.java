package me.pixodro;

import android.content.Context;
import android.os.Bundle;
import android.os.PowerManager;
import org.cocos2dx.lib.Cocos2dxActivity;

public class FuriousBlocks extends Cocos2dxActivity {
    PowerManager.WakeLock wakeLock;

    protected void onCreate(Bundle savedInstanceState) {
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
}
