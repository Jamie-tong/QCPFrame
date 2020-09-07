#ifndef CCHECKBOXHEADERVIEW
#define CCHECKBOXHEADERVIEW

#endif // CCHECKBOXHEADERVIEW

#include <QtGui>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>
#include "ViewEditer.h"

class CCheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    CCheckBoxHeaderView( int checkColumnIndex,
             Qt::Orientation orientation,
             QWidget * parent = 0) :
    QHeaderView(orientation, parent)
    {
        isOn = false;
        m_checkColIdx = checkColumnIndex;
    }

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        painter->save();
        QHeaderView::paintSection(painter, rect, logicalIndex);
        painter->restore();
        if (logicalIndex == m_checkColIdx)
        {
            QStyleOptionButton option;
            //for (int i=0; i<logicalIndex; ++i)
            //width += sectionSize( i );
            option.rect = QRect(3, 5, 15, 15);
            if (isOn)
                option.state = QStyle::State_On;
            else
                option.state = QStyle::State_Off;
            // this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
            this->style()->drawControl(QStyle::CE_CheckBox, &option, painter);
        }

    }
    void mousePressEvent(QMouseEvent *event)
    {
        if (visualIndexAt(event->pos().x()) == m_checkColIdx)
        {
    //        setSortIndicatorShown( false );
            if (isOn)
            {
                isOn = false;
               ViewEditer::getInstance()->sig_SelAllOrNot(false);///发送信号使槽函数跟新界面的复选框。
            }
            else
            {
                isOn = true;
                ViewEditer::getInstance()->sig_SelAllOrNot(true);
            }

            this->updateSection(m_checkColIdx);

        }
    //    else
    //        setSortIndicatorShown( true );

        QHeaderView::mousePressEvent(event);
    }

private:
    bool isOn;
    int m_checkColIdx;
};
