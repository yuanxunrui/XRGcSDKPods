//
//  XROrgSDK.h
//  GcSDKDemo
//
//  Created by 袁训锐 on 2018/9/7.
//  Copyright © 2018年 XR. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,XRGetCardListType) {
    XRGetCardListTypeDefault = -1,
    XRGetCardListTypeClose = 0,//未开
    XRGetCardListTypeOpen = 1//已开
};
typedef void (^Gc_Sdk_Org_CompletionBlock)(NSString *resultCode,NSString *resultMsg,id result);

@interface XROrgSDK : NSObject

/** 初始化 */
+ (XROrgSDK *)shareSDK;

#pragma mark - API
/**
 @brief 获取所有交通卡列表

 @param userId 用户唯一识别ID
 */
- (void)getTCardList:(NSString *)userId
             openFlg:(XRGetCardListType)flg
     completionBlock:(Gc_Sdk_Org_CompletionBlock)block;


#pragma mark - 开卡
/** 开卡需要进行数据签名，流程与发码平台一致 */
/**
 @brief 获取开通电子卡待签名数据

 @param userId userId
 @param orgCode 发卡机构代码
 */
- (void)openTCardSignBodyData:(NSString *)userId
                      orgCode:(NSString *)orgCode
                    signBlock:(void(^)(NSString *resultCode,NSString *resultMsg,NSString *plain_data_json,NSString *plain_data))block;

/**
 @brief 开通电子卡
 
 @param plain_data_json 带签名数据包
 @param plain_data 签名数据
 @param block 结果回调
 */
- (void)openTCard:(NSString *)plain_data_json
         signData:(NSString *)plain_data
  completionBlock:(Gc_Sdk_Org_CompletionBlock)block;
@end
