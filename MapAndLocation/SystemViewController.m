//
//  SystemViewController.m
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

#import "SystemViewController.h"
#import <MapKit/MapKit.h>

@interface SystemViewController ()

@property(nonatomic,strong)CLGeocoder *geocoder;


@end

@implementation SystemViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _geocoder = [[CLGeocoder alloc]init];
    
//    [self singleLocation];
//    [self moreLocation];
    [self mapNavigation];
}
/**
 单个位置的标注,在地图上定位
 
 下面的代码演示了如何在苹果自带地图应用上标记一个位置，首先根据反地理编码获得一个CLPlacemark位置对象，然后将其转换为MKPlacemark对象用于MKMapItem初始化，最后调用其openInMapsWithLaunchOptions:打开地图应用并标记：
 */
-(void)singleLocation
{
    //根据“上海市”进行地理编码
    [_geocoder geocodeAddressString:@"上海市" completionHandler:^(NSArray *placemarks, NSError *error) {
        CLPlacemark *clPlacemark=[placemarks firstObject];//获取第一个地标
        MKPlacemark *mkplacemark=[[MKPlacemark alloc]initWithPlacemark:clPlacemark];//定位地标转化为地图的地标
        NSDictionary *options=@{MKLaunchOptionsMapTypeKey:@(MKMapTypeStandard)};
        MKMapItem *mapItem=[[MKMapItem alloc]initWithPlacemark:mkplacemark];
        [mapItem openInMapsWithLaunchOptions:options];
    }];
}
/**
 标记多个位置
 
 如果要标记多个位置需要调用MKMapItem的静态方法，下面的代码演示中需要注意，使用CLGeocoder进行定位时一次只能定位到一个位置，所以第二个位置定位放到了第一个位置获取成功之后。
 */
-(void)moreLocation
{
    //根据“上海市”进行地理编码
    [_geocoder geocodeAddressString:@"上海市" completionHandler:^(NSArray *placemarks, NSError *error) {
        CLPlacemark *clPlacemark1=[placemarks firstObject];//获取第一个地标
        MKPlacemark *mkPlacemark1=[[MKPlacemark alloc]initWithPlacemark:clPlacemark1];
        //注意地理编码一次只能定位到一个位置，不能同时定位，所在放到第一个位置定位完成回调函数中再次定位
        [_geocoder geocodeAddressString:@"阜阳市" completionHandler:^(NSArray *placemarks, NSError *error) {
            CLPlacemark *clPlacemark2=[placemarks firstObject];//获取第一个地标
            MKPlacemark *mkPlacemark2=[[MKPlacemark alloc]initWithPlacemark:clPlacemark2];
            NSDictionary *options=@{MKLaunchOptionsMapTypeKey:@(MKMapTypeStandard)};
            //MKMapItem *mapItem1=[MKMapItem mapItemForCurrentLocation];//当前位置
            MKMapItem *mapItem1=[[MKMapItem alloc]initWithPlacemark:mkPlacemark1];
            MKMapItem *mapItem2=[[MKMapItem alloc]initWithPlacemark:mkPlacemark2];
            [MKMapItem openMapsWithItems:@[mapItem1,mapItem2] launchOptions:options];
            
        }];
        
    }];
}
/**
 地图导航
 
 要使用地图导航功能在自带地图应用中相当简单，只要设置参数配置导航模式即可，例如在上面代码基础上设置驾驶模式，则地图应用会启动驾驶模式计算两点之间的距离同时对路线进行规划。
 */
-(void)mapNavigation
{
    //根据“上海市”地理编码
    [_geocoder geocodeAddressString:@"上海市" completionHandler:^(NSArray *placemarks, NSError *error) {
        CLPlacemark *clPlacemark1=[placemarks firstObject];//获取第一个地标
        MKPlacemark *mkPlacemark1=[[MKPlacemark alloc]initWithPlacemark:clPlacemark1];
        //注意地理编码一次只能定位到一个位置，不能同时定位，所在放到第一个位置定位完成回调函数中再次定位
        [_geocoder geocodeAddressString:@"阜阳市" completionHandler:^(NSArray *placemarks, NSError *error) {
            CLPlacemark *clPlacemark2=[placemarks firstObject];//获取第一个地标
            MKPlacemark *mkPlacemark2=[[MKPlacemark alloc]initWithPlacemark:clPlacemark2];
            NSDictionary *options=@{MKLaunchOptionsMapTypeKey:@(MKMapTypeStandard),MKLaunchOptionsDirectionsModeKey:MKLaunchOptionsDirectionsModeDriving};
            //MKMapItem *mapItem1=[MKMapItem mapItemForCurrentLocation];//当前位置
            MKMapItem *mapItem1=[[MKMapItem alloc]initWithPlacemark:mkPlacemark1];
            MKMapItem *mapItem2=[[MKMapItem alloc]initWithPlacemark:mkPlacemark2];
            [MKMapItem openMapsWithItems:@[mapItem1,mapItem2] launchOptions:options];
        }];
        
    }];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
