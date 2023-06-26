
#include <QCoreApplication>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
class Widget: public QWidget
{
public:
    Widget(QWidget*parent = nullptr)
        :QWidget(parent)
    {
        this->resize(500,600);
        QPushButton*btn1 = new QPushButton("两点距离",this);
        btn1->setGeometry(100,60,100,100);
        connect(btn1,&QPushButton::clicked,this,[=](){
            QPoint p (3,7);
            QPoint q (-1,4);
            int lengthSquared = QPoint::dotProduct(p,q);
            qDebug()<<"lengthSquared:"<<lengthSquared;
        });
        QPushButton* btn2 = new QPushButton("设置坐标",this);
        connect(btn2,&QPushButton::clicked,this,&Widget::testSetPoint);
        testOperator();
        testQsize();
    };
    void testSetPoint()
    {
        QPoint p;
        p.setX(p.x()+1);
        p.setY(p.y()+5);
        qDebug()<<"p.x =%d,p.y=%d"<<p.x()<<p.y();
    }
    void testOperator()
    {
        QPoint p(3,7);
        QPoint q(-1,4);
        p+=q;
        qDebug()<<"p+q:"<<p;
        p-=q;
        qDebug()<<"p-q:"<<p;
        QPoint R(-3,10);
        R/= 2.5;
        qDebug()<<"R/2.5:"<<R;
        R *= 2.5;
        qDebug()<<"R*2.5:"<<R;
    }

    void testQsize()
    {
        QSize sz;
        if(sz.isEmpty())
            qDebug()<<"sz isEmpty:"<< sz.width()<<sz.height();
        QSize sz2(50,30);  //矩形尺寸
        if(sz2.isValid())
            qDebug()<< "sz width:"<<sz2.width()<<"sz height:"<< sz2.height();
        QSize sz3(0,0);
        if(sz3.isNull())
            qDebug()<<"sz3 null:"<<sz3.width()<<sz3.height();

        QSize sz4(50,60);
        qDebug("width = %d,height =%d",sz4.width(),sz4.height());
        sz4.setWidth(100);
        sz4.setHeight(200);
        qDebug("width = %d,height =%d",sz4.width(),sz4.height());
    }

    void testScale()
    {
        QSize t1(10,12);
        t1.scale(60,60,Qt::IgnoreAspectRatio);
        // t1.scale(QSize(20,20),Qt::IgnoreAspectRatio);
        QSize t2(10,12);
        t2.scale(60,60,Qt::KeepAspectRatio);
        QSize t3(10,12);
        t2.scale(60,60,Qt::KeepAspectRatioByExpanding);
    }

    void paintWay1()
    {
        QPainter painter(this);//指定了this,begin()和end()函数
        painter.drawLine(30,230,350,230);  //画线的函数
        painter.setPen(Qt::red);           //设置画笔的颜色为红色
        painter.drawRect(10,10,100,100);   //画矩形的函数
        painter.setPen(QPen(Qt::green,5)); //设置画笔颜色为绿色，宽度为5
        painter.setBrush(Qt::blue);        //设置画笔的颜色为蓝色
        painter.drawEllipse(130,10,250,200);//画椭圆的函数
    }
    void paintWay2()
    {
        QPainter painter;
        painter.begin(this);
        painter.drawLine(30,230,350,230);
        painter.end();
    }

    ~Widget()
    {
    }
    //重写的父类的虚函数，自动调用（当窗口需要重绘制时候）
protected:
    void paintEvent(QPaintEvent*event)override
    {
        paintWay1();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

