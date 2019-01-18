//
//  XRResults.h
//  GcSDKDemo
//
//  Created by 袁训锐 on 2018/5/17.
//  Copyright © 2018年 XR. All rights reserved.
//  返回值

#import <Foundation/Foundation.h>

@class XRRealResultInfo;
@interface XRResults : NSObject

@property (nonatomic,copy) NSString *resultCode;//返回结果码
@property (nonatomic,copy) NSString *resultMsg;//返回提示信息
@property (nonatomic,copy) NSString *resultCound;//返回信息条数
@property (nonatomic,strong) id body;//返回消息体

@end
