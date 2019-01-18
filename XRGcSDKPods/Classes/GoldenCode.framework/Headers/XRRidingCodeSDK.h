//
//  XRQRSDKManager.h
//  Example_SmartCard
//
//  Created by 中交金码 on 2018/1/23.
//  Copyright © 2018年 中交金码. All rights reserved.
//  yuanxunrui 乘车码SDK相关API

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "XRRealNameInfo.h"
#import "XRGcSdkHeader.h"

@class XRUserInfo,XRUpSignInfo,XRResults;

//待签名数据回调
typedef void (^Gc_Sdk_SignBody_Block)(NSString *resultCode,NSString *resultMsg,NSString *plain_data_json,NSString *plain_data);

//返回值回调
typedef void (^Gc_Sdk_Result_Block)(XRResults *results);

@interface XRRidingCodeSDK : NSObject
#pragma mark 初始化

/**
 @brief SDK实例化
 */
+ (XRRidingCodeSDK *)shareSDK;

/**
 @brief 清空签名信息
 
 注：执行此操作后SDK内部与发卡机构签名相关缓存会被清空，
    开发者有需要需重新请求发卡机构签名
 */
- (BOOL)clearCacheSignInfo;

/**
 @brief 切换SDK账户
 
 注：在App账户切换时调用，调用此api后SDK内部缓存数据会清空，
    届时开发者再想生码需要重新走生码流程
 */
- (BOOL)switchUser;


/**
 @brief 获取当前版本号*/
- (NSString *)getCurrentVersion;
#pragma mark 登陆/注册SDK

/**
 @brief 基本信息注册
 
 @param appKey 金码发放注册key
 @param sdk_pk 发码平台公钥
 
 注：1、需在SDK注册之前调用，否则可能会出现部分API不灵敏
    2、在 didFinishLaunchingWithOptions 中调用
 */
- (BOOL)setAppKey:(NSString *)appKey
     sdkPublicKey:(NSString *)sdk_pk;

/**
 @brief 设置发卡机构代码
 
 @param orgCode 发卡机构代码
 @return bol
 注：集成过程中如果存在更改/配置机构服务代码情况，则调用此API，
    调用此API后，SDK会自动抹除生码相关缓存信息，开发者需重新进行用户公私钥及发卡机构签名的更新操作
 */
- (BOOL)setOrgCode:(NSString *)orgCode;

/**
 @brief 获取 注册SDK待签名数据
 @param userId  用户ID
 */
- (void)registerGoldenCodeSignBodyData:(NSString *)userId
                             signBlock:(Gc_Sdk_SignBody_Block)signBlock;

/**
 @brief 注册SDK
 @param plain_data_json 带签名数据包（可通过registerGoldenCodeSignBodyData直接获取）
 @param plain_data 签名数据
 @param block 结果回调
 */
- (void)registerGoldenCode:(NSString *)plain_data_json
                  signData:(NSString *)plain_data
           completionBlock:(Gc_Sdk_Result_Block)block;

#pragma mark 签名
/**
 @brief 模拟appServer签名，用于集成方前期服务端未集成签名架包时做模拟签名用，
    内部加密钥匙随时可能变换，变换则该签名方法立即作废，测试时需与开发人员联系
 @param mingwen 待签名数据
 @param app_pa 测试私钥
 @param signBlock 返回签名信息
 result :签名结果 ；isSignOK：是否签名成功;msg:提示信息*/
- (void)signAPI:(NSString *)mingwen
         app_pa:(NSString *)app_pa
      signBlock:(void(^)(id result,BOOL isSignOK,NSString *msg))signBlock;

#pragma mark 实名制
/**
 @brief 实名制  获取待签名数据*/
- (void)realNameSignBodyData:(XRRealNameInfo *)info
                   signBlock:(Gc_Sdk_SignBody_Block)signBlock;


/**
 @brief 实名制认证
 
 @param plain_data_json 待签名数据包
 @param plain_data 签名信息
 @param block 结果回调
 */
- (void)realNameData:(NSString *)plain_data_json
            signData:(NSString *)plain_data
     completionBlock:(Gc_Sdk_Result_Block)block;

#pragma mark 实名制查询
/**
 @brief 获取待签名数据
 @param userId 用户唯一识别ID*/
- (void)queryRealNameSignBodyDataWithUserId:(NSString *)userId
                                  signBlock:(Gc_Sdk_SignBody_Block)signBlock;
/**
 @brief 实名制查询
 @param plain_data_json 待签名数据包
 @param plain_data 签名信息
 */
- (void)queryRealNameWithJson:(NSString *)plain_data_json
                     signData:(NSString *)plain_data
              CompletionBlock:(Gc_Sdk_Result_Block)block;



#pragma mark 用户密钥信息
/**
 @brief 获取 用户密钥待签名数据*/
- (void)updateKeySignBodyData:(NSString *)userId
                    signBlock:(Gc_Sdk_SignBody_Block)signBlock;

/**
 @brief 更新 用户密钥
 
 @param plain_data_json 签名原始数据
 @param plain_data 签名数据
 */
- (void)updateKeyData:(NSString *)plain_data_json
             signData:(NSString *)plain_data
      completionBlock:(Gc_Sdk_Result_Block)block;


/**
 @brief 本地更新用户密钥
 
 通过本地算法直接生成用户密钥，非服务端操作，用法与用户密钥用法一致
 */
- (void)updateLocalKeyBlock:(void(^)(NSString *resultCode,NSString *resultMsg,id body))block;

#pragma mark 发卡机构签名信息

/**
 @brief 获取 发卡方信息待签名数据*/
- (void)updateCardIssuerSignBodyData:(XRUpSignInfo *)signInfo
                           signBlock:(Gc_Sdk_SignBody_Block)signBlock;


/**
 @brief 更新 发卡方信息
 必要条件：获取密钥成功*/
- (void)updateCardIssuerData:(NSString *)plain_data_json
                    signData:(NSString *)plain_data
             completionBlock:(Gc_Sdk_Result_Block)block;

#pragma mark 脱机生码
/**
 @brief 脱机生码

 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param width 二维码 宽度
 @param block 返回值 XRResults
 
 注：生码必要条件--注册SDK成功+更新密钥成功+更新发卡机构签名成功
 */
- (void)riseRidingCode:(NSString *)userId
               orgCode:(NSString *)orgCode
            imageWidth:(CGFloat)width
       completionBlock:(Gc_Sdk_Result_Block)block;

#pragma mark 脱机生码（含自定义域）
/**
 @brief 脱机生码（含自定义域）
 
 @param userId 用户唯一ID
 @param orgCode 发卡机构代码
 @param customField 用户自定义域（hex格式，只能包含(0-9,a-f)，固定长度64位）
 @param width 二维码宽度(>0,当<=0时按50像素处理)
 @param block 返回值
 */
- (void)riseRidingCodeEX:(NSString *)userId
                 orgCode:(NSString *)orgCode
             customField:(NSString *)customField
              imageWidth:(CGFloat)width
         completionBlock:(Gc_Sdk_Result_Block)block;
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#pragma mark 联机生码（单码）

/**
 @brief 获取联机生码（单码）待签名数据
 
 @param userId 用户唯一识别ID
 @param appKey 入网机构代码
 @param orgCode 发卡机构代码
 @param block 返回值
 */
- (void)riseOnLineQRSignBodyData:(NSString *)userId
                          appKey:(NSString *)appKey
                         orgCode:(NSString *)orgCode
                       signBlock:(Gc_Sdk_SignBody_Block)block;
/**
 @brief 联机生码（单码）
 
 @param plain_data_json 待签名数据json
 @param plain_data 签名信息
 @param width 二维码宽度
 @param block 返回值
 */
- (void)riseOnLineQrWithJson:(NSString *)plain_data_json
                    signData:(NSString *)plain_data
                       width:(CGFloat)width
             completionBlock:(Gc_Sdk_Result_Block)block;
#pragma mark 其他

/**
 @brief 是否打开Debug日志
 @param isOpen YES：开／NO：关
 */
- (void)xr_openSDKDebugLog:(BOOL)isOpen;
@end
