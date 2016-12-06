//
//  TXAnnotation.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

//大头针
//
//在iOS开发中经常会标记某个位置，需要使用地图标注，也就是大家俗称的“大头针”。只要一个NSObject类实现MKAnnotation协议就可以作为一个大头针，通常会重写协议中coordinate（标记位置）、title（标题）、subtitle（子标题）三个属性，然后在程序中创建大头针对象并调用addAnnotation:方法添加大头针即可（之所以iOS没有定义一个基类实现这个协议供开发者使用，多数原因应该是MKAnnotation是一个模型对象，对于多数应用模型会稍有不同，例如后面的内容中会给大头针模型对象添加其他属性）。

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface TXAnnotation : NSObject<MKAnnotation>

@property(nonatomic,assign)CLLocationCoordinate2D coordinate;
@property(nonatomic,copy)NSString *title;
@property(nonatomic,copy)NSString *subtitle;

@end
