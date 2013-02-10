package me.pixodro;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.PowerManager;
import com.facebook.Session;
import com.facebook.SessionState;
import org.cocos2dx.lib.Cocos2dxActivity;

public class FuriousBlocks extends Cocos2dxActivity {
  private static FuriousBlocks me = null;

  static {
    System.loadLibrary("furiousblocks");
  }

  // Facebook
  private Session.StatusCallback statusCallback = new SessionStatusCallback();

  // Wake lock
  private PowerManager.WakeLock wakeLock;

  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    me = this;

    // Wake lock
    PowerManager powerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
    wakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock Tag");

    // Facebook
    Session session = Session.getActiveSession();
    if (session == null) {
      if (savedInstanceState != null) {
        session = Session.restoreSession(this, null, statusCallback, savedInstanceState);
      }
      if (session == null) {
        session = new Session(this);
      }
      Session.setActiveSession(session);
      if (session.getState().equals(SessionState.CREATED_TOKEN_LOADED)) {
          final List<String> permissions = new ArrayList<String>();
          permissions.add("user_likes");
          session.openForRead(new Session.OpenRequest(this).setCallback(statusCallback).setPermissions(permissions));
      }
    }
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

  @Override
  public void onStart() {
    super.onStart();
    Session.getActiveSession().addCallback(statusCallback);
  }

  @Override
  public void onStop() {
    super.onStop();
    Session.getActiveSession().removeCallback(statusCallback);
  }

  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent data) {
    super.onActivityResult(requestCode, resultCode, data);
    Session.getActiveSession().onActivityResult(this, requestCode, resultCode, data);
  }

  @Override
  protected void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    Session session = Session.getActiveSession();
    Session.saveSession(session, outState);
  }

  private class SessionStatusCallback implements Session.StatusCallback {
    @Override
    public void call(Session session, SessionState state, Exception exception) {
      facebookSessionStatusCallback(state.toString(), session.getAccessToken());
    }
  }

  public static void openURL(String url) {
    Intent intent = new Intent(Intent.ACTION_VIEW);
    intent.setData(Uri.parse(url));
    me.startActivity(intent);
  }

  public static void facebookLogin() {
    Session session = Session.getActiveSession();
    if (!session.isOpened() && !session.isClosed()) {
      session.openForRead(new Session.OpenRequest(me).setCallback(me.statusCallback));
    } else {
      Session.openActiveSession(me, true, me.statusCallback);
    }
  }

  public static void facebookLogout() {
    Session session = Session.getActiveSession();
    if (!session.isClosed()) {
      session.closeAndClearTokenInformation();
    }
  }

  private native void facebookSessionStatusCallback(String sessionStatus, String accessToken);
}
