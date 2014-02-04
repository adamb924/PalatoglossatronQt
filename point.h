#ifndef POINT_H
#define POINT_H

class QPoint;
class QString;
class QXmlStreamWriter;

class Point
{
public:
    Point();
    ~Point();
    Point(int x, int y);
    Point(QPoint pt);
    QPoint* pt();
    QPoint* ptTransformed();
    void serialize(QXmlStreamWriter *xmlstream);
    int x();
    int y();
    int Tx();
    int Ty();
    void setPointTransformed(int x, int y);

private:
    QPoint *point;
    QPoint *pointTransformed;
};

#endif // POINT_H
