//
//  ZJAccountSDK.h
//  ZJAccountSDK
//
//  Created by 中交金码 on 2018/3/6.
//  Copyright © 2018年 中交金码. All rights reserved.
//  yuanxunrui 账户SDK所需全部外抛API

#import <Foundation/Foundation.h>
#import "XRGcSdkHeader.h"

#pragma mark - 通知Key
/**
 @brief 切换支付方式时获取当前支付方式是否有生码资格
 返回值： 0-不可生码  1-可生码*/
extern NSString *const K_SDK_NOTIFICATION_PAYMENT;

/**
 @brief 用于唤醒微信H5充值/支付操作结束后自动退出web支付页面，
 触发前提：
 1、开发者需配置scheme：zj-unicode.com
 2、进行微信h5操作时需配置returnUrl
 2、需在application: openURL: options:中通过url.host捕捉‘2’中配置的returnUrl，并发送该通知*/
extern NSString *const K_SDK_NOTIFICATION_WECHAT_H5;

#pragma mark - enum
//交易信息查询状态
typedef NS_ENUM(NSInteger,Gc_enum_tanscationStatus) {
    Gc_enum_transtat_default = -1,
    Gc_enum_transtat_waitting = 1,//等待支付
    Gc_enum_transtat_success = 2,//支付成功
    Gc_enum_transtat_failure = 3//支付失败
};
//充值记录
typedef NS_ENUM(NSInteger,Gc_enum_recharge_status) {
    Gc_enum_recharge_default = -1,
    Gc_enum_recharge_doing = 1,//充值中
    Gc_enum_recharge_success = 2,//充值成功
    Gc_enum_recharge_failure = 3//充值失败
};

typedef void (^Gc_Sdk_Account_CompletionBlock)(NSString *resultCode,NSString *resultMsg,id result);

@interface XRAccountSDK : NSObject

@property (nonatomic,copy,readonly,getter=appKey)NSString *appKey;
/**
 初始化
 单例*/
+ (XRAccountSDK *)shareAccSDK;

#pragma mark - 获取用户账户信息
/**
 @brief 获取账户信息
 
 @param userId 用户app唯一Id
 @param orgCode 发卡机构代码
 @param block 回调，返回执行结果*/
- (void)getAccountInfo:(NSString *)userId
               orgCode:(NSString *)orgCode
       completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


#pragma mark - 支付渠道
/**
 @brief 获取支付渠道信息
 
 @param userId 用户app唯一Id
 @param orgCode 发卡机构代码
 @param block 成功回调，返回执行结果*/
- (void)getChannelInfo:(NSString *)userId
               orgCode:(NSString *)orgCode
       completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 设置支付渠道
 @param userId 用户app唯一Id
 @param mode 支付模式 ：0-出行宝  6-银行卡,默认0
 @paran orgCode 发卡机构代码
 */
- (void)setPaymentMode:(NSString *)userId
           paymentMode:(NSString *)mode
               orgCode:(NSString *)orgCode
       completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;
#pragma mark - 查询 余额
/**
 @brief 查询 余额
 
 @param userId userId
 @param orgCode 发卡机构代码
 */
- (void)queryBalance:(NSString *)userId
             orgCode:(NSString *)orgCode
     completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

#pragma mark - 查询 充值方式
/**
 @brief 查询 充值方式
 
 @param userId 用户APP唯一识别ID
 @param orgCode 发卡机构代码
 
 channelId:渠道 ID(0-卡片余额、 1-支付宝、 2-微信(待定)、 6-一网通银行卡)
 */
- (void)queryPayWay:(NSString *)userId
            orgCode:(NSString *)orgCode
    completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

#pragma mark - 一网通银行卡

/**
 @brief 充值 余额（一网通银行卡）
 
 @param userId 用户应用唯一识别ID
 @param amt 充值金额（元）
 @param envFlg 招商银行客户端 0-未安装 1-安装
 @param orgCode 发卡机构代码
 @param returnUrl 商户返回url
 @param block 回调返回
 */
- (void)rechargeAccountCmb:(NSString *)userId
                   tranAmt:(NSString *)amt
                    envFlg:(int)envFlg
                   orgCode:(NSString *)orgCode
                 returnUrl:(NSString *)returnUrl
           completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

/**
 @brief 重新支付订单
 
 @param userId 用户唯一识别ID
 @param transNo 支付流水号（订单编号）
 @param envFlg 招商银行客户端 0-未安装 1-安装
 @param returnUrl 商户返回url
 @param block 返回值
 */
- (void)againPaymentCmb:(NSString *)userId
                transNo:(NSString *)transNo
                 envFlg:(int)envFlg
              returnUrl:(NSString *)returnUrl
        completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 开通免密付（一网通银行卡）
 
 @param userId 用户app唯一识别ID
 @param returnUrl 商户返回url
 @param orgCode 发卡机构代码
 @param block 回调
 */
- (void)openWithholdCmb:(NSString *)userId
                orgCode:(NSString *)orgCode
              returnUrl:(NSString *)returnUrl
        completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

/**
 @brief 解约 免密付（银行卡）
 
 @param orgCode 发卡机构代码
 */
- (void)closeWithhold:(NSString *)userId
              orgCode:(NSString *)orgCode
      completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

#pragma mark - 订单交易
/**
 @brief 查询交易信息
 
 @param tranStat 查询条件，默认状态下显示全部数据
 @param orgCode 发卡机构代码
 @param startDate 查询开始时间 格式：yyyy-MM-dd
 @param endDate 查询结束时间 格式 yyyy-MM-dd
 @param pageNo 当前页数,从 1 开始
 @param pageSize 每页获取条数*/
- (void)getTransactionList:(NSString *)userId
                   orgCode:(NSString *)orgCode
                  tranStat:(Gc_enum_tanscationStatus)tranStat
                 startDate:(NSString *)startDate
                   endDate:(NSString *)endDate
                    pageNo:(int)pageNo
                  pageSize:(int)pageSize
           completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 获取充值记录
 @param tranStat 查询条件，默认状态下显示全部数据
 @param orgCode 发卡机构代码
 @param startDate 查询开始时间 格式：yyyy-MM-dd
 @param endDate 查询结束时间 格式 yyyy-MM-dd
 @param pageNo 当前页数,从 1 开始
 @param pageSize 每页获取条数
 orderStat 1:充值中 2：充值成功 3:充值失败*/
- (void)getBalanceList:(NSString *)userId
               orgCode:(NSString *)orgCode
              tranStat:(Gc_enum_recharge_status)tranStat
             startDate:(NSString *)startDate
               endDate:(NSString *)endDate
                pageNo:(int)pageNo
              pageSize:(int)pageSize
       completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 获取充值和提现记录

 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param pageNo 当前页数
 @param pageSize 一页显示条数
 @param block 回调
 */
- (void)getBalanceTransListWithUserId:(NSString *)userId
                              orgCode:(NSString *)orgCode
                            startDate:(NSString *)startDate
                              endDate:(NSString *)endDate
                               pageNo:(int)pageNo
                             pageSize:(int)pageSize
                      completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

/**
 @brief 获取交易信息的交易明细

 @param userId 用户唯一ID
 @param tranSno 支付订单编号
 */
- (void)getTransactionDetail:(NSString *)userId
                     tranSno:(NSString *)tranSno
             completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


#pragma mark - 支付宝
/**
 @brief 充值 余额（支付宝）
 
 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param amt 金额（元）
 @param returnUrl 商户返回URL
 @param block 回调
 */
- (void)alipayRecharge:(NSString *)userId
               orgCode:(NSString *)orgCode
               tranAmt:(NSString *)amt
             returnUrl:(NSString *)returnUrl
       completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 针对支付失败的订单再次支付（支付宝）
 
 @param userId 用户唯一识别ID
 @param transactionNo 失败交易编号
 @param block 回调
 */
- (void)againAlipay:(NSString *)userId
            tranSno:(NSString *)transactionNo
    completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 支付宝签约代扣url
 @param userId 用户唯一Id
 @param orgCode 发卡机构代码
 @param returnUrl 签约代扣成功返回Url
 @param block 成功回调，返回执行结果*/
- (void)alipaySignWithUserId:(NSString *)userId
                     orgCode:(NSString *)orgCode
                   returnUrl:(NSString *)returnUrl
             completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 支付宝代扣签约查询*/
- (void)queryAlipaySign:(NSString *)userId
        completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 支付宝解约代扣
 @param orgCode 发卡机构代码
 返回参数： 1:解约成功 2:用户未签约*/
- (void)alipayUnsign:(NSString *)userId
             orgCode:(NSString *)orgCode
     completionBlock:(Gc_Sdk_Account_CompletionBlock)block;

#pragma mark - 微信（APP）

/**
 @brief 微信-充值（APP专用）
 
 @tranAmt 提现金额（元）*/
- (void)weChatPageRechargeWithUserId:(NSString *)userId orgCode:(NSString *)orgCode tranAmt:(NSString *)tranAmt completionBlock:(Gc_Sdk_Account_CompletionBlock)block
#ifndef KGC
__attribute__((unavailable("该方法暂不可用")));
#endif
;
/**
 @brief 针对支付失败的订单再次支付（APP专用）
 */
- (void)weChatPagePayWithUserId:(NSString *)userId tranSno:(NSString *)tranSno completionBlock:(Gc_Sdk_Account_CompletionBlock)block
#ifndef KGC
__attribute__((unavailable("该方法暂不可用")));
#endif
;

/**
 @brief 微信唤醒APP进行免密签约（APP专用）
 */
- (void)wechatAgentSignWithUserId:(NSString *)userId
                          orgCode:(NSString *)orgCode
                  completionBlock:(Gc_Sdk_Account_CompletionBlock)block
#ifndef KGC
__attribute__((unavailable("该方法暂不可用")));
#endif
;

/**
 @brief 微信免密支付（代扣）--解约
 APP & H5 共用
 */
- (void)wechatUnsignWithUserId:(NSString *)userId
               completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;

#pragma mark 微信（H5）
/**
 @brief 微信H5支付（H5专用）
 
 @param userId 用户ID
 @param orgCode 发卡机构代码
 @param tranAmt 金额（元）
 @param refer 此处暂固定传：@"zj-unicode.com"
 @param navigationController 当前导航栏控制器
 @param returnUrl 成功后回调url（需开发人员自行捕捉，下文说明），最好不为空（为空的话捕捉不到url，微信H5支付成功后会留在微信，返回不了商户），需配置固定scheme：“zj-unicode.com”，
在application:openURL:options:方法中可以通过url.host判断并设置跳转逻辑
 例：returnUrl传入“XXXX”，支付成功后application:openURL:options：方法的url.host可以获取到"XXXX"
  */
- (void)wechatRechargeH5WithUserId:(NSString *)userId
                           orgCode:(NSString *)orgCode
                           tranAmt:(NSString *)tranAmt
                             refer:(NSString *)refer
              navigationController:(UINavigationController *)navigationController
                         returnUrl:(NSString *)returnUrl
                   completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 失败交易微信h5补单（H5专用）

 @param userId 用户ID
 @param transNo 失败订单编号
 @param navigationController 当前导航栏控制器
 @param returnUrl 成功后回调scheme，最好不为空，不需要在info中配置，
 在application:openURL:options:方法中可以通过url.host判断并设置跳转逻辑
 */
- (void)wechatPagePayH5WithUserId:(NSString *)userId
                          transNo:(NSString *)transNo
                            refer:(NSString *)refer
             navigationController:(UINavigationController *)navigationController
                        returnUrl:(NSString *)returnUrl
                  completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 微信免密签约（H5专用）

 @param userId 用户APP唯一识别ID
 @param orgCode 发卡机构代码
 @param refer 请求微信H5签约URL配置参数，域名格式，值由金码平台配置并下发，eg：zj-unicode.com
 @param navigationController 当前操作控制器（必须为navigationController格式）
 @param block 回调
 */
- (void)wechatAgentSignH5WithUserId:(NSString *)userId
                            orgCode:(NSString *)orgCode
                              refer:(NSString *)refer
               navigationController:(UINavigationController *)navigationController
                    completionBlock:(Gc_Sdk_Account_CompletionBlock)block;
#pragma mark - 获取可提现渠道
/**
 @brief 获取可提现渠道

 @param userId 用户唯一识别ID
 @param successBlock 1-支付宝 2-微信 6-银行
 */
- (void)getChannelWithDrawWithUserId:(NSString *)userId
                     completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;


#pragma mark - 支付密码相关


/**
 @brief 设置支付密码（首次设置、修改密码、忘记密码都会走此接口）
 
 @param userId 唯一ID
 @param pwd 新密码
 @param token 验证身份证号成功后返回
 @param block 回调
 */
- (void)setPasswordWithUserId:(NSString *)userId
                     password:(NSString *)pwd
                        token:(NSString *)token
              completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 验证身份证号码（用于忘记密码找回,验证身份证号码）
 
 @param userId 用户唯一ID
 @param idCardNo 身份证ID
 @param block 回调
 */
- (void)checkIdCardNoWithUserId:(NSString *)userId
                       idCardNo:(NSString *)idCardNo
                completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


#pragma mark - 提现API
/**
 @brief 统一提现API，集成支付宝、银行卡提现方式
 申请提现（先检测是否设置支付密码，）
 
 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param bankId 银行卡ID
 @param tranAmt 提现金额（元）
 @param channelId 提现渠道 1-支付宝 2-微信  6-招行 默认6
 @param sel 忘记密码时触发，
 @param toSelf 目标
 @param successBlock 回调
 */
- (void)refundWithUserId:(NSString *)userId
                 orgCode:(NSString *)orgCode
                  bankId:(NSString *)bankId
                 tranAmt:(NSString *)tranAmt
               channelId:(NSString *)channelId
                     sel:(SEL)sel
                  toSelf:(id)toSelf
         completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;


#pragma mark - 提现--银行卡
/**
 @brief 绑定银行卡
 
 @param userId 用户唯一识别ID
 @param bankNo 银行卡号
 @param bankBranchName 分行名称
 @param idCardNo 身份证号
 @param mobile 手机号
 @param realName 姓名
 @param bankPlace 开户行所在地
 @param successBlock 回调
 */
- (void)bindBankCard:(NSString *)userId
              bankNo:(NSString *)bankNo
      bankBranchName:(NSString *)bankBranchName
            idCardNo:(NSString *)idCardNo
              mobile:(NSString *)mobile
            realName:(NSString *)realName
           bankPlace:(NSString *)bankPlace
     completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;


/**
 @brief 获取银行卡列表
 
 @param userId 用户唯一识别ID
 @param successBlock 回调
 */
- (void)findBankInfosWithUserId:(NSString *)userId
                completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;

#pragma mark - 提现--支付宝

/**
 @brief 查看绑定的支付宝账号（脱敏数据）
 
 @param userId 用户唯一ID
 @param orgCode 发卡机构代码
 @param block 回调
 */
- (void)findAlipayNoWithUserId:(NSString *)userId
                       orgCode:(NSString *)orgCode
               completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 绑定支付宝账号
 
 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param thirdPayNo 支付宝账号
 @param block return
 */
- (void)bindAlipayNoWithUserId:(NSString *)userId
                       orgCode:(NSString *)orgCode
                    thirdPayNo:(NSString *)thirdPayNo
               completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


/**
 @brief 解绑支付宝账号
 
 @param userId 用户唯一识别ID
 @param orgCode 发卡机构代码
 @param block 返回值
 */
- (void)unBindAlipayNoWithUserId:(NSString *)userId
                         orgCode:(NSString *)orgCode
                 completionBlock:(Gc_Sdk_Account_CompletionBlock)block;


#pragma mark - 余额退款V2
/**
 用户提现：获取提现渠道及脱敏账号信息*/
- (void)getRefundAcctWithUserId:(NSString *)userId
                        orgCode:(NSString *)orgCode
                completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;


/**
 用户提现：申请提现
 @param channelId 1-支付宝 2-微信*/
- (void)refundWithUserId:(NSString *)userId
                 orgCode:(NSString *)orgCode
               channelId:(NSString *)channelId
         completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;


/**
 用户提现：撤销提现
 @userId  用户app唯一Id
 @orgCode  发码机构代码
 */
- (void)refundallBackoutWithUserId:(NSString *)userId
                           orgCode:(NSString *)orgCode
                   completionBlock:(Gc_Sdk_Account_CompletionBlock)successBlock;

#pragma mark - 常见问题说明
#pragma mark 微信H5支付成功后未返回商户
/**
 注意：微信H5支付成功后未返回商户可能情况：
 1、未按要求配置scheme（固定格式:"zj-unicode.com"）
 2、未按要求配置returnUrl（域名SDK内部已做处理，此处不需要写域名）
 3、通过url.host捕捉到回调后需手动发送固定通知：K_SDK_NOTIFICATION_WECHAT_H5（具体本页搜索“K_SDK_NOTIFICATION_WECHAT_H5”看用法）*/

@end
