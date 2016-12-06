//
//  ViewController.m
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

#import "ViewController.h"
#import <CoreLocation/CoreLocation.h>
#import "MapViewController.h"

@interface ViewController ()<CLLocationManagerDelegate>
{
    //定位管理器
    CLLocationManager *_locationManager;
    //地理编码者
    CLGeocoder *_geocoder;
}
@property (weak, nonatomic) IBOutlet UIButton *locationButton;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _locationManager = [[CLLocationManager alloc]init];
    if (![CLLocationManager locationServicesEnabled]) {
        NSLog(@"location service unenable，please turn on");
        return ;
    }
    
    //用户是否授权
    if ([CLLocationManager authorizationStatus] == kCLAuthorizationStatusNotDetermined) {
        [_locationManager requestWhenInUseAuthorization];
    }else if ([CLLocationManager authorizationStatus] == kCLAuthorizationStatusAuthorizedWhenInUse)
    {
        _locationManager.delegate = self ;
        //定位精度:定位频率和定位精度并不应当越精确越好，需要视实际情况而定，因为越精确越耗性能，也就越费电
        _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
        //定位频率，每隔多少米定位一次
        CLLocationDistance distance = 10.0 ;
        _locationManager.distanceFilter = distance ;
        //启动跟踪定位
        [_locationManager startUpdatingLocation];
        
        _geocoder = [[CLGeocoder alloc]init];
    }
    
    
//    [self getCoordinateByAddress:@"中国上海市虹口区欧阳路街道四达路58弄"];
}
/**
 跟踪定位代理，每次位置发生变化就会执行，模拟器测试时需要设置一个虚拟位置，否则在模拟器中无法调用此方法
 定位成功后会根据设置情况频繁调用，
 @param manager 定位管理器
 @param locations 地理位置对象数组，每个元素一个CLLocation代表地理位置信息（包含经度、纬度、海报、行走速度等信息），之所以返回数组是因为有些时候一个位置点可能包含多个位置
 */
-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
    CLLocation *location = [locations firstObject];
    //位置坐标
    CLLocationCoordinate2D coordinate = location.coordinate ;
    NSLog(@"经度：%f,纬度：%f,海拔：%f,航向：%f,行走速度：%f",coordinate.longitude,coordinate.latitude,location.altitude,location.course,location.speed);
    //如果不需要实时定位，使用完即使关闭定位服务
    [_locationManager stopUpdatingLocation];
    
    [self getAddressByLatitude:coordinate.latitude longitude:coordinate.longitude];
}
#pragma mark 根据坐标取得地名
-(void)getAddressByLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude{
    //反地理编码
    CLLocation *location=[[CLLocation alloc]initWithLatitude:latitude longitude:longitude];
    [_geocoder reverseGeocodeLocation:location completionHandler:^(NSArray *placemarks, NSError *error) {
        CLPlacemark *placemark=[placemarks firstObject];
        NSDictionary *info = placemark.addressDictionary ;
        NSString *address = [NSString stringWithFormat:@"%@-%@-%@-%@-%@-%@-%@-%@-%@",info[@"City"],info[@"Country"],info[@"SubThoroughfare"],info[@"FormattedAddressLines"][0],info[@"Name"],info[@"State"],info[@"SubLocality"],info[@"Street"],info[@"Thoroughfare"]];
        NSLog(@"详细信息:%@--%@",placemark.addressDictionary,address);
        [_locationButton setTitle:info[@"FormattedAddressLines"][0] forState:UIControlStateNormal];

    }];
}
#pragma mark 根据地名确定地理坐标
-(void)getCoordinateByAddress:(NSString *)address{
    //地理编码
    [_geocoder geocodeAddressString:address completionHandler:^(NSArray *placemarks, NSError *error) {
        //取得第一个地标，地标中存储了详细的地址信息，注意：一个地名可能搜索出多个地址
        CLPlacemark *placemark=[placemarks firstObject];
        
        CLLocation *location=placemark.location;//位置
        CLRegion *region=placemark.region;//区域
        NSDictionary *addressDic= placemark.addressDictionary;//详细地址信息字典,包含以下部分信息
        //        NSString *name=placemark.name;//地名
        //        NSString *thoroughfare=placemark.thoroughfare;//街道
        //        NSString *subThoroughfare=placemark.subThoroughfare; //街道相关信息，例如门牌等
        //        NSString *locality=placemark.locality; // 城市
        //        NSString *subLocality=placemark.subLocality; // 城市相关信息，例如标志性建筑
        //        NSString *administrativeArea=placemark.administrativeArea; // 州
        //        NSString *subAdministrativeArea=placemark.subAdministrativeArea; //其他行政区域信息
        //        NSString *postalCode=placemark.postalCode; //邮编
        //        NSString *ISOcountryCode=placemark.ISOcountryCode; //国家编码
        //        NSString *country=placemark.country; //国家
        //        NSString *inlandWater=placemark.inlandWater; //水源、湖泊
        //        NSString *ocean=placemark.ocean; // 海洋
        //        NSArray *areasOfInterest=placemark.areasOfInterest; //关联的或利益相关的地标
        NSLog(@"位置:%@,区域:%@,详细信息:%@",location,region,addressDic);
    }];
}
- (IBAction)locationClick:(id)sender {
    UIWindow *window = [UIApplication sharedApplication].delegate.window;
    window.rootViewController = [[MapViewController alloc]init];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
