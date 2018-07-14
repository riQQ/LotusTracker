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
    QRect preferencesButton;
    void drawStatistics(QPainter &painter);

protected:
    void onPositionChanged();
    void onScaleChanged();
    void afterPaintEvent(QPainter &painter);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit DeckTrackerPlayer(QWidget *parent = nullptr);
    ~DeckTrackerPlayer();
    void applyCurrentSettings();
    void loadDeck(Deck deck);

signals:

public slots:
    void onPlayerPutInLibraryCard(Card* card);
    void onPlayerDrawCard(Card* card);
    void onPlayerDiscardCard(Card* card);
    void onPlayerDiscardFromLibraryCard(Card* card);
    void onPlayerPutOnBattlefieldCard(Card* card);
    void onShowOnlyRemainingCardsEnabled(bool enabled);
    void onStatisticsEnabled(bool enabled);
};

#endif // DECKTRACKERPLAYER_H
