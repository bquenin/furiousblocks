//
//  testAppController.h
//  test
//
//  Created by Bertrand Quenin on 11/11/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
  UIWindow *window;
  RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;
- (BOOL)openSessionWithAllowLoginUI:(BOOL)allowLoginUI;


@end

