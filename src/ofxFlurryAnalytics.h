/*
 *  ofxiPhoneAnayltics.h
 *  sws023
 *
 *  Created by Zach Gage on 1/5/10.
 *  Copyright 2010 stfj. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#import "ofMain.h"
#import "Flurry.h"

#pragma once

class ofxiPhoneFlurryAnalytics
{
public:
    
	ofxiPhoneFlurryAnalytics(NSString * appId); // log in
    
//    void start(NSString * appId);
	void logEvent(NSString * eventName);
    
	void logEventWithVar(NSString * eventName, NSString * varName, float varValue);
    
};