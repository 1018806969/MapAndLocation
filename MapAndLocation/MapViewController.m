//
//  MapViewController.m
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

#import "MapViewController.h"
#import <MapKit/MapKit.h>
#import <CoreLocation/CoreLocation.h>
#import "TXAnnotation.h"
#import "CustomAnnotation.h"
#import "SystemViewController.h"

@interface MapViewController ()<MKMapViewDelegate>
{
    CLLocationManager *_locationManager;
//    MKMapView         *_mapView;
    __weak IBOutlet MKMapView *_mapView;
}
@end

@implementation MapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    [self testAnnotation];
    [self testCustomAnnotation];
}
-(void)testCustomAnnotation
{
    //设置代理
    _mapView.delegate=self;
    
    //请求定位服务
    _locationManager=[[CLLocationManager alloc]init];
    if(![CLLocationManager locationServicesEnabled]||[CLLocationManager authorizationStatus]!=kCLAuthorizationStatusAuthorizedWhenInUse){
        [_locationManager requestWhenInUseAuthorization];
    }
    
    //用户位置追踪(用户位置追踪用于标记用户当前位置，此时会调用定位服务)
    _mapView.userTrackingMode=MKUserTrackingModeFollow;
    
    //设置地图类型
    _mapView.mapType=MKMapTypeStandard;
    
    //添加大头针
    [self addCustomAnnotation];
}
#pragma mark 添加大头针
-(void)addCustomAnnotation{
    CLLocationCoordinate2D location1=CLLocationCoordinate2DMake(31.268607, 121.491609);
    CustomAnnotation *annotation1=[[CustomAnnotation alloc]init];
    annotation1.title=@"51jk";
    annotation1.subtitle=@"workspace";
    annotation1.coordinate=location1;
    annotation1.image = [UIImage imageNamed:@"annotation"];
    [_mapView addAnnotation:annotation1];
    
    CLLocationCoordinate2D location2=CLLocationCoordinate2DMake(31.258607, 121.491609);
    CustomAnnotation *annotation2=[[CustomAnnotation alloc]init];
    annotation2.title=@"河沙杭城";
    annotation2.subtitle=@"home";
    annotation2.coordinate=location2;
    annotation1.image = [UIImage imageNamed:@"annotation"];
    [_mapView addAnnotation:annotation2];
}
#pragma mark 显示大头针时调用，注意方法中的annotation参数是即将显示的大头针对象
-(MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation{
    //由于当前位置的标注也是一个大头针，所以此时需要判断，此代理方法返回nil使用默认大头针视图
    if ([annotation isKindOfClass:[CustomAnnotation class]]) {
        static NSString *key1=@"AnnotationKey1";
        MKAnnotationView *annotationView=[_mapView dequeueReusableAnnotationViewWithIdentifier:key1];
        //如果缓存池中不存在则新建
        if (!annotationView) {
            annotationView=[[MKAnnotationView alloc]initWithAnnotation:annotation reuseIdentifier:key1];
            annotationView.canShowCallout=true;//允许交互点击
            annotationView.calloutOffset=CGPointMake(0, 1);//定义详情视图偏移量
            annotationView.leftCalloutAccessoryView=[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"1"]];//定义详情左侧视图
        }
        
        //修改大头针视图
        //重新设置此类大头针视图的大头针模型(因为有可能是从缓存池中取出来的，位置是放到缓存池时的位置)
        annotationView.annotation=annotation;
        annotationView.image=((CustomAnnotation *)annotation).image;//设置大头针视图的图片
        
        return annotationView;
    }else {
        return nil;
    }
}
#pragma mark----------------test annotation---------------------------

-(void)testAnnotation
{
    _mapView.delegate = self ;
    
    _locationManager = [[CLLocationManager alloc]init];
    if (![CLLocationManager locationServicesEnabled]) {
        NSLog(@"location services unable,please turn on");
        return ;
    }
    if (!([CLLocationManager authorizationStatus] == kCLAuthorizationStatusAuthorizedWhenInUse)) {
        [_locationManager requestWhenInUseAuthorization];
    }
    //用户位置追踪，用于标记用户当前位置，此时会调用定位服务
    _mapView.userTrackingMode = MKUserTrackingModeFollow;
    _mapView.mapType = MKMapTypeStandard ;
    
    
    [self addAnnotation];
}
//添加大头针
-(void)addAnnotation{
    CLLocationCoordinate2D location1=CLLocationCoordinate2DMake(31.268607, 121.491609);
    TXAnnotation *annotation1=[[TXAnnotation alloc]init];
    annotation1.title=@"51jk";
    annotation1.subtitle=@"workspace";
    annotation1.coordinate=location1;
    [_mapView addAnnotation:annotation1];
    
    CLLocationCoordinate2D location2=CLLocationCoordinate2DMake(31.258607, 121.491609);
    TXAnnotation *annotation2=[[TXAnnotation alloc]init];
    annotation2.title=@"河沙杭城";
    annotation2.subtitle=@"home";
    annotation2.coordinate=location2;
    [_mapView addAnnotation:annotation2];
}
#pragma mark 更新用户位置，只要用户位置改变则调用此方法（包括第一次定位到用户位置）
-(void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation{
    
    NSLog(@"%@",userLocation);
    //设置地图显示范围(如果不进行区域设置会自动显示区域范围并指定当前用户位置为地图中心点)
//    MKCoordinateSpan span= MKCoordinateSpanMake(0.01, 0.01);
//    MKCoordinateRegion region=MKCoordinateRegionMake(userLocation.location.coordinate, span);
//    [_mapView setRegion:region animated:true];
}
- (IBAction)systemMapApplication:(id)sender {
    
    UIWindow *window = [UIApplication sharedApplication].delegate.window;
    window.rootViewController = [[SystemViewController alloc]init];
    
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
