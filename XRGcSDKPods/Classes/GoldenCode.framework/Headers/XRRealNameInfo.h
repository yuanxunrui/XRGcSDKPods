//
//  XRRealNameInfo.h
//  GcSDKDemo
//
//  Created by 袁训锐 on 2018/5/16.
//  Copyright © 2018年 XR. All rights reserved.
//

#import <Foundation/Foundation.h>
#pragma mark - 请求参数数据
@interface XRRealNameInfo : NSObject

////必填项有“必填”说明////

/**
用户APP唯一Id
必填*/
@property(nonatomic,copy) NSString *userId;
/**
 用户真实姓名
 必填
 需真实有效*/
@property(nonatomic,copy) NSString *custName;
/**
 用户身份证号
 必填
 需真实有效*/
@property(nonatomic,copy) NSString *idNumber;
/**
 证件类型(1：身份证)
 必填，默认1*/
@property(nonatomic,copy) NSString *idType;
/**
 用户电话*/
@property(nonatomic,copy) NSString *custPhone;
/**
 银行卡号*/
@property(nonatomic,copy) NSString *bankCardNo;
/**
 签名信息*/
@property (nonatomic,copy) NSString *signature;
/**
 验证字段有效性
 SDK内部调用，开发者无需处理*/
@property (nonatomic,assign,getter=isValid,readonly) BOOL isValid;

/**
 实名制
 SDK内部自动调用，无需开发者操作*/
- (NSDictionary *)realNameInfo;

@end
/////////////////////////////////
/////////////////////////////////
#pragma mark - 实名认证返回值数据
@interface XRRealResultInfo : NSObject
/**
 SDK账户唯一识别ID
 *注册SDK成功后获取*/
@property(nonatomic,copy) NSString *codeUserId;
/**
 用户账户号*/
@property(nonatomic,copy) NSString *userAcctCode;
/**
 用户姓名*/
@property(nonatomic,copy) NSString *custName;
/**
 用户电话*/
@property(nonatomic,copy) NSString *custPhone;
/**
 银行卡号*/
@property(nonatomic,copy) NSString *bankCardNo;
/**
 身份证号*/
@property(nonatomic,copy) NSString *idNumber;
/**
 证件类型（1-身份证）*/
@property(nonatomic,copy) NSString *idType;
/**
 实名认证状态
 0-未实名 1-已实名 2-未知*/
@property(nonatomic,copy) NSString *state;
/**
 是否实名
 yes/no*/
@property (nonatomic,assign,readonly) BOOL isRealName;
@end
