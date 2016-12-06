//
//  ViewController.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

//定位和编码

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

//Core Location framework

//要实现地图、导航功能，往往需要先熟悉定位功能，在iOS中通过Core Location框架进行定位操作。Core Location自身可以单独使用，和地图开发框架MapKit完全是独立的，但是往往地图开发要配合定位框架使用。在Core Location中主要包含了定位、地理编码（包括反编码）功能。

//定位是一个很常用的功能，如一些地图软件打开之后如果用户允许软件定位的话，那么打开软件后就会自动锁定到当前位置，如果用户手机移动那么当前位置也会跟随着变化。要实现这个功能需要使用Core Loaction中CLLocationManager类，首先看一下这个类的一些主要方法和属性：

//类方法	说明
//+ (BOOL)locationServicesEnabled;	是否启用定位服务，通常如果用户没有启用定位服务可以提示用户打开定位服务
//+ (CLAuthorizationStatus)authorizationStatus;	定位服务授权状态，返回枚举类型：
//kCLAuthorizationStatusNotDetermined： 用户尚未做出决定是否启用定位服务
//kCLAuthorizationStatusRestricted： 没有获得用户授权使用定位服务,可能用户没有自己禁止访问授权
//kCLAuthorizationStatusDenied ：用户已经明确禁止应用使用定位服务或者当前系统定位服务处于关闭状态
//kCLAuthorizationStatusAuthorizedAlways： 应用获得授权可以一直使用定位服务，即使应用不在使用状态
//kCLAuthorizationStatusAuthorizedWhenInUse： 使用此应用过程中允许访问定位服务
//属性	说明
//desiredAccuracy	定位精度，枚举类型：
//kCLLocationAccuracyBest：最精确定位
//CLLocationAccuracy kCLLocationAccuracyNearestTenMeters：十米误差范围
//kCLLocationAccuracyHundredMeters:百米误差范围
//kCLLocationAccuracyKilometer:千米误差范围
//kCLLocationAccuracyThreeKilometers:三千米误差范围
//
//distanceFilter	位置信息更新最小距离，只有移动大于这个距离才更新位置信息，默认为kCLDistanceFilterNone：不进行距离限制
//对象方法	说明
//startUpdatingLocation	开始定位追踪，开始定位后将按照用户设置的更新频率执行-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations;方法反馈定位信息
//stopUpdatingLocation	停止定位追踪
//startUpdatingHeading	开始导航方向追踪
//stopUpdatingHeading	停止导航方向追踪
//startMonitoringForRegion:	开始对某个区域进行定位追踪，开始对某个区域进行定位后。如果用户进入或者走出某个区域会调用- (void)locationManager:(CLLocationManager *)manager
//          didEnterRegion:(CLRegion *)region和- (void)locationManager:(CLLocationManager *)manager
//           didExitRegion:(CLRegion *)region代理方法反馈相关信息
//stopMonitoringForRegion:	停止对某个区域进行定位追踪
//requestWhenInUseAuthorization	请求获得应用使用时的定位服务授权，注意使用此方法前在要在info.plist中配置NSLocationWhenInUseUsageDescription
//requestAlwaysAuthorization	请求获得应用一直使用定位服务授权，注意使用此方法前要在info.plist中配置NSLocationAlwaysUsageDescription
//代理方法	说明
//-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations;	位置发生改变后执行（第一次定位到某个位置之后也会执行）
//- (void)locationManager:(CLLocationManager *)manager
//       didUpdateHeading:(CLHeading *)newHeading;	导航方向发生变化后执行
//- (void)locationManager:(CLLocationManager *)manager
//         didEnterRegion:(CLRegion *)region	进入某个区域之后执行
//- (void)locationManager:(CLLocationManager *)manager
//          didExitRegion:(CLRegion *)region	走出某个区域之后执行

//iOS 8 还提供了更加人性化的定位服务选项。App 的定位服务不再仅仅是关闭或打开，现在，定位服务的启用提供了三个选项，「永不」「使用应用程序期间」和「始终」。同时，考虑到能耗问题，如果一款 App 要求始终能在后台开启定位服务，iOS 8 不仅会在首次打开 App 时主动向你询问，还会在日常使用中弹窗提醒你该 App 一直在后台使用定位服务，并询问你是否继续允许。在iOS7及以前的版本，如果在应用程序中使用定位服务只要在程序中调用startUpdatingLocation方法应用就会询问用户是否允许此应用是否允许使用定位服务，同时在提示过程中可以通过在info.plist中配置通过配置Privacy - Location Usage Description告诉用户使用的目的，同时这个配置是可选的。
//但是在iOS8中配置配置项发生了变化，可以通过配置NSLocationAlwaysUsageDescription或者NSLocationWhenInUseUsageDescription来告诉用户使用定位服务的目的，并且注意这个配置是必须的，如果不进行配置则默认情况下应用无法使用定位服务，打开应用不会给出打开定位服务的提示，除非安装后自己设置此应用的定位服务。同时，在应用程序中需要根据配置对requestAlwaysAuthorization或locationServicesEnabled方法进行请求。由于本人机器已经更新到最新的iOS8.1下面的内容主要针对iOS8，使用iOS7的朋友需要稍作调整。
//除了提供定位功能，CLLocationManager还可以调用startMonitoringForRegion:方法对指定区域进行监控。


//除了提供位置跟踪功能之外，在定位服务中还包含CLGeocoder类用于处理地理编码和逆地理编码（又叫反地理编码）功能。
//
//地理编码：根据给定的位置（通常是地名）确定地理坐标(经、纬度)。
//
//逆地理编码：可以根据地理坐标（经、纬度）确定位置信息（街道、门牌等）。
//
//CLGeocoder最主要的两个方法就是- (void)geocodeAddressString:(NSString *)addressString completionHandler:(CLGeocodeCompletionHandler)completionHandler;和- (void)reverseGeocodeLocation:(CLLocation *)location completionHandler:(CLGeocodeCompletionHandler)completionHandler;，分别用于地理编码和逆地理编码。下面简单演示一下：

@end

