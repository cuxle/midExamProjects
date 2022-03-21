#ifndef MAT2QTFORMATMETHOD_H
#define MAT2QTFORMATMETHOD_H
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
// 这是第二种将CV::mat转化为Qimage的函数方法
// 这种方法能够直接识别读入的mat的类型，并且进行相应的转换为Qimage和Qpixmap
// 使用这种方法不需要额外调用cvtColor函数来进行BGR转换为RGB

namespace CV2QTFORMAT {
   QImage  cvMatToQImage( const cv::Mat &inMat );//cvMat转换为QImage
   QPixmap cvMatToQPixmap( const cv::Mat &inMat );//cvMat转换为Qpixmap
}

#endif // MAT2QTFORMATMETHOD_H

