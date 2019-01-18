//
//  XRUpSignInfo.h
//
//  Created by 中交金码 on 2018/2/8.
//  Copyright © 2018年 中交金码. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface XRUpSignInfo : NSObject
//注：未加特殊说明的均为【必填】项
/**
 用户唯一识别ID*/
@property (nonatomic,copy) NSString *userId;
/**
 入网机构号*/
@property (nonatomic,copy) NSString *appKey;
/**
 用户账户号*/
@property (nonatomic,copy) NSString *userAcctCode;
/**
 发码机构代码*/
@property (nonatomic,copy) NSString *orgCode;
/**
 支付账户号（非必填）*/
@property (nonatomic,copy) NSString *payAcctCode;
/**
 发卡机构代码（非必填）*/
@property (nonatomic,copy) NSString *cardMechanismCode;
/**
 发码平台代码（非必填）*/
@property (nonatomic,copy) NSString *codePlatformCode;
/**
 发卡机构自定义域（非必填）只能为hex格式字母数字(0-9,a-f)，64位固定长度*/
@property (nonatomic,copy) NSString *isserRefData;
/**
 金码标志位（非必填，固定值:1）*/
@property (nonatomic,copy) NSString *flagType;
/**
 金码保留域（非必填）*/
@property (nonatomic,copy) NSString *payInfo;

//私有方法，集成者无需理会
@property (nonatomic,assign,readonly,getter=isSignValid) BOOL isSignValid;

@end
