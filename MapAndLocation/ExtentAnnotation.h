//
//  ExtentAnnotation.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ExtentAnnotation : NSObject
/*
 通过上面的示例不难看出MKAnnotationView足够强大（何况还有MKPinAnnotationView），很多信息都可以进行设置，但是唯独不能修改大头针描述详情视图（仅仅支持详情中左右视图内容）。要实现这个需求目前开发中普遍采用的思路就是:
 
 a.点击一个大头针A时重新在A的坐标处添加另一个大头针B（注意此时将A对应的大头针视图canShowCallout设置为false）作为大头针详情模型，然后在- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;代理方法中判断大头针类型，如果是B则重写MKAnnotationView（可以自定义一个类C继承于MKAnnotationView），返回自定义大头针视图C。
 
 b.定义大头针视图C继承于MKAnnotationView（或者MKPinAnnotationView）,在自定义大头针视图中添加自己的控件，完成自定义布局。
 
 在使用百度地图客户端时当点击一个搜索位置时可以看到此位置的评价等信息，视图效果大概如下：
 
 Baidu_CalloutView
 
 下面不妨试着实现一下这个效果：
 
 大头针模型：KCAnnotation.h
 
 //
 //  KCAnnotation.h
 //  MapKit
 //
 //  Created by Kenshin Cui on 14/3/27.
 //  Copyright (c) 2014年 Kenshin Cui. All rights reserved.
 //
 
 #import <Foundation/Foundation.h>
 #import <MapKit/MapKit.h>
 
 @interface KCAnnotation : NSObject<MKAnnotation>
 
 @property (nonatomic) CLLocationCoordinate2D coordinate;
 @property (nonatomic, copy) NSString *title;
 @property (nonatomic, copy) NSString *subtitle;
 
 #pragma mark 自定义一个图片属性在创建大头针视图时使用
 @property (nonatomic,strong) UIImage *image;
 
 #pragma mark 大头针详情左侧图标
 @property (nonatomic,strong) UIImage *icon;
 #pragma mark 大头针详情描述
 @property (nonatomic,copy) NSString *detail;
 #pragma mark 大头针右下方星级评价
 @property (nonatomic,strong) UIImage *rate;
 
 @end
 弹出详情大头针模型：KCCalloutAnnotation.h
 
 //
 //  KCCalloutAnnotation.h
 //  MapKit
 //
 //  Created by Kenshin Cui on 14/3/27.
 //  Copyright (c) 2014年 Kenshin Cui. All rights reserved.
 //
 
 #import <UIKit/UIKit.h>
 #import <CoreLocation/CoreLocation.h>
 #import <MapKit/MapKit.h>
 
 @interface KCCalloutAnnotation : NSObject<MKAnnotation>
 
 @property (nonatomic) CLLocationCoordinate2D coordinate;
 @property (nonatomic, copy,readonly) NSString *title;
 @property (nonatomic, copy,readonly) NSString *subtitle;
 
 #pragma mark 左侧图标
 @property (nonatomic,strong) UIImage *icon;
 #pragma mark 详情描述
 @property (nonatomic,copy) NSString *detail;
 #pragma mark 星级评价
 @property (nonatomic,strong) UIImage *rate;
 
 @end
 弹出详情大头针视图：KCCalloutAnnotatonView.h
 
 //
 //  KCCalloutView.h
 //  MapKit
 //
 //  Created by Kenshin Cui on 14/3/27.
 //  Copyright (c) 2014年 Kenshin Cui. All rights reserved.
 //  自定义弹出标注视图
 
 #import <UIKit/UIKit.h>
 #import <CoreLocation/CoreLocation.h>
 #import <MapKit/MapKit.h>
 #import "KCCalloutAnnotation.h"
 
 @interface KCCalloutAnnotationView : MKAnnotationView
 
 @property (nonatomic ,strong) KCCalloutAnnotation *annotation;
 
 #pragma mark 从缓存取出标注视图
 +(instancetype)calloutViewWithMapView:(MKMapView *)mapView;
 
 @end
 KCCalloutAnnotationView.m
 
 //
 //  KCCalloutView.m
 //  MapKit
 //
 //  Created by Kenshin Cui on 14/3/27.
 //  Copyright (c) 2014年 Kenshin Cui. All rights reserved.
 //
 
 #import "KCCalloutAnnotationView.h"
 #define kSpacing 5
 #define kDetailFontSize 12
 #define kViewOffset 80
 
 @interface KCCalloutAnnotationView(){
 UIView *_backgroundView;
 UIImageView *_iconView;
 UILabel *_detailLabel;
 UIImageView *_rateView;
 }
 
 @end
 
 @implementation KCCalloutAnnotationView
 
 -(instancetype)init{
 if(self=[super init]){
 [self layoutUI];
 }
 return self;
 }
 -(instancetype)initWithFrame:(CGRect)frame{
 if (self=[super initWithFrame:frame]) {
 [self layoutUI];
 }
 return self;
 }
 
 -(void)layoutUI{
 //背景
 _backgroundView=[[UIView alloc]init];
 _backgroundView.backgroundColor=[UIColor whiteColor];
 //左侧添加图标
 _iconView=[[UIImageView alloc]init];
 
 //上方详情
 _detailLabel=[[UILabel alloc]init];
 _detailLabel.lineBreakMode=NSLineBreakByWordWrapping;
 //[_text sizeToFit];
 _detailLabel.font=[UIFont systemFontOfSize:kDetailFontSize];
 
 //下方星级
 _rateView=[[UIImageView alloc]init];
 
 [self addSubview:_backgroundView];
 [self addSubview:_iconView];
 [self addSubview:_detailLabel];
 [self addSubview:_rateView];
 }
 
 +(instancetype)calloutViewWithMapView:(MKMapView *)mapView{
 static NSString *calloutKey=@"calloutKey1";
 KCCalloutAnnotationView *calloutView=(KCCalloutAnnotationView *)[mapView dequeueReusableAnnotationViewWithIdentifier:calloutKey];
 if (!calloutView) {
 calloutView=[[KCCalloutAnnotationView alloc]init];
 }
 return calloutView;
 }
 
 #pragma mark 当给大头针视图设置大头针模型时可以在此处根据模型设置视图内容
 -(void)setAnnotation:(KCCalloutAnnotation *)annotation{
 [super setAnnotation:annotation];
 //根据模型调整布局
 _iconView.image=annotation.icon;
 _iconView.frame=CGRectMake(kSpacing, kSpacing, annotation.icon.size.width, annotation.icon.size.height);
 
 _detailLabel.text=annotation.detail;
 float detailWidth=150.0;
 CGSize detailSize= [annotation.detail boundingRectWithSize:CGSizeMake(detailWidth, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName: [UIFont systemFontOfSize:kDetailFontSize]} context:nil].size;
 float detailX=CGRectGetMaxX(_iconView.frame)+kSpacing;
 _detailLabel.frame=CGRectMake(detailX, kSpacing, detailSize.width, detailSize.height);
 _rateView.image=annotation.rate;
 _rateView.frame=CGRectMake(detailX, CGRectGetMaxY(_detailLabel.frame)+kSpacing, annotation.rate.size.width, annotation.rate.size.height);
 
 float backgroundWidth=CGRectGetMaxX(_detailLabel.frame)+kSpacing;
 float backgroundHeight=_iconView.frame.size.height+2*kSpacing;
 _backgroundView.frame=CGRectMake(0, 0, backgroundWidth, backgroundHeight);
 self.bounds=CGRectMake(0, 0, backgroundWidth, backgroundHeight+kViewOffset);
 
 }
 @end
 主视图控制器：KCMainViewController.m
 
 //
 //  KCMainViewController.m
 //  MapKit Annotation
 //
 //  Created by Kenshin Cui on 14/3/27.
 //  Copyright (c) 2014年 Kenshin Cui. All rights reserved.
 //  37.785834   -122.406417
 //  39.92 116.39
 
 #import "KCMainViewController.h"
 #import <CoreLocation/CoreLocation.h>
 #import <MapKit/MapKit.h>
 #import "KCAnnotation.h"
 #import "KCCalloutAnnotationView.h"
 #import "KCCalloutAnnotationView.h"
 
 @interface KCMainViewController ()<MKMapViewDelegate>{
 CLLocationManager *_locationManager;
 MKMapView *_mapView;
 }
 
 @end
 
 @implementation KCMainViewController
 
 - (void)viewDidLoad {
 [super viewDidLoad];
 
 [self initGUI];
 }
 
 #pragma mark 添加地图控件
 -(void)initGUI{
 CGRect rect=[UIScreen mainScreen].bounds;
 _mapView=[[MKMapView alloc]initWithFrame:rect];
 [self.view addSubview:_mapView];
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
 [self addAnnotation];
 }
 
 #pragma mark 添加大头针
 -(void)addAnnotation{
 CLLocationCoordinate2D location1=CLLocationCoordinate2DMake(39.95, 116.35);
 KCAnnotation *annotation1=[[KCAnnotation alloc]init];
 annotation1.title=@"CMJ Studio";
 annotation1.subtitle=@"Kenshin Cui's Studios";
 annotation1.coordinate=location1;
 annotation1.image=[UIImage imageNamed:@"icon_pin_floating.png"];
 annotation1.icon=[UIImage imageNamed:@"icon_mark1.png"];
 annotation1.detail=@"CMJ Studio...";
 annotation1.rate=[UIImage imageNamed:@"icon_Movie_Star_rating.png"];
 [_mapView addAnnotation:annotation1];
 
 CLLocationCoordinate2D location2=CLLocationCoordinate2DMake(39.87, 116.35);
 KCAnnotation *annotation2=[[KCAnnotation alloc]init];
 annotation2.title=@"Kenshin&Kaoru";
 annotation2.subtitle=@"Kenshin Cui's Home";
 annotation2.coordinate=location2;
 annotation2.image=[UIImage imageNamed:@"icon_paopao_waterdrop_streetscape.png"];
 annotation2.icon=[UIImage imageNamed:@"icon_mark2.png"];
 annotation2.detail=@"Kenshin Cui...";
 annotation2.rate=[UIImage imageNamed:@"icon_Movie_Star_rating.png"];
 [_mapView addAnnotation:annotation2];
 }
 
 #pragma mark - 地图控件代理方法
 #pragma mark 显示大头针时调用，注意方法中的annotation参数是即将显示的大头针对象
 -(MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation{
 //由于当前位置的标注也是一个大头针，所以此时需要判断，此代理方法返回nil使用默认大头针视图
 if ([annotation isKindOfClass:[KCAnnotation class]]) {
 static NSString *key1=@"AnnotationKey1";
 MKAnnotationView *annotationView=[_mapView dequeueReusableAnnotationViewWithIdentifier:key1];
 //如果缓存池中不存在则新建
 if (!annotationView) {
 annotationView=[[MKAnnotationView alloc]initWithAnnotation:annotation reuseIdentifier:key1];
 //            annotationView.canShowCallout=true;//允许交互点击
 annotationView.calloutOffset=CGPointMake(0, 1);//定义详情视图偏移量
 annotationView.leftCalloutAccessoryView=[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"icon_classify_cafe.png"]];//定义详情左侧视图
 }
 
 //修改大头针视图
 //重新设置此类大头针视图的大头针模型(因为有可能是从缓存池中取出来的，位置是放到缓存池时的位置)
 annotationView.annotation=annotation;
 annotationView.image=((KCAnnotation *)annotation).image;//设置大头针视图的图片
 
 return annotationView;
 }else if([annotation isKindOfClass:[KCCalloutAnnotation class]]){
 //对于作为弹出详情视图的自定义大头针视图无弹出交互功能（canShowCallout=false，这是默认值），在其中可以自由添加其他视图（因为它本身继承于UIView）
 KCCalloutAnnotationView *calloutView=[KCCalloutAnnotationView calloutViewWithMapView:mapView];
 calloutView.annotation=annotation;
 return calloutView;
 } else {
 return nil;
 }
 }
 
 #pragma mark 选中大头针时触发
 //点击一般的大头针KCAnnotation时添加一个大头针作为所点大头针的弹出详情视图
 -(void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view{
 KCAnnotation *annotation=view.annotation;
 if ([view.annotation isKindOfClass:[KCAnnotation class]]) {
 //点击一个大头针时移除其他弹出详情视图
 //        [self removeCustomAnnotation];
 //添加详情大头针，渲染此大头针视图时将此模型对象赋值给自定义大头针视图完成自动布局
 KCCalloutAnnotation *annotation1=[[KCCalloutAnnotation alloc]init];
 annotation1.icon=annotation.icon;
 annotation1.detail=annotation.detail;
 annotation1.rate=annotation.rate;
 annotation1.coordinate=view.annotation.coordinate;
 [mapView addAnnotation:annotation1];
 }
 }
 
 #pragma mark 取消选中时触发
 -(void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view{
 [self removeCustomAnnotation];
 }
 
 #pragma mark 移除所用自定义大头针
 -(void)removeCustomAnnotation{
 [_mapView.annotations enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
 if ([obj isKindOfClass:[KCCalloutAnnotation class]]) {
 [_mapView removeAnnotation:obj];
 }
 }];
 }
 @end
 在这个过程中需要注意几点：
 
 1.大头针A作为一个普通大头针，其中最好保存自定义大头针视图C所需要的模型以便根据不同的模型初始化视图。
 
 2.自定义大头针视图C的大头针模型B中不需要title、subtitle属性，最好设置为只读；模型中最后保存自定义大头针视图C所需要的布局模型数据。
 
 3.只有点击非B类大头针时才新增自定义大头针，并且增加时要首先移除其他B类大头针避免重叠（一般建议放到取消大头针选择的代理方法中）。
 
 4.通常在自定义大头针视图C设置大头针模型时布局界面，此时需要注意新增大头针的位置，通常需要偏移一定的距离才能达到理想的效果。
 
 
 
 
 */
@end
