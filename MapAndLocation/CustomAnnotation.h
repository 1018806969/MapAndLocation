//
//  CustomAnnotation.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
//设置大头针视图
//
//在一些应用中系统默认的大头针样式可能无法满足实际的需求，此时就需要修改大头针视图默认样式。根据前面MapKit的代理方法不难发现- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;方法可以返回一个大头针视图，只要实现这个方法并在这个方法中定义一个大头针视图MKAnnotationView对象并设置相关属性就可以改变默认大头针的样式。MKAnnotationView常用属性：
//
//属性	说明
//annotation	大头针模型信息，包括标题、子标题、地理位置。
//image	大头针图片
//canShowCallout	点击大头针是否显示标题、子标题内容等，注意如果在- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;方法中重新定义大头针默认情况是无法交互的需要设置为true。
//calloutOffset	点击大头针时弹出详情信息视图的偏移量
//selected	是否被选中状态
//leftCalloutAccessoryView	弹出详情左侧视图
//rightCalloutAccessoryView	弹出详情右侧视图
//需要注意：
//
//a.这个代理方法的调用时机:每当有大头针显示到系统可视界面中时就会调用此方法返回一个大头针视图放到界面中，同时当前系统位置标注（也就是地图中蓝色的位置点）也是一个大头针，也会调用此方法，因此处理大头针视图时需要区别对待。
//
//b.类似于UITableView的代理方法，此方法调用频繁，开发过程中需要重复利用MapKit的缓存池将大头针视图缓存起来重复利用。
//
//c.自定义大头针默认情况下不允许交互，如果交互需要设置canShowCallout=true
//
//d.如果代理方法返回nil则会使用默认大头针视图，需要根据情况设置。
//
//下面以一个示例进行大头针视图设置，这里设置了大头针的图片、弹出视图、偏移量等信息。

//注意：
//
//在MapKit框架中除了MKAnnotationView之外还有一个MKPinAnnotationView，它是MKAnnotationView的子类，相比MKAnnotationView多了两个属性pinColor和animationDrop，分别用于设置大头针视图颜色和添加大头针动画。

@interface CustomAnnotation : NSObject<MKAnnotation>



@property (nonatomic) CLLocationCoordinate2D coordinate;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subtitle;

#pragma mark 自定义一个图片属性在创建大头针视图时使用
@property (nonatomic,strong) UIImage *image;

@end
