//
//  XRGcSdkTool.h
//  GoldenCode
//
//  Created by 袁训锐 on 2018/8/13.
//  Copyright © 2018年 XR. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,Gc_sdk_network_status) {
    Gc_sdk_network_status_no = 0,
    Gc_sdk_network_status_wwan,
    Gc_sdk_network_status_wifi
};
//网络状态
typedef void (^Gc_Sdk_Network_Block)(Gc_sdk_network_status status);

@interface XRGcSdkTool : NSObject

/**
 检测当前网络状态
 */
+ (void)xr_checkNetworkBlock:(Gc_Sdk_Network_Block)networkStatus;
#pragma mark SM2加密&&解密
/**
 sm2加密

 @param scr 明文
 @param pk 公钥
 @param encBlock 返回值
 */
+ (void)xr_sm2_encryptWithSrc:(NSString *)scr
                           pk:(NSString *)pk
                     encBlock:(void(^)(BOOL isEncOK,NSString *encStr,id result))encBlock;
/**
 sm2解密

 @param enc 密文
 @param pa 私钥
 @param decBlock 返回值
 */
+ (void)xr_sm2_decryptWithEnc:(NSString *)enc
                           pa:(NSString *)pa
                     decBlock:(void(^)(BOOL isDecOK,NSString *decStr,id result))decBlock;
@end
