//
//  MapViewController.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//


//map 介绍三种自定义annotation

#import <UIKit/UIKit.h>

@interface MapViewController : UIViewController

//MapKit

//iOS从6.0开始地图数据不再由谷歌驱动，而是改用自家地图，当然在国内它的数据是由高德地图提供的。这样一来，如果在iOS6.0之前进行地图开发的话使用方法会有所不同，基于目前的情况其实使用iOS6.0之前版本的系统基本已经寥寥无几了，所有在接下来的内容中不会再针对iOS5及之前版本的地图开发进行介绍。
//
//在iOS中进行地图开发主要有两种方式，一种是直接利用MapKit框架进行地图开发，利用这种方式可以对地图进行精准的控制；另一种方式是直接调用苹果官方自带的地图应用，主要用于一些简单的地图应用（例如：进行导航覆盖物填充等），无法进行精确的控制。当然，本节重点内容还是前者，后面的内容也会稍加提示。
//
//用MapKit之前需要简单了解一下MapKit中地图展示控件MKMapView的的一些常用属性和方法，具体如下表：
//属性	说明
//userTrackingMode	跟踪类型，是一个枚举：
//MKUserTrackingModeNone :不进行用户位置跟踪；
//MKUserTrackingModeFollow :跟踪用户位置；
//MKUserTrackingModeFollowWithHeading :跟踪用户位置并且跟踪用户前进方向；
//mapType	地图类型，是一个枚举：
//MKMapTypeStandard :标准地图，一般情况下使用此地图即可满足；
//MKMapTypeSatellite ：卫星地图；
//MKMapTypeHybrid ：混合地图，加载最慢比较消耗资源；
//userLocation	用户位置，只读属性
//annotations	当前地图中的所有大头针，只读属性
//对象方法	说明
//- (void)addAnnotation:(id <MKAnnotation>)annotation;	添加大头针，对应的有添加大头针数组
//- (void)removeAnnotation:(id <MKAnnotation>)annotation;	删除大头针，对应的有删除大头针数组
//- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;
//
//设置地图显示区域，用于控制当前屏幕显示地图范围
//- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;	设置地图中心点位置
//- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;	将地理坐标（经纬度）转化为数学坐标（UIKit坐标）
//- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;	将数学坐标转换为地理坐标
//- (MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;	从缓存池中取出大头针，类似于UITableView中取出UITableViewCell，为了进行性能优化而设计
//- (void)selectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;	选中指定的大头针
//- (void)deselectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;	取消选中指定的大头针
//代理方法	说明
//- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation ;	用户位置发生改变时触发（第一次定位到用户位置也会触发该方法）
//- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation ;	显示区域发生改变后触发
//- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;	地图加载完成后触发
//- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;	显示大头针时触发，返回大头针视图，通常自定义大头针可以通过此方法进行
//- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view	点击选中某个大头针时触发
//- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view	取消选中大头针时触发
//- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id <MKOverlay>)overlay	渲染地图覆盖物时触发
//用户位置跟踪
//
//在很多带有地图的应用中默认打开地图都会显示用户当前位置，同时将当前位置标记出来放到屏幕中点方便用户对周围情况进行查看。如果在iOS6或者iOS7中实现这个功能只需要添加地图控件、设置用户跟踪模式、在-(void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation代理方法中设置地图中心区域及显示范围。但是在iOS8中用法稍有不同：
//
//1.由于在地图中进行用户位置跟踪需要使用定位功能，而定位功能在iOS8中设计发生了变化，因此必须按照前面定位章节中提到的内容进行配置和请求。
//
//2.iOS8中不需要进行中心点的指定，默认会将当前位置设置中心点并自动设置显示区域范围。
//
//了解以上两点，要进行用户位置跟踪其实就相当简单了，值得一提的是-(void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation这个代理方法。这个方法只有在定位（利用前面章节中的定位内容）到当前位置之后就会调用，以后每当用户位置发生改变就会触发，调用频率相当频繁。
//
//大头针
//
//在iOS开发中经常会标记某个位置，需要使用地图标注，也就是大家俗称的“大头针”。只要一个NSObject类实现MKAnnotation协议就可以作为一个大头针，通常会重写协议中coordinate（标记位置）、title（标题）、subtitle（子标题）三个属性，然后在程序中创建大头针对象并调用addAnnotation:方法添加大头针即可（之所以iOS没有定义一个基类实现这个协议供开发者使用，多数原因应该是MKAnnotation是一个模型对象，对于多数应用模型会稍有不同，例如后面的内容中会给大头针模型对象添加其他属性）。

@end
