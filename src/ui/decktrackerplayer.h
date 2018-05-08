#ifndef DECKTRACKERPLAYER_H
#define DECKTRACKERPLAYER_H

#include "decktrackerbase.h"
#include "../entity/card.h"
#include "../entity/deck.h"

#include <QWidget>

class DeckTrackerPlayer : public DeckTrackerBase
{
    Q_OBJECT
private:
    bool isStatisticsEnabled;
    QPen bgPen, statisticsPen;
    QFont statisticsFont;
    void drawStatistics(QPainter &painter);

protected:
    void onPositionChanged();
    void onScaleChanged();
    void afterPaintEvent(QPainter &painter);

public:
    explicit DeckTrackerPlayer(QWidget *parent = nullptr);
    ~DeckTrackerPlayer();

signals:

public slots:
    void onPlayerDeckSelected(Deck deck);
    void onPlayerDrawCard(Card* card);
    void onStatisticsEnabled(bool enabled);
};

#endif // DECKTRACKERPLAYER_H