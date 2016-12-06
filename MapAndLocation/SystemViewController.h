//
//  SystemViewController.h
//  MapAndLocation
//
//  Created by txx on 16/12/6.
//  Copyright © 2016年 txx. All rights reserved.
//

//使用自带的地图应用

#import <UIKit/UIKit.h>

@interface SystemViewController : UIViewController

//除了可以使用MapKit框架进行地图开发，对地图有精确的控制和自定义之外，如果对于应用没有特殊要求的话选用苹果自带的地图应用也是一个不错的选择。使用苹果自带的应用时需要用到MapKit中的MKMapItem类，这个类有一个openInMapsWithLaunchOptions:动态方法和一个openMapsWithItems: launchOptions:静态方法用于打开苹果地图应用。第一个方法用于在地图上标注一个位置，第二个方法除了可以标注多个位置外还可以进行多个位置之间的驾驶导航，使用起来也是相当方便。在熟悉这两个方法使用之前有必要对两个方法中的options参数做一下简单说明：
//
//键(常量)	说明	值
//MKLaunchOptionsDirectionsModeKey	路线模式，常量
//MKLaunchOptionsDirectionsModeDriving  驾车模式
//MKLaunchOptionsDirectionsModeWalking 步行模式
//MKLaunchOptionsMapTypeKey	地图类型，枚举
//MKMapTypeStandard ：标准模式
//MKMapTypeSatellite ：卫星模式
//MKMapTypeHybrid  ：混合模式
//MKLaunchOptionsMapCenterKey	中心点坐标，CLLocationCoordinate2D类型
//MKLaunchOptionsMapSpanKey	地图显示跨度，MKCoordinateSpan 类型
//MKLaunchOptionsShowsTrafficKey	是否 显示交通状况，布尔型
//MKLaunchOptionsCameraKey	3D地图效果，MKMapCamera类型
//注意：此属性从iOS7及以后可用，前面的属性从iOS6开始可用



//注意：其实如果不用苹果自带的地图应用也可以实现地图导航，MapKit中提供了MKDirectionRequest对象用于计算路线，提供了MKDirections用于计算方向，这样一来只需要调用MKMapView的addOverlay等方法添加覆盖物即可实现类似的效果，有兴趣的朋友可以试一下。
//
//由于定位和地图框架中用到了诸多类，有些初学者容易混淆，下面简单对比一下。
//
//CLLocation：用于表示位置信息，包含地理坐标、海拔等信息，包含在CoreLoaction框架中。
//
//MKUserLocation：一个特殊的大头针，表示用户当前位置。
//
//CLPlacemark：定位框架中地标类，封装了详细的地理信息。
//
//MKPlacemark：类似于CLPlacemark，只是它在MapKit框架中，可以根据CLPlacemark创建MKPlacemark。
@end
