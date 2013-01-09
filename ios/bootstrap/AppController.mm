//
//  testAppController.mm
//  test
//
//  Created by Bertrand Quenin on 11/11/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#import <FacebookSDK/FacebookSDK.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"
//#import "Appirater.h"

@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (void)sessionStateChanged:(FBSession *)session
                      state:(FBSessionState)state
                      error:(NSError *)error {
  // FBSample logic
  // Any time the session is closed, we want to display the login controller (the user
  // cannot use the application unless they are logged in to Facebook). When the session
  // is opened successfully, hide the login controller and show the main UI.
  switch (state) {
    case FBSessionStateOpen: {
      AppDelegate::setLoggedIn(true);
      AppDelegate::setAccessToken(std::string([[FBSession.activeSession accessToken] cStringUsingEncoding:NSUTF8StringEncoding]));

      // FBSample logic
      // Pre-fetch and cache the friends for the friend picker as soon as possible to improve
      // responsiveness when the user tags their friends.
      //
      // FBCacheDescriptor *cacheDescriptor = [FBFriendPickerViewController cacheDescriptor];
      // [cacheDescriptor prefetchAndCacheForSession:session];
    }
      break;

    case FBSessionStateClosed: {
      AppDelegate::setLoggedIn(false);
      AppDelegate::setAccessToken("none");
      // FBSample logic
      // Once the user has logged out, we want them to be looking at the root view.
      [FBSession.activeSession closeAndClearTokenInformation];
    }
      break;

    case FBSessionStateClosedLoginFailed: {
      AppDelegate::setLoggedIn(false);
      AppDelegate::setAccessToken("none");
      // if the token goes invalid we want to switch right back to
      // the login view, however we do it with a slight delay in order to
      // account for a race between this and the login view disappearing
      // a moment before
    }
      break;

    default:
      AppDelegate::setLoggedIn(false);
      break;
  }

//  [[NSNotificationCenter defaultCenter] postNotificationName:SCSessionStateChangedNotification
//                                                      object:session];
//
//  if (error) {
//    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"Error: %@",
//                                                                                           [SCAppDelegate FBErrorCodeDescription:error.code]]
//                                                        message:error.localizedDescription
//                                                       delegate:nil
//                                              cancelButtonTitle:@"OK"
//                                              otherButtonTitles:nil];
//    [alertView show];
//  }
}

- (BOOL)openSessionWithAllowLoginUI:(BOOL)allowLoginUI {
  return [FBSession openActiveSessionWithReadPermissions:nil allowLoginUI:allowLoginUI
                                       completionHandler:^(FBSession *session, FBSessionState state, NSError *error) {
                                         [self sessionStateChanged:session state:state error:error];
                                       }];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

  // Override point for customization after application launch.

  // Add the view controller's view to the window and display.
  window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
  EAGLView *__glView = [EAGLView viewWithFrame:[window bounds]
                                   pixelFormat:kEAGLColorFormatRGBA8
                                   depthFormat:GL_DEPTH_COMPONENT16 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];

  // Use RootViewController manage EAGLView
  viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
  viewController.wantsFullScreenLayout = YES;
  viewController.view = __glView;

  // Set RootViewController to window
  if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
    // warning: addSubView doesn't work on iOS6
    [window addSubview:viewController.view];
  }
  else {
    // use this method on ios6
    [window setRootViewController:viewController];
  }

  [window makeKeyAndVisible];

  [[UIApplication sharedApplication] setStatusBarHidden:YES];

  // FBSample logic
  // See if we have a valid token for the current state.
  if (![self openSessionWithAllowLoginUI:NO]) {
//    // No? Display the login page.
//    [self openSessionWithAllowLoginUI:YES];
  }

  cocos2d::CCApplication::sharedApplication()->run();

//  [Appirater setAppId:@"586087328"];
//  [Appirater setDaysUntilPrompt:1];
//  [Appirater setUsesUntilPrompt:10];
//  [Appirater setSignificantEventsUntilPrompt:-1];
//  [Appirater setTimeBeforeReminding:2];
//  [Appirater setDebug:YES];
//
//  [Appirater appLaunched:YES];

  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  /*
   Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
   Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
   */
  cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  /*
   Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
   */
  cocos2d::CCDirector::sharedDirector()->resume();

  // FBSample logic
  // We need to properly handle activation of the application with regards to SSO
  //  (e.g., returning from iOS 6.0 authorization dialog or from fast app switching).
  [FBSession.activeSession handleDidBecomeActive];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  /*
   Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
   If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
   */
  cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  /*
   Called as part of transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
   */
  cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();

//  [Appirater appEnteredForeground:YES];
}

- (void)applicationWillTerminate:(UIApplication *)application {
  /*
   Called when the application is about to terminate.
   See also applicationDidEnterBackground:.
   */
  // FBSample logic
  // if the app is going away, we close the session object; this is a good idea because
  // things may be hanging off the session, that need releasing (completion block, etc.) and
  // other components in the app may be awaiting close notification in order to do cleanup
  [FBSession.activeSession close];
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
  /*
   Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
   */
  cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

- (void)dealloc {
  [super dealloc];
}

@end